/* Implementation file for Simple Data Exchange Protocol (SDEP) */

/* ------------------------ INCLUDES ---------------------------------------- */
#include "sdep/sdep.h"
#include "spi/spi.h"
#include "common/utils.h"

/* ------------------------ GLOBAL VARIABLES -------------------------------- */

/*!
 * Semaphore for synchronizing access to below buffers
 */
semaphore_t sdepBufferSemaphore = 0;

/*!
 * SDEP_MSG buffers into which incoming SDEP messages are placed by the BLE
 * interrupt handler
 */
SDEP_MSG_BUFFER sdepIRQBuffer;
SDEP_MSG_BUFFER sdepRespBuffer;
SDEP_MSG_BUFFER sdepAlertBuffer;
SDEP_MSG_BUFFER sdepErrorBuffer;

/* ------------------------ STATIC FUNCTIONS -------------------------------- */

/*!
 * Performs a deep copy from SDEP_MSG pointed to by pSrc to SDEP_MSG pointed
 * to by pDest
 *
 * @param[in/out] pDest     Pointer to destination SDEP_MSG
 * @param[in/out] pSrc      Pointer to source SDEP_MSG
 */
void
_sdepMsgCopy(SDEP_MSG *pDest, SDEP_MSG *pSrc)
{
    // Copy hdr
    pDest->hdr.msgtype    = pSrc->hdr.msgtype;
    pDest->hdr.msgid      = pSrc->hdr.msgid;
    pDest->hdr.payloadLen = pSrc->hdr.payloadLen;

    // Copy message payload
    uint8_t i;
    for (i = 0; i < SDEP_MAX_PAYLOAD_LEN; ++i)
    {
        pDest->payload[i] = pSrc->payload[i];
    }
}

/* ------------------------ FUNCTION DEFINITIONS ---------------------------- */

/*!
 * @ref sdep.h for function documentation
 */
void
sdepMsgSend(SDEP_MSG *pMsg)
{
    uint8_t  lsb    = pMsg->hdr.msgid.cmdid & 0xff;
    uint8_t  msb    = pMsg->hdr.msgid.cmdid >> 8;
    uint8_t  len    = pMsg->hdr.payloadLen & ~(1 << 7);
    uint8_t *pByte  = &pMsg->payload[0];

    spiMasterSendByte(pMsg->hdr.msgtype, NULL);
    spiMasterSendByte(lsb, NULL);
    spiMasterSendByte(msb, NULL);
    spiMasterSendByte(pMsg->hdr.payloadLen, NULL);

    // Send payload
    uint8_t i;
    for (i = 0; i < len; ++i)
    {
        spiMasterSendByte(*pByte, NULL);
        ++pByte;
    }
    spiMasterSendDone();
}

/*!
 * @ref sdep.h for function documentation
 */
void
sdepMsgRecv(SDEP_MSG *pMsg)
{
    uint8_t  lsb;
    uint8_t  msb;
    uint8_t  len;
    uint8_t *pByte = &pMsg->payload[0];

    // Receive header
    pMsg->hdr.msgtype    = spiMasterRecvByte();
    lsb                  = spiMasterRecvByte();
    msb                  = spiMasterRecvByte();
    pMsg->hdr.payloadLen = spiMasterRecvByte();

    pMsg->hdr.msgid.cmdid = ((uint16_t)msb << 8) | lsb;

    if (pMsg->hdr.msgtype == SDEP_MSGTYPE_ERROR) return;

    // Receive payload
    len = pMsg->hdr.payloadLen & ~(1 << 7);
    uint8_t i;
    for (i = 0; i < len; ++i)
    {
        *pByte = spiMasterRecvByte();
        ++pByte;
    }
}

/*!
 * @ref sdep.h for function documentation
 */
uint8_t
sdepRespCollect(void)
{
    uint8_t i = 0;
    uint8_t moreData;

    do {
        sdepMsgRecv(&sdepIRQBuffer.buffer[i]);
        moreData = sdepIRQBuffer.buffer[i].hdr.payloadLen & (1 << 7);
        ++i;
    } while (moreData && i < SDEP_MAX_MSG_BUFFER_LEN);

    sdepIRQBuffer.numMsgs = i;

    return sdepIRQBuffer.buffer[0].hdr.msgtype;
}

/*!
 * @ref sdep.h for function documentation
 */
void
sdepResponseMsgHandler(void)
{
    uint8_t len = sdepIRQBuffer.numMsgs;
    sdepRespBuffer.numMsgs = len;

    // Copy the data from the IRQ's resp buffer into the sdepRespBuffer
    uint8_t i;
    for (i = 0; i < len; ++i)
    {
        _sdepMsgCopy(&sdepRespBuffer.buffer[i], &sdepIRQBuffer.buffer[i]);
    }
}

/*!
 * @ref sdep.h for function documentation
 */
void
sdepAlertMsgHandler(void)
{
    uint8_t len = sdepIRQBuffer.numMsgs;
    sdepAlertBuffer.numMsgs = len;

    // Copy the data from the IRQ's resp buffer into the sdepAlertBuffer
    uint8_t i;
    for (i = 0; i < len; ++i)
    {
        _sdepMsgCopy(&sdepAlertBuffer.buffer[i], &sdepIRQBuffer.buffer[i]);
    }

    /* TODO: implement alert handling
    // Extract alert id from the alert buffer
    uint16_t alertid = sdepAlertBuffer.buffer[i].hdr.alertid;

    switch (alertid)
    {
        case SDEP_ALERTID_RSVD:
            // Reserved for future use
            break;
        case SDEP_ALERTID_SYS_RESET:
            // BLE module about to undergo sys reset
            break;
        case SDEP_ALERTID_BATTERY_LOW:
            // Battery level of BLE module is low
            break;
        case SDEP_ALERTID_BATTERY_CRITICIAL:
            // Battery level of BLE module is very low
            break;
    }
    */
}

/*!
 * @ref sdep.h for function documentation
 */
void
sdepErrorMsgHandler(void)
{
    uint8_t len = sdepIRQBuffer.numMsgs;
    sdepErrorBuffer.numMsgs = len;

    // Copy the data from the IRQ's resp buffer into the sdepErrorBuffer
    uint8_t i;
    for (i = 0; i < len; ++i)
    {
        _sdepMsgCopy(&sdepErrorBuffer.buffer[i], &sdepIRQBuffer.buffer[i]);
    }

    /* TODO: implement error handling
    // Extract errorid from the error buffer
    uint16_t errorid = sdepErrorBuffer.buffer[i].hdr.errorid;

    switch (errorid)
    {
        case SDEP_ERRORID_RSVD:
            // Reserved for future use
            break;
        case SDEP_ERRORID_INVALID_CMDID:
            // Invalid cmd id sent to BLE module
            break;
        case SDEP_ERRORID_INVALID_PAYLOAD:
            // Invalid payload sent to BLE module
            break;
    }
    */
}
