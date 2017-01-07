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
 * Description:  Deletes bonding information stored on teh BLuefruit LE module
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

// TODO: Add macros for sending BLE commands -- pay attention to payloads 
//       that require multiple packets

/*!
 * Macro to send AT command to BLE module
 */
#define BLE_STD_AT_SEND \
        SDEP_AT_CMD_SEND(0x02, at)

/*!
 * Macro to send ATI command to BLE module
 */
#define BLE_STD_ATI_SEND \
        SDEP_AT_CMD_SEND(0x03, ati)

/*!
 * Macro to send ATZ command to BLE module
 */
#define BLE_STD_ATZ_SEND \
        SDEP_AT_CMD_SEND(0x03, atz)

/*!
 * Macro to send ATE command to BLE module
 */
#define BLE_STD_ATE_SEND \
        SDEP_AT_CMD_SEND(0x03, ate)

/*!
 * Macro to send PPP (+++) command to BLE module
 */
#define BLE_STD_PPP_SEND \
        SDEP_AT_CMD_SEND(0x03, ppp)

/*!
 * Macro to send AT+FACTORYRESET command to BLE module
 */
#define BLE_GP_FACTORYRESET_SEND \
        SDEP_AT_CMD_SEND(0x0F, atFactoryReset)

/*!
 * Macro to send AT+DFU command to BLE module
 */
#define BLE_GP_DFU_SEND \
        SDEP_AT_CMD_SEND(0x06, atDfu)

/*!
 * Macro to send AT+HELP command to BLE module
 */
#define BLE_GP_HELP_SEND \
        SDEP_AT_CMD_SEND(0x07, atHelp)

/*!
 * Macro to send AT+NVMWRITE command to BLE module
 */
#define BLE_GP_NVMWRITE_SEND \
        SDEP_AT_CMD_SEND(0x0B, atNvmWrite)

/*!
 * Macro to send AT+NVMREAD command to BLE module
 */
#define BLE_GP_NVMREAD_SEND \
        SDEP_AT_CMD_SEND(0x0A, atNvmRead)

/*!
 * Macro to send AT+MODESWITCHEN command to BLE module
 */
#define BLE_GP_MODESWITCHEN_SEND \
        SDEP_AT_CMD_SEND(0x0F, atModeSwitchEn)

/*!
 * Macro to send AT+BAUDRATE command to BLE module
 */
#define BLE_HW_BAUDRATE_SEND \
        SDEP_AT_CMD_SEND(0x0B, atBaudRate)

/*!
 * Macro to send AT+HWADC command to BLE module
 */
#define BLE_HW_HWADC_SEND \
        SDEP_AT_CMD_SEND(0x08, atHwAdc)

/*!
 * Macro to send AT+HWGETDIETEMP command to BLE module
 */
#define BLE_HW_HWGETDIETEMP_SEND \
        SDEP_AT_CMD_SEND(0x0F, atHwGetDieTemp)

/*!
 * Macro to send AT+HWGPIO command to BLE module
 */
#define BLE_HW_HWGPIO_SEND \
        SDEP_AT_CMD_SEND(0x09, atHwGpio)

/*!
 * Macro to send AT+HWGPIOMODE command to BLE module
 */
#define BLE_HW_HWGPIOMODE_SEND \
        SDEP_AT_CMD_SEND(0x0D, atHwGpioMode)

/*!
 * Macro to send AT+HWI2CSCAN command to BLE module
 */
#define BLE_HW_HWI2CSCAN_SEND \
        SDEP_AT_CMD_SEND(0x0C, atHwI2cScan)

/*!
 * Macro to send AT+HWVBAT command to BLE module
 */
#define BLE_HW_HWVBAT_SEND \
        SDEP_AT_CMD_SEND(0x09, atHwVBat)

/*!
 * Macro to send AT+HWRANDOM command to BLE module
 */
#define BLE_HW_HWRANDOM_SEND \
        SDEP_AT_CMD_SEND(0x0B, atHwRandom)

/*!
 * Macro to send AT+HWMODELED command to BLE module
 */
#define BLE_HW_HWMODELED_SEND \
        SDEP_AT_CMD_SEND(0x0C, atHwModeLed)

/*!
 * Macro to send AT+UARTFLOW command to BLE module
 */
#define BLE_HW_UARTFLOW_SEND \
        SDEP_AT_CMD_SEND(0x0B, atUartFlow)

/*!
 * Macro to send AT+BLEPOWERLEVEL command to BLE module
 */
#define BLE_GENERIC_BLEPOWERLEVEL_SEND \
        SDEP_AT_CMD_SEND(0x10, atBlePowerLevel)

/*!
 * Macro to send AT+BLEGETADDRTYPE command to BLE module
 * 
 * TODO: This command's payload is > 16 bytes.
 */
#define BLE_GENERIC_BLEGETADDRTYPE_SEND \
        SDEP_AT_CMD_SEND(0x11, atBleGetAddrType)

/*!
 * Macro to send AT+BLEGETADDR command to BLE module
 */
#define BLE_GENERIC_BLEGETADDR_SEND \
        SDEP_AT_CMD_SEND(0x0D, atBleGetAddr)

/*!
 * Macro to send AT+BLEGETPEERADDR command to BLE module
 *
 * TODO: This command's payload is > 16 bytes
 */
#define BLE_GENERIC_BLEGETPEERADDR_SEND \
        SDEP_AT_CMD_SEND(0x11, atBleGetPeerAddr)

/*!
 * Macro to send AT+BLEGETRSSI command to BLE module
 */
#define BLE_GENERIC_BLEGETRSSI_SEND \
        SDEP_AT_CMD_SEND(0x0D, atBleGetRssi)

/*!
 * Macro to send AT+BLEUARTX command to BLE module
 */
#define BLE_SERVICE_BLEUARTTX_SEND \
        SDEP_AT_CMD_SEND(0x0C, atBleUartTx)

/*!
 * Macro to send AT+BLEUARTTXF command to BLE module
 */
#define BLE_SERVICE_BLEUARTTXF_SEND \
        SDEP_AT_CMD_SEND(0x0D, atBleUartTxF)

/*!
 * Macro to send AT+BLEUARTRX command to BLE module
 */
#define BLE_SERVICE_BLEUARTRX_SEND \
        SDEP_AT_CMD_SEND(0x0C, atBLeUartRx)

/*!
 * Macro to send AT+BLEUARTFIFO command to BLE module
 */
#define BLE_SERVICE_BLEUARTFIFO_SEND \
        SDEP_AT_CMD_SEND(0x0E, atBleUartFifo)

/*!
 * Macro to send AT+BLEKEYBOARDEN command to BLE module
 */
#define BLE_SERVICE_BLEKEYBOARDEN_SEND \
        SDEP_AT_CMD_SEND(0x10, atBleKeyboardEn)

/*!
 * Macro to send AT+BLEKEYBOARD command to BLE module
 */
#define BLE_SERVICE_BLEKEYBOARD_SEND \
        SDEP_AT_CMD_SEND(0x0E, atBleKeyboard)

/*!
 * Macro to send AT+BLEKEYBOARDCODE command to BLE module
 * 
 * TODO: This command's payload is > 16 bytes.
 */
#define BLE_SERVICE_BLEKEYBOARDCODE_SEND \
        SDEP_AT_CMD_SEND(0x12, atBleKeyboardCode)

/*!
 * Macro to send AT+BLEHIDEN command to BLE module
 */
#define BLE_SERVICE_BLEHIDEN_SEND \
        SDEP_AT_CMD_SEND(0x0B, atBleHidEn)

/*!
 * Macro to send AT+BLEHIDMOUSEMOVE command to BLE module
 * 
 * TODO: This command's payload is > 16 bytes.
 */
#define BLE_SERVICE_BLEHIDMOUSEMOVE_SEND \
        SDEP_AT_CMD_SEND(0x12, atBleHidMouseMove)

/*!
 * Macro to send AT+BLEHIDMOUSEBUTTON command to BLE module
 * 
 * TODO: This command's payload is > 16 bytes.
 */
#define BLE_SERVICE_BLEHIDMOUSEBUTTON_SEND \
        SDEP_AT_CMD_SEND(0x14, atBleHidMouseButton)

/*!
 * Macro to send AT+BLEHIDCONTROLKEY command to BLE module
 * 
 * TODO: This command's payload is > 16 bytes.
 */
#define BLE_SERVICE_BLEHIDCONTROLKEY_SEND \
        SDEP_AT_CMD_SEND(0x13, atBleHidControlKey)

/*!
 * Macro to send AT+BLEHIDGAMEPADEN command to BLE module
 * 
 * TODO: This command's payload is > 16 bytes.
 */
#define BLE_SERVICE_BLEHIDGAMEPADEN_SEND \
        SDEP_AT_CMD_SEND(0x12, atBleHidGamePadEn)

/*!
 * Macro to send AT+BLEHIDGAMEPAD command to BLE module
 */
#define BLE_SERVICE_BLEHIDGAMEPAD_SEND \
        SDEP_AT_CMD_SEND(0x10, atBleHidGamePad)

/*!
 * Macro to send AT+BLEMIDIEN command to BLE module
 */
#define BLE_SERVICE_BLEMIDIEN_SEND \
        SDEP_AT_CMD_SEND(0x0C, atBleMidiEn)

/*!
 * Macro to send AT+BLEMIDIRX command to BLE module
 */
#define BLE_SERVICE_BLEMIDIRX_SEND \
        SDEP_AT_CMD_SEND(0x0C, atBleMidiRx)

/*!
 * Macro to send AT+BLEMIDITX command to BLE module
 */
#define BLE_SERVICE_BLEMIDITX_SEND \
        SDEP_AT_CMD_SEND(0x0C, atBleMidiTx)

/*!
 * Macro to send AT+BLEBATTEN command to BLE module
 */
#define BLE_SERVICE_BLEBATTEN_SEND \
        SDEP_AT_CMD_SEND(0x0C, atBleBattEn)

/*!
 * Macro to send AT+BLEBATTVAL command to BLE module
 */
#define BLE_SERVICE_BLEBATTVAL_SEND \
        SDEP_AT_CMD_SEND(0x0D, atBleBattVal)

/*!
 * Macro to send AT+GAPCONNECTABLE command to BLE module
 * 
 * TODO: This command's payload is > 16 bytes.
 */
#define BLE_GAP_GAPCONNECTABLE_SEND \
        SDEP_AT_CMD_SEND(0x11, atGapConnectAble)

/*!
 * Macro to send AT+GAPGETCONN command to BLE module
 */
#define BLE_GAP_GAPGETCONN_SEND \
        SDEP_AT_CMD_SEND(0x0D, atGapGetConn)

/*!
 * Macro to send AT+GAPDISCONNECT command to BLE module
 */
#define BLE_GAP_GAPDISCONNECT_SEND \
        SDEP_AT_CMD_SEND(0x10, atGapDisconnect)

/*!
 * Macro to send AT+GAPDEVNAME command to BLE module
 */
#define BLE_GAP_GAPDEVNAME_SEND \
        SDEP_AT_CMD_SEND(0x0D, atGapDevName)

/*!
 * Macro to send AT+GAPDELBONDS command to BLE module
 */
#define BLE_GAP_GAPDELBONDS_SEND \
        SDEP_AT_CMD_SEND(0x0E, atGapDelBonds)

/*!
 * Macro to send AT+GAPINTERVALS command to BLE module
 */
#define BLE_GAP_GAPINTERVALS_SEND \
        SDEP_AT_CMD_SEND(0x0F, atGapIntervals)

/*!
 * Macro to send AT+GAPSTARTADV command to BLE module
 */
#define BLE_GAP_GAPSTARTADV_SEND \
        SDEP_AT_CMD_SEND(0x0E, atGapStartAdv)

/*!
 * Macro to send AT+GAPSTOPADV command to BLE module
 */
#define BLE_GAP_GAPSTOPADV_SEND \
        SDEP_AT_CMD_SEND(0x0D, atGapStopAdv)

/*!
 * Macro to send AT+GAPSETADVDATA command to BLE module
 */
#define BLE_GAP_GAPSETADVDATA_SEND \
        SDEP_AT_CMD_SEND(0x10, atGapSetAdvData)

/*!
 * Macro to send AT+GATTCLEAR command to BLE module
 */
#define BLE_GATT_GATTCLEAR_SEND \
        SDEP_AT_CMD_SEND(0x0C, atGattClear)

/*!
 * Macro to send AT+GATTADDSERVICE command to BLE module
 * 
 * TODO: This command's payload is > 16 bytes.
 */
#define BLE_GATT_GATTADDSERVICE_SEND \
        SDEP_AT_CMD_SEND(0x11, atGattAddService)

/*!
 * Macro to send AT+GATTADDCHAR command to BLE module
 */
#define BLE_GATT_GATTADDCHAR_SEND \
        SDEP_AT_CMD_SEND(0x0E, atGattAddChar)

/*!
 * Macro to send AT+GATTCHAR command to BLE module
 */
#define BLE_GATT_GATTCHAR_SEND \
        SDEP_AT_CMD_SEND(0x0B, atGattChar)

/*!
 * Macro to send AT+GATTLIST command to BLE module
 */
#define BLE_GATT_GATTLIST_SEND \
        SDEP_AT_CMD_SEND(0x0B, atGattList)

/*!
 * Macro to send AT+GATTCHARRAW command to BLE module
 */
#define BLE_GATT_GATTCHARRAW_SEND \
        SDEP_AT_CMD_SEND(0x0E, atGattCharRaw)

/*!
 * Macro to send AT+DBGMEMRD command to BLE module
 */
#define BLE_DBG_DBGMEMRD_SEND \
        SDEP_AT_CMD_SEND(0x0B, atDbgMemRd)

/*!
 * Macro to send AT+DBGNVMRD command to BLE module
 */
#define BLE_DBG_DBGNVMRD_SEND \
        SDEP_AT_CMD_SEND(0x0B, atDbgNvmRd)

/*!
 * Macro to send AT+DBGSTACKSIZE command to BLE module
 */
#define BLE_DBG_DBGSTACKSIZE_SEND \
        SDEP_AT_CMD_SEND(0x0F, atDbgStackSize)

/*!
 * Macro to send AT+DBGSTACKDUMP command to BLE module
 */
#define BLE_DBG_DBGSTACKDUMP_SEND \
        SDEP_AT_CMD_SEND(0x0F, atDbgStackDump)

// TODO: Implement ISR macro for SPI interrupts

#endif // _BLE_H_
