CC=avr-gcc
OBJCOPY=avr-objcopy

AVRDUDE=avrdude

MCU=atmega328p
MCU_FLAG=-mmcu=$(MCU)

BUILD_DIR=build

PORT?=/dev/ttyUSB0

F_CPU=16000000
OPTIMIZATION_FLAG=-O

SOURCES:=usart.c main.c
OBJECTS:=$(patsubst %.c, %.o, $(SOURCES))

TARGET=console
TARGET_ELF:=$(TARGET).elf
TARGET_HEX:=$(patsubst %.elf,%.hex,$(TARGET_ELF))

.PHONY: all

all: compile

%.o: %.c
	$(CC) $(MCU_FLAG) -DF_CPU=$(F_CPU) $(OPTIMIZATION_FLAG) -c $< -o $(BUILD_DIR)/$@


compile: builddir
    
	$(CC) $(MCU_FLAG) -DF_CPU=$(F_CPU) $(OPTIMIZATION_FLAG) $(SOURCES) -o $(BUILD_DIR)/$(TARGET_ELF)
	$(OBJCOPY) -O ihex $(BUILD_DIR)/$(TARGET_ELF) $(BUILD_DIR)/$(TARGET_HEX)

builddir:
	mkdir -p $(BUILD_DIR)

program:
	$(AVRDUDE) -p atmega328p -P $(PORT) -b 57600 -c arduino -U flash:w:$(BUILD_DIR)/$(TARGET_HEX):i

clean:
	rm -R $(BUILD_DIR)
