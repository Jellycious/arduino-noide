#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"
#include "lcd1602.h"

static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar, 
        usart_getchar, _FDEV_SETUP_RW);

void init(void) {
    /* Set user LED as output. */
    DDRB |= (1 << DDB5);
    /* Set user LED to high */
    PORTB |= (1 << PINB5);
    
    usart_init(USART_BAUD_9600);
    lcd1602_init(LCD_DOTS_5x8, LCD_LINES_2);
}

void cursor_test(void) {
    while(1)
    {
        for (int i = 0; i < 16; i++) {
            lcd1602_set_cursor(i, i % 2);
            lcd1602_cursor(i%2, (i+1)%2);
            _delay_ms(1000);
        }
    }
}

void writing_test(void) {
    /* Hide cursor */
    lcd1602_cursor(false, false);
    lcd1602_set_cursor(0, 0);

    char start = 0xa1;
    char end = 0xdf;

    while(1)
    {
        for(int i = 0; i < 0x68; i++)
        {
            char c = i;
            if(c > (end - start))
            {
                c = c % (end - start);
            }

            c = c + start;
            lcd1602_write(c);
        }

        lcd1602_set_cursor(0, 0);

        for(int i = 0; i < 16; i++)
        {
            lcd1602_lshift();
            _delay_ms(1);
            lcd1602_set_cursor(i, i % 2);
            _delay_ms(2000);
        }

        lcd1602_clear();
    }
}


int main() {
    init();
    stdout = stdin = &mystdout;

    writing_test();
    return 1;
}
