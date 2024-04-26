#include "lcd1602.h"

uint8_t BLACKLIGHT_MASK = _BV(LCD_LED_PIN);
uint8_t COLS = 0x00; 
bool TWO_LINES = false; 

static void _pcf8574_write(uint8_t d);
static void _send_command(uint8_t command, bool rs, bool rw);

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

/* Initialize I2C module */
void lcd1602_init(void){
    tw_init(TW_FREQ_100K, false);

    _delay_ms(500);

    /* Enable 4-bit mode operation */
    _send_command(0x02, 0, 0);

    /* Enable 4-bit with 2 lines and 5x8 characters */
    _send_command(0x28, 0, 0);

    /* Turn on display, cursor blinking and cursor character */
    _send_command(0x0f, 0, 0);

    /* Clear Display */
    lcd1602_clear();



    return;
};

/* Set cursor position */
void lcd1602_set_cursor(uint8_t pos) {
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

/* Turn on/off LCD blacklight */
void lcd1602_blacklight(bool on) {
    if (on) {
        BLACKLIGHT_MASK = _BV(LCD_LED_PIN);
    }else {
        BLACKLIGHT_MASK = 0x00;
    }
    _pcf8574_write(BLACKLIGHT_MASK);
}
