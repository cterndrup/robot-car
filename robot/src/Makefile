SRC_PATH  := /home/pi/robot/src
INC	      := /home/pi/robot/inc
PWMDIR	  := $(SRC_PATH)/pwm
PWMOBJS   := pfcpwm.o
TIMERDIR  := $(SRC_PATH)/timer/timer16
TIMEROBJS := timer16.o

PWMOBJS   := $(patsubst %.o, $(PWMDIR)/%.o, $(PWMOBJS))
TIMEROBJS := $(patsubst %.o, $(TIMERDIR)/%.o, $(TIMEROBJS))

OBJS	  := $(TIMEROBJS) $(PWMOBJS)
EXEC	  := main
MAIN_OBJ  := main.o
MAIN_SRC  := main.c
HEX		  := main.hex
MCU		  := atmega2560

.PHONY: all copy upload clean

all: $(EXEC)

$(EXEC): $(MAIN_OBJ)
	avr-gcc -mmcu=$(MCU) $(MAIN_OBJ) $(OBJS) -o $(EXEC)

$(MAIN_OBJ): $(MAIN_SRC) $(OBJS)
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(MCU) -c $(MAIN_SRC) -o $(MAIN_OBJ) -I $(INC)

$(PWMDIR)/%.o: $(PWMDIR)/%.c $(TIMEROBJS)
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(MCU) -c $< -o $@ -I $(INC)

$(TIMERDIR)/%.o: $(TIMERDIR)/%.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(MCU) -c $< -o $@ -I $(INC)

copy:
	avr-objcopy -O ihex -R .eeprom $(EXEC) $(HEX)

upload:
	avrdude -D -F -V -c wiring -p m2560 -P /dev/ttyACM0 -b 115200 -U flash:w:$(HEX)

clean:
	rm $(MAIN_OBJ) $(OBJS) $(HEX) $(EXEC)
