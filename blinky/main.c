#include <avr/io.h>
#include <util/delay.h>

void init(void) {
    // Set user LED direction to output
    DDRB |= (0x01 << DDB1);
    // Set user LED HIGH
    PORTB |= (0x01 << PINB5);
}

void blink(void) {
    while(1) {

        // Set user LED LOW
        PORTB &= (~(1 << PINB5));
        _delay_ms(1000);

        // Set user LED HIGH
        PORTB |= (1 << PINB5);
        _delay_ms(1000);
    }
}


void main() {
    init();
    blink();
}
