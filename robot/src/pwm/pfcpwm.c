/* Implementation file for Phase & Frequency Correct PWM */

/* ------------------------- SYSTEM INCLUDES -------------------------------- */
#include <stdlib.h>
#include <avr/io.h>

/* ------------------------- APPLICATION INCLUDES --------------------------- */
#include "pwm/pfcpwm.h"
#include "common/utils.h"

/* ------------------------- FUNCTION DEFINITIONS --------------------------- */

/*!
 * @ref pfcpwm.h for function documentation
 */
STATUS
pwmConstruct
(
    PWM     *pPwm,
    REG8    *ddr,
    uint8_t  bit1,
    uint8_t  bit2,
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
    // Sanity check the pointer to the pwm object
    if (pPwm == NULL)
    {
        return STATUS_ERR_INVALID_PTR;
    }

    // Populate the pwm object data fields
    pPwm->ddr    = ddr;
    pPwm->bit1   = bit1;
    pPwm->bit2   = bit2;

    pPwm->prr    = prr;
    pPwm->prrBit = prrBit;

    pPwm->tccrA  = tccrA;
    pPwm->tccrB  = tccrB;
    pPwm->clkSrc = clkSrc;

    pPwm->ocrA   = ocrA;
    pPwm->ocrB   = ocrB;
    pPwm->ocrC   = ocrC;

    // Populate the pwm object's methods
    pPwm->pwmInit         = pwmInit;
    pPwm->pwmSetDutyCycle = pwmSetDutyCycle;

    return STATUS_OK;
}


/*!
 * @ref pfcpwm.h for function documentation
 */
STATUS
pwmInit
(
    PWM *pPwm
)
{
    // Sanity check the input pointer
    if (pPwm == NULL)
    {
        return STATUS_ERR_INVALID_PTR;
    }

    // Initialize 16-bit timer
    timer16Init(pPwm->prr, pPwm->prrBit, pPwm->tccrA, pPwm->tccrB,
        TIMER_MODE_WGM_PFC_PWM_TOP_OCRnA,
        TIMER_MODE_COM_PFC_PWM_CLEAR_UP, pPwm->clkSrc);
    
    // Initialize output compare registers
    SET_OUTPUT_COMPARE_REG(*(pPwm->ocrA), 0xFFFF);
    SET_OUTPUT_COMPARE_REG(*(pPwm->ocrB), 0x0000);
    SET_OUTPUT_COMPARE_REG(*(pPwm->ocrC), 0x0000);

    // Set OCnx pin to output to enable PWM waveform generation
    SET_PORT_BIT_OUTPUT(*(pPwm->ddr), pPwm->bit1);
    SET_PORT_BIT_OUTPUT(*(pPwm->ddr), pPwm->bit2);

    return STATUS_OK;
}

/*!
 * @ref pfcpwm.h for function documentation
 */
STATUS
pwmSetDutyCycle
(
    PWM     *pPwm,
    uint8_t  pct
)
{
    // Sanity check the input pointer
    if (pPwm == NULL)
    {
        return STATUS_ERR_INVALID_PTR;
    }

    // Set PWM duty cycle
    if (pPwm->dir == PWM_FORWARD)
    {
        *pPwm->ocrB = (*pPwm->ocrA/100)*pct;
        *pPwm->ocrC = 0x0000;
    }
    else if (pPwm->dir == PWM_REVERSE)
    {
        *pPwm->ocrC = (*pPwm->ocrA/100)*pct;
        *pPwm->ocrB = 0x0000;
    }
    else
    {
        return STATUS_ERR_GENERAL;
    }

    return STATUS_OK;
}

