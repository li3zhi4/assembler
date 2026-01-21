all:
	$(MAKE) -C 01_START
	$(MAKE) -C 02_KERNEL_64

clean:
	$(MAKE) -C 01_START clean
	$(MAKE) -C 02_KERNEL_64 clean
	rm -f tools/create_fs fs.img

tools:
	gcc -o tools/create_fs tools/create_fs.c

test: tools all
	tools/create_fs
	dd if=fs.img of=02_KERNEL_64/boot.img seek=1 bs=512 conv=notrunc
	qemu-system-x86_64 -m 64 -drive format=raw,file=02_KERNEL_64/boot.img -nographic -serial stdio -monitor null -no-reboot

.PHONY: all clean test tools
