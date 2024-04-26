#include <avr/io.h>
#include <stdio.h>

#ifndef _USART_H
#define _USART_H

#ifdef __cplusplus
extern "C" {
#endif

void usart_init();
void usart_9600();
int usart_putchar(char c, FILE *stream);
int usart_getchar(FILE *stream);

#ifdef __cpluspluc
}
#endif /* END __cplusplus */

#endif /* END _USART_H */
