/* Header file for Phase and Frequency Correct PWM Timer mode */

#ifndef _PFCPWM_H_
#define _PFCPWM_H_

/* ------------------------ INCLUDES ---------------------------------------- */
#include "timer/timer16/timer16.h"
#include "common/utils.h"

/* ------------------------ MACROS AND DEFINES ------------------------------ */
#define NON_INVERTED_PWM    (0)
#define INVERTED_PWM        (1)

// See note in PWM struct below above field dir
#define PWM_FORWARD         (0)
#define PWM_REVERSE         (1)

/* ------------------------ TYPE DEFINITIONS -------------------------------- */

/*!
 * Forward definition of the PWM object
 */
typedef struct PWM PWM;

/*!
 * Type definition for the PWM object's constructor
 * 
 * @param[in/out] pPWM      pointer to the PWM object to construct
 * @param[in/out] ddr       A data direction register for port
 * @param[in]     bit1      The bit of port to initialize PWM on
 * @param[in]     bit2      The bit of port to initialize PWM on
 * @param[in/out] prr       A power reduction register
 * @param[in]     prrBit    The bit in the power reduction register to clear
 *                          in order to enable the corresponding timer unit
 * @param[in/out] tccrA     Timer control register A
 * @param[in/out] tccrB     Timer control register B
 * @param[in]     clkSrc    The clock source for the timer used for PWM
 * @param[in/out] ocrA      Output compare register A of timer used for PWM
 * @param[in/out] ocrB      Output compare register B of timer used for PWM
 * @param[in/out] ocrC      Output compare register C of timer used for PWM
 *
 * @return STATUS_OK if PWM constructed successfully
 * @return STATUS_ERR_INVALID_PTR if input pointer is NULL
 */
typedef STATUS PWMConstruct(PWM *pPWM, REG8 *ddr, uint8_t bit1, uint8_t bit2,
                            REG8 *prr, uint8_t prrBit, REG8 *tccrA, REG8 *tccrB,
                            uint8_t clkSrc, REG16 *ocrA, REG16 *ocrB,
                            REG16 *ocrC);

/*!
 * Type definition for function to initialize phase & frequency correct (PFC)
 * PWM.
 *
 * @param[in/out] pPWM  pointer to PWM object to initialize
 * 
 * @return STATUS_OK if PWM initialized successfully
 * @return STATUS_ERR_INVALID_PTR if input pointer is NULL
 */
typedef STATUS PWMInit(PWM *pPWM);

/*!
 * Type definition for the PWM object's setDutyCycle method
 * 
 * param[in/out] pPWM   pointer to the PWM object's duty cycle to change
 * param[in]     pct    percent representing PWM duty cycle
 */
typedef STATUS PWMSetDutyCycle(PWM *pPWM, uint8_t pct);

/*!
 * Type definition for the PWM object's reverse method
 *
 * param[in/out] pPWM   pointer to the PWM object's direction to reverse
 * 
 */
typedef STATUS PWMReverse(PWM *pPWM);

/*!
 * Structure definition for the pwm object
 */
struct PWM
{
    //
    // This field is used for the purposes of determining which output 
    // compare register to modify when setting the PWM duty cycle.
    //
    uint8_t dir;

    //
    // Data direction register and associated bit used to set waveform
    // generation pin to output
    //
    REG8   *ddr;
    uint8_t bit1;
    uint8_t bit2;

    //
    // Power reduction register and associated bit used to enable underlying
    // timer unit used for generating PWM
    //
    REG8   *prr;
    uint8_t prrBit;    

    //
    // Timer control registers and Clk source for underlying timer unit used
    // for generating PWM
    //
    REG8   *tccrA;
    REG8   *tccrB;
    uint8_t clkSrc;

    // Output compare registers used for setting PWM duty cycle
    REG16  *ocrA;
    REG16  *ocrB;
    REG16  *ocrC;

    // Method to initialize this PWM object
    PWMInit         *pwmInit;

    // Method to set PWM duty cycle
    PWMSetDutyCycle *pwmSetDutyCycle;

    // Method to reverse PWM direction
    PWMReverse      *pwmReverse;
};

// TODO: Deprecate use of this macro
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

/* ------------------------ FUNCTION PROTOTYPES ----------------------------- */
PWMConstruct    pwmConstruct;
PWMInit         pwmInit;
PWMSetDutyCycle pwmSetDutyCycle;
PWMReverse      pwmReverse;

#endif /* _PFCPWM_H_ */
