# Programming Arduino Nano with avr-gcc

This is a basic template for programming the Arduino Nano outside of the Arduino Development Environment with [AVR-LIBC](https://www.nongnu.org/avr-libc/).

There are two templates:
 - Blinky (Blinks user LED on Arduino Boards)
 - Console (Prints Hello World to USART)

## Usage:
To build: `make`

To program: `make PORT=<usb_port> program`

## Dependencies:
    - make
    - avrdude
    - avr-gcc
    - avr-binutils
    - avr-libc
