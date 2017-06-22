/* Header file for UART Interface */

#ifndef _UART_H_
#define _UART_H_

/* ------------------------- APPLICATION INCLUDES --------------------------- */
#include "common/utils.h"

/* ------------------------ MACROS AND DEFINES ------------------------------ */

/*!
 * UART parity mode bits
 */
#define UART_PARITY_MODE_DISABLED   (0b00)
#define UART_PARITY_MODE_EVEN       (0b10)
#define UART_PARITY_MODE_ODD        (0b11)

/*!
 * UART data size
 */
#define UART_CHAR_SIZE_5            (0b000)
#define UART_CHAR_SIZE_6            (0b001)
#define UART_CHAR_SIZE_7            (0b010)
#define UART_CHAR_SIZE_8            (0b011)

/*!
 * UART baud rate (these are the values to be written to UBRRn)
 */
#define UART_BAUD_2400              (0x19)
#define UART_BAUD_4800              (0x0C)
#define UART_BAUD_9600              (0x06)
#define UART_BAUD_14400             (0x03)
#define UART_BAUD_19200             (0x02)

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

/* ------------------------ FUNCTION PROTOTYPES ----------------------------- */

/*!
 * Function to initialize UART
 *
 * @param[in/out] PRRn      Power Reduction Register n
 * @param[in/out] UCSRnA    UART Control and Status Register A
 * @param[in/out] UCSRnB    UART Control and Status Register B
 * @param[in/out] UCSRnC    UART Control and Status Register C
 * @param[in/out] UBRRnH    UART Baud Rate Register High
 * @param[in/out] UBRRnL    UART Baud Rate Register Low
 */
void uartInit(REG8 *PRRn,
              REG8 *UCSRnA,
              REG8 *UCSRnB,
              REG8 *UCSRnC,
              REG8 *UBRRnH,
              REG8 *UBRRnL);

/*!
 * Function transmit a single data byte of UART
 *
 * @param[in/out]  UDRn     UART data register n
 * @param[in]      data     A byte of data to transmit over UART TX
 */
void uartTX(REG8 *UDRn, uint8_t data);

#endif // _UART_H_
