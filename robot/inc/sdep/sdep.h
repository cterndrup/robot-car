/* Header file for Simple Data Exchange Protocol (SDEP) */

#ifndef _SDEP_H_
#define _SDEP_H_

/* ------------------------ INCLUDES ---------------------------------------- */

/* ------------------------ MACROS AND DEFINES ------------------------------ */
#define SDEP_MSGTYPE_CMD                (0x10)
#define SDEP_MSGTYPE_RESPONSE           (0x20)
#define SDEP_MSGTYPE_ALERT              (0x40)
#define SDEP_MSGTYPE_ERROR              (0x80)

#define SDEP_CMDTYPE_INITIALIZE         (0xBEEF)
#define SDEP_CMDTYPE_AT_WRAPPER         (0x0A00)
#define SDEP_CMDTYPE_BLE_UARTTX         (0x0A01)
#define SDEP_CMDTYPE_BLE_UARTRX         (0x0A02)

#define SDEP_ALERTID_RSVD               (0x0000)
#define SDEP_ALERTID_SYS_RESET          (0x0001)
#define SDEP_ALERTID_BATTERY_LOW        (0x0002)
#define SDEP_ALERTID_BATTERY_CRITICAL   (0x0003)

#define SDEP_ERRORID_RSVD               (0x0000)
#define SDEP_ERRORID_INVALID_CMDID      (0x0001)
#define SDEP_ERRORID_INVALID_PAYLOAD    (0x0003)

// TODO: Modify to handle commands w/ payloads > 16 bytes
/*!
 * Macro to send an SDEP command to the BLE module
 *
 * @param[in] length    The length of the payload, in bytes
 * @param[in] payload   A pointer to a character string representing the payload
 */
#define SDEP_AT_CMD_SEND(length, payload) \
        do { \
            /* Send SDEP header */ \
            spiMasterSend(SDEP_MSGTYPE_CMD); \
            spiMasterSend(0x00); \
            spiMasterSend(0x0A); \
            spiMasterSend(length); \
            /* Send SDEP payload */ \
            char *letter = payload; \
            while (letter != '\0') \
            { \
                spiMasterSend(*letter); \
                letter++; \
            } \
            /* Terminate the send */ \
            spiMasterTerminate(); \
        } while (0)
               

#endif // _SDEP_H_
