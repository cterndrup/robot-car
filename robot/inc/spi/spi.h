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
 * @param[in/out]   pRecvByte A pointer to a byte of data. If not NULL, this
 *                            argument is populated with the data sent from
 *                            the slave device. 
 */
void spiMasterSendByte(unsigned char sendByte, unsigned char *pRecvByte);

/*!
 * Function to receive a single byte of data from SPI slave
 * 
 * @return    A unsigned char representing the data received from the slave. 
 */
unsigned char spiMasterRecvByte(void);

/*!
 * Function to terminate SPI send by raising the chip select high
 *
 */
inline void spiMasterSendDone(void);

#endif // _SPI_H_
