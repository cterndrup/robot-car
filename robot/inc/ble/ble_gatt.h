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

#define BLE_GATT_MAX_SERVICES                (10)
#define BLE_GATT_MAX_CHARACTERISTICS         (30)
#define BLE_GATT_MAX_CHARACTERISTIC_BUF_SIZE (32)
#define BLE_GATT_MAX_CCDS                    (16)

// NOTE: This is set somewhat arbitrarily, and does not reflect a requirement
#define BLE_GATT_NUM_CHAR_PER_SERVICE        (3)

#define BLE_GATT_CHAR_UUID_LEN               (7)
#define BLE_GATT_CHAR_PROPERTIES_LEN         (5)
#define BLE_GATT_CHAR_VALUE_MIN_LEN          (3)
#define BLE_GATT_CHAR_VALUE_MAX_LEN          (3)
#define BLE_GATT_CHAR_VALUE_LEN              (21)
#define BLE_GATT_CHAR_INDEX_LEN              (3)

#define BLE_GATT_CHAR_PROP_READ              (0x02)
#define BLE_GATT_CHAR_PROP_WRITE             (0x04)
#define BLE_GATT_CHAR_PROP_WRITE_NO_RESP     (0x08)
#define BLE_GATT_CHAR_PROP_NOTIFY            (0x10)
#define BLE_GATT_CHAR_PROP_INDICATE          (0x020)

#define BLE_GATT_SERVICE_UUID_LEN            (7)
#define BLE_GATT_SERVICE_UUID128_LEN         (48)
#define BLE_GATT_SERVICE_INDEX_LEN           (3)

/* ------------------------ TYPEDEFS ---------------------------------------- */

/*!
 * Type definition for Bluetooth LE characteristic
 * Universally Unique Identifier (UUID)
 */
typedef char ble_char_uuid[BLE_GATT_CHAR_UUID_LEN];

/*!
 * Type definition for Bluetooth LE characteristic properties
 */
typedef char ble_char_properties[BLE_GATT_CHAR_PROPERTIES_LEN];

/*!
 * Type definition for Bluetooth LE characteristic value size min and max
 */
typedef char ble_char_value_min_len[BLE_GATT_CHAR_VALUE_MIN_LEN];
typedef char ble_char_value_max_len[BLE_GATT_CHAR_VALUE_MAX_LEN];

/*!
 * Type definition for Bluetooth LE characteristic value
 */
typedef char ble_char_value[BLE_GATT_CHAR_VALUE_LEN];

/*!
 * Type definition for Bluetooth LE characteristic index
 */
typedef char ble_char_index[BLE_GATT_CHAR_INDEX_LEN];

/*!
 * Type definition for Bluetooth LE service UUID (16-bit)
 */
typedef char ble_service_uuid[BLE_GATT_SERVICE_UUID_LEN];

/*!
 * Type definition for Bluetooth LE service UUID (128-bit)
 */
typedef char ble_service_uuid128[BLE_GATT_SERVICE_UUID128_LEN];

/*!
 * Type definition for Bluetooth LE service index
 */
typedef char ble_service_index[BLE_GATT_SERVICE_INDEX_LEN];

/*!
 * Type definition for Bluetooth LE characteristic update handler
 */
typedef void (*ble_char_update_handler)(void);

/*!
 * Structure representing a Bluetooth LE GATT characteristic
 */
typedef struct BLE_GATT_CHAR
{
    uint8_t                 numIndex;
    ble_char_index          index;

    ble_char_uuid           uuid;
    ble_char_properties     properties;    

    ble_char_value_min_len  minLen;
    ble_char_value_max_len  maxLen;

    ble_char_value          value;

    ble_char_update_handler handler;
} BLE_GATT_CHAR;

/*!
 * Structure representing a Bluetooth LE GATT service
 */
typedef struct BLE_GATT_SERVICE
{
    uint8_t           numIndex;
    ble_service_index index;

    union uuid
    {
        ble_service_uuid    uuid16;
        ble_service_uuid128 uuid128;
    } uuid;

    uint8_t       numCharacteristics;
    BLE_GATT_CHAR characteristics[BLE_GATT_NUM_CHAR_PER_SERVICE];
} BLE_GATT_SERVICE;

#endif // _BLE_GATT_H_
