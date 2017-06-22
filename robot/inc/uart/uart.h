/* Header file for UART Interface */

#ifndef _UART_H_
#define _UART_H_

/* ------------------------- SYSTEM INCLUDES -------------------------------- */
#include <avr/io.h>

/* ------------------------- APPLICATION INCLUDES --------------------------- */
#include "common/utils.h"

/* ------------------------ MACROS AND DEFINES ------------------------------ */

/*!
 * UART Control and Status Register A bit definitions
 */
#define RXCn    (7) // UART Receive Complete
#define TXCn    (6) // UART Transmit Complete
#define UDREn   (5) // UART Data Register Empty
#define FEn     (4) // Frame Error
#define DORn    (3) // Data OverRun
#define UPEn    (2) // UART Parity Error
#define U2Xn    (1) // Double the UART Transmission Speed
#define MPCMn   (0) // Multi-processor Communication Mode

/*!
 * UART Control and Status Register B bit definitions
 */
#define RXCIEn  (7) // RX Complete Interrupt Enable n
#define TXCIEn  (6) // TX Complete Interrupt Enable n
#define UDRIEn  (5) // UART Data Register Empty Interrupt Enable n
#define RXENn   (4) // Receiver Enable n
#define TXENn   (3) // Transmitter Enable n
#define UCSZn2  (2) // Character Size n
#define RXB8n   (1) // Receive Data Bit 8 n
#define TXB8n   (0) // Transmit Data Bit 8 n

/*!
 * UART Control and Status Register C bit definitions
 */
#define UMSELn1 (7) // UART Mode Select bit 1
#define UMSELn0 (6) // UART Mode Select bit 0
#define UPMn1   (5) // Parity Mode bit 1
#define UPMn0   (4) // Parity Mode bit 0
#define USBSn   (3) // Stop Bit Select
#define UCSZn1  (2) // Character Size bit 1
#define UCSZn0  (1) // Character Size bit 0
#define UCPOLn  (0) // Clock Polarity

/* ------------------------ TYPEDEFS ---------------------------------------- */

/*!
 * Forward declaration of UART structure
 */
typedef struct UART UART;

/*!
 * UART parity mode bits
 */
typedef enum UART_PARITY_MODE
{
    UART_PARITY_MODE_DISABLED = 0b00,
    UART_PARITY_MODE_EVEN     = 0b10,
    UART_PARITY_MODE_ODD      = 0b11
} UART_PARITY_MODE;

/*!
 * UART data size
 */
typedef enum UART_CHAR_SIZE
{
    UART_CHAR_SIZE_5 = 0b000,
    UART_CHAR_SIZE_6 = 0b001,
    UART_CHAR_SIZE_7 = 0b010,
    UART_CHAR_SIZE_8 = 0b011
} UART_CHAR_SIZE;

/*!
 * UART baud rate (these are the values to be written to UBRRn)
 */
typedef enum UART_BAUD
{
    UART_BAUD_2400  = 0x19,
    UART_BAUD_4800  = 0x0C,
    UART_BAUD_9600  = 0x06,
    UART_BAUD_14400 = 0x03,
    UART_BAUD_19200 = 0x02
} UART_BAUD;

/*!
 * UART Power Reduction Register bits
 */
typedef enum UART_PR_BIT
{
    UART_PR_PRUSART0 = PRUSART0, // In PRR0
    UART_PR_PRUSART1 = PRUSART1, // In PRR1
    UART_PR_PRUSART2 = PRUSART2, // In PRR1
    UART_PR_PRUSART3 = PRUSART3  // In PRR1
} UART_PR_BIT;

/*!
 * Function to construct UART
 *
 * @param[in/out] uart      Pointer to UART object
 * @param[in/out] UDRn      UART data register n
 * @param[in/out] UCSRnA    UART Control and Status Register A
 * @param[in/out] UCSRnB    UART Control and Status Register B
 * @param[in/out] UCSRnC    UART Control and Status Register C
 * @param[in/out] UBRRnH    UART Baud Rate Register High
 * @param[in/out] UBRRnL    UART Baud Rate Register Low
 * @param[in]     parity    Parity mode for UART frame
 * @param[in]     dataSize  Size of data portion of UART frame
 * @param[in]     baud      UART Baud Rate
 */
typedef void
UartConstruct(UART             *uart,
              REG8             *UDRn,
              REG8             *UCSRnA,
              REG8             *UCSRnB,
              REG8             *UCSRnC,
              REG8             *UBRRnH,
              REG8             *UBRRnL,
              UART_PARITY_MODE  parity,
              UART_CHAR_SIZE    dataSize,
              UART_BAUD         baud);

/*!
 * Function to initialize UART
 *
 * @param[in/out] uart      Pointer to UART object
 * @param[in/out] PRRn      Power Reduction Register n
 * @param[in]     PRBitn    Power Reduction UART n bit
 */
typedef void
UartInit(UART        *uart,
         REG8        *PRRn,
         UART_PR_BIT  PRBITn);

/*!
 * Function transmit a single data byte of UART
 *
 * @param[in/out]  uart     Pointer to UART object
 * @param[in]      data     A byte of data to transmit over UART TX
 */
typedef void
UartTX(UART *uart, uint8_t data);

/* ------------------------ STRUCTURE DEFINITION ---------------------------- */

/*!
 * UART object
 */
struct UART
{
    // UART Data Register
    REG8 *UDRn;

    // UART Status and Control Registers
    REG8 *UCSRnA;
    REG8 *UCSRnB;
    REG8 *UCSRnC;

    // UART Baud Rate Registers
    REG8 *UBRRnH;
    REG8 *UBRRnL;

    // UART Parity
    UART_PARITY_MODE parity;

    // UART Data Size
    UART_CHAR_SIZE   dataSize;

    // UART Baud Rate
    UART_BAUD        baud;
};

/* ------------------------ FUNCTION PROTOTYPES ----------------------------- */
UartConstruct uartConstruct;
UartInit      uartInit;
UartTX        uartTX;

#endif // _UART_H_
