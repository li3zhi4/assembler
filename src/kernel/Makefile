.PHONY: all clean

C_SOURCES := $(wildcard *.c) $(wildcard drivers/*.c) $(wildcard fs/*.c) $(wildcard mm/*.c) $(wildcard arch/x86_64/*.c)
ASM_SOURCES := $(wildcard arch/x86_64/*.asm) $(wildcard drivers/*.asm)

OBJS := $(patsubst %.c,%.o,$(C_SOURCES)) $(patsubst %.asm,%.o,$(ASM_SOURCES))

CC = gcc
LD = ld
ASM = nasm

CFLAGS = -m64 -mcmodel=kernel -ffreestanding -fno-pie -O2 -Wall -Wextra -Iinclude

all: kernel.bin

clean:
	rm -f $(OBJS) kernel.bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(ASM) -f elf64 $< -o $@

kernel.bin: $(OBJS)
	$(LD) -m elf_x86_64 -Ttext 0x100000 -o $@ $(OBJS) -nostdlib
