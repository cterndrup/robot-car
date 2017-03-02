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

    do
    {
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
        sdepRespBuffer.buffer[i] = sdepIRQBuffer.buffer[i];
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
        sdepAlertBuffer.buffer[i] = sdepIRQBuffer.buffer[i];
    }
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
        sdepErrorBuffer.buffer[i] = sdepIRQBuffer.buffer[i];
    }
}
