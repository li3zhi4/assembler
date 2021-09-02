all: boot2.bin
	dd if=/dev/zero of=boot.img bs=512 count=2880
	dd if=boot.bin of=boot.img bs=512 count=1 conv=notrunc
boot2.bin:
	nasm boot.asm -o boot.bin
clean:
	rm -rf *.bin *.img
