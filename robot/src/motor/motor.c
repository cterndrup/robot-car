/* Implementation file for Motor object */

/* ------------------------- SYSTEM INCLUDES -------------------------------- */
#include <avr/io.h>
#include <stdlib.h>

/* ------------------------- APPLICATION INCLUDES --------------------------- */
#include "motor/motor.h"
#include "common/utils.h"

/* ------------------------- FUNCTION DEFINITIONS  -------------------------- */

/*!
 * @ref motor.h for function documentation
 */
STATUS
motorConstruct(Motor *pMotor, PWM *pPwm)
{
    // Ensure the pointer is not NULL
    if (pMotor == NULL || pPwm == NULL)
    {
        return STATUS_ERR_INVALID_PTR;
    }

    pMotor->pPwm = pPwm;

    // Set the default speed and direction of the motor
    pMotor->speed      = DEFAULT_SPEED;
    pMotor->bDirection = DEFAULT_DIR;

    // Initialize motor's methods
    pMotor->driveForward = motorDriveForward;
    pMotor->driveReverse = motorDriveReverse;
    pMotor->stop         = motorStop;
    pMotor->changeSpeed  = motorChangeSpeed;

    return STATUS_OK;
}

/*!
 * @ref motor.h for function documentation
 */
STATUS
motorDriveForward(Motor *pMotor, uint8_t speed)
{
    // Ensure the input pointer is not NULL
    if (pMotor == NULL)
    {
        return STATUS_ERR_INVALID_PTR;
    }

    // Ensure the speed is valid
    if (speed > 100)
    {
        speed = 100;
    }

    // Set the motor's speed and direction
    pMotor->speed = speed;

    if (pMotor->bDirection == REVERSE_DIR)
    {
        pMotor->pPwm->dir  = PWM_FORWARD;
        pMotor->bDirection = FORWARD_DIR;
    }

    pMotor->pPwm->pwmSetDutyCycle(pMotor->pPwm, speed);

    return STATUS_OK;
}

/*!
 * @ref motor.h for function documentation
 */
STATUS
motorDriveReverse(Motor *pMotor, uint8_t speed)
{
    // Ensure the input pointer is not NULL
    if (pMotor == NULL)
    {
        return STATUS_ERR_INVALID_PTR;
    }

    // Ensure the speed is valid
    if (speed > 100)
    {
        speed = 100;
    }

    // Set the motor's speed and direction
    pMotor->speed = speed;

    if (pMotor->bDirection == FORWARD_DIR)
    {
        pMotor->pPwm->dir  = PWM_REVERSE;
        pMotor->bDirection = REVERSE_DIR;
    }

    pMotor->pPwm->pwmSetDutyCycle(pMotor->pPwm, speed);

    return STATUS_OK;
}

/*!
 * @ref motor.h for function documentation
 */
STATUS
motorStop(Motor *pMotor)
{
    // Ensure the input pointer is not NULL
    if (pMotor == NULL)
    {
        return STATUS_ERR_INVALID_PTR;
    }

    // Set the motor's speed and direction
    pMotor->speed = DEFAULT_SPEED;
    pMotor->pPwm->pwmSetDutyCycle(pMotor->pPwm, 0);

    return STATUS_OK;
}

/*!
 * @ref motor.h for function documentation
 */
STATUS
motorChangeSpeed(Motor *pMotor, uint8_t speed)
{
    // Ensure the input pointer is not NULL
    if (pMotor == NULL)
    {
        return STATUS_ERR_INVALID_PTR;
    }

    // Ensure the speed is valid
    if (speed > 100)
    {
        speed = 100;
    }

    // Set the motor's speed
    pMotor->speed = speed;
    pMotor->pPwm->pwmSetDutyCycle(pMotor->pPwm, speed);

    return STATUS_OK;
}
