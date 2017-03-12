/* Main function for robot execution */

/* ------------------------  SYSTEM INCLUDES -------------------------------- */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/* ------------------------ APPLICATION INCLUDES ---------------------------- */
#include "car/car.h"
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

Car car;

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
    // Do the driving...
    lf.driveForward(&lf, 100);
    lb.driveForward(&lb, 25);
    rf.driveForward(&rf, 100);
    rb.driveForward(&rb, 25);
}

void test_changeSpeed(uint8_t speed)
{
    // Change speed of each motor
    lf.changeSpeed(&lf, speed);
    lb.changeSpeed(&lb, speed);
    rf.changeSpeed(&rf, speed);
    rb.changeSpeed(&rb, speed);
}

void test_driveReverseFullSpeed()
{
    // Reverse each motor and drive full speed
    lf.driveReverse(&lf, 25);
    lb.driveReverse(&lb, 100);
    rf.driveReverse(&rf, 25);
    rb.driveReverse(&rb, 100);
}

void test_stop()
{
    // Stop each motor
    lf.stop(&lf);
    lb.stop(&lb);
    rf.stop(&rf);
    rb.stop(&rb);
}

int main(void)
{
    // Enable global interrupts
    sei();

    // Initialize PWM and Motors
    test_initialize();

    while (true)
    {
        test_driveForwardFullSpeed();
        _delay_ms(2000);
        test_driveReverseFullSpeed();
        _delay_ms(2000);
        test_stop();
        _delay_ms(2000);
    }

    return 0;
}

