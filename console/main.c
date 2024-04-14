#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"

static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar, 
        usart_getchar, _FDEV_SETUP_RW);

void init(void) {
    /* Set user LED as output. */
    DDRB |= (1 << DDB5);
    /* Set user LED to high */
    PORTB |= (1 << PINB5);
    
    usart_init();
}

void loop(void) {
    while(1) {
        printf("Hello World\n");
        _delay_ms(1000);
    }
}


void main() {
    init();
    stdout = stdin = &mystdout;

    loop();
}
