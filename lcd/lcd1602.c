#include "lcd1602.h"

#include <util/delay.h>

#include "usart.h"
#include "libs/avr-i2c-library/twi_master.h"


uint8_t BLACKLIGHT_MASK = _BV(LCD_LED_PIN);

uint8_t LCD_LINES = 1;

static void _pcf8574_write(uint8_t d);
static void _send_command(uint8_t command, bool rs, bool rw);

/* Initialize I2C module */
void lcd1602_init(lcd_dots_t dots, lcd_lines_t lines){
    /* Initialize I2C and signal external pull-ups are used */
    tw_init(TW_FREQ_100K, false);

    /* Initial required delay before communicating */
    _delay_ms(500);

    /* Enable 4-bit mode operation */
    _send_command(0x02, 0, 0);

    /* Enable 4-bit with 1/2 lines and 5x8/5x10 characters */
    uint8_t function_set = _BV(LCD_FS_DL);

    if (dots == LCD_DOTS_5x10) {
        /* Set flag for 5x10 dots characters */
        function_set |= _BV(LCD_FS_F);
    }
    if(lines == LCD_LINES_2) {
        /* Set flag for 2 lines */
        LCD_LINES = 2;
        function_set |= _BV(LCD_FS_N);
    }

    _send_command(function_set, 0, 0);

    /* Set cursor increment and don't accompany display shift */
    _send_command(0x06, 0, 0);

    /* Turn on display, cursor blinking and cursor character */
    _send_command(0x0f, 0, 0);

    /* Clear Display */
    lcd1602_clear();
};

/*
 * Set cursor position
 *
 * index: where to place cursor
 * line: which line to place cursor
 *
 *
 */
void lcd1602_set_cursor(uint8_t index, uint8_t line) {
    uint8_t pos = (index % 0x40) + ((line % LCD_LINES) * 0x40);

    uint8_t command = (pos & 0b01111111) | _BV(LCD_D7_PIN);
    _send_command(command, 0, 0);
}

/* Write a character to the LCD display */
void lcd1602_write(char c) {
    _send_command(c, 1, 0);
}

/* Right shift display */
void lcd1602_rshift(void) {
    _send_command(0x1f, 0, 0);
}

/* Left shift display */
void lcd1602_lshift(void) {
    _send_command(0x18, 0, 0);
}

/* Clear screen */
void lcd1602_clear(void) {
    _send_command(0x01, 0, 0);
    /* Wait, because clearing screen takes longer */
    _delay_us(1600);
}

/* Turn on/off cursor and cursor blinking */
void lcd1602_cursor(bool cursor, bool blinking) {
    uint8_t command = _BV(3) | _BV(LCD_DC_D) | (cursor << LCD_DC_C) | (blinking << LCD_DC_B);
    _send_command(command, 0, 0);
}

/* Turn on/off LCD blacklight */
void lcd1602_blacklight(bool on) {
    if (on) {
        BLACKLIGHT_MASK = _BV(LCD_LED_PIN);
    }else {
        BLACKLIGHT_MASK = 0x00;
    }
    _pcf8574_write(BLACKLIGHT_MASK);
}


/* Private functions */

/* Write a single value to I/O Expander */
static void _pcf8574_write(uint8_t d) {
    uint8_t buf[1];
    buf[0] = d;
    tw_master_transmit(LCD_TWI_ADDR, buf, 1, false);
    return;
};

/* Send command to LCD controller */
static void _send_command(uint8_t data, bool rs,  bool rw) {
    printf("Addr: %x\n", LCD_TWI_ADDR);
    uint8_t low_data = data & 0x0f;
    uint8_t high_data = (data & 0xf0) >> 4;

    /* Write higher four data bits first */
    uint8_t command = _DB(high_data) | _RS(rs) | _RW(rw) | BLACKLIGHT_MASK;
    _pcf8574_write(command);
    _pcf8574_write(command | _BV(LCD_E_PIN));
    _pcf8574_write(command);


    /* Write lower four data bits second */
    command = _DB(low_data) | _RS(rs) | _RW(rw) | BLACKLIGHT_MASK;
    _pcf8574_write(command);
    _pcf8574_write(command | _BV(LCD_E_PIN));
    _pcf8574_write(command);
}

