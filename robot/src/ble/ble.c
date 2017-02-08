/*! Implementation file for Bluetooth Low Energy code */

/* ------------------------ SYSTEM INCLUDES --------------------------------- */

/* ------------------------ APPLICATION INCLUDES ---------------------------- */
#include "spi/spi.h"
#include "sdep/sdep.h"
#include "ble/ble.h"
#include "common/utils.h"

/* ------------------------ FUNCTION DEFINITIONS  --------------------------- */

/*!
 * Fetch the next BLE_CMD_SEND_STATE given the current state and state
 * variables
 *
 * @param[in] nextState     the current BLE_CMD_SEND_STATE
 * @param[in] bytesSent     the number of bytes sent in the current packet
 * @param[in] baseDone      boolean indicating whether the base string has been
 *                          fully sent
 * @param[in] modeDone      boolean indicating whether the mode string has been
 *                          fully sent
 * @param[in] payloadDone   boolean indicating whether the payload string has
 *                          been fully sent
 *
 * @return    the next state to traverse to in the state machine
 */
static BLE_CMD_SEND_STATE
_bleCmdSendNextState
(
    BLE_CMD_SEND_STATE nextState,
    uint8_t            bytesSent,
    bool               baseDone,
    bool               modeDone,
    bool               payloadDone
)
{
    BLE_CMD_SEND_STATE next;
    switch (nextState)
    {
        case INIT:
        {
            next = SEND_HDR;
            break;
        }
        case SEND_HDR:
        {
            next = SEND_BASE;
            break;
        }
        case SEND_BASE:
        {
            if (!baseDone && bytesSent < 16)
            {
                next = SEND_BASE;
            }
            else if (!baseDone && bytesSent == 16)
            {
                next = SEND_HDR;
            }
            else // if (baseDone)
            {
                next = SEND_MODE;
            }
            break;
        }
        case SEND_MODE:
        {
            if (!modeDone && bytesSent < 16)
            {
                next = SEND_MODE;
            }
            else if (!modeDone && bytesSent == 16)
            {
                next = SEND_HDR;
            }
            else // if (modeDone)
            {
                next = SEND_PAYLOAD;
            }
            break;
        }
        case SEND_PAYLOAD:
        {
            if (!payloadDone && bytesSent < 16)
            {
                next = SEND_PAYLOAD;
            }
            else if (!payloadDone && bytesSent == 16)
            {
                next = SEND_HDR;
            }
            else // if (payloadDone)
            {
                next = DONE;
            }
            break;
        }
        case DONE:
    }

    return next;
}

/*!
 * @ref ble.h for function documentation
 */
void
bleCmdSend
(
    uint8_t          length,
    const char      *pBase,
    const char      *pMode,
    const char      *pPayload
)
{
    char *pByte = pBase; 
    char *pLoad = pPayload;
    char *pM    = pMode;

    bool    done        = false;
    bool    baseDone    = false;
    bool    modeDone    = false;
    bool    payloadDone = false;
    uint8_t bytesSent   = 0;
    BLE_CMD_SEND_STATE nextState = INIT;

    while (!done)
    {
        // Update next state given current state
        nextState = _bleCmdSendNextState(nextState, bytesSent, baseDone, 
                                         modeDone, payloadDone); 

        switch (nextState)
        {
            case INIT:
            case SEND_HDR:
            {
                bytesSent = 0;
                spiMasterSendByte(SDEP_MSGTYPE_CMD);
                spiMasterSendByte(0x00);
                spiMasterSendByte(0x0A);
                spiMasterSendByte(length);
                bytesSent += 4;
                break;
            }
            case SEND_BASE:
            {
                if (!baseDone)
                {
                    spiMasterSendByte(*pByte);
                    bytesSent++;
                    pByte++;
                    if (pByte == '\0') baseDone = true;
                }
                break;
            }
            case SEND_MODE:
            {
                if (!modeDone)
                {
                    spiMasterSendByte(*pM);
                    bytesSent++;
                    pM++;
                    if (pM == '\0') modeDone = true;
                }
                break;
            }
            case SEND_PAYLOAD:
            {
                if (!payloadDone)
                {
                    spiMasterSendByte(*pLoad);
                    bytesSent++;
                    pLoad++;
                    if (pLoad == '\0') payloadDone = true;
                }
                break;
            }
            case DONE:
            {
                done = true;
            }
        }
    }
}
