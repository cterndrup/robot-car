SRC_PATH  := /Users/colint/Development/robot-car/robot/src#/home/pi/robot/src
INC       := /Users/colint/Development/robot-car/robot/inc#/home/pi/robot/inc

MOTORDIR  := $(SRC_PATH)/motor
MOTOROBJS := motor.o

PWMDIR    := $(SRC_PATH)/pwm
PWMOBJS   := pfcpwm.o

TIMERDIR  := $(SRC_PATH)/timer/timer16
TIMEROBJS := timer16.o

BLEDIR    := $(SRC_PATH)/ble
BLEOBJS   := ble.o

SPIDIR    := $(SRC_PATH)/spi
SPIOBJS   := spi.o

MOTOROBJS := $(patsubst %.o, $(MOTORDIR)/%.o, $(MOTOROBJS))
PWMOBJS   := $(patsubst %.o, $(PWMDIR)/%.o, $(PWMOBJS))
TIMEROBJS := $(patsubst %.o, $(TIMERDIR)/%.o, $(TIMEROBJS))
BLEOBJS   := $(patsubst %.o, $(BLEDIR)/%.o, $(BLEOBJS))
SPIOBJS   := $(patsubst %.o, $(SPIDIR)/%.o, $(SPIOBJS))

OBJS      := $(MOTOROBJS) $(PWMOBJS) $(TIMEROBJS) $(BLEOBJS) $(SPIOBJS)
EXEC      := main
MAIN_OBJ  := main.o
MAIN_SRC  := main.c
HEX       := main.hex
MCU       := atmega2560

.PHONY: all copy upload clean

all: $(EXEC)

$(EXEC): $(MAIN_OBJ) $(OBJS)
	avr-gcc -mmcu=$(MCU) $(MAIN_OBJ) $(OBJS) -o $(EXEC)

$(MAIN_OBJ): $(MAIN_SRC) #$(OBJS)
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(MCU) -c $(MAIN_SRC) -o $(MAIN_OBJ) -I $(INC)

$(MOTORDIR)/%.o: $(MOTORDIR)/%.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(MCU) -c $< -o $@ -I $(INC)

$(PWMDIR)/%.o: $(PWMDIR)/%.c #$(TIMEROBJS)
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(MCU) -c $< -o $@ -I $(INC)

$(TIMERDIR)/%.o: $(TIMERDIR)/%.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(MCU) -c $< -o $@ -I $(INC)

$(BLEDIR)/%.o: $(BLEDIR)/%.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(MCU) -c $< -o $@ -I $(INC)

$(SPIDIR)/%.o: $(SPIDIR)/%.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=$(MCU) -c $< -o $@ -I $(INC)

copy:
	avr-objcopy -O ihex -R .eeprom $(EXEC) $(HEX)

upload:
	avrdude -D -F -V -c wiring -p m2560 -P /dev/cu.usbmodem1411 -b 115200 -U flash:w:$(HEX)

clean:
	rm $(MAIN_OBJ) $(OBJS) $(HEX) $(EXEC)
