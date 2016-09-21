/* Header file for Phase and Frequency Correct PWM Timer mode */

#ifndef _PFCPWM_H_
#define _PFCPWM_H_

/* ------------------------ INCLUDES ---------------------------------------- */
#include "timer/timer16/timer16.h"
#include "common/utils.h"

/* ------------------------ MACROS AND DEFINES ------------------------------ */
#define NON_INVERTED_PWM    (0)
#define INVERTED_PWM        (1)

/*!
 * Helper macro to set the PWM duty cycle
 * 
 * @param[in/out] ocr   An output compare register 
 *                      (i.e. OCR1 for 16-bit timer 1)
 * @param[in]     pct   The duty cycle % (so 100% is 100, not 1)
 * 
 * @note OCRA must be greater than 100; Otherwise OCRB will be set to 0 due to
 *       integer division
 */
#define PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(ocr, pct) \
        do { \
            ocr##B = ((ocr##A)/100)*(pct); \
        } while (0)

/*!
 * Helper macro to initialize phase & frequency correct (PFC) PWM on the I/O
 * bit of the provided port
 *
 * @param[in/out] ddr       A data direction register for port
 * @param[in]     bit       The bit of port to initialize PWM on
 * @param[in/out] prr       A power reduction register
 * @param[in]     prrBit    The bit in the power reduction register to clear
 *                          in order to enable the corresponding timer unit
 * @param[in/out] tccr      A timer control register
 * @param[in]     clkSrc    The clock source for the timer used for PWM
 * @param[in/out] ocr       An output compare register of timer used for PWM
 */
#define PFC_PWM_TOP_OCRnA_INIT(ddr, bit, prr, prrBit, tccr, \
            clkSrc, ocr) \
        do { \
            /* initialize 16 bit timer */ \
            TIMER16_INIT(prr, prrBit, tccr, \
                TIMER_MODE_WGM_PFC_PWM_TOP_OCRnA, \
                TIMER_MODE_COM_PFC_PWM_CLEAR_UP, clkSrc); \
            /* initialize output compare registers */ \
            SET_OUTPUT_COMPARE_REG(ocr##A, 0xFFFF); \
            SET_OUTPUT_COMPARE_REG(ocr##B, 0xFFFF); \
            /*set appropriate port bits to output mode */ \
            SET_PORT_BIT_OUTPUT(ddr, bit); \
        } while (0)

/* ------------------------ FUNCTION DECLARATIONS --------------------------- */

/*!
 * Function to initialize phase & frequency correct (PFC) PWM on the I/O
 * bit of the provided port
 *
 * @param[in/out] ddr       A data direction register for port
 * @param[in]     bit       The bit of port to initialize PWM on
 * @param[in/out] prr       A power reduction register
 * @param[in]     prrBit    The bit in the power reduction register to clear
 *                          in order to enable the corresponding timer unit
 * @param[in/out] tccrA     Timer control register A
 * @param[in/out] tccrB     Timer control register B
 * @param[in]     clkSrc    The clock source for the timer used for PWM
 * @param[in/out] ocrA      Output compare register A of timer used for PWM
 * @param[in/out] ocrB      Output compare register B of timer used for PWM
 * @param[in/out] ocrC      Output compare register C of timer used for PWM
 */
void pfcPWMInit(REG8 *ddr, uint8_t bit, REG8 *prr, uint8_t prrBit, REG8 *tccrA,
                REG8 *tccrB, uint8_t clkSrc, REG16 *ocrA, REG16 *ocrB,
                REG16 *ocrC);

#endif /* _PFCPWM_H_ */
