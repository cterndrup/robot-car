/*! Implementation file for LCD Interface */

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

    lcd->writeBuffer = uart->UDRn;
}

/*!
 * @ref lcd.h for function documentation
 */
void
lcdCursorCmdSend(LCD *lcd, LCD_CURSOR_CMD cmd)
{
    if (lcd == NULL)
        return;

    *(lcd->writeBuffer) = cmd; 
}

/*!
 * @ref lcd.h for function documentation
 */
void
lcdBacklightCmdSend(LCD *lcd, LCD_BACKLIGHT_CMD cmd)
{
    if (lcd == NULL)
        return;

    *(lcd->writeBuffer) = cmd;   
}

/*!
 * @ref lcd.h for function documentation
 */
void
lcdDisplayCmdSend(LCD *lcd, LCD_DISPLAY_CMD cmd)
{
    if (lcd == NULL)
        return;

    *(lcd->writeBuffer) = cmd;
}

/*!
 * @ref lcd.h for function documentation
 */
void
lcdCharacterSend(LCD *lcd, char c)
{
    if (lcd == NULL)
        return;

    *(lcd->writeBuffer) = c;
}
