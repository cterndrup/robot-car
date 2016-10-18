/* Header file for 16-bit timer/counters */

#ifndef _TIMER16_H_
#define _TIMER16_H_

/* ------------------------ INCLUDES ---------------------------------------- */
#include "common/utils.h"

/* ------------------------ MACROS AND DEFINES ------------------------------ */
#define COUNTER_BOTTOM  (0x0000)
#define COUNTER_MAX     (0xFFFF)

//
// USEFUL ABBREVIATIONS
// WGM = waveform generation mode
// PC = phase correct
// PWM = pulse width modulation
// CTC = clear timer on compare match
// FPWM = Fast PWM
// PFC = phase and frequency correct
// ICRn = input capture register for timer n
// OCRnA = output compare register A for timer n
// COM = compare output mode
//

#define TIMER_MODE_WGM_NORMAL               (0x00)
#define TIMER_MODE_WGM_PC_PWM_8b            (0x01)
#define TIMER_MODE_WGM_PC_PWM_9b            (0x02)
#define TIMER_MODE_WGM_PC_PWM_10b           (0x03)
#define TIMER_MODE_WGM_CTC                  (0x04)
#define TIMER_MODE_WGM_FPWM_8b              (0x05)
#define TIMER_MODE_WGM_FPWM_9b              (0x06)
#define TIMER_MODE_WGM_FPWM_10b             (0x07)
#define TIMER_MODE_WGM_PFC_PWM_TOP_ICRn     (0x08)
#define TIMER_MODE_WGM_PFC_PWM_TOP_OCRnA    (0x09)  
#define TIMER_MODE_WGM_PC_PWM_TOP_ICRn      (0x0A)
#define TIMER_MODE_WGM_PC_PWM_TOP_OCRnA     (0x0B)
#define TIMER_MODE_WGM_CTC_TOP_ICRn         (0x0C)
#define TIMER_MODE_WGM_FPWM_TOP_ICRn        (0x0E)
#define TIMER_MODE_WGM_FPWM_TOP_OCRnA       (0x0F)

#define TIMER_MODE_COM_NON_PWM_NORMAL       (0x00)
#define TIMER_MODE_COM_NON_PWM_TOGGLE       (0x01)
#define TIMER_MODE_COM_NON_PWM_CLEAR        (0x02)
#define TIMER_MODE_COM_NON_PWM_SET          (0x03)

#define TIMER_MODE_COM_FPWM_NORMAL          (0x00) 
#define TIMER_MODE_COM_FPWM_TOGGLE          (0x01)
#define TIMER_MODE_COM_FPWM_CLEAR           (0x02)
#define TIMER_MODE_COM_FPWM_SET             (0x03)

#define TIMER_MODE_COM_PFC_PWM_NORMAL       (0x00)
#define TIMER_MODE_COM_PFC_PWM_TOGGLE       (0x01)
#define TIMER_MODE_COM_PFC_PWM_CLEAR_UP     (0x02)
#define TIMER_MODE_COM_PFC_PWM_SET_UP       (0x03)

#define CLK_SEL_NO_SOURCE                   (0x00)
#define CLK_SEL_NO_PRESCALE                 (0x01)
#define CLK_SEL_PRESCALE_8                  (0x02)
#define CLK_SEL_PRESCALE_64                 (0x03)
#define CLK_SEL_PRESCALE_256                (0x04)
#define CLK_SEL_PRESCALE_1024               (0x05)
#define CLK_SEL_EXTERN_FALL_EDGE            (0x06)
#define CLK_SEL_EXTERN_RISE_EDGE            (0x07)

/*!
 * Helper macro to set the waveform generation bits of the timer control
 * registers
 *
 * @param[in/out] tccrA     Timer control register A 
 *                          (i.e. TCCR1A for 16-bit timer 1)
 * @param[in/out] tccrB     Timer control register B 
 *                          (i.e. TCCR1B for 16-bit timer 1)
 * @param[in]     mode      The waveform generation mode (see #define's above)
 */
#define SET_TIMER_MODE_WGM(tccrA, tccrB, mode) \
        do { \
            tccrA |= ((mode) & 0b00000011); \
            tccrB |= (((mode) << 1) & 0b00011000); \
        } while (0)

/*!
 * Helper macro to set the compare output mode bits of the timer control
 * registers
 * 
 * @param[in/out] reg   Timer control register (i.e. TCCR1 for 16-bit timer 1)
 * @param[in]     mode  The compare output mode (see #define's above)
 */
#define SET_TIMER_MODE_COM(reg, mode) \
        do { \
            uint8_t modeMask = (mode) & 0b00000011; \
            reg |= (modeMask << 6); \
            reg |= (modeMask << 4); \
            reg |= (modeMask << 2); \
        } while (0)

/*!
 * Helper macro to set the waveform generation mode bits and the compare 
 * output mode bits of the timer control registers
 *
 * @param[in\out] tccrA     Timer control register A
 *                          (i.e. TCCR1A for 16-bit timer 1)
 * @param[in\out] tccrB     Timer control register B
 *                          (i.e. TCCR1B for 16-bit timer 1)
 * @param[in]     comMode   The compare output mode
 * @param[in]     wgmMode   The waveform generation mode  
 */
#define SET_TIMER_MODE(tccrA, tccrB, wgmMode, comMode) \
        do { \
            SET_TIMER_MODE_WGM(tccrA, tccrB, wgmMode); \
            SET_TIMER_MODE_COM(tccrA, comMode); \
        } while (0)
 
/*!
 * Helper macro to set the clock source bits of timer control register B
 * 
 * @param[in/out] tccrB     Timer control register B 
 *                          (i.e. TCCR1B for 16-bit timer 1)
 * @param[in]     source    The desired clock source for the timer/counter
 */
#define SET_CLK_SOURCE(tccrB, source) \
        do { \
            tccrB |= source; \
        } while (0)

/*!
 * Helper macro to set output compare register to provided value
 * 
 * @param[in/out] reg   Output compare register 
 *                      (i.e. OCR1{A,B,C} for 16-bit Timer 1)
 * @param[in]     val   The value reg is set to
 */
#define SET_OUTPUT_COMPARE_REG(reg, val) \
        do { \
            reg = val; \
        } while (0)
/*!
 * Helper macro to intialize a 16-bit timer
 *
 * @param[in/out] prr       A power reduction register (i.e. PRR1) whose given
 *                          bits are cleared to enable timer to be initialized
 * @param[in]     prrBit    Bit in prr to be cleared
 * @param[in]     comMode   The compare output mode for the timer
 * @param[in]     wgmMode   The waveform generation mode for th timer
 * @param[in]     clkSrc    The clock source for the timer
 */
#define TIMER16_INIT(prr, prrBit, tccr, wgmMode, comMode, clkSrc) \
        do { \
            /* clear appropriate power/reduction timer bit to 0 */ \
            CLEAR_BIT(prr, prrBit); \
            /* set timer mode */ \
            SET_TIMER_MODE(tccr, wgmMode, comMode); \
            /* set clk source */ \
            SET_CLK_SOURCE(tccr##B, clkSrc); \
        } while (0)

/* ------------------------ FUNCTION DEFINITIONS ---------------------------- */

/*!
 * Function to intialize a 16-bit timer
 *
 * @param[in/out] prr       A power reduction register (i.e. PRR1) whose given
 *                          bits are cleared to enable timer to be initialized
 * @param[in]     prrBit    Bit in prr to be cleared
 * @param[in/out] tccrA     Timer control register A for chosen timer
 * @param[in/out] tccrB     Timer control register B for chosen timer
 * @param[in]     comMode   The compare output mode for the timer
 * @param[in]     wgmMode   The waveform generation mode for th timer
 * @param[in]     clkSrc    The clock source for the timer
 */
void timer16Init(REG8 *prr, uint8_t prrBit, REG8 *tccrA, REG8 *tccrB,
                 uint8_t wgmMode, uint8_t comMode, uint8_t clkSrc);

#endif /* _TIMER16_H_ */
