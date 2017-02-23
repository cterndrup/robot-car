/*! Implementation file for Bluetooth Low Energy code */

/* ------------------------ SYSTEM INCLUDES --------------------------------- */
#include <avr/io.h>
#include <avr/interrupt.h>

/* ------------------------ APPLICATION INCLUDES ---------------------------- */
#include "spi/spi.h"
#include "sdep/sdep.h"
#include "ble/ble.h"
#include "common/utils.h"

/* ------------------------ FUNCTION DEFINITIONS  --------------------------- */

/*!
 * Fetch the next BLE_ALERT_RECV_STATE given the current state and state
 * variables
 *
 * @param[in] nextState     the current BLE_ALERT_RECV_STATE
 * @param[in] bytesRead     the number of bytes read for the current packet
 * @param[in] length        the length of the current packet being read
 *
 * @return  the next state to traverse to in the state machine
 */
static inline BLE_ALERT_RECV_STATE
_bleAlertRecvNextState
(
    BLE_ALERT_RECV_STATE nextState,
    uint8_t              bytesRead,
    unsigned char        length
)
{
    BLE_ALERT_RECV_STATE next;

    switch (nextState)
    {
        case ALERT_INIT:
        {
            next = READ_HDR;
            break;
        }
        case READ_HDR:
        {
            next = READ_PAYLOAD;
            break;
        }
        case READ_PAYLOAD:
        {
            if (bytesRead < 16 && length > 0)
            {
                next = READ_PAYLOAD;
            }
            else if (bytesRead == 16 && length != 0)
            {
                next = READ_HDR;
            }
            else if (length == 0)
            {
                next = ALERT_DONE;
            } 
            break;
        }
        case ALERT_DONE:
            break;
    }

    return next;
}

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
        case SEND_INIT:
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
                next = SEND_DONE;
            }
            break;
        }
        case SEND_DONE:
            break;
    }

    return next;
}

/*!
 * @ref ble.h for function documentation
 */
void
bleIRQRegister(void)
{
    // Set BLE_IRQ pin to input
    SET_PORT_BIT_INPUT(DDRD, BLE_IRQ);

    // Set pins to correponding to SW interrupts to outputs
    SET_PORT_BIT_OUTPUT(DDRD, BLE_IRQ_RESP);
    SET_PORT_BIT_OUTPUT(DDRE, BLE_IRQ_ALERT);
    SET_PORT_BIT_OUTPUT(DDRE, BLE_IRQ_ERROR);

    // Clear interrupt flags for BLE_IRQs before setting sense control bits
    CLEAR_BIT(EIMSK, BLE_IRQ);
    CLEAR_BIT(EIMSK, BLE_IRQ_RESP);
    CLEAR_BIT(EIMSK, BLE_IRQ_ALERT);
    CLEAR_BIT(EIMSK, BLE_IRQ_ERROR);

    // Set sense control bits to trigger interrupts on rising edge trigger
    SET_BIT(EICRA, ISC20);
    SET_BIT(EICRA, ISC21);
    SET_BIT(EICRA, ISC30);
    SET_BIT(EICRA, ISC31);

    SET_BIT(EICRB, ISC60);
    SET_BIT(EICRB, ISC61);
    SET_BIT(EICRB, ISC70);
    SET_BIT(EICRB, ISC71);

    // Clear interrupt flag bits (by writing 1) before enable interrupts
    SET_BIT(EIFR, BLE_IRQ);
    SET_BIT(EIFR, BLE_IRQ_RESP);
    SET_BIT(EIFR, BLE_IRQ_ALERT);
    SET_BIT(EIFR, BLE_IRQ_ERROR);

    // Enables external interrupt on BLE_IRQ pin
    SET_BIT(EIMSK, BLE_IRQ);
    SET_BIT(EIMSK, BLE_IRQ_RESP);
    SET_BIT(EIMSK, BLE_IRQ_ALERT);
    SET_BIT(EIMSK, BLE_IRQ_ERROR);
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
    const char *pByte = pBase; 
    const char *pLoad = pPayload;
    const char *pM    = pMode;

    bool    done        = false;
    bool    baseDone    = false;
    bool    modeDone    = false;
    bool    payloadDone = false;
    uint8_t bytesSent   = 0;
    BLE_CMD_SEND_STATE nextState = SEND_INIT;

    while (!done)
    {
        // Update next state given current state
        nextState = _bleCmdSendNextState(nextState, bytesSent, baseDone, 
                                         modeDone, payloadDone); 

        switch (nextState)
        {
            case SEND_INIT:
            case SEND_HDR:
            {
                bytesSent = 0;
                spiMasterSendByte(SDEP_MSGTYPE_CMD, NULL);
                spiMasterSendByte(0x00, NULL);
                spiMasterSendByte(0x0A, NULL);
                if (length > 16)
                    spiMasterSendByte((1 << 7) | length, NULL);
                else
                    spiMasterSendByte(length, NULL);
                spiMasterSendDone();
                bytesSent += 4;
                break;
            }
            case SEND_BASE:
            {
                if (!baseDone)
                {
                    spiMasterSendByte(*pByte, NULL);
                    spiMasterSendDone();
                    length--;
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
                    spiMasterSendByte(*pM, NULL);
                    spiMasterSendDone();
                    length--;
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
                    spiMasterSendByte(*pLoad, NULL);
                    spiMasterSendDone();
                    length--;
                    bytesSent++;
                    pLoad++;
                    if (pLoad == '\0') payloadDone = true;
                }
                break;
            }
            case SEND_DONE:
            {
                done = true;
            }
        }
    }
}

/* ------------------------ ISR DEFS ---------------------------------------- */

/*!
 * Registers the external BLE interrupt handler with the MCU
 */
ISR(BLE_vect, ISR_NOBLOCK)
{
    //
    // Dispatch to appropriate ISR handler for Response, Alert, or Error msgs
    // based on message type
    //
    unsigned char msgtype = spiMasterRecvByte();

    // Raise software interrupt to invoke proper handling routine
    switch(msgtype)
    {
        case SDEP_MSGTYPE_RESPONSE:
        {
            RAISE_BLE_IRQ_RESP;
            break;
        }
        case SDEP_MSGTYPE_ALERT:
        {
            RAISE_BLE_IRQ_ALERT;
            break;
        }
        case SDEP_MSGTYPE_ERROR:
        {
            RAISE_BLE_IRQ_ERROR;
        }
    }
}

/*!
 * Registers the external BLE response message handler with the MCU
 */
ISR(BLE_RESP_vect, ISR_BLOCK)
{
    // TODO: implement response handler
}

/*!
 * Global buffer for storing BLE ALERT MSG payload
 */
unsigned char bleAlertBuffer[BLE_ALERT_BUF_SIZE];

/*!
 * Registers the external BLE alert message handler with the MCU
 */
ISR(BLE_ALERT_vect, ISR_BLOCK)
{
    // Remember message type has already been read when this handler is called
    bool          firstIter = true;
    bool          done      = false;
    unsigned char length    = 0;
    uint8_t       bytesRead = 0;
    unsigned char msgtype, alertIDh, alertIDl;
    BLE_ALERT_RECV_STATE nextState = ALERT_INIT;

    unsigned char *buf = &bleAlertBuffer[0];

    while (!done)
    {
        // update nextState
        nextState = _bleAlertRecvNextState(nextState, bytesRead, length);

        switch (nextState)
        {
            case ALERT_INIT:
            case READ_HDR:
            {
                if (!firstIter)
                {
                    msgtype = spiMasterRecvByte();
                }
                bytesRead = 1;
                alertIDl = spiMasterRecvByte();
                alertIDh = spiMasterRecvByte();
                length   = spiMasterRecvByte();
                bytesRead += 3;
                break;
            }
            case READ_PAYLOAD:
            {
                *buf = spiMasterRecvByte();
                bytesRead++;
                buf++;
                break;
            }
            case ALERT_DONE:
            {
                *buf = 0;
                done = true;
            }
        }

        firstIter = false;
    }
}

/*!
 * Registers the external BLE alert message handler with the MCU
 */
ISR(BLE_ERROR_vect, ISR_BLOCK)
{
    // TODO: implement error handler
}

