/* Implementation file for 16-bit timer */

/* ------------------------- SYSTEM INCLUDES -------------------------------- */
#include <avr/io.h>

/* ------------------------- APPLICATION INCLUDES --------------------------- */
#include "timer/timer16/timer16.h"
#include "common/utils.h"

/* ------------------------- FUNCTION DEFINITIONS --------------------------- */

/*!
 * @ref timer16.h for function documentation
 */
void
timer16Init
(
    REG8 *prr,
    uint8_t prrBit,
    REG8 *tccrA,
    REG8 *tccrB,
    uint8_t wgmMode,
    uint8_t comMode,
    uint8_t clkSrc
)
{
    // Clear appropriate power/reduction timer bit to 0
    CLEAR_BIT(*prr, prrBit);

    // Set timer mode
    SET_TIMER_MODE(*tccrA, *tccrB, wgmMode, comMode);

    // Set the timer's clock source
    SET_CLK_SOURCE(*tccrB, clkSrc);
}
