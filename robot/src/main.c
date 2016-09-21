/* Main function for robot execution */

/* ------------------------  SYSTEM INCLUDES -------------------------------- */
#include <avr/io.h>
#include <util/delay.h>

/* ------------------------ APPLICATION INCLUDES ---------------------------- */
#include "pwm/pfcpwm.h"
#include "common/utils.h"

/* ------------------------ MAIN -------------------------------------------- */
int main(void)
{
    // 
    // Currently, this code is commented out because the enables pins 
    // are fixed high on the L298 motor driver by jumpers. 
    //
    // Initialize directional I/O register bits 
    // to outputs
    //
    // SET_PORT_BIT_OUTPUT(DDRC, 0);
    // SET_PORT_BIT_OUTPUT(DDRC, 1);
    //

    //
    // Trivial test program to drive a motor using two inputs:
    // 1). A PWM output signal to drive the motor
    // 2). A low output signal
    // 
    // High on motor input 1, low on motor input 2 drives the motor in the 
    // forward direction. PWM is used to control the speed of the motor.
    //

    // Initialize PWM
    pfcPWMInit(&DDRE, 4, &PRR1, 3, &TCCR3A, &TCCR3B, CLK_SEL_NO_PRESCALE,
        &OCR3A, &OCR3B, &OCR3C);
    pfcPWMInit(&DDRB, 6, &PRR0, 1, &TCCR1A, &TCCR1B, CLK_SEL_NO_PRESCALE,
        &OCR1A, &OCR1B, &OCR1C);
    pfcPWMInit(&DDRL, 4, &PRR1, 5, &TCCR5A, &TCCR5B, CLK_SEL_NO_PRESCALE,
        &OCR5A, &OCR5B, &OCR5C);
    pfcPWMInit(&DDRH, 4, &PRR1, 4, &TCCR4A, &TCCR4B, CLK_SEL_NO_PRESCALE,
        &OCR4A, &OCR4B, &OCR4C);

    // Run infinitely
    while (1)
    {
        // Set duty cycle
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR3, 0);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR1, 0);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR5, 0);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR4, 0);
        _delay_ms(2000);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR3, 25);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR1, 25);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR5, 25);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR4, 25);
        _delay_ms(2000);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR3, 50);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR1, 50);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR5, 50);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR4, 50);
        _delay_ms(2000);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR3, 75);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR1, 75);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR5, 75);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR4, 75);
        _delay_ms(2000);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR3, 100);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR1, 100);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR5, 100);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR4, 100);
        _delay_ms(2000);
    }

    return 0;
}
