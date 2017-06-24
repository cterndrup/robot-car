/*! Tests for LCD */

#include <avr/io.h>
#include <util/delay.h>
#include "lcd/lcd.h"

int main(void)
{
    UART uart;
    LCD  lcd;

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

    lcdConstruct(&lcd, &uart);
    lcd.lcdDisplayCmdSend(&lcd, LCD_DISPLAY_CMD_ON_CURSOR_BLINK);
    lcd.lcdBacklightCmdSend(&lcd, LCD_BACKLIGHT_CMD_ON);
    lcd.lcdCursorCmdSend(&lcd, LCD_CURSOR_CMD_FF); _delay_ms(10);
    lcd.lcdWrite(&lcd, "TEST!");

    while(1);

    return 0;
}
