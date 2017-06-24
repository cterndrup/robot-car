/* Implementation file for Bluetooth Low Energy code */

/* ------------------------ SYSTEM INCLUDES --------------------------------- */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

/* ------------------------ APPLICATION INCLUDES ---------------------------- */
#include "spi/spi.h"
#include "sdep/sdep.h"
#include "ble/ble.h"
#include "car/car.h"
#include "common/utils.h"

/* ------------------------ EXTERNS ----------------------------------------- */

/*!
 * External declaration of semaphore for synchronizing access to sdep buffers
 */
extern semaphore_t sdepBufferSemaphore;

/*!
 * External declaration of sdepRespBuffer
 */
extern SDEP_MSG_BUFFER sdepRespBuffer;

/*!
 * External declaration of the Car object
 */
extern Car car;

/* ------------------------ STATIC VARIABLES -------------------------------- */

/*!
 * Declaration of RobotDriveService and its characteristics
 */
BLE_GATT_SERVICE RobotDriveService;
BLE_GATT_CHAR    RobotDriveCharSpeed;
BLE_GATT_CHAR    RobotDriveCharDirection;

/*!
 * Definition of BLE module name
 */
static const char *bleDeviceName = "BluefruitLE";

/*!
 * Definition of empty BLE command payload
 */
static const char bleCmdEmptyPayload[1] = {'\0'};



/* STANDARD AT-COMMAND STRINGS */

/*!
 * Command Name: AT
 * Description:  Acts as ping to check if in command mode
 */
static const char *at  = "AT";

/*!
 * Command Name: ATI
 * Description:  Displays basic info about the Bluefruit module
 */
static const char *ati = "ATI";

/*!
 * Command Name: ATZ
 * Description:  Performs a system reset
 */
static const char *atz = "ATZ";

/*!
 * Command Name: ATE
 * Description:  Enables/disables echo of input chars with AT parser
 */
static const char *ate = "ATE";

/*!
 * Command Name: PPP (+++)
 * Description:  Dynamically switches between DATA/CMD mode...
 */
static const char *ppp = "+++";



/* GENERAL PURPOSE AT-COMMAND STRINGS */

/*!
 * Command Name: AT+FACTORYRESET
 * Description:  Clear any user config data from NVM: and performs factory reset
 *               before resetting module
 */
static const char *atFactoryReset = "AT+FACTORYRESET";

/*!
 * Command Name: AT+DFU
 * Description:  Forces module into DFU mode, allowing over the air firmware
 *               updates using dedicate DFU app
 */
static const char *atDfu = "AT+DFU";

/*!
 * Command Name: AT+HELP
 * Description:  Displays comma-separated list of all AT parser commands
 *               available on the system
 */
static const char *atHelp = "AT+HELP";

/*!
 * Command Name: AT+NVMWRITE
 * Description:  Writes data to the 256 byte user non-volatile memory region
 */
static const char *atNvmWrite = "AT+NVMWRITE";

/*!
 * Command Name: AT+NVMREAD
 * Description:  Reads data form the 256 byte user non-volatile memory region
 */
static const char *atNvmRead = "AT+NVMREAD";

/*!
 * Command Name: AT+MODESWITCHEN
 * Description:  Enables of disables mode switches via the '+++' command on the
 *               BLE peripheral of BLE UART side of the connection
 */
static const char *atModeSwitchEn = "AT+MODESWITCHEN";



/* HARDWARE AT-COMMAND STRINGS */

/*!
 * Command Name: AT+BAUDRATE
 * Description:  Changes the baud rate used by the HW UART peripheral on the
 *               nRF51822
 */
static const char *atBaudRate = "AT+BAUDRATE";

/*!
 * Command Name: AT+HWADC
 * Description:  Performs an ADC conversion on the specified ADC pin
 */
static const char *atHwAdc = "AT+HWADC";

/*!
 * Command Name: AT+HWGETDIETEMP
 * Description:  Gets the temperature in degree celcius of the BLE module's die
 */
static const char *atHwGetDieTemp = "AT+HWGETDIETEMP";

/*!
 * Command Name: AT+HWGPIO
 * Description:  Gets or sets the value of the specified GPIO pin (depending on
 *               the mode of the pin
 */
static const char *atHwGpio = "AT+HWGPIO";

/*!
 * Command Name: AT+HWGPIOMODE
 * Description:  This will set the mode for the specified GPIO pin
 */
static const char *atHwGpioMode = "AT+HWGPIOMODE";

/*!
 * Command Name: AT+HWI2CSCAN
 * Description:  Scans the I2C bus to try to detect any connected I2C devices
 *               and returns addresses of devices that were found during scan
 *               process
 */
static const char *atHwI2cScan = "AT+HWI2CSCAN";

/*!
 * Command Name: AT+HWVBAT
 * Description:  Returns the main power supply voltage level in millivolts
 */
static const char *atHwVBat = "AT+HWVBAT";

/*!
 * Command Name: AT+HWRANDOM
 * Description:  Generates a random 32-bit number using the HW random number
 *               generator on the nRF51822 (based on white noise)
 */
static const char *atHwRandom = "AT+HWRANDOM";

/*!
 * Command Name: AT+HWMODELED
 * Description:  Allows oyu to override hte default behavior of the MODE led
 *               (which indicates the operaing mode by default)
 */
static const char *atHwModeLed = "AT+HWMODELED";

/*!
 * Command Name: AT+UARTFLOW
 * Description:  Enables or disable hardware flow control (CTS + RTS) on the
 *               UART peripheral block of the nRF51822
 */
static const char *atUartFlow = "AT+UARTFLOW";



/* BLE GENERIC AT-COMMAND STRINGS */

/*!
 * Command Name: AT+BLEPOWERLEVEL
 * Description:  Gets or sets the current transmit power level for the module's
 *               radio (higher transmit power equals better range, lower
 *               transmit power equals better battery life
 */
static const char *atBlePowerLevel = "AT+BLEPOWERLEVEL";

/*!
 * Command Name: AT+BLEGETADDRTYPE
 * Description:  Gets the address type (for the 48-bit BLE device address)
 */
static const char *atBleGetAddrType = "AT+BLEGETADDRTYPE";

/*!
 * Command Name: AT+BLEGETADDR
 * Description:  Gets the 48-bit BLE device address
 */
static const char *atBleGetAddr = "AT+BLEGETADDR";

/*!
 * Command Name: AT+BLEGETPEERADDR
 * Description:  Gets the 48-bit address of the peer (central) device we are
 *               connected to
 */
static const char *atBleGetPeerAddr = "AT+BLEGETPEERADDR";

/*!
 * Command Name: AT+BLEGETRSSI
 * Description:  Gets the RSSI (Received Signal Strength Indicator), which can
 *               be used to estimate the reliability of data transmission
 *               between two devices (the lower the number the better)
 */
static const char *atBleGetRssi = "AT+BLEGETRSSI";



/* BLE SERVICES AT-COMMAND STRINGS */

/*!
 * Command Name: AT+BLEUARTTX
 * Description:  This command will transmit the specified text message out via
 *               the UART Service while you are running in Command Mode
 */
static const char *atBleUartTx = "AT+BLEUARTTX";

/*!
 * Command Name: AT+BLEUARTTXF
 * Decription:   This is a convenience function that serves the same purpose as
 *               AT+BLEUARTTX, but data is immediately sent in a single BLE
 *               packet
 */
static const char *atBleUartTxF = "AT+BLEUARTTXF";

/*!
 * Command Name: AT+BLEUARTRX
 * Description:  This command will dump the UART service's RX buffer to the
 *               display if any data has been received from the UART service
 *               while running in Command Mode
 */
static const char *atBleUartRx = "AT+BLEUARTRX";

/*!
 * Command Name: AT+BLEUARTFIFO
 * Description:  This command will return the free space available in the BLE
 *               UART TX and RX FIFOs
 */
static const char *atBleUartFifo = "AT+BLEUARTFIFO";

/*!
 * Command Name; AT+BLEKEYBOARDEN
 * Description:  This command will enable GATT over HID keyboard support, which
 *               allows you to emulate a keyboard on supported iOS and Android
 *               devices
 */
static const char *atBleKeyboardEn = "AT+BLEKEYBOARDEN";

/*!
 * Command Name: AT+BLEKEYBOARD
 * Description:  Sends text data over the BLE keyboard interface
 */
static const char *atBleKeyboard = "AT+BLEKEYBOARD";

/*!
 * Command Name: AT+BLEKEYBOARDCODE
 * Description:  Sends a raw hex sequence of USB HID keycodes to the BLE
 *               keyboard interface including key modifiers and up to six alpha-
 *               numeric characters
 */
static const char *atBleKeyboardCode = "AT+BLEKEYBOARDCODE";

/*!
 * Command Name: AT+BLEHIDEN
 * Description:  This command will enable GATT over HID support, which allows
 *               you to emulate a keyboard, moust or mediat control on supported
 *               iOS, Android, OSX and Windows 10 devices
 */
static const char *atBleHidEn = "AT+BLEHIDEN";

/*!
 * Command Name: AT+BLEHIDMOUSEMOVE
 * Description:  Moves the HID mouse or scroll wheel position the specified
 *               number of ticks
 */
static const char *atBleHidMouseMove = "AT+BLEHIDMOUSEMOVE";

/*!
 * Command Name: AT+BLEHIDMOUSEBUTTON
 * Description:  Manipulates the HID mouse buttons via the specific string(s)
 */
static const char *atBleHidMouseButton = "AT+BLEHIDMOUSEBUTTON";

/*!
 * Command Name: AT+BLEHIDCONTROLKEY
 * Description:  Sends HID media control commands for the bonded device
 */
static const char *atBleHidControlKey = "AT+BLEHIDCONTROLKEY";

/*!
 * Command Name: AT+BLEHIDGAMEPADEN
 * Description:  Enables HID gamepad support in the HID service
 */
static const char *atBleHidGamePadEn = "AT+BLEHiDGAMEPADEN";

/*!
 * Command Name: AT+BLEHIDGAMEPAD
 * Description:  Sends a specific HID gamepad payload out over BLE
 */
static const char *atBleHidGamePad = "AT+BLEHIDGAMEPAD";

/*!
 * Command Name; AT+BLEMIDIEN
 * Description:  Enables or disables the BLE MIDI service
 */
static const char *atBleMidiEn = "AT+BLEMIDIEN";

/*!
 * Command Name: AT+BLEMIDIRX
 * Description:  Reads an incoming MIDI character array from the buffer
 */
static const char *atBleMidiRx = "AT+BLEMIDIRX";

/*!
 * Command Name: AT+BLEMIDITX
 * Description:  Sends a MIDI event to host
 */
static const char *atBleMidiTx = "AT+BLEMIDITX";

/*!
 * Command Name: AT+BLEBATTEN
 * Description:  Enables the Battery Service following the definition from the
 *               Bluetooth SIG
 */
static const char *atBleBattEn = "AT+BLEBATTEN";

/*!
 * Command Name: AT+BLEBATTVAL
 * Description:  Sets the current battery level in percentage (0..100) for the
 *               Battery Service
 */
static const char *atBleBattVal = "AT+BLEBATTVAL";



/* DEBUG AT-COMMANDS */
/*!
 * NOTE: Debug commands should be used with care since they can easily lead to
 *       HardFault on ARM Cortex-M core of BLE module
 */

/*!
 * Command Name: AT+DBGMEMRD
 * Description:  Displays the raw memory contents at the specified address
 */
static const char *atDbgMemRd = "AT+DBGMEMRD";

/*!
 * Command Name: AT+DBGNVMRD
 * Description:  Displays the raw contents of the config data section of non-
 *               volatile memory
 */
static const char *atDbgNvmRd = "AT+DBGNVMRD";

/*!
 * Command Name: AT+DBGSTACKSIZE
 * Description:  Returns the current stack size, to help detect stack overflow
 *               or detect stack memory usage when optimizing memory usage on
 *               the system
 */
static const char *atDbgStackSize = "AT+DBGSTACKSIZE";

/*!
 * Command Name: AT+DBGSTACKDUMP
 * Description:  Dumps the current stack contents -- Unused sections of stack
 *               memory are filled with '0xCAFEFOOD' to help determine where
 *               stack usage stops
 */
static const char *atDbgStackDump = "AT+DBGSTACKDUMP";



/* BLE GENERIC ACCESS PROFILE (GAP) AT-COMMANDS */

/*!
 * Command Name: AT+GAPCONNECTABLE
 * Description:  This command can be used to prevent the device from being
 *               'connectable'
 */
static const char *atGapConnectAble = "AT+GAPCONNECTABLE";

/*!
 * Command Name: AT+GAPGETCONN
 * Description:  Displays the current connection status
 */
static const char *atGapGetConn = "AT+GAPGETCONN";

/*!
 * Command Name: AT+GAPDISCONNECT
 * Description:  Disconnects to the external device if we are currently
 *               connected
 */
static const char *atGapDisconnect = "AT+GAPDISCONNECT";

/*!
 * Command Name: AT+GAPDEVNAME
 * Description:  Gets or sets the device name, which is included in the
 *               advertising payload for the Bluefruit LE module
 */
static const char *atGapDevName = "AT+GAPDEVNAME";

/*!
 * Command Name: AT+GAPDELBONDS
 * Description:  Deletes bonding information stored on the Bluefruit LE module
 */
static const char *atGapDelBonds = "AT+GAPDELBONDS";

/*!
 * Command Name: AT+GAPINTERVALS
 * Description:  Gets or sets the varios advertising and connection intervals
 *               for the Bluefruit LE module
 */
static const char *atGapIntervals = "AT+GAPINTERVALS";

/*!
 * Command Name: AT+GAPSTARTADV
 * Description:  Causes the Bluefruit LE module to start transmitting
 *               advertising packets if this isn't already the case
 */
static const char *atGapStartAdv = "AT+GAPSTARTADV";

/*!
 * Command Name: AT+GAPSTOPADV
 * Description:  Stops advertising packets from being transmitted by the
 *               Bluefruit LE module
 */
static const char *atGapStopAdv = "AT+GAPSTOPADV";

/*!
 * Command Name: AT+GAPSETADVDATA
 * Description:  Sets the raw advertising data payload to the specified byte
 *               array (overriding the normal advertising data), following the
 *               guidelines in the Bluetooth 4.0 or 4.1 Core Specification
 */
static const char *atGapSetAdvData = "AT+GAPSETADVDATA";



/* BLE GENERIC ATTRIBUTE PROFILE (GATT) AT-COMMAND STRINGS */

/*!
 * Command Name: AT+GATTCLEAR
 * Description:  Clears any custom GATT services and characteristics that have
 *               been defined on the device
 */
static const char *atGattClear = "AT+GATTCLEAR";

/*!
 * Command Name: AT+GATTADDSERVICE
 * Description:  Adds a new custom service definition to the device
 */
static const char *atGattAddService = "AT+GATTADDSERVICE";

/*!
 * Command Name: AT+GATTADDCHAR
 * Description:  Adds a custom characteristic to the last service that was
 *               added to the peripheral (via AT+GATTADDSERVICE)
 */
static const char *atGattAddChar = "AT+GATTADDCHAR";

/*!
 * Command Name: AT+GATTCHAR
 * Description:  Gets or sets the value of the specified custom GATT
 *               characteristic (based on the index ID returned when the
 *               characteristic was added to the system via AT+GATTADDCHAR)
 */
static const char *atGattChar = "AT+GATTCHAR";

/*!
 * Command Name: AT+GATTLIST
 * Description:  Lists all custom GATT services and characteristics that have
 *               been defined on the device
 */
static const char *atGattList = "AT+GATTLIST";

/*!
 * Command Name: AT+GATTCHARRAW
 * Description:  This read only command reads binary (instead of ASCII) data
 *               from a characteristic
 */
static const char *atGattCharRaw = "AT+GATTCHARRAW";

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
_robotDriveServiceSpeedHandler(ble_char_value value)
{
    uint8_t speed = string2int(&value[0]);
    car.carDrive(&car, speed, car.direction);
}

/*!
 * Update handler for the RobotDriveService direction characteristic
 */
static void
_robotDriveServiceDirectionHandler(ble_char_value value)
{
    uint8_t dir = string2int(&value[0]);
    car.carDrive(&car, car.speed, dir);
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
    pBLE->bleConnect              = bleConnect;
    pBLE->bleServicesConfigure    = bleServicesConfigure;
    pBLE->bleCharacteristicUpdate = bleCharacteristicUpdate;
    pBLE->blePing                 = blePing;
    pBLE->bleInfo                 = bleInfo;
}

/*!
 * @ref ble.h for function documentation
 */
void
bleInitialize(BLE *pBLE)
{
    // Register the BLE external interrupt
    _bleIRQRegister();
}

/*!
 * @ref ble.h for function documentation
 */
void
bleConnect(BLE *pBLE)
{
    char reply[SDEP_MAX_FULL_MSG_LEN];

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
        pChar->handler(&newValue[0]);
    }
}

/*!
 * @ref ble.h for function documentation
 */
uint8_t
blePing(BLE *pBLE)
{
    char reply[SDEP_MAX_FULL_MSG_LEN];
    memset(&reply[0], 0, SDEP_MAX_FULL_MSG_LEN);

    _bleCmdSend(at, BLE_CMD_EMPTY_PAYLOAD, EXEC, &reply[0]);

    return !(reply[0] == 'O' && reply[1] == 'K');
}

/*!
 * @ref ble.h for function documentation
 */
void
bleInfo(BLE *pBLE, char info[], uint8_t infoLen)
{
    char reply[SDEP_MAX_FULL_MSG_LEN];
    memset(&reply[0], 0, SDEP_MAX_FULL_MSG_LEN);

    _bleCmdSend(ati, BLE_CMD_EMPTY_PAYLOAD, EXEC, &reply[0]);
    memcpy(&info[0],
           &reply[0],
           infoLen < SDEP_MAX_FULL_MSG_LEN ? infoLen : SDEP_MAX_FULL_MSG_LEN);
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
