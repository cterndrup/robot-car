/*! Implementation file for LCD Interface */

/* ------------------------- SYSTEM INCLUDES -------------------------------- */
#include <stdlib.h>

/* ------------------------- APPLICATION INCLUDES --------------------------- */
#include "lcd/lcd.h"
#include "common/utils.h"

/* ------------------------- FUNCTION DEFINITIONS --------------------------- */

/*!
 * @ref lcd.h for function documentation
 */
void
lcdConstruct(LCD *lcd, UART *uart)
{
    if (lcd == NULL || uart == NULL)
        return;

    lcd->uart = uart;

    lcd->lcdCursorCmdSend    = lcdCursorCmdSend;
    lcd->lcdBacklightCmdSend = lcdBacklightCmdSend;
    lcd->lcdDisplayCmdSend   = lcdDisplayCmdSend;
    lcd->lcdCharacterSend    = lcdCharacterSend;
    lcd->lcdWrite            = lcdWrite;
}

/*!
 * @ref lcd.h for function documentation
 */
void
lcdCursorCmdSend(LCD *lcd, LCD_CURSOR_CMD cmd)
{
    if (lcd == NULL)
        return;

    uartTX(lcd->uart, (uint8_t)cmd);
}

/*!
 * @ref lcd.h for function documentation
 */
void
lcdBacklightCmdSend(LCD *lcd, LCD_BACKLIGHT_CMD cmd)
{
    if (lcd == NULL)
        return;

    uartTX(lcd->uart, (uint8_t)cmd);
}

/*!
 * @ref lcd.h for function documentation
 */
void
lcdDisplayCmdSend(LCD *lcd, LCD_DISPLAY_CMD cmd)
{
    if (lcd == NULL)
        return;

    uartTX(lcd->uart, (uint8_t)cmd);
}

/*!
 * @ref lcd.h for function documentation
 */
void
lcdCharacterSend(LCD *lcd, char c)
{
    if (lcd == NULL)
        return;

    uartTX(lcd->uart, (uint8_t)c);
}

/*!
 * @ref lcd.h for function documentation
 */
void
lcdWrite(LCD *lcd, const char *str)
{
    if (lcd == NULL || str == NULL)
        return;

    while (*str != '\0')
    {
        lcd->lcdCharacterSend(lcd, *str);
        str++;
    }
}
