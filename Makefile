.PHONY: all clean test tools

all: boot.img

clean:
	$(MAKE) -C src/boot clean
	$(MAKE) -C src/kernel clean
	rm -f boot.img tools/create_fs

test: all
	qemu-system-x86_64 -m 64 -drive format=raw,file=boot.img -nographic -serial stdio -monitor null -no-reboot

boot.img: src/boot/boot.bin src/kernel/kernel.bin
	dd if=src/boot/boot.bin of=boot.img bs=512 count=1
	dd if=src/kernel/kernel.bin of=boot.img bs=512 seek=1

src/boot/boot.bin:
	$(MAKE) -C src/boot

src/kernel/kernel.bin:
	$(MAKE) -C src/kernel

tools:
	gcc -o tools/create_fs tools/create_fs.c
