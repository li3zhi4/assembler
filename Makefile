all: boot2.bin
        dd if=/dev/zero of=boot1.img bs=512 count=2880
        dd if=boot1.bin of=boot1.img bs=512 count=1 conv=notrunc
boot2.bin:
        nasm boot1.asm -o boot1.bin
clean:
        rm -rf *.bin *.img
