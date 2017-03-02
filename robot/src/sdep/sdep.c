/* Implementation file for Simple Data Exchange Protocol (SDEP) */

/* ------------------------ INCLUDES ---------------------------------------- */
#include "sdep/sdep.h"
#include "spi/spi.h"

/* ------------------------ GLOBAL VARIABLES -------------------------------- */

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
    for (int i = 0; i < SDEP_MAX_PAYLOAD_LEN; ++i)
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
    uint8_t *pByte  = &(pMsg->payload[0]);

    spiMasterSendByte(pMsg->hdr.msgtype);
    spiMasterSendByte(lsb);
    spiMasterSendByte(msb);
    spiMasterSendByte(pMsg->hdr.payloadLen);

    // Send payload
    for (uint8_t i = 0; i < len; ++i)
    {
        spiMasterSendByte(*pByte);
        ++pByte;
    }
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
    spiMasterRecv(&pMsg->hdr.msgtype);
    spiMasterRecv(&lsb);
    spiMasterRecv(&msb);
    spiMasterRecv(&pMsg->hdr.payloadLen);

    pMsg->hdr.msgid.cmdid = ((uint16_t)msb << 8) | lsb;

    if (pMsg->hdr.msgtype == SDEP_MSG_ERROR) return;

    // Receive payload
    len = pMsg->hdr.payloadLen & ~(1 << 7);
    for (uint8_t i = 0; i < len; ++i)
    {
        spiMasterRecv(pByte);
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
        moreData = sdepIRQBuffer.buffer[i].payloadLen & (1 << 7);
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
    for (uint8_t i = 0; i < len; ++i)
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
    for (uint8_t i = 0; i < len; ++i)
    {
        _sdepMsgCopy(&sdepAlertBuffer.buffer[i], &sdepIRQBuffer.buffer[i]);
    }

    // TODO: complete implementation
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
    for (uint8_t i = 0; i < len; ++i)
    {
        _sdepMsgCopy(&sdepErrorBuffer.buffer[i], &sdepIRQBuffer.buffer[i]);
    }

    // TODO: complete implementation
}
