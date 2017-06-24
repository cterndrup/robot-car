/*! Tests for BLE */

#include "car/car.h"
#include "ble/ble.h"
#include "lcd/lcd.h"

// This build dependency is flawed.
Car car;

// Tests
uint8_t blePingTest(BLE *pBLE);
uint8_t bleInfoTest(BLE *pBLE);

int main(void)
{
    uint8_t res1, res2;
    UART    uart;
    LCD     lcd;
    BLE     ble;

    // UART init
    uartConstruct(&uart,
                  &UDR0,
                  &UCSR0A,
                  &UCSR0B,
                  &UCSR0C,
                  &UBRR0H,
                  &UBRR0L,
                  UART_PARITY_MODE_DISABLED,
                  UART_CHAR_SIZE_8,
                  UART_BAUD_9600);

    uartInit(&uart, &PRR0, UART_PR_PRUSART0);

    // LCD init
    lcdConstruct(&lcd, &uart);
    lcd.lcdDisplayCmdSend(&lcd, LCD_DISPLAY_CMD_ON_CURSOR_BLINK);
    lcd.lcdBacklightCmdSend(&lcd, LCD_BACKLIGHT_CMD_ON);

    // SPI init
    spiMasterInit();

    // BLE init
    bleConstruct(&ble);
    ble.bleInitialize(&ble);

    // BLE tests
    res1 = blePingTest(&ble);
    if (res1) {
        lcd.lcdWrite(&lcd, "PING TEST: FAILED");
    } else {
        lcd.lcdWrite(&lcd, "PING TEST: PASSED");
    }

    res2 = bleInfoTest(&ble);
    if (res2) {
        lcd.lcdWrite(&lcd, "INFO TEST: FAILED");
    } else {
        lcd.lcdWrite(&lcd, "INFO TEST: PASSED");
    } 

    return 0;
}

uint8_t blePingTest(BLE *pBLE)
{
    return (uint8_t)(pBLE->blePing(pBLE));
}

uint8_t bleInfoTest(BLE *pBLE)
{
    char response[3];
    response[0] = 0; response[1] = 0; response[2] = 0;

    pBLE->bleInfo(pBLE, response, 3);

    return !(response[0] == 'B' && response[1] == 'L' && response[2] == 'E');
}
