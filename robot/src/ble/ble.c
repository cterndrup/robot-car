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
 */
static void
_bleCmdSend
(
)
{
    // TODO: implement
}

/* ------------------------ ISR DEFS ---------------------------------------- */

/*!
 * Registers the external BLE interrupt handler with the MCU
 */
ISR(BLE_vect, ISR_BLOCK)
{
    // Process messages from the BLE module
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
