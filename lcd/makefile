CC=avr-gcc
OBJCOPY=avr-objcopy

AVRDUDE=avrdude

MCU=atmega328p
MCU_FLAG=-mmcu=$(MCU)

BUILD_DIR=build

TARGET=lcd
TARGET_ELF:=$(TARGET).elf
TARGET_HEX:=$(patsubst %.elf,%.hex,$(TARGET_ELF))

PORT?=/dev/ttyUSB0
PROGRAMMER_BAUD_RATE=115200 #or 57600

F_CPU=16000000
OPTIMIZATION_FLAG=-O
CFLAGS += -funsigned-char -Wall

LIBS_DIR=libs
LIBS_SOURCES=$(shell find $(LIBS_DIR)/ -name '*.c')

SOURCES:=$(LIBS_SOURCES) usart.c lcd1602.c main.c
OBJECTS:=$(patsubst %.c, %.o, $(SOURCES))


.PHONY: all

all: clean compile

%.o: %.c
	$(CC) $(CFLAGS) $(MCU_FLAG) -DF_CPU=$(F_CPU) $(OPTIMIZATION_FLAG) -c $< -o $(BUILD_DIR)/$@


compile: builddir
    
	$(CC) $(CFLAGS) $(MCU_FLAG) -DF_CPU=$(F_CPU) $(OPTIMIZATION_FLAG) $(SOURCES) -o $(BUILD_DIR)/$(TARGET_ELF)
	$(OBJCOPY) -O ihex $(BUILD_DIR)/$(TARGET_ELF) $(BUILD_DIR)/$(TARGET_HEX)

builddir:
	mkdir -p $(BUILD_DIR)

program: compile
	$(AVRDUDE) -p atmega328p -P $(PORT) -b $(PROGRAMMER_BAUD_RATE) -c arduino -U flash:w:$(BUILD_DIR)/$(TARGET_HEX):i

clean:
	rm -Rf $(BUILD_DIR)
