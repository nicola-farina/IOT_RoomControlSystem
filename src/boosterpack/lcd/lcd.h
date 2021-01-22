#ifndef SRC_BOOSTERPACK_LCD_LCD_H_
#define SRC_BOOSTERPACK_LCD_LCD_H_

#include <src/boosterpack/lcd/driver/Crystalfontz128x128_ST7735.h> // LCD driver

#include <ti/grlib/grlib.h> // Graphics library

#include <stdbool.h>


#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 128
#define FONT_SIZE 14
#define PADDING 4

void lcd_init();
void lcd_draw_screen();
void lcd_draw_alarm_status(bool enabled);

#endif
