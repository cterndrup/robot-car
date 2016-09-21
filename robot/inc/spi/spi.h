/* Header file for SPI Interface */

#ifndef _SPI_H_
#define _SPI_H_

/* ------------------------ INCLUDES ---------------------------------------- */
#include <avr/io.h>

/* ------------------------ MACROS AND DEFINES ------------------------------ */

/*!
 * There is only one pin for SS, SCK, MOSI, and MISO on the ATmega 2560. 
 * Therefore, it makes sense to define their
 * corresponding pin names to more SPI friendly names.
 */
#define DDR_SPI     DDRB
#define SPI_PORT    PORTB

#define SS          (0)
#define SCK         (1)
#define MOSI        (2)
#define MISO        (3)

/* ------------------------ FUNCTION PROTOTYPES ----------------------------- */

/*!
 * Function to initialize SPI as master
 */
void spiMasterInit(void);

/*!
 * Function to transmit a single byte of data to SPI slave
 * 
 * @param[in]       sendByte  A byte of data to send to SPI slave
 * @param[in/out]   pRecvByte  A pointer to a byte of data. If not NULL, this
 *                            argument is populated with the data sent from
 *                            the slave device. 
 */
void spiMasterSend(char sendByte, char *pRecvByte);

/*!
 * Function to receive a single byte of data from SPI slave
 * 
 * @param[in] sendByte   A byte of data to send to SPI slave. Ideally,
 *                       this value would be meaningless to the slave
 *                       device. This is needed because the master must
 *                       generate the SCK pulses needed for the slave to
 *                       transmit, which can only be done through a master send.
 *
 * @return    A character representing the data received from the slave. 
 */
char spiMasterRecv(char sendByte);

#endif // _SPI_H_
