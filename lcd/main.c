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

void loop(void) {
    lcd1602_set_cursor(0x00);

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

        for(int i = 0; i < 10; i++)
        {
            lcd1602_lshift();
            _delay_ms(800);
        }

        lcd1602_clear();
    }
}


int main() {
    init();
    stdout = stdin = &mystdout;

    loop();
    return 1;
}
