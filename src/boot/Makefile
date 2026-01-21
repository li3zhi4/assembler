.PHONY: all clean

all: boot.bin

clean:
	rm -f boot.bin

boot.bin: boot.asm
	nasm -f bin boot.asm -o boot.bin
