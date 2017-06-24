/* Header file for Motor object */

#ifndef _MOTOR_H_
#define _MOTOR_H_

/* ------------------------ INCLUDES ---------------------------------------- */
#include <avr/io.h>

#include "pwm/pfcpwm.h"
#include "common/utils.h"

/* ------------------------ TYPE DEFINITIONS -------------------------------- */

/*!
 * Forward defintion of the Motor object
 */
typedef struct Motor Motor;

/*!
 * Type definition for the Motor object's constructor
 *
 * @param[in/out] pMotor    pointer to the Motor object to construct
 * @param[in/out] pPwm      pointer to the PWM object used by this motor
 *
 * @return STATUS_OK if motor construct successfully
 * @return STATUS_ERR_INVALID_PTR if input pointer is NULL
 */
typedef STATUS MotorConstruct(Motor *pMotor, PWM *pPwm);

/*!
 * Type definition for the Motor object's driveForward method
 *
 * @param[in/out] pMotor    pointer to the Motor object to drive forward
 * @param[in]     speed     forward speed to drive Motor
 */
typedef STATUS MotorDriveForward(Motor *pMotor, uint8_t speed);

/*!
 * Type definition for the Motor object's driveReverse method
 *
 * @param[in/out] pMotor    pointer to the Motor object to drive reverse
 * @param[in]     speed     reverse speed to drive Motor
 */
typedef STATUS MotorDriveReverse(Motor *pMotor, uint8_t speed);

/*!
 * Type definition for the Motor object's stop method
 *
 * @param[in/out] pMotor    pointer to the Motor object to stop
 */
typedef STATUS MotorStop(Motor *pMotor);

/*!
 * Type definition for the Motor object's changeSpeed method
 *
 * @param[in/out] pMotor    pointer to the Moto object to change speed
 * @param[in]     speed     speed to drive Motor
 */
typedef STATUS MotorChangeSpeed(Motor *pMotor, uint8_t speed);

/*!
 * Structure definition for the motor object
 */
struct Motor
{
    //
    // Unsigned 8-bit integer representing the motor's speed. Speed is
    // represented by percentage of total speed capable by the motor.
    //
    uint8_t            speed;

    //
    // Boolean value representing direction of the motor's rotation. 0
    // represents forward and 1 represents reverse.
    //
    uint8_t            bDirection;

    // PWM object to control motor speed and direction
    PWM               *pPwm;

    // Method to drive motor forward
    MotorDriveForward *driveForward;

    // Method to drive motor in reverse
    MotorDriveReverse *driveReverse;

    // Method to stop the motor
    MotorStop         *stop;

    // Method to change the motor's speed
    MotorChangeSpeed  *changeSpeed;
};

/* ------------------------ MACROS AND DEFINES ------------------------------ */
#define FORWARD_DIR     (0)
#define REVERSE_DIR     (1)
#define DEFAULT_SPEED   (0)
#define DEFAULT_DIR     FORWARD_DIR

/* ------------------------ FUNCTION PROTOTYPES ----------------------------- */
MotorConstruct    motorConstruct;
MotorDriveForward motorDriveForward;
MotorDriveReverse motorDriveReverse;
MotorStop         motorStop;
MotorChangeSpeed  motorChangeSpeed;

#endif // _MOTOR_H_
