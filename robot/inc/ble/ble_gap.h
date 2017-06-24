/* Header file for Bluetooth Low Energy Generic Access Profile (GAP) */

#ifndef _BLE_GAP_H_
#define _BLE_GAP_H_

/* ------------------------ INCLUDES ---------------------------------------- */
#include "common/utils.h"

/* ------------------------ MACROS AND DEFINES ------------------------------ */

/*!
 * Sets whether BLE module can be connected to by other BLE enabled devices
 *
 * @param[in/out] pBle          Pointer to the BLE object
 * @param[in]     connectable   true to set device to connectable; else false
 */
typedef void BleGapConnStatusSet(BLE *pBLE, bool connectable);

/*!
 * Gets the connection status for the BLE module
 *
 * @param[in/out] pBle      Pointer to the BLE object
 */
typedef void BleGapConnStatusGet(BLE *pBLE);

/*!
 * Disconnects from any devices to which BLE module currently has connection
 *
 * @param[in/out] pBle      Pointer to the BLE object
 */
typedef void BleGapDisconnect(BLE *pBLE);

/*!
 * Sets the BLE module's device name
 *
 * @param[in/out] pBle   Pointer to the BLE object
 * @param[in]     name   c-string representing the device name
 */
typedef void BleGapDeviceNameSet(BLE *pBLE, const char *name);

/*!
 * Gets the BLE module's device name
 *
 * @param[in/out] pBle      Pointer to the BLE object
 */
typedef void BleGapDeviceNameGet(BLE *pBLE);

/*!
 * Start advertising services, etc.
 *
 * @param[in/out] pBle      Pointer to the BLE object
 */
typedef void BleGapAdvStart(BLE *pBLE);

/*!
 * Stop advertising services, etc.
 *
 * @param[in/out] pBle      Pointer to the BLE object
 */
typedef void BleGapAdvStop(BLE *pBLE);

#endif // _BLE_GAP_H_
