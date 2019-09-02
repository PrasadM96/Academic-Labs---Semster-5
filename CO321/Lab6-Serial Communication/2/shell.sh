#!/bin/bash

avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -o binary $1
avr-objcopy -O ihex -R .eeprom binary hex_file.hex

sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:hex_file.hex


