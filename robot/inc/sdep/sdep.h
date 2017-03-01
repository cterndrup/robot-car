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

#define SDEP_MAX_PAYLOAD_LEN            (0x0010)

/* ------------------------ STRUCT DEFINITION ------------------------------- */

typedef struct SDEP_MSG
{
    // Message header
    struct hdr
    {
        // Type of SDEP msg
        uint8_t  msgtype;
    
        // msgid (command, alert, or error)
        union msgid
        {
            uint16_t cmdid;
            uint16_t alertid;
            uint16_t errorid;
        };
    
        // Length of the payload byte (or rsvd in case of error msg)
        uint8_t payloadLen;
    };

    // Message payload
    uint8_t payload[SDEP_MAX_PAYLOAD_LEN];
} SDEP_MSG;

/* ------------------------ FUNCTION PROTOTYPES ----------------------------- */

/*!
 * Sends an SDEP_MSG
 *
 * @param[in/out] pMsg  Pointer to the SDEP_MSG to send
 */
void sdepMsgSend(SDEP_MSG *pMsg);

/*!
 * Receives an SDEP_MSG
 *
 * @param[in/out] pMsg  Pointer to an SDEP_MSG populated from the receival
 *
 * @note This function should only be called when it is known data is available
 *       on the BLE module
 */
void sdepMsgRecv(SDEP_MSG *pMsg);

#endif // _SDEP_H_
