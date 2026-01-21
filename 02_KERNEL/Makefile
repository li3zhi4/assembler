C_SOURCES = $(wildcard *.c)
ASM_SOURCES = $(wildcard *.asm)
OBJS = $(C_SOURCES:.c=.o) $(ASM_SOURCES:.asm=.o)
CC = gcc
LD = ld
ASM = nasm

all: boot.img

%.o: %.c
	$(CC) -m32 -c $< -o $@ -ffreestanding -O2 -Wall -Wextra

%.o: %.asm
	$(ASM) -f elf32 $< -o $@

kernel.bin: $(OBJS)
	$(LD) -m elf_i386 -Ttext 0x1000 -o $@ $^

boot.img: kernel.bin ../01_START/boot.bin
	dd if=../01_START/boot.bin of=boot.img bs=512 count=1
	dd if=kernel.bin of=boot.img bs=512 seek=1

clean:
	rm -f *.o kernel.bin boot.img

.PHONY: all clean
