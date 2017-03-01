/* Header file for Bluetooth Low Energy Generic Access Profile (GAP) */

#ifndef _BLE_GAP_H_
#define _BLE_GAP_H_

/* ------------------------ GLOBAL VARIABLES -------------------------------- */

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

#endif // _BLE_GAP_H_