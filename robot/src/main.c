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
        &OCR3A, &OCR3B);

    SET_PORT_BIT_OUTPUT(DDRH, 4);
    CLEAR_BIT(PORTH, 4);

    // Run infinitely
    while (1)
    {
        // Set duty cycle
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR3, 0);
        _delay_ms(2000);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR3, 25);
        _delay_ms(2000);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR3, 50);
        _delay_ms(2000);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR3, 75);
        _delay_ms(2000);
        PFC_PWM_TOP_OCRnA_SET_DUTY_CYCLE(OCR3, 100);
        _delay_ms(2000);
    }

    return 0;
}
