/* Header file for Bluetooth Low Energy Generic ATTribute Profile (GATT) */

#ifndef _BLE_GATT_H_
#define _BLE_GATT_H_

/* ------------------------ GLOBAL VARIABLES -------------------------------- */

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

/* ------------------------ MACROS AND DEFINES ------------------------------ */

/*!
 * GATT specific definitinons
 */
#define BLE_GATT_MAX_SERVICES                10
#define BLE_GATT_MAX_CHARACTERISTICS         30
#define BLE_GATT_MAX_CHARACTERISTIC_BUF_SIZE 32
#define BLE_GATT_MAX_CCDS                    16

/* ------------------------ TYPEDEFS ---------------------------------------- */

/*!
 * Clears any custom BLE GATT services and characterstics defined on the module
 *
 * @param[in/out] pBLE      Pointer to the BLE object
 */
typedef void BleGattClear(BLE *pBLE);

/*!
 * Lists all custom GATT services and characteristics that have been defined
 * on the device
 *
 * @param[in/out] pBLE      Pointer to the BLE object
 */
typedef void BleGattList(BLE *pBLE);

#endif // _BLE_GATT_H_
