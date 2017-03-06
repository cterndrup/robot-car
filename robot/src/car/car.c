/* Implementation file for the Car object */

/* ------------------------ INCLUDES ---------------------------------------- */
#include "car/car.h"

/* ------------------------ STATIC FUNCTIONS -------------------------------- */

/*!
 * Drives the car forward
 *
 * @param[in/out] pCar  Pointer to Car object
 * @param[in]     speed Speed to drive forward (as % of total speed)
 */
static void
_carDriveForward
(
    Car     *pCar,
    uint8_t  speed
)
{
    pCar->direction = DRIVE_FORWARD;

    pCar->pFrontLeft->driveForward(pCar->pFrontLeft, speed);
    pCar->pFrontRight->driveForward(pCar->pFrontRight, speed);
    pCar->pBackLeft->driveForward(pCar->pBackLeft, speed);
    pCar->pBackRight->driveForward(pCar->pBackRight, speed);
}

/*!
 * Drives the car in reverse
 *
 * @param[in/out] pCar  Pointer to Car object
 * @param[in]     speed Speed to drive car in reverse
 */
static void
_carDriveReverse
(
    Car     *pCar,
    uint8_t  speed
)
{
    pCar->direction = DRIVE_REVERSE;

    pCar->pFrontLeft->driveReverse(pCar->pFrontLeft, speed);
    pCar->pFrontRight->driveReverse(pCar->pFrontRight, speed);
    pCar->pBackLeft->driveReverse(pCar->pBackLeft, speed);
    pCar->pBackRight->driveReverse(pCar->pBackRight, speed);
}

/*!
 * Turns the car left while moving forward
 *
 * @param[in/out] pCar  Pointer to Car object
 * @param[in]     speed Speed to drive
 */
static void
_carDriveForwardLeft
(
    Car     *pCar,
    uint8_t  speed
)
{
    pCar->direction = DRIVE_FORWARD | DRIVE_LEFT;

    pCar->pFrontLeft->driveForward(pCar->pFrontLeft, DRIVE_TURN_SPEED);
    pCar->pFrontRight->driveForward(pCar->pFrontRight, speed);
    pCar->pBackLeft->driveForward(pCar->pBackLeft, DRIVE_TURN_SPEED);
    pCar->pBackRight->driveForward(pCar->pBackRight, speed);
}

/*!
 * Turns the car right while moving forward
 *
 * @param[in/out] pCar  Pointer to Car object
 * @param[in]     speed Speed to drive
 */
static void
_carDriveForwardRight
(
    Car     *pCar,
    uint8_t  speed
)
{
    pCar->direction = DRIVE_FORWARD | DRIVE_RIGHT;

    pCar->pFrontLeft->driveForward(pCar->pFrontLeft, speed);
    pCar->pFrontRight->driveForward(pCar->pFrontRight, DRIVE_TURN_SPEED);
    pCar->pBackLeft->driveForward(pCar->pBackLeft, speed);
    pCar->pBackRight->driveForward(pCar->pBackRight, DRIVE_TURN_SPEED);
}

/*!
 * Turns the car left (relative to front of car) while moving in reverse
 *
 * @param[in/out] pCar  Pointer to Car object
 * @param[in]     speed Speed to drive
 */
static void
_carDriveReverseLeft
(
    Car     *pCar,
    uint8_t  speed
)
{
    pCar->direction = DRIVE_REVERSE | DRIVE_LEFT;

    pCar->pFrontLeft->driveReverse(pCar->pFrontLeft, DRIVE_TURN_SPEED);
    pCar->pFrontRight->driveReverse(pCar->pFrontRight, speed);
    pCar->pBackLeft->driveReverse(pCar->pBackLeft, DRIVE_TURN_SPEED);
    pCar->pBackRight->driveReverse(pCar->pBackRight, speed);
}

/*!
 * Turns the car right (relative to front of car) while moving in reverse
 *
 * @param[in/out] pCar  Pointer to Car object
 * @param[in]     speed Speed to drive
 */
static void
_carDriveReverseRight
(
    Car     *pCar,
    uint8_t  speed
)
{
    pCar->direction = DRIVE_REVERSE | DRIVE_RIGHT;

    pCar->pFrontLeft->driveReverse(pCar->pFrontLeft, speed);
    pCar->pFrontRight->driveReverse(pCar->pFrontRight, DRIVE_TURN_SPEED);
    pCar->pBackLeft->driveReverse(pCar->pBackLeft, speed);
    pCar->pBackRight->driveReverse(pCar->pBackRight, DRIVE_TURN_SPEED);
}

/* ------------------------ FUNCTION DEFINITIONS ---------------------------- */

/*!
 * @ref car.h for function documentation
 */
void
carConstruct
(
    Car   *pCar,
    Motor *pFrontLeft,
    Motor *pFrontRight,
    Motor *pBackLeft,
    Motor *pBackRight
)
{
    pCar->speed     = 0;
    pCar->direction = DRIVE_FORWARD;

    pCar->pFrontLeft  = pFrontLeft;
    pCar->pFrontRight = pFrontRight;
    pCar->pBackLeft   = pBackLeft;
    pCar->pBackRight  = pBackRight;

    pCar->carDrive = carDrive;
}

/*!
 * @ref car.h for function documentation
 */
void
carDrive
(
    Car     *pCar,
    uint8_t  speed,
    uint8_t  direction
)
{
    switch (direction)
    {
        case DRIVE_FORWARD:
            _carDriveForward(pCar, speed);
            break;
        case DRIVE_REVERSE:
            _carDriveReverse(pCar, speed);
            break;
        case DRIVE_FORWARD|DRIVE_LEFT:
            _carDriveForwardLeft(pCar, speed);
            break;
        case DRIVE_FORWARD|DRIVE_RIGHT:
            _carDriveForwardRight(pCar, speed);
            break;
        case DRIVE_REVERSE|DRIVE_LEFT:
            _carDriveReverseLeft(pCar, speed);
            break;
        case DRIVE_REVERSE|DRIVE_RIGHT:
            _carDriveReverseRight(pCar, speed);
    }
}
