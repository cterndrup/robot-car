/* Implementation file for Phase & Frequency Correct PWM */

/* ------------------------- SYSTEM INCLUDES -------------------------------- */
#include <avr/io.h>

/* ------------------------- APPLICATION INCLUDES --------------------------- */
#include "pwm/pfcpwm.h"
#include "common/utils.h"

/* ------------------------- FUNCTIONS -------------------------------------- */

/*!
 * @ref pfcpwm.h for function documentation
 */
void
pfcPWMInit
(
    REG8    *ddr,
    uint8_t  bit,
    REG8    *prr,
    uint8_t  prrBit,
    REG8    *tccrA,
    REG8    *tccrB,
    uint8_t  clkSrc,
    REG16   *ocrA,
    REG16   *ocrB,
    REG16   *ocrC
)
{
    // Initialize 16-bit timer
    timer16Init(prr, prrBit, tccrA, tccrB, TIMER_MODE_WGM_PFC_PWM_TOP_OCRnA,
        TIMER_MODE_COM_PFC_PWM_CLEAR_UP, clkSrc);
    
    // Initialize output compare registers
    SET_OUTPUT_COMPARE_REG(*ocrA, 0xFFFF);
    SET_OUTPUT_COMPARE_REG(*ocrB, 0x0000);
    SET_OUTPUT_COMPARE_REG(*ocrC, 0x0000);

    // Set OCnx pin to output to enable PWM waveform generation
    SET_PORT_BIT_OUTPUT(*ddr, bit);
}
