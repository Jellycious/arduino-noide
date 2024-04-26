# LCD library for AVR Microcontrollers

## Description
This libary has been written for LCD displays that use the HD44780 LCD controller in combination with the PCF8574(T) I/O Expander, which you commonly find in electronic starter kits. This library has been tested on the Atmega328p, but should work on any AVR compatible microcontroller.

## Usage

- Adjust pin and address definitions inside of `lcd1602.h` if neccesary
- Initialize module with `lcd1602_init(dots, lines)`
