/* Header file for LCD Interface */

#ifndef _LCD_H_
#define _LCD_H_

/* ------------------------ APPLICATION INCLUDES ---------------------------- */
#include "uart/uart.h"

/* ------------------------ MACROS AND DEFINES ------------------------------ */

/*! Display custom character X */
#define LCD_CMD_CUSTOM_0                    (0x00)
#define LCD_CMD_CUSTOM_1                    (0x01)
#define LCD_CMD_CUSTOM_2                    (0x02)
#define LCD_CMD_CUSTOM_3                    (0x03)
#define LCD_CMD_CUSTOM_4                    (0x04)
#define LCD_CMD_CUSTOM_5                    (0x05)
#define LCD_CMD_CUSTOM_6                    (0x06)
#define LCD_CMD_CUSTOM_7                    (0x07)

/*! Cursor control commands */
#define LCD_CMD_CURSOR_LEFT                 (0x08)
#define LCD_CMD_CURSOR_RIGHT                (0x09)
#define LCD_CMD_CURSOR_LF                   (0x0A)
#define LCD_CMD_CURSOR_FF                   (0x0C)
#define LCD_CMD_CURSOR_CR                   (0x0D)

/*! Backlight on/off */
#define LCD_CMD_BACKLIGHT_ON                (0x11)
#define LCD_CMD_BACKLIGHT_OFF               (0x12)

/*! Display on/off */
#define LCD_CMD_DISP_OFF                    (0x15)
#define LCD_CMD_DISP_ON_NO_CURSOR_NO_BLINK  (0x16)
#define LCD_CMD_DISP_ON_NO_CURSOR_BLINK     (0x17)
#define LCD_CMD_DISP_ON_CURSOR_NO_BLINK     (0x18)
#define LCD_CMD_DISP_ON_CURSOR_BLINK        (0x19)

/*! Display ASCII characters -- send ASCII code over TX line */

/* ------------------------ TYPEDEFS ---------------------------------------- */

/*!
 * Forward declaration of LCD structure
 */
typedef struct LCD LCD;

/*!
 * LCD Custom Commands
 */
typedef enum LCD_CUSTOM_CMD
{
    LCD_CUSTOM_CMD_0 = LCD_CMD_CUSTOM_0,
    LCD_CUSTOM_CMD_1 = LCD_CMD_CUSTOM_1,
    LCD_CUSTOM_CMD_2 = LCD_CMD_CUSTOM_2,
    LCD_CUSTOM_CMD_3 = LCD_CMD_CUSTOM_3,
    LCD_CUSTOM_CMD_4 = LCD_CMD_CUSTOM_4,
    LCD_CUSTOM_CMD_5 = LCD_CMD_CUSTOM_5,
    LCD_CUSTOM_CMD_6 = LCD_CMD_CUSTOM_6,
    LCD_CUSTOM_CMD_7 = LCD_CMD_CUSTOM_7
} LCD_CUSTOM_CMD;

/*!
 * LCD Cursor Control Commands
 */
typedef enum LCD_CURSOR_CMD
{
    LCD_CURSOR_CMD_LEFT  = LCD_CMD_CURSOR_LEFT,
    LCD_CURSOR_CMD_RIGHT = LCD_CMD_CURSOR_RIGHT,
    LCD_CURSOR_CMD_LF    = LCD_CMD_CURSOR_LF,
    LCD_CURSOR_CMD_FF    = LCD_CMD_CURSOR_FF,
    LCD_CURSOR_CMD_CR    = LCD_CMD_CURSOR_CR
} LCD_CURSOR_CMD;

/*!
 * LCD Backlight Commands
 */
typedef enum LCD_BACKLIGHT_CMD
{
    LCD_BACKLIGHT_CMD_ON  = LCD_CMD_BACKLIGHT_ON,
    LCD_BACKLIGHT_CMD_OFF = LCD_CMD_BACKLIGHT_OFF
} LCD_BACKLIGHT_CMD;

/*!
 * LCD Display Commands
 */
typedef enum LCD_DISPLAY_CMD
{
    LCD_DISPLAY_CMD_OFF                   = LCD_CMD_DISP_OFF,
    LCD_DISPLAY_CMD_ON_NO_CURSOR_NO_BLINK = LCD_CMD_DISP_ON_NO_CURSOR_NO_BLINK,
    LCD_DISPLAY_CMD_ON_NO_CURSOR_BLINK    = LCD_CMD_DISP_ON_NO_CURSOR_BLINK,
    LCD_DISPLAY_CMD_ON_CURSOR_BLINK       = LCD_CMD_DISP_ON_CURSOR_BLINK
} LCD_DISPLAY_CMD;

/*!
 * Function to construct LCD object
 *
 * @param[in/out] lcd   Pointer to LCD object
 * @param[in/out] uart  Pointer to UART object
 */
typedef
void LcdConstruct(LCD *lcd, UART *uart);

/*!
 * Function to send cursor control command to LCD
 *
 * @param[in/out] lcd   Pointer to LCD object
 * @param[in]     cmd   Cursor command to send to LCD
 */
typedef
void LcdCursorCmdSend(LCD *lcd, LCD_CURSOR_CMD cmd);

/*!
 * Function to send backlight control command to LCD
 *
 * @param[in/out] lcd   Pointer to LCD object
 * @param[in]     cmd   Backlight command to send to LCD
 */
typedef
void LcdBacklightCmdSend(LCD *lcd, LCD_BACKLIGHT_CMD cmd);

/*!
 * Function to send display control command to LCD
 *
 * @param[in/out] lcd   Pointer to LCD object
 * @param[in]     cmd   Display command to send to LCD
 */
typedef
void LcdDisplayCmdSend(LCD *lcd, LCD_DISPLAY_CMD cmd);

/*!
 * Function to send character to LCD
 *
 * @param[in/out] lcd   Pointer to LCD object
 * @param[in]     c     Character to send to LCD
 */
typedef
void LcdCharacterSend(LCD *lcd, char c);

/*!
 * Function to write character string to LCD
 *
 * @param[in/out] lcd   Pointer to LCD object
 * @param[in]     str   String to send to LCD
 */
typedef
void LcdWrite(LCD *lcd, const char *str);

/*!
 * Function to write character string to LCD followed by a new line
 *
 * @param[in/out] lcd   Pointer to LCD object
 * @param[in]     str   String to send to LCD
 */
typedef
void LcdPrintln(LCD *lcd, const char *str);

/*!
 * Function to clear LCD screen
 *
 * @param[in/out] lcd   Pointer to LCD object
 */
typedef
void LcdClear(LCD *lcd);

/* ------------------------ STRUCTURE DEFINITION  --------------------------- */

/*!
 * LCD object
 */
struct LCD
{
    // Pointer to UART object
    UART *uart;

    LcdCursorCmdSend    *lcdCursorCmdSend;
    LcdBacklightCmdSend *lcdBacklightCmdSend;
    LcdDisplayCmdSend   *lcdDisplayCmdSend;
    LcdCharacterSend    *lcdCharacterSend;
    LcdWrite            *lcdWrite;
    LcdPrintln          *lcdPrintln;
    LcdClear            *lcdClear;
};

/* ------------------------ FUNCTION PROTOTYPES ----------------------------- */
LcdConstruct        lcdConstruct;
LcdCursorCmdSend    lcdCursorCmdSend;
LcdBacklightCmdSend lcdBacklightCmdSend;
LcdDisplayCmdSend   lcdDisplayCmdSend;
LcdCharacterSend    lcdCharacterSend;
LcdWrite            lcdWrite;
LcdPrintln          lcdPrintln;
LcdClear            lcdClear;

#endif // _LCD_H_
