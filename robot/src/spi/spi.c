/* Implementation file for SPI Interface */

/* ------------------------- SYSTEM INCLUDES -------------------------------- */
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

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

    // MISO as input
    SET_PORT_BIT_INPUT(DDR_SPI, MISO);

    // Select Clock Polarity/Phase
    CLEAR_BIT(SPCR, CPOL);
    CLEAR_BIT(SPCR, CPHA);

    // Select SPI Clock Rate
    CLEAR_BIT(SPCR, SPR1);
    CLEAR_BIT(SPCR, SPR0);

    // Select Master
    SET_BIT(SPCR, MSTR);

    // Disable SPI interrupts
    CLEAR_BIT(SPCR, SPIE);

    // Enable SPI
    SET_BIT(SPCR, SPE);
}

/*!
 * @ref spi.h for function documentation
 */
void
spiMasterSendByte(uint8_t sendByte, uint8_t *pRecvByte)
{
    // Pull SS low
    CLEAR_BIT(SPI_PORT, SS);

    // Enforce 100 us delay before sending data -- required by SDEP
    _delay_us(100);

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
}

/*!
 * @ref spi.h for function documentation
 */
uint8_t
spiMasterRecvByte(void)
{
    uint8_t data;
    spiMasterSendByte(0xFF, &data);
    return data;
}

/*!
 * @ref spi.h for function documentation
 */
inline void
spiMasterSendDone(void)
{
    // Pull SS high
    SET_BIT(SPI_PORT, SS);
}
