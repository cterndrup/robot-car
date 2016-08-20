/* Main function for robot execution */

/* ------------------------ SYSTEM INCLUDES --------------------------------- */
#include <avr/io.h>
//#include <util/delay.h>

/* ------------------------ APPLICATION INCLUDES ---------------------------- */
#include "pwm/pfcpwm.h"
#include "common/utils.h"

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
    // Trivial test program to drive a signal motor using two inputs:
    // 1). A PWM output signal to drive the motor
    // 2). A low output signal
    // 
    // High on motor input 1, low on motor input 2 drives the motor in the 
    // forward direction. PWM is used to control the speed of the motor.
    //

    // Initialize PWM on 4th bit of PORTE
    PFC_PWM_TOP_OCRnA_INIT(PORTE, DDRE, 4, PRR1, 3, TCCR3,
        CLK_SEL_NO_PRESCALE, OCR3);

    // Set $th bit of PORTH to an output, then clear it
    SET_PORT_BIT_OUTPUT(DDRH, 4);
    CLEAR_BIT(PORTH, 4);

    // Run infinitely
    while (1);

    return 0;
}