#include <stdio.h>

#include "usart.h"

static void usart_4800() {
    #undef BAUD
    #define BAUD 4800
    #include <util/setbaud.h>
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    /* Enable Transmitter and Receiver */
    UCSR0B = (1 << RXEN0)|(1 << TXEN0);
    return;
}

static void usart_9600() {
    #undef BAUD
    #define BAUD 9600
    #include <util/setbaud.h>
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    /* Enable Transmitter and Receiver */
    UCSR0B = (1 << RXEN0)|(1 << TXEN0);
    return;
}

static void usart_19200() {
    #undef BAUD
    #define BAUD 19200
    #include <util/setbaud.h>
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    /* Enable Transmitter and Receiver */
    UCSR0B = (1 << RXEN0)|(1 << TXEN0);
    return;
}

static void usart_38400() {
    #undef BAUD
    #define BAUD 38400
    #include <util/setbaud.h>
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    /* Enable Transmitter and Receiver */
    UCSR0B = (1 << RXEN0)|(1 << TXEN0);
    return;
}

static void usart_57600() {
    #undef BAUD
    #define BAUD 57600
    #include <util/setbaud.h>
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    /* Enable Transmitter and Receiver */
    UCSR0B = (1 << RXEN0)|(1 << TXEN0);
    return;
}

void usart_init(USART_BAUD_t baud) {

    /* Set baud rate */
    switch(baud) {
        case USART_BAUD_4800:
            usart_4800();
            break;
        case USART_BAUD_9600:
            usart_9600();
            break;
        case USART_BAUD_19200:
            usart_19200();
            break;
        case USART_BAUD_38400:
            usart_38400();
            break;
        case USART_BAUD_57600:
            usart_57600();
            break;
        default:
            break;
    }
}

int usart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        /* Insert extra carriage return before new line */
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
