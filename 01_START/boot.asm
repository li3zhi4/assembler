[org 0x7c00]

KERNEL_LOAD_ADDR equ 0x1000
KERNEL_SECTOR equ 2

start:
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

    call load_kernel

    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SELECTOR:protected_mode_start

load_kernel:
    mov ah, 0x02
    mov al, 1
    mov ch, 0
    mov cl, KERNEL_SECTOR
    mov dh, 0
    mov bx, KERNEL_LOAD_ADDR
    int 0x13
    jc load_kernel
    ret

gdt_start:
    dd 0, 0
    dw 0xffff, 0, 0x9a00, 0x00cf
    dw 0xffff, 0, 0x9200, 0x00cf
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SELECTOR equ 0x08
DATA_SELECTOR equ 0x10

[bits 32]
protected_mode_start:
    mov ax, DATA_SELECTOR
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax

    jmp KERNEL_LOAD_ADDR

[bits 16]
    times 510-($-$$) db 0
    dw 0xaa55
