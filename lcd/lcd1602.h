#ifndef LCD1602_H_
#define LCD1602_H_

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

#include "usart.h"
#include "libs/avr-i2c-library/twi_master.h"

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

void lcd1602_init(void);
void lcd1602_set_cursor(uint8_t pos);
void lcd1602_write(char c);
void lcd1602_clear(void);
void lcd1602_rshift(void);
void lcd1602_lshift(void);


#endif /* End LCD1602_H_ */
