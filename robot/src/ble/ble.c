/* Implementation file for Bluetooth Low Energy code */

/* ------------------------ SYSTEM INCLUDES --------------------------------- */
#include <avr/io.h>
#include <avr/interrupt.h>

/* ------------------------ APPLICATION INCLUDES ---------------------------- */
#include "spi/spi.h"
#include "sdep/sdep.h"
#include "ble/ble.h"
#include "common/utils.h"

/* ------------------------ EXTERNS ----------------------------------------- */

/*!
 * External definition of semaphore for synchronizing access to sdep buffers
 */
extern semaphore_t sdepBufferSemaphore;

/*!
 * External definition of sdepRespBuffer
 */
extern SDEP_MSG_BUFFER sdepRespBuffer;

/* ------------------------ GLOBAL VARIABLES -------------------------------- */

/*!
 * Declaration of RobotDriveService and its characteristics
 */
BLE_GATT_SERVICE RobotDriveService;
BLE_GATT_CHAR    RobotDriveCharSpeed;
BLE_GATT_CHAR    RobotDriveCharDirection;

/* ------------------------ STATIC FUNCTIONS -------------------------------- */

/*!
 * Registers module's external interrupts with MCU
 */
static void
_bleIRQRegister(void)
{
    // Set BLE_IRQ pin to input
    SET_PORT_BIT_INPUT(DDRD, BLE_IRQ);

    // Clear interrupt flags for BLE_IRQs before setting sense control bits
    CLEAR_BIT(EIMSK, BLE_IRQ);

    // Set sense control bits to trigger interrupts on rising edge trigger
    SET_BIT(EICRA, ISC20);
    SET_BIT(EICRA, ISC21);

    // Clear interrupt flag bits (by writing 1) before enable interrupts
    SET_BIT(EIFR, BLE_IRQ);

    // Enables external interrupt on BLE_IRQ pin
    SET_BIT(EIMSK, BLE_IRQ);
}

/*!
 * Synchronously sends AT-commands to the BLE module
 *
 * @param[in]     atCommand   string representing an AT command to send to BLE
 * @param[in]     payload     string representing the payload of the AT command
 * @param[in]     cmdMode     specifies whether command is read, write, exec...
 * @param[in/out] reply       string representing the reply from BLE module
 */
static void
_bleCmdSend
(
    const char    *atCommand,
    const char    *payload,
    SDEP_CMD_MODE  cmdMode,
    char          *reply
)
{
    SDEP_MSG  msg;
    char     *p;
    char      fullPayload[SDEP_MAX_FULL_MSG_LEN];
    uint8_t   len = 0;

    msg.hdr.msgtype     = SDEP_MSGTYPE_CMD;
    msg.hdr.msgid.cmdid = SDEP_CMDTYPE_AT_WRAPPER;

    p = atCommand;
    while (p != NULL && *p != '\0')
    {
        fullPayload[len] = *p;
        ++p;
        ++len;
    }

    switch (cmdMode)
    {
        case TEST:
            fullPayload[len++] = '=';
            fullPayload[len++] = '?';
            break;
        case WRITE:
            fullPayload[len++] = '=';
            break;
        case READ:
            fullPayload[len++] = '?';
        case EXEC:
            break;
    }

    p = payload;
    while (len < SDEP_MAX_FULL_MSG_LEN && p != NULL && *p != '\0')
    {
        fullPayload[len] = *p;
        ++p;
        ++len;
    }
    fullPayload[len] = '\0';

    // Send SDEP_MSGs corresponding to BLE command
    p = &fullPayload[0];
    while (len > 0)
    {
        // Write payload
        uint8_t payloadLen = 0;
        uint8_t i;
        for (i = 0; p != NULL && *p != '\0' && i < SDEP_MAX_PAYLOAD_LEN; ++i)
        {
            msg.payload[i] = (uint8_t)(*p);
            ++p;
            ++payloadLen;
        }

        // Send message
        msg.hdr.payloadLen = (len > 16) ? ((1 << 7) | payloadLen) : payloadLen;
        sdepMsgSend(&msg);

        len -= payloadLen;
    }

    // Wait until buffer is available
    while (!sdepBufferSemaphore);

    // "Lock" the buffer to read the reply
    cli();

    if (reply != NULL)
    {
        // Iterate through the number of message in reply
        uint8_t k = 0;
        uint8_t i;
        for (i = 0; i < sdepRespBuffer.numMsgs; ++i)
        {
            // Iterate through payload of current message
            uint8_t len = sdepRespBuffer.buffer[i].hdr.payloadLen & ~(1 << 7);
            uint8_t j;
            for (j = 0; j < len; ++j)
            {
                reply[k++] = sdepRespBuffer.buffer[i].payload[j]; 
            }
        }   
    }

    // Clear the semaphore
    sdepBufferSemaphore = 0;

    // "Unlock" the buffer
    sei();
}

/*!
 * Reads a BLE GATT characteristic
 *
 * @param[in/out] pChar     Pointer to BLE GATT characteristic to read
 * @param[in/out] value     Value of retrieved characteristic
 */
static void
_bleGattCharacteristicRead
(
    BLE_GATT_CHAR  *pChar,
    ble_char_value  value
)
{
    // Send command to BLE module
    char *idx = &pChar->index[0];
    _bleCmdSend(atGattChar, idx, WRITE, &value[0]);

    // Copy value to BLE object
    char *dst = &pChar->value[0];
    char *src = &value[0];
    stringcpy(dst, src);
}

/*!
 * Writes a BLE GATT characteristic
 *
 * @param[in/out] pChar     Pointer to BLE GATT characteristic to write
 * @param[in]     value     Value of characteristic to set
 */
static void 
_bleGattCharacteristicWrite
(
    BLE_GATT_CHAR  *pChar,
    ble_char_value  value
)
{
    // Perform copy of value to BLE
    char *dst = &pChar->value[0];
    char *src = &value[0];
    stringcpy(dst, src);

    // Construct the payload
    char payload[BLE_GATT_CHAR_INDEX_LEN+BLE_GATT_CHAR_VALUE_LEN-1];
    char *idx = &pChar->index[0];
    char *p   = &payload[0];
    while (*idx != '\0')
    {
        *p = *idx;
        ++p;
        ++idx; 
    }
    *p = ',';
    ++p;

    char *v = &value[0];
    stringcpy(p, v);

    // Send value to BLE module
    _bleCmdSend(atGattChar, payload, WRITE, NULL);
}

/*!
 * Adds a custom GATT service
 *
 * @param[in/out] pBLE      Pointer to BLE object
 * @param[in/out] pService  Pointer to BLE_GATT_SERVICE to add
 */
static void
_bleGattServiceAdd
(
    BLE              *pBLE,
    BLE_GATT_SERVICE *pService
)
{
    // Construct payload
    char payload[SDEP_MAX_FULL_MSG_LEN];
    stringcat(&payload[0], "UUID128=", &pService->uuid.uuid128[0]);

    // Send add service command to BLE module
    _bleCmdSend(atGattAddService, &payload[0], WRITE, &pService->index[0]);
    pService->numIndex = string2int(&pService->index[0]);

    // Add service to BLE object
    pBLE->services[pService->numIndex] = *pService;
}

/*!
 * Adds a GATT characteristic
 *
 * @param[in/out] pBLE      Pointer to BLE object
 * @param[in/out] pService  Pointer to BLE_GATT_SERVICE to which char is added
 * @param[in/out] pChar     Pointer to BLE_GATT_CHAR to add
 */
static void
_bleGattCharacteristicAdd
(
    BLE              *pBLE,
    BLE_GATT_SERVICE *pService,
    BLE_GATT_CHAR    *pChar
)
{
    // Construct payload
    char payload[SDEP_MAX_FULL_MSG_LEN];
    char *p = stringcat(&payload[0], "UUID=", &pChar->index[0]);
    p = stringcat(p, ",PROPERTIES=", &pChar->properties[0]);
    p = stringcat(p, ",MIN_LEN=", &pChar->minLen[0]);
    p = stringcat(p, ",MAX_LEN=", &pChar->maxLen[0]);
    stringcat(p, ",VALUE=", &pChar->value[0]);

    // Send command to BLE module
    _bleCmdSend(atGattAddChar, &payload[0], WRITE, &pChar->index[0]);
    pChar->numIndex = string2int(&pChar->index[0]);

    // Add characteristic to service
    pService->characteristics[pChar->numIndex] = *pChar;
    ++pService->numCharacteristics;
}

/*!
 * Initializes a custom GATT service
 *
 * @param[in/out] pService  Pointer to GATT service to initialize
 * @param[in]     uuid      Service's 128-bit UUID
 */
static void
_bleGattServiceInitialize
(
    BLE_GATT_SERVICE    *pService,
    const char          *uuid
)
{
    stringcpy(&pService->uuid.uuid128[0], &uuid[0]);
    pService->numCharacteristics = 0;
}

/*!
 * Initializes a GATT characteristic
 *
 * @param[in/out] pChar     Pointer to GATT characteristic to initialize
 * @param[in]     uuid      Characteristic's UUID
 * @param[in]     props     Characteristic's properties
 * @param[in]     minLen    Characteristic's value's minimum length in bytes
 * @param[in]     maxLen    Characteristic's value's maximum length in bytes
 * @param[in]     value     Characteristic's value's initial value
 * @param[in]     handler   Characteristic's update handler
 */
static void
_bleGattCharacteristicInitialize
(
    BLE_GATT_CHAR           *pChar,
    const char              *uuid,
    const char              *props,
    const char              *minLen,
    const char              *maxLen,
    const char              *value,
    ble_char_update_handler  handler
)
{
    stringcpy(&pChar->uuid[0], &uuid[0]);
    stringcpy(&pChar->properties[0], &props[0]);
    stringcpy(&pChar->minLen[0], &minLen[0]);
    stringcpy(&pChar->maxLen[0], &maxLen[0]);
    stringcpy(&pChar->value[0], &value[0]);

    pChar->handler = handler;
}

/*!
 * Update handler for the RobotDriveService speed characteristic
 */
static void
_robotDriveServiceSpeedHandler(void)
{
    // TODO
    return;
}

/*!
 * Update handler for the RobotDriveService direction characteristic
 */
static void
_robotDriveServiceDirectionHandler(void)
{
    // TODO
    return;
}

/* ------------------------ FUNCTION DEFINITIONS ---------------------------- */

/*!
 * @ref ble.h for function documentation
 */
void
bleConstruct(BLE *pBLE)
{
    // Initialize methods of BLE object
    pBLE->bleInitialize           = bleInitialize;
    pBLE->bleServicesConfigure    = bleServicesConfigure;
    pBLE->bleCharacteristicUpdate = bleCharacteristicUpdate;
}

/*!
 * @ref ble.h for function documentation
 */
void
bleInitialize(BLE *pBLE)
{
    char reply[SDEP_MAX_FULL_MSG_LEN];

    // Register the BLE external interrupt
    _bleIRQRegister();

    // Ensure BLE device is connectable
    _bleCmdSend(atGapConnectAble, "1", WRITE, NULL);

    // Advertise until connection with central is made
    _bleCmdSend(atGapStartAdv, BLE_CMD_EMPTY_PAYLOAD, EXEC, NULL);

    do {
        _bleCmdSend(atGapGetConn, BLE_CMD_EMPTY_PAYLOAD, EXEC, &reply[0]);
        // Poll the resp buffer until connection is made
    } while (reply[0] == '0');

    // Stop advertising
    _bleCmdSend(atGapStopAdv, BLE_CMD_EMPTY_PAYLOAD, EXEC, NULL);
}

/*!
 * @ref ble.h for function documentation
 */
void
bleServicesConfigure(BLE *pBLE)
{
    // Clears all BLE services and characteristics defined on the device
    _bleCmdSend(atGattClear, BLE_CMD_EMPTY_PAYLOAD, EXEC, NULL);

    // Sets BLE device name (optional)
    _bleCmdSend(atGapDevName, bleDeviceName, WRITE, NULL);

    // Enable custom RobotDrive service
    _bleGattServiceInitialize(&RobotDriveService,
                              "00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00"
                             );
    _bleGattCharacteristicInitialize(&RobotDriveCharSpeed,
                              "00-00-00-01-00-00-00-00-00-00-00-00-00-00-00-00",
                              "0x04",
                              "1",
                              "3",
                              "0",
                              _robotDriveServiceSpeedHandler);
    _bleGattCharacteristicInitialize(&RobotDriveCharDirection,
                              "00-00-00-10-00-00-00-00-00-00-00-00-00-00-00-00",
                              "0x04",
                              "1",
                              "1",
                              "0",
                              _robotDriveServiceDirectionHandler);

    _bleGattServiceAdd(pBLE, &RobotDriveService);
    _bleGattCharacteristicAdd(pBLE, &RobotDriveService, &RobotDriveCharSpeed);
    _bleGattCharacteristicAdd(pBLE, &RobotDriveService,
                              &RobotDriveCharDirection);

    // Enable Bluetooth Battery Service
    _bleCmdSend(atBleBattEn, "1", WRITE, NULL);

    // Perform system reset to enable services
    _bleCmdSend(atz, BLE_CMD_EMPTY_PAYLOAD, EXEC, NULL);
}

/*!
 * @ref ble.h for function documentation
 */
void
bleCharacteristicUpdate
(
    BLE           *pBLE,
    BLE_GATT_CHAR *pChar
)
{
    // Read the characteristic value from BLE struct
    char *currValue = &pChar->value[0];

    // Compare to most recently recorded value on BLE module
    char newValue[BLE_GATT_CHAR_VALUE_LEN];
    _bleGattCharacteristicRead(pChar, &newValue[0]);

    // If different, then set old value to new value and act accordingly
    if (!stringcmp(currValue, &newValue[0]))
    {
        // Call characteristic update handler
        pChar->handler();
    }
}

/* ------------------------ ISR DEFS ---------------------------------------- */

/*!
 * Registers the external BLE interrupt handler with the MCU
 */
ISR(BLE_vect, ISR_BLOCK)
{
    // Process messages from the BLE module while available
    while (BLE_PORT & (1 << BLE_IRQ))
    {
        uint8_t msgtype = sdepRespCollect();

        switch(msgtype)
        {
            case SDEP_MSGTYPE_RESPONSE:
                sdepResponseMsgHandler();
                break;
            case SDEP_MSGTYPE_ALERT:
                sdepAlertMsgHandler();
                break;
            case SDEP_MSGTYPE_ERROR:
                sdepErrorMsgHandler();
                break;
        }
    }

    // Signal the semaphore
    sdepBufferSemaphore = 1;
}
