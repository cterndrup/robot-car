/*! Implementation file for Bluetooth Low Energy code */

/* ------------------------ SYSTEM INCLUDES --------------------------------- */
#include <avr/io.h>
#include <avr/interrupt.h>

/* ------------------------ APPLICATION INCLUDES ---------------------------- */
#include "spi/spi.h"
#include "sdep/sdep.h"
#include "ble/ble.h"
#include "common/utils.h"

/* ------------------------ FUNCTION DEFINITIONS ---------------------------- */

/* ------------------------ STATIC FUNCTIONS -------------------------------- */

/*!
 * Registers module's external interrupts with MCU
 */
static void
_bleIRQRegister(void)
{
    // Set BLE_IRQ pin to input
    SET_PORT_BIT_INPUT(DDRD, BLE_IRQ);

    // Clear interrupt flags for BLE_IRQs before setting sense control bits
    CLEAR_BIT(EIMSK, BLE_IRQ);

    // Set sense control bits to trigger interrupts on rising edge trigger
    SET_BIT(EICRA, ISC20);
    SET_BIT(EICRA, ISC21);

    // Clear interrupt flag bits (by writing 1) before enable interrupts
    SET_BIT(EIFR, BLE_IRQ);

    // Enables external interrupt on BLE_IRQ pin
    SET_BIT(EIMSK, BLE_IRQ);
}

/*!
 * Sends AT-commands to the BLE module
 *
 * @param[in] atCommand   c-string representing an AT command to send to BLE
 * @param[in] payload     c-string representing the payload of the AT command
 */
static void
_bleCmdSend
(
    const char    *atCommand,
    const char    *payload,
    SDEP_CMD_MODE  cmdMode
)
{
    SDEP_MSG  msg;
    char     *p;
    char      fullPayload[SDEP_MAX_FULL_MSG_LEN];
    uint8_t   len = 0;

    msg.hdr.msgtype     = SDEP_MSGTYPE_CMD;
    msg.hdr.msgid.cmdid = SDEP_CMDTYPE_AT_WRAPPER;

    p = atCommand;
    while (p != NULL && *p != '\0')
    {
        fullPayload[len] = *p;
        ++p;
        ++len;
    }

    switch (cmdMode)
    {
        case TEST:
            fullPayload[len++] = '=';
            fullPayload[len++] = '?';
            break;
        case WRITE:
            fullPayload[len++] = '=';
            break;
        case READ:
            fullPayload[len++] = '?';
        case EXEC:
            break;
    }

    p = payload;
    while (len < SDEP_MAX_FULL_MSG_LEN && p != NULL && *p != '\0')
    {
        fullPayload[len] = *p;
        ++p;
        ++len;
    }
    fullPayload[len] = '\0';

    // Send SDEP_MSGs corresponding to BLE command
    p = &fullPayload[0];
    while (len > 0)
    {
        // Write payload
        uint8_t payloadLen = 0;
        for (uint8_t i = 0;
             p != NULL && *p != '\0' && i < MAX_PAYLOAD_LEN; ++i)
        {
            msg.payload[i] = (uint8_t)(*p);
            ++p;
            ++payloadLen;
        }

        // Send message
        msg.hdr.payloadLen = (len > 16) ? ((1 << 7) | payloadLen) : payloadLen;
        sdepMsgSend(&msg);

        len -= payloadLen;
    }
}

/* ------------------------ ISR DEFS ---------------------------------------- */

/*!
 * Registers the external BLE interrupt handler with the MCU
 */
ISR(BLE_vect, ISR_BLOCK)
{
    // Process messages from the BLE module while available
    while (BLE_PORT & (1 << BLE_IRQ))
    {
        uint8_t msgtype = sdepRespCollect();

        switch(msgtype)
        {
            case SDEP_MSGTYPE_RESPONSE:
                sdepResponseMsgHandler();
                break;
            case SDEP_MSGTYPE_ALERT:
                sdepAlertMsgHandler();
                break;
            case SDEP_MSGTYPE_ERROR:
                sdepErrorMsgHandler();
                break;
        }
    }
}
