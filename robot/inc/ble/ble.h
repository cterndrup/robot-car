/* Header file for Bluetooth Low Energy code */

#ifndef _BLE_H_
#define _BLE_H_

/* ----------------------- INCLUDES ----------------------------------------- */

/* ----------------------- MACROS AND DEFINES ------------------------------- */

/*!
 * MCU I/O pin corresponding to BLE module's IRQ pin
 */
#define BLE_PORT PORTD
#define BLE_IRQ  2
#define BLE_vect INT2_vect

/*!
 * Definition of empty BLE command payload
 */
#define BLE_CMD_EMPTY_PAYLOAD           (&bleCmdEmptyPayload[0])

/* ------------------------ TYPEDEFS ---------------------------------------- */

/*!
 * Forward declaration of BLE object
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

/*!
 * Constructor for the BLE object
 *
 * @param[in/out] pBLE  Pointer to the Bluetooth LE object
 */
typedef void BleConstruct(BLE *pBLE);

/*!
 * Initialization method for the BLE object
 *
 * @param[in/out] pBLE  Pointer to the Bluetooth LE object
 */
typedef void BleInitialize(BLE *pBLE);

/*!
 * Configures the BLE GATT services offered by the BLE object
 *
 * @param[in/out] pBLE  Pointer to the Bluetooth LE object
 */
typedef void BleServicesConfigure(BLE *pBLE);

/*!
 * Updates a BLE GATT characteristic configured for the BLE object
 *
 * @param[in/out] pBLE  Pointer to the Bluetooth LE object
 * @param[in/out] pChar Pointer to BLE GATT characteristic to update
 */
typedef void BleCharacteristicUpdate(BLE *pBLE, BLE_GATT_CHAR *pChar);

/* ------------------------ STRUCT DEFINITION ------------------------------- */

/*!
 * Definition of the Bluetooth Low Energy object
 */
struct BLE
{
    // BLE services
    BLE_GATT_SERVICE         services[BLE_GATT_MAX_SERVICES];

    // BLE generic methods
    BleInitialize           *bleInitialize;

    // BLE Services methods
    BleServicesConfigure    *bleServicesConfigure;

    // BLE Characteristics methods
    BleCharacteristicUpdate *bleCharacteristicUpdate;
};

/* ------------------------ FUNCTION PROTOTYPES ----------------------------- */

// BLE generic methods
BleConstruct            bleConstruct;
BleInitialize           bleInitialize;

// BLE services methods
BleServicesConfigure    bleServicesConfigure;

// BLE Characteristics methods
BleCharacteristicUpdate bleCharacteristicUpdate;

#endif // _BLE_H_
