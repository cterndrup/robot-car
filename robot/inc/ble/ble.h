/* Header file for Bluetooth Low Energy code */

#ifndef _BLE_H_
#define _BLE_H_

/* ----------------------- INCLUDES ----------------------------------------- */

/* ----------------------- MACROS AND DEFINES ------------------------------- */

/*!
 * Macro for the MCU I/O pin corresponding to BLE module's IRQ pin
 */
#define BLE_PORT PORTD
#define BLE_IRQ  2
#define BLE_vect INT2_vect

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

/* ------------------------ TYPEDEFS ---------------------------------------- */

/*!
 * Forward definition of BLE object
 */
typedef struct BLE BLE;

/*!
 * BLE GAP specific methods and defs
 */
#include "ble/ble_gap.h"

/*!
 * BLE GATT specific methods and defs
 */
#include "ble/ble_gatt.h"

// TODO: Add documentation
/*
typedef void BleConstruct(BLE *pBLE);

typedef void BleInitialize(BLE *pBLE);

typedef void BleServericesConfigure(BLE *pBLE);

typedef void BleCharacteristicUpdate(BLE *pBLE); 
*/

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

/* ------------------------ STRUCT DEFINITION ------------------------------- */

/*!
 * Definition of the Bluetooth Low Energy object
 */
struct BLE
{
    // Services, Characteristics
    // TODO: Add services and characteristics, buffer for characteristic idxs
    // struct BLEServices[MAX_SERVICES];

    // BLE generic methods
    BleConstruct            *bleConstruct;
    BleInitialize           *bleInitialize;

    // BLE Services methods
    BleServicesConfigure    *bleServicesConfigure;

    // BLE Characteristics methods
    BleCharacteristicUpdate *bleCharacteristicUpdate;

    // BLE GAP methods
    BleGapConnStatusGet     *bleGapConnStatusGet;
    BleGapConnStatusSet     *bleGapConnStatusSet;
    BleGapDisconnect        *bleGapDisconnect;

    // BLE GATT methods
    BleGattClear            *bleGattClear;
    BleGattList             *bleGattList;
};

/* ------------------------ FUNCTION PROTOTYPES ----------------------------- */

// BLE generic methods
BleConstruct            bleConstruct;
BleInitialize           bleInitialize;

// BLE services methods
BleServicesConfigure    bleServicesConfigure;

// BLE Characteristics methods
BleCharacteristicUpdate bleCharacteristicUpdate;

// BLE GAP methods
BleGapConnStatusGet     bleGapConnStatusGet;
BleGapConnStatusSet     bleGapConnStatusSet;
BleGapDisconnect        bleGapDisconnect;

// BLE GATT methods
BleGattClear            bleGattClear;
BleGattList             bleGattList;

#endif // _BLE_H_
