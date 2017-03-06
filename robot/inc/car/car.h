/* Header file for the Car object */

#ifndef _CAR_H_
#define _CAR_H_

/* ------------------------ INCLUDES ---------------------------------------- */
#include "motor/motor.h"
#include "common/utils.h"

/* ------------------------ MACROS AND DEFINES ------------------------------ */

/*!
 * Definitions of valid directions in which the Car object can drive
 */
#define DRIVE_FORWARD (0x00)
#define DRIVE_REVERSE (0x01)
#define DRIVE_LEFT    (0x02)
#define DRIVE_RIGHT   (0x04)

/*!
 * Definition of turn speed for motors not primarily driving the turn
 */
#define DRIVE_TURN_SPEED (0x05)

/* ------------------------ TYPEDEFS ---------------------------------------- */

/*!
 * Forward declaration of the Car structure
 */
typedef struct Car Car;

/*!
 * Constructs a Car object
 *
 * @param[in/out] pCar          Pointer to Car object to construct
 * @param[in]     pFrontLeft    Pointer to Car's front left Motor
 * @param[in]     pFrontRight   Pointer to Car's front right Motor
 * @param[in]     pBackLeft     Pointer to Car's back left Motor
 * @param[in]     pBackRight    Pointer to Car's back right Motor
 */
typedef void CarConstruct(Car   *pCar,
                          Motor *pFrontLeft,
                          Motor *pFrontRight,
                          Motor *pBackLeft,
                          Motor *pBackRight);

/*!
 * Drives the car according to given speed and direction
 *
 * @param[in/out] pCar      Pointer to Car object
 * @param[in]     speed     Speed to drive (as % of total speed) 
 * @param[in]     direction Direction to drive relative to front of the car
 */
typedef void CarDrive(Car *pCar, uint8_t speed, uint8_t direction);

/* ------------------------ STRUCT DEFINITIONS  ----------------------------- */

/*!
 * Definition of Car structure
 */
struct Car
{
    // Car's speed as a percentage of its maximum speed
    uint8_t        speed;

    // Direction in which Car is driving
    uint8_t        direction;

    // Pointers to each of the Car's Motor's
    Motor         *pFrontLeft;
    Motor         *pFrontRight;
    Motor         *pBackLeft;
    Motor         *pBackRight;

    // Method to drive car given speed and direction
    CarDrive      *carDrive;
};

/* ------------------------ FUNCTION PROTOTYPES ----------------------------- */
CarConstruct carConstruct;
CarDrive     carDrive;

#endif // _CAR_H_
