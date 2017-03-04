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
    char          *reply,
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
        for (uint8_t i = 0;
             p != NULL && *p != '\0' && i < MAX_PAYLOAD_LEN; ++i)
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
        for (uint8_t i = 0; i < sdepRespBuffer.numMsgs; ++i)
        {
            // Iterate through payload of current message
            uint8_t len = sdepRespBuffer.buffer[i].payloadLen & ~(1 << 7);
            for (uint8_t j = 0; j < len; ++j)
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
 * @param[in/out] pBLE          Pointer to BLE object
 * @param[in]     serviceIdx    Index in services list for given service
 * @param[in]     charIdx       Index in characteristics list for given
 *                              characteristic
 * @param[in/out] value         Value of retrieved characteristic
 */
static void
_bleGattCharacteristicRead
(
    BLE               *pBLE, 
    uint8_t            serviceIdx,
    uint8_t            charIdx,
    ble_char_value     value
)
{
    // Send command to BLE module
    char *idx = &pBLE->services[serviceIdx].characteristics[charIdx].index[0];
    _bleCmdSend(atGattChar, idx, EXEC, &value[0]);

    // Copy value to BLE object
    char *dst = &pBLE->services[serviceIdx].characteristics[charIdx].value[0];
    char *src = &value[0];
    stringcpy(dst, src);
}

/*!
 * Writes a BLE GATT characteristic
 *
 * @param[in/out] pBLE          Pointer to BLE object
 * @param[in]     serviceIdx    Index in services list for given service
 * @param[in]     charIdx       Index in characteristics list for given
 *                              characteristic
 * @param[in]     value         Value of characteristic to set
 */
static void 
_bleGattCharacteristicWrite
(
    BLE               *pBLE,
    ble_service_index  serviceIdx,
    ble_char_index     charIdx,
    ble_char_value     value
)
{
    // Perform copy of value to BLE
    char *dst = &pBLE->services[serviceIdx].characteristics[charIdx].value[0];
    char *src = &value[0];
    stringcpy(dst, src);

    // Construct the payload
    char payload[BLE_GATT_CHAR_INDEX_LEN+BLE_GATT_CHAR_VALUE_LEN-1];
    char *idx = &pBLE->services[serviceIdx].characteristics[charIdx].value[0];
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

    pBLE->bleGapConnStatusGet = bleGapConnStatusGet;
    pBLE->bleGapConnStatusSet = bleGapConnStatusSet;
    pBLE->bleGapDisconnect    = bleGapDisconnect;

    pBLE->bleGattClear = bleGattClear;
    pBLE->bleGattList  = bleGattList;
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
    // Sets BLE device name (optional)
    _bleCmdSend(atGapDevName, bleDeviceName, WRITE, NULL);

    // Enable custom RobotDrive service
    // TODO

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
    BLE     *pBLE,
    uint8_t  serviceIdx,
    uint8_t  charIdx
)
{
    // Read the characteristic value from BLE struct
    char *currValue =
        &pBLE->services[serviceIdx].characteristics[charIdx].value[0];

    // Compare to most recently recorded value on BLE module
    char newValue[BLE_GATT_CHAR_VALUE_LEN];
    _bleGattCharacteristicRead(pBLE, serviceIdx, charIdx, &newValue[0]);

    // If different, then set old value to new value and act accordingly
    if (!stringcmp(currValue, &newValue[0]))
    {
        // Call characteristic update handler
        pBLE->services[serviceIdx].characteristics[charIdx].handler();
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
