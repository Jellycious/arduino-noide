#include <avr/io.h>
#include <stdio.h>

void usart_init();
void usart_9600();
int usart_putchar(char c, FILE *stream);
int usart_getchar(FILE *stream);
