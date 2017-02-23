/* Header file for Bluetooth Low Energy code */

#ifndef _BLE_H_
#define _BLE_H_

/* ----------------------- INCLUDES ----------------------------------------- */

/* ----------------------- GLOBAL VARIABLES --------------------------------- */

/* STANDARD AT-COMMAND STRINGS */

/*!
 * Command Name: AT
 * Description:  Acts as ping to check if in command mode
 */
const char *at  = "AT";

/*!
 * Command Name: ATI
 * Description:  Displays basic info about the Bluefruit module
 */
const char *ati = "ATI";

/*!
 * Command Name: ATZ
 * Description:  Performs a system reset
 */
const char *atz = "ATZ";

/*!
 * Command Name: ATE
 * Description:  Enables/disables echo of input chars with AT parser
 */
const char *ate = "ATE";

/*!
 * Command Name: PPP (+++)
 * Description:  Dynamically switches between DATA/CMD mode...
 */
const char *ppp = "+++";



/* GENERAL PURPOSE AT-COMMAND STRINGS */

/*!
 * Command Name: AT+FACTORYRESET
 * Description:  Clear any user config data from NVM: and performs factory reset
 *               before resetting module
 */
const char *atFactoryReset = "AT+FACTORYRESET";

/*!
 * Command Name: AT+DFU
 * Description:  Forces module into DFU mode, allowing over the air firmware
 *               updates using dedicate DFU app
 */
const char *atDfu = "AT+DFU";

/*!
 * Command Name: AT+HELP
 * Description:  Displays comma-separated list of all AT parser commands
 *               available on the system
 */
const char *atHelp = "AT+HELP";

/*!
 * Command Name: AT+NVMWRITE
 * Description:  Writes data to the 256 byte user non-volatile memory region
 */
const char *atNvmWrite = "AT+NVMWRITE";

/*!
 * Command Name: AT+NVMREAD
 * Description:  Reads data form the 256 byte user non-volatile memory region
 */
const char *atNvmRead = "AT+NVMREAD";

/*!
 * Command Name: AT+MODESWITCHEN
 * Description:  Enables of disables mode switches via the '+++' command on the
 *               BLE peripheral of BLE UART side of the connection
 */
const char *atModeSwitchEn = "AT+MODESWITCHEN";



/* HARDWARE AT-COMMAND STRINGS */

/*!
 * Command Name: AT+BAUDRATE
 * Description:  Changes the baud rate used by the HW UART peripheral on the
 *               nRF51822
 */
const char *atBaudRate = "AT+BAUDRATE";

/*!
 * Command Name: AT+HWADC
 * Description:  Performs an ADC conversion on the specified ADC pin
 */
const char *atHwAdc = "AT+HWADC";

/*!
 * Command Name: AT+HWGETDIETEMP
 * Description:  Gets the temperature in degree celcius of the BLE module's die
 */
const char *atHwGetDieTemp = "AT+HWGETDIETEMP";

/*!
 * Command Name: AT+HWGPIO
 * Description:  Gets or sets the value of the specified GPIO pin (depending on
 *               the mode of the pin
 */
const char *atHwGpio = "AT+HWGPIO";

/*!
 * Command Name: AT+HWGPIOMODE
 * Description:  This will set the mode for the specified GPIO pin
 */
const char *atHwGpioMode = "AT+HWGPIOMODE";

/*!
 * Command Name: AT+HWI2CSCAN
 * Description:  Scans the I2C bus to try to detect any connected I2C devices
 *               and returns addresses of devices that were found during scan
 *               process
 */
const char *atHwI2cScan = "AT+HWI2CSCAN";

/*!
 * Command Name: AT+HWVBAT
 * Description:  Returns the main power supply voltage level in millivolts
 */
const char *atHwVBat = "AT+HWVBAT";

/*!
 * Command Name: AT+HWRANDOM
 * Description:  Generates a random 32-bit number using the HW random number
 *               generator on the nRF51822 (based on white noise)
 */
const char *atHwRandom = "AT+HWRANDOM";

/*!
 * Command Name: AT+HWMODELED
 * Description:  Allows oyu to override hte default behavior of the MODE led
 *               (which indicates the operaing mode by default)
 */
const char *atHwModeLed = "AT+HWMODELED";

/*!
 * Command Name: AT+UARTFLOW
 * Description:  Enables or disable hardware flow control (CTS + RTS) on the
 *               UART peripheral block of the nRF51822
 */
const char *atUartFlow = "AT+UARTFLOW";



/* BLE GENERIC AT-COMMAND STRINGS */

/*!
 * Command Name: AT+BLEPOWERLEVEL
 * Description:  Gets or sets the current transmit power level for the module's
 *               radio (higher transmit power equals better range, lower
 *               transmit power equals better battery life
 */
const char *atBlePowerLevel = "AT+BLEPOWERLEVEL";

/*!
 * Command Name: AT+BLEGETADDRTYPE
 * Description:  Gets the address type (for the 48-bit BLE device address)
 */
const char *atBleGetAddrType = "AT+BLEGETADDRTYPE";

/*!
 * Command Name: AT+BLEGETADDR
 * Description:  Gets the 48-bit BLE device address
 */
const char *atBleGetAddr = "AT+BLEGETADDR";

/*!
 * Command Name: AT+BLEGETPEERADDR
 * Description:  Gets the 48-bit address of the peer (central) device we are
 *               connected to
 */
const char *atBleGetPeerAddr = "AT+BLEGETPEERADDR";

/*!
 * Command Name: AT+BLEGETRSSI
 * Description:  Gets the RSSI (Received Signal Strength Indicator), which can
 *               be used to estimate the reliability of data transmission
 *               between two devices (the lower the number the better)
 */
const char *atBleGetRssi = "AT+BLEGETRSSI";



/* BLE SERVICES AT-COMMAND STRINGS */

/*!
 * Command Name: AT+BLEUARTTX
 * Description:  This command will transmit the specified text message out via
 *               the UART Service while you are running in Command Mode
 */
const char *atBleUartTx = "AT+BLEUARTTX";

/*!
 * Command Name: AT+BLEUARTTXF
 * Decription:   This is a convenience functino that serves the same purpose as
 *               AT+BLEUARTTX, but data is immdiately sent in a singlbe BLE 
 *               packet
 */
const char *atBleUartTxF = "AT+BLEUARTTXF";

/*!
 * Command Name: AT+BLEUARTRX
 * Description:  This command will dump the UART service's RX buffer to the
 *               display if any data has been received from the UART service
 *               while running in Command Mode
 */
const char *atBleUartRx = "AT+BLEUARTRX";

/*!
 * Command Name: AT+BLEUARTFIFO
 * Description:  This command will return the free space available in the BLE
 *               UART TX and RX FIFOs
 */
const char *atBleUartFifo = "AT+BLEUARTFIFO";

/*!
 * Command Name; AT+BLEKEYBOARDEN
 * Description:  This command will enable GATT over HID keyboard support, which
 *               allows you to emulate a keyboard on supported iOS and Android
 *               devices
 */
const char *atBleKeyboardEn = "AT+BLEKEYBOARDEN";

/*!
 * Command Name: AT+BLEKEYBOARD
 * Description:  Sends text data over the BLE keyboard interface
 */
const char *atBleKeyboard = "AT+BLEKEYBOARD";

/*!
 * Command Name: AT+BLEKEYBOARDCODE
 * Description:  Sends a raw hex sequence of USB HID keycodes to the BLE
 *               keyboard interface including key modifiers and up to six alpha-
 *               numeric characters
 */
const char *atBleKeyboardCode = "AT+BLEKEYBOARDCODE";

/*!
 * Command Name: AT+BLEHIDEN
 * Description:  This command will enable GATT over HID support, which allows
 *               you to emulate a keyboard, moust or mediat control on supported
 *               iOS, Android, OSX and Windows 10 devices
 */
const char *atBleHidEn = "AT+BLEHIDEN";

/*!
 * Command Name: AT+BLEHIDMOUSEMOVE
 * Description:  Moves the HID mouse or scroll wheel position the specified
 *               number of ticks
 */
const char *atBleHidMouseMove = "AT+BLEHIDMOUSEMOVE";

/*!
 * Command Name: AT+BLEHIDMOUSEBUTTON
 * Description:  Manipulates the HID mouse buttons via the specific string(s)
 */
const char *atBleHidMouseButton = "AT+BLEHIDMOUSEBUTTON";

/*!
 * Command Name: AT+BLEHIDCONTROLKEY
 * Description:  Sends HID media control commands for the bonded device
 */
const char *atBleHidControlKey = "AT+BLEHIDCONTROLKEY";

/*!
 * Command Name: AT+BLEHIDGAMEPADEN
 * Description:  Enables HID gamepad support in the HID service
 */
const char *atBleHidGamePadEn = "AT+BLEHiDGAMEPADEN";

/*!
 * Command Name: AT+BLEHIDGAMEPAD
 * Description:  Sends a specific HID gamepad payload out over BLE
 */
const char *atBleHidGamePad = "AT+BLEHIDGAMEPAD";

/*!
 * Command Name; AT+BLEMIDIEN
 * Description:  Enables or disables the BLE MIDI service
 */
const char *atBleMidiEn = "AT+BLEMIDIEN";

/*!
 * Command Name: AT+BLEMIDIRX
 * Description:  Reads an incoming MIDI character array from the buffer
 */
const char *atBleMidiRx = "AT+BLEMIDIRX";

/*!
 * Command Name: AT+BLEMIDITX
 * Description:  Sends a MIDI event to host
 */
const char *atBleMidiTx = "AT+BLEMIDITX";

/*!
 * Command Name: AT+BLEBATTEN
 * Description:  Enables the Battery Service following the definition from the
 *               Bluetooth SIG
 */
const char *atBleBattEn = "AT+BLEBATTEN";

/*!
 * Command Name: AT+BLEBATTVAL
 * Description:  Sets the current battery level in percentage (0..100) for the
 *               Battery Service
 */
const char *atBleBattVal = "AT+BLEBATTVAL";



/* BLE GENERIC ACCESS PROFILE (GAP) AT-COMMANDS */

/*!
 * Command Name: AT+GAPCONNECTABLE
 * Description:  This command can be used to prevent the device from being
 *               'connectable'
 */
const char *atGapConnectAble = "AT+GAPCONNECTABLE";

/*!
 * Command Name: AT+GAPGETCONN
 * Description:  Displays the current connection status
 */
const char *atGapGetConn = "AT+GAPGETCONN";

/*!
 * Command Name: AT+GAPDISCONNECT
 * Description:  Disconnects to the external device if we are currently
 *               connected
 */
const char *atGapDisconnect = "AT+GAPDISCONNECT";

/*!
 * Command Name: AT+GAPDEVNAME
 * Description:  Gets or sets the device name, which is included in the
 *               advertising payload for the Bluefruit LE module
 */
const char *atGapDevName = "AT+GAPDEVNAME";

/*!
 * Command Name: AT+GAPDELBONDS
 * Description:  Deletes bonding information stored on the BLuefruit LE module
 */
const char *atGapDelBonds = "AT+GAPDELBONDS";

/*!
 * Command Name: AT+GAPINTERVALS
 * Description:  Gets or sets the varios advertising and connection intervals
 *               for the Bluefruit LE module
 */
const char *atGapIntervals = "AT+GAPINTERVALS";

/*!
 * Command Name: AT+GAPSTARTADV
 * Description:  Causes the Bluefruit LE module to start transmitting 
 *               advertising packets if this isn't already the case
 */
const char *atGapStartAdv = "AT+GAPSTARTADV";

/*!
 * Command Name: AT+GAPSTOPADV
 * Description:  Stops advertising packets from being transmitted by the
 *               Bluefruit LE module
 */
const char *atGapStopAdv = "AT+GAPSTOPADV";

/*!
 * Command Name: AT+GAPSETADVDATA
 * Description:  Sets the raw advertising data payload to the specified byte
 *               array (overriding the normal advertising data), following the
 *               guidelines in the Bluetooth 4.0 or 4.1 Core Specification
 */
const char *atGapSetAdvData = "AT+GAPSETADVDATA";



/* BLE GENERIC ATTRIBUTE PROFILE (GATT) AT-COMMAND STRINGS */

/*!
 * Command Name: AT+GATTCLEAR
 * Description:  Clears any custom GATT services and characteristics that have
 *               been defined on the device
 */
const char *atGattClear = "AT+GATTCLEAR";

/*!
 * Command Name: AT+GATTADDSERVICE
 * Description:  Adds a new custom service definition to the device
 */
const char *atGattAddService = "AT+GATTADDSERVICE";

/*!
 * Command Name: AT+GATTADDCHAR
 * Description:  Adds a custom characteristic to the last service that was
 *               added to the peripheral (via AT+GATTADDSERVICE)
 */
const char *atGattAddChar = "AT+GATTADDCHAR";

/*!
 * Command Name: AT+GATTCHAR
 * Description:  Gets or sets the value of the specified custom GATT
 *               characteristic (based on the index ID returned when the
 *               characteristic was added to the system via AT+GATTADDCHAR)
 */
const char *atGattChar = "AT+GATTCHAR";

/*!
 * Command Name: AT+GATTLIST
 * Description:  Lists all custom GATT services and characteristics that have
 *               been defined on the device
 */
const char *atGattList = "AT+GATTLIST";

/*!
 * Command Name: AT+GATTCHARRAW
 * Description:  This read only command reads binary (instead of ASCII) data
 *               from a characteristic
 */
const char *atGattCharRaw = "AT+GATTCHARRAW";


 
/* DEBUG AT-COMMANDS */
/*! 
 * NOTE: Debug commands should be used with care since they can easily lead to 
 *       HardFault on ARM Cortex-M core of BLE module
 */

/*!
 * Command Name: AT+DBGMEMRD
 * Description:  Displays the raw memory contents at the specified address
 */
const char *atDbgMemRd = "AT+DBGMEMRD";

/*!
 * Command Name: AT+DBGNVMRD
 * Description:  Displays the raw contents of the config data section of non-
 *               volatile memory
 */
const char *atDbgNvmRd = "AT+DBGNVMRD";

/*!
 * Command Name: AT+DBGSTACKSIZE
 * Description:  Returns the current stack size, to help detect stack overflow
 *               or detect stack memory usage when optimizing memory usage on
 *               the system
 */
const char *atDbgStackSize = "AT+DBGSTACKSIZE";

/*!
 * Command Name: AT+DBGSTACKDUMP
 * Description:  Dumps the current stack contents -- Unused sections of stack
 *               memory are filled with '0xCAFEFOOD' to help determine where
 *               stack usage stops
 */
const char *atDbgStackDump = "AT+DBGSTACKDUMP";

/* ----------------------- MACROS AND DEFINES ------------------------------- */

/*!
 * Macro for the MCU I/O pin corresponding to BLE module's IRQ pin
 */
#define BLE_IRQ  2
#define BLE_vect INT2_vect

/*!
 * Macro for the MCU I/O pin corresponding to SW interrupt for BLE response
 * msg handling
 */
#define BLE_IRQ_RESP  3
#define BLE_RESP_vect INT3_vect
#define RAISE_BLE_IRQ_RESP \
        SET_BIT(PORTD, BLE_IRQ_RESP)

/*!
 * Macro for the MCU I/O pin corresponding to SW interrupt for BLE alert
 * msg handling
 */
#define BLE_IRQ_ALERT  6
#define BLE_ALERT_vect INT6_vect
#define RAISE_BLE_IRQ_ALERT \
        SET_BIT(PORTE, BLE_IRQ_ALERT)
#define BLE_ALERT_BUF_SIZE 2

/*!
 * Macro for the MCU I/O pin corresponding to SW interrupt for BLE error
 * msg handling
 */
#define BLE_IRQ_ERROR  7
#define BLE_ERROR_vect INT7_vect
#define RAISE_BLE_IRQ_ERROR \
        SET_BIT(PORTE, BLE_IRQ_ERROR)

/* ------------------------ ENUMS ------------------------------------------- */

/*!
 * Enumeration of BLE_CMD_SEND_STATEs for the state machine implemented in
 * bleCmdSend()
 */
typedef enum BLE_CMD_SEND_STATE
             {SEND_INIT, SEND_HDR, SEND_BASE, 
              SEND_MODE, SEND_PAYLOAD, SEND_DONE}
             BLE_CMD_SEND_STATE;

/*!
 * Enumeration of BLE_ALERT_RECV_STATEs for the state machine implemented for
 * handling BLE ALERT messages from the BLE module
 */
typedef enum BLE_ALERT_RECV_STATE
             {ALERT_INIT, READ_HDR, READ_PAYLOAD, ALERT_DONE}
             BLE_ALERT_RECV_STATE;

/* ------------------------ TYPEDEFS ---------------------------------------- */

/*!
 * Sends AT-commands to the BLE module
 *
 * @param[in] length    The length of the payload of the AT-command
 * @param[in] pBase     The base AT-command string
 * @param[in] pMode     The AT-command mode
 * @param[in] pPayload  The payload in addition ot the base AT-command string
 */
typedef void BleCmdSend(uint8_t length, const char *pBase,
                        const char *pMode, const char *pPayload);

/* ------------------------ FUNCTION PROTOTYPES ----------------------------- */

/*!
 * Registers BLE module's external interrupts with MCU
 */
void BleIRQRegister(void);

BleCmdSend bleCmdSend;

#endif // _BLE_H_
