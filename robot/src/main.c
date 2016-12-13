/* Main function for robot execution */

/* ------------------------  SYSTEM INCLUDES -------------------------------- */
#include <avr/io.h>
#include <util/delay.h>

/* ------------------------ APPLICATION INCLUDES ---------------------------- */
#include "motor/motor.h"
#include "pwm/pfcpwm.h"
#include "common/utils.h"

/* ------------------------ MAIN -------------------------------------------- */
PWM leftFront;
PWM leftBack;
PWM rightFront;
PWM rightBack;

Motor lf;
Motor lb;
Motor rf;
Motor rb;

void test_initialize()
{
    // Construct/Initialize PWM
    pwmConstruct(&leftFront, &DDRE, 4, 5, &PRR1, 3, &TCCR3A, &TCCR3B,
                 CLK_SEL_NO_PRESCALE, &OCR3A, &OCR3B, &OCR3C);
    pwmConstruct(&leftBack, &DDRH, 4, 5, &PRR1, 4, &TCCR4A, &TCCR4B,
                 CLK_SEL_NO_PRESCALE, &OCR4A, &OCR4B, &OCR4C);
    pwmConstruct(&rightFront, &DDRB, 6, 7, &PRR0, 3, &TCCR1A, &TCCR1B,
                 CLK_SEL_NO_PRESCALE, &OCR1A, &OCR1B, &OCR1C);
    pwmConstruct(&rightBack, &DDRL, 4, 5, &PRR1, 5, &TCCR5A, &TCCR5B,
                 CLK_SEL_NO_PRESCALE, &OCR5A, &OCR5B, &OCR5C);

    pwmInit(&leftFront);
    pwmInit(&leftBack);
    pwmInit(&rightFront);
    pwmInit(&rightBack);

    // Construct motors...
    motorConstruct(&lf, &leftFront);
    motorConstruct(&lb, &leftBack);
    motorConstruct(&rf, &rightFront);
    motorConstruct(&rb, &rightBack);
}

void test_driveForwardFullSpeed()
{
    // Initialize PWM and Motors
    test_initialize();

    // Do the driving...
    lf.driveForward(&lf, 100);
    lb.driveForward(&lb, 100);
    rf.driveForward(&rf, 100);
    rb.driveForward(&rb, 100);
}

int main(void)
{
    while (TRUE)
    {
        test_driveForwardFullSpeed();
    }

    return 0;
}

