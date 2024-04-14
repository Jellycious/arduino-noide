#include <stdio.h>

#include "usart.h"

void usart_init() {
    /* Set baud rate */
    #define BAUD 9600
    #include <util/setbaud.h>
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    
    // Enable transmitter and receiver
    UCSR0B = (1 << RXEN0)|(1 << TXEN0);
}

int usart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        usart_putchar('\r', stream);
    }
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    return 0;
}
int usart_getchar(FILE *stream) {
    /* Blocking */
    char c;
    /* Block until there is data available */
    loop_until_bit_is_set(UCSR0A, RXC0);
    c = UDR0;
    return c;
}
