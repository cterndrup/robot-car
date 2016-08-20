EXEC = main
OBJS = main.o
SRC	 = main.c
HEX	 = main.hex
MCU	 = atmega2560
INC  = /home/pi/robot/inc

all: $(EXEC)

$(EXEC): $(OBJS)
	avr-gcc -mmcu=$(MCU) $(OBJS) -o $(EXEC)

$(OBJS): $(SRC)
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(MCU) -c $(SRC) -o $(OBJS) -I $(INC)

copy:
	avr-objcopy -O ihex -R .eeprom $(EXEC) $(HEX)

upload:
	avrdude -D -F -V -c wiring -p m2560 -P /dev/ttyACM0 -b 115200 -U flash:w:$(HEX)

clean:
	rm $(OBJS) $(HEX) $(EXEC)
