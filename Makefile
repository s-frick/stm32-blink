CC=arm-none-eabi-gcc
CFLAGS=-mcpu=cortex-m4 -mthumb -nostdlib
CPPFLAGS=-DSTM32F401xE 

LINKER_FILE=linker_script.ld
LDFLAGS=-T $(LINKER_FILE) \
				-specs=rdimon.specs \
				-lc \
				-lrdimon

all: blink.elf

blink.elf: main.o startup.o system_stm32f4xx.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o blink.elf

main.o: main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) main.c -c

startup.o: startup.c
	$(CC) $(CFLAGS) $(CPPFLAGS) startup.c -c

PROGRAMMER=openocd
PROGRAMMER_FLAGS=-f interface/stlink-v2-1.cfg -f target/stm32f4x.cfg
flash: blink.elf
	$(PROGRAMMER) $(PROGRAMMER_FLAGS) -c "program blink.elf verify reset exit"

.PHONY: clean
clean:
	rm -rf *.o *.elf
