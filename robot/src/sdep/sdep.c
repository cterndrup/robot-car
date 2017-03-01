/* Implementation file for Simple Data Exchange Protocol (SDEP) */

/* ------------------------ INCLUDES ---------------------------------------- */
#include "sdep/sdep.h"
#include "spi/spi.h"

/* ------------------------ FUNCTION DEFINITIONS ---------------------------- */

/*!
 * @ref sdep.h for function documentation
 */
void
sdepMsgSend(SDEP_MSG *pMsg)
{
    uint8_t  lsb    = 0xff & pMsg->hdr.msgid.cmdid;
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
