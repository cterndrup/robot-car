/* Implementation file for UART Interface */

/* ------------------------- SYSTEM INCLUDES -------------------------------- */
#include <avr/io.h>

/* ------------------------- APPLICATION INCLUDES --------------------------- */
#include "uart/uart.h"
#include "common/utils.h"

/* ------------------------- FUNCTION DEFINITIONS --------------------------- */

/*!
 * @ref uart.h for function documentation
 */
void
uartInit
(
    REG8             *PRRn,
    UART_PR_BIT       PRBitn,
    REG8             *UCSRnA,
    REG8             *UCSRnB,
    REG8             *UCSRnC,
    REG8             *UBRRnH,
    REG8             *UBRRnL,
    UART_PARITY_MODE  parity,
    UART_CHAR_SIZE    dataSize,
    UART_BAUD         baud
)
{
    // Power Reduction Register n init
    CLEAR_BIT(*PRRn, PRBitn);

    //
    // USART Control and Status Register A init
    // --> Clear the transmit complete flag
    // --> Disable double transmit speed
    // --> Disable multi-processor communication mode
    //
    CLEAR_BIT(*UCSRnA, TXCn);
    CLEAR_BIT(*UCSRnA, U2Xn);
    CLEAR_BIT(*UCSRnA, MPCMn);

    //
    // USART Control and Status Register C init
    // --> Set USART mode to asynchronous
    // --> Disable parity
    //
    *UCSRnC = 0x06 | (parity << 4) | dataSize;

    //
    // USART Baud Rate Registers init
    // --> Set Baud Rate
    //
    *UBRRnH = baud >> 8;
    *UBRRnL = 0x00ff & baud;

    //
    // USART Control and Status Register B init
    // --> Enable transmit
    // --> Disable receive
    //
    *UCSRnB = 0x08;
}

/*!
 * @ref uart.h for function documentation
 */
void
uartTX(REG8 *UDRn, REG8 *UCSRnA, uint8_t data)
{
    // Wait until the UART data register is empty
    while (!(*UCSRnA & (1 << UDREn)));

    // Transmit the byte
    *UDRn = data; 
}
