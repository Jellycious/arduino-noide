#include <avr/io.h>
#include <stdio.h>

#ifndef _USART_H
#define _USART_H

typedef enum {
    USART_BAUD_4800,
    USART_BAUD_9600,
    USART_BAUD_19200,
    USART_BAUD_38400,
    USART_BAUD_57600,
    USART_BAUD_115200,
} USART_BAUD_t;

void usart_init(USART_BAUD_t baud);
int usart_putchar(char c, FILE *stream);
int usart_getchar(FILE *stream);

#endif /* END _USART_H */
