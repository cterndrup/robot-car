/* Implementation file for UART Interface */

/* ------------------------- SYSTEM INCLUDES -------------------------------- */
#include <stdlib.h>

/* ------------------------- APPLICATION INCLUDES --------------------------- */
#include "uart/uart.h"

/* ------------------------- FUNCTION DEFINITIONS --------------------------- */

/*!
 * @ref uart.h for function documentation
 */
void
uartConstruct
(
    UART             *uart,
    REG8             *UDRn,
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
    if (uart == NULL)
        return;

    // Copy registers
    uart->UDRn   = UDRn;
    uart->UCSRnA = UCSRnA;   
    uart->UCSRnB = UCSRnB;   
    uart->UCSRnC = UCSRnC;
    uart->UBRRnH = UBRRnH;
    uart->UBRRnL = UBRRnL;

    uart->parity   = parity;
    uart->dataSize = dataSize;
    uart->baud     = baud;
}

/*!
 * @ref uart.h for function documentation
 */
void
uartInit
(
    UART             *uart,
    REG8             *PRRn,
    UART_PR_BIT       PRBitn
)
{
    REG8      *UCSRnA;
    UART_BAUD  baud;

    if (uart == NULL)
        return;

    // Power Reduction Register n init
    CLEAR_BIT(*PRRn, PRBitn);

    //
    // USART Control and Status Register A init
    // --> Clear the transmit complete flag
    // --> Disable double transmit speed
    // --> Disable multi-processor communication mode
    //
    UCSRnA = uart->UCSRnA;
    CLEAR_BIT(*UCSRnA, TXCn);
    CLEAR_BIT(*UCSRnA, U2Xn);
    CLEAR_BIT(*UCSRnA, MPCMn);

    //
    // USART Control and Status Register C init
    // --> Set USART mode to asynchronous
    // --> Disable parity
    //
    *(uart->UCSRnC) = 0x06 | (uart->parity << 4) | uart->dataSize;

    //
    // USART Baud Rate Registers init
    // --> Set Baud Rate
    //
    baud = uart->baud;
    *(uart->UBRRnH) = baud >> 8;
    *(uart->UBRRnL) = 0x00ff & baud;

    //
    // USART Control and Status Register B init
    // --> Enable transmit
    // --> Disable receive
    //
    *(uart->UCSRnB) = 0x08;
}

/*!
 * @ref uart.h for function documentation
 */
void
uartTX(UART *uart, uint8_t data)
{
    REG8 *UCSRnA;

    if (uart == NULL)
        return;

    // Wait until the UART data register is empty
    UCSRnA = uart->UCSRnA;
    while (!(*UCSRnA & (1 << UDREn)));

    // Transmit the byte
    *(uart->UDRn) = data; 
}
