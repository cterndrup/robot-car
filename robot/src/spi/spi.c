/* Implementation file for SPI Interface */

/* ------------------------- SYSTEM INCLUDES -------------------------------- */
#include <stdlib.h>
#include <avr/io.h>

/* ------------------------- APPLICATION INCLUDES --------------------------- */
#include "spi/spi.h"
#include "common/utils.h"

/* ------------------------- FUNCTION DEFINITIONS --------------------------- */

/*!
 * @ref spi.h for function documentation
 */
void
spiMasterInit(void)
{
    // Clear PRSPI bit in PRRO
    CLEAR_BIT(PRR0, PRSPI);

    // MOSI, SCK, and !SS as outputs
    SET_PORT_BIT_OUTPUT(DDR_SPI, SS);
    SET_PORT_BIT_OUTPUT(DDR_SPI, SCK);
    SET_PORT_BIT_OUTPUT(DDR_SPI, MOSI);

    // Select Clock Polarity/Phase
    CLEAR_BIT(SPCR, CPOL);
    CLEAR_BIT(SPCR, CPHA);

    // Select SPI Clock Rate
    CLEAR_BIT(SPCR, SPR1);
    CLEAR_BIT(SPCR, SPR0);

    // Select Master
    SET_BIT(SPCR, MSTR);

    // Enable SPI interrupts
    SET_BIT(SPCR, SPIE);

    // Enable SPI
    SET_BIT(SPCR, SPE);
}

/*!
 * @ref spi.h for function documentation
 */
void
spiMasterSendByte(char sendByte, char *pRecvByte)
{
    // Pull SS low
    CLEAR_BIT(SPI_PORT, SS);

    // Write data to SPI DR
    SPDR = sendByte;

    // Poll until write complete
    while (!(SPSR & (1 << SPIF)));

    //
    // Read the value sent from the slave into byte pointed to by pRecvByte,
    // as long as pRecvByte is not NULL
    //
    if (pRecvByte != NULL)
        *pRecvByte = SPDR;

    //
    // Responsibility of the caller to pull SS high when transmission is 
    // complete
    //
    // TODO: Don't forget to address this.
}

/*!
 * @ref spi.h for function documentation
 */
char
spiMasterRecvByte(char sendByte)
{
    char data;
    spiMasterSendByte(sendByte, &data); 
    return data;
}

/*!
 * @ref spi.h for function documentation
 */
void
spiMasterTerminate(void)
{
    // Pull SS high
    SET_BIT(SPI_PORT, SS);
}
