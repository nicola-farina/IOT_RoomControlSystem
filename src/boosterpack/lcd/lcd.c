#include <src/boosterpack/lcd/lcd.h>

#include <string.h>

/* Graphics context to use with graphics library */
Graphics_Context g_sContext;

/* Initialize the LCD */
void lcd_init() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);

    // Set foreground and background color
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);

    // Set font
    Graphics_setFont(&g_sContext, &g_sFontCmss14);
}

/* Draw the main screen of the alarm system */
void lcd_draw_screen() {
    char text[20] = "Room Control System";
    uint8_t line = 0, lineHeight = FONT_SIZE + (PADDING*2);

    // Draw heading text
    Graphics_drawStringCentered(
        &g_sContext,
        (int8_t *)text, AUTO_STRING_LENGTH,
        DISPLAY_WIDTH/2, FONT_SIZE/2,
        OPAQUE_TEXT
    );
    line++;

    // Draw horizontal line
    Graphics_drawLineH(&g_sContext, PADDING, DISPLAY_WIDTH-PADDING, line*lineHeight);

    // Draw alarm status text
    strcpy(text, "Alarm Status");
    Graphics_drawStringCentered(
        &g_sContext,
        (int8_t *)text, AUTO_STRING_LENGTH,
        DISPLAY_WIDTH/2, (line*lineHeight)+(FONT_SIZE/2),
        OPAQUE_TEXT
    );

    // Draw alarm status
    lcd_draw_alarm_status(0);
}

/* Draw the text saying if the alarm is ON or OFF */
void lcd_draw_alarm_status(bool enabled) {
    char text[5];
    if(enabled) {
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_DARK_GREEN);
        strcpy(text, " ON ");
    }
    else {
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
        strcpy(text, "OFF");
    }

    // Set a bigger font
    Graphics_setFont(&g_sContext, &g_sFontCmss32b);

    // Write either ON or OFF
    Graphics_drawStringCentered(
        &g_sContext,
        (int8_t *)text, AUTO_STRING_LENGTH,
        DISPLAY_WIDTH/2, (3*FONT_SIZE+PADDING*2)+(FONT_SIZE/2),
        OPAQUE_TEXT
    );
}
