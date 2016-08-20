/* header file for Phase and Frequency Correct PWM Timer mode */

#ifndef _PFCPWM_H_
#define _PFCPWM_H_

/* ------------------------ INCLUDES ---------------------------------------- */
#include "timer/timer16/timer16.h"

/* ------------------------ MACROS AND DEFINES ------------------------------ */
#define NON_INVERTED_PWM    (0)
#define INVERTED_PWM        (1)

// TODO: Make this work
/*!
 * Helper macro to set the PWM duty cycle
 * 
 * @param[in/out] ocr   An output compare register 
 *                      (i.e. OCR1 for 16-bit timer 1)
 * @param[in]     pct   The duty cycle % (so 100% is 100, not 1)
 */
#define PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(ocr, pct) \
        ocr##B = ocr##A*pct/100

/*!
 * Helper macro to initialize phase & frequency correct (PFC) PWM on the I/O
 * bit of the provided port
 *
 * @param[in/out] port      An I/O port
 * @param[in/out] ddr       A data direction register for port
 * @param[in]     bit       The bit of port to initialize PWM on
 * @param[in/out] prr       A power reduction register
 * @param[in]     prrBit    The bit in the power reduction register to clear
 *                          in order to enable the corresponding timer unit
 * @param[in]     tccr      A timer control register
 * @param[in]     clkSrc    The clock source for the timer used for PWM
 * @param[in]     ocr       An output compare register of timer used for PWM
 */
#define PFC_PWM_TOP_OCRnA_INIT(port, ddr, bit, prr, prrBit, tccr, \
            clkSrc, ocr) \
        do { \
            /*set appropriate port bits to output mode */ \
            SET_PORT_BIT_OUTPUT(ddr, bit); \
            /* initialize 16 bit timer */ \
            TIMER16_INIT(port, prr, prrBit, tccr, \
                TIMER_MODE_WGM_PFC_PWM_TOP_OCRnA, \
                TIMER_MODE_COM_PFC_PWM_CLEAR_UP, clkSrc); \
            /* initialize output compare registers */ \
            SET_OUTPUT_COMPARE_REG(ocr##A, 0xFFFF); \
            SET_OUTPUT_COMPARE_REG(ocr##B, 0x3FFF); \
        } while (0)
            
#endif /* _PFCPWM_H_ */
