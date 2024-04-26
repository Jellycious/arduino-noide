#ifndef LCD1602_H_
#define LCD1602_H_

#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>

/* I2C address of LCD display */
#define LCD_TWI_ADDR 0x27

/* Define I2C pins */
/* Overrides the pin definitions in the I2C library */
#undef TW_SCL_PIN
#define TW_SCL_PIN  PORTC5

#undef TW_SDA_PIN
#define TW_SDA_PIN  PORTC4

#undef TW_PORT
#define TW_PORT     PORTC   /* Data output port */

#undef TW_DDR
#define TW_DDR      DDRC    /* Data direction port */

/* Bit function helpers */
#define _RS(bit) (bit << LCD_RS_PIN)
#define _RW(bit) (bit << LCD_RW_PIN)
#define _DB(nibble) (nibble << LCD_D4_PIN)

/* Internal wiring between I/O Expander and LCD controller */
/* For example: Bit 0 of I/O expander goes to RS pin of LCD controller */
#define LCD_RS_PIN 0
#define LCD_RW_PIN 1
#define LCD_E_PIN 2
#define LCD_LED_PIN 3
#define LCD_D4_PIN 4
#define LCD_D5_PIN 5
#define LCD_D6_PIN 6
#define LCD_D7_PIN 7

#define LCD_FS_DL 4
#define LCD_FS_N 3
#define LCD_FS_F 2

#define LCD_DC_D 2
#define LCD_DC_C 1
#define LCD_DC_B 0

/* LCD configurations options */
typedef enum {
    LCD_DOTS_5x10,
    LCD_DOTS_5x8,
} lcd_dots_t;

typedef enum {
    LCD_LINES_1,
    LCD_LINES_2,
} lcd_lines_t;

void lcd1602_init(lcd_dots_t dots, lcd_lines_t lines);
void lcd1602_set_cursor(uint8_t index, uint8_t line);
void lcd1602_cursor(bool cursor, bool blinking);
void lcd1602_write(char c);
void lcd1602_clear(void);
void lcd1602_rshift(void);
void lcd1602_lshift(void);


#endif /* End LCD1602_H_ */
