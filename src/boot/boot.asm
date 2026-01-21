[org 0x7c00]

KERNEL_LOAD_ADDR equ 0x100000
KERNEL_SECTOR equ 2

start:
    ; Initialize segment registers
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

    ; Load the kernel from disk
    call load_kernel

    ; Enter 64-bit long mode
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SELECTOR:protected_mode_start

load_kernel:
    mov ah, 0x02 ; Read sectors command
    mov al, 64   ; Read 64 sectors (32 KB)
    mov ch, 0    ; Cylinder 0
    mov cl, KERNEL_SECTOR ; Start at sector 2
    mov dh, 0    ; Head 0
    mov bx, 0x8000 ; Load kernel to a temporary safe address
    int 0x13
    jc load_kernel
    ret

gdt_start:
    ; Null descriptor
    dd 0, 0
    ; 32-bit code descriptor
    dw 0xffff, 0, 0x9a00, 0x00cf
    ; 32-bit data descriptor
    dw 0xffff, 0, 0x9200, 0x00cf
    ; 64-bit code descriptor
    dw 0, 0, 0x9a00, 0x00af
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SELECTOR equ 0x08
DATA_SELECTOR equ 0x10
LONG_MODE_SELECTOR equ 0x18

[bits 32]
protected_mode_start:
    ; Set up data segments
    mov ax, DATA_SELECTOR
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax

    ; Setup page tables for identity mapping
    mov edi, 0x1000 ; PML4 table
    mov cr3, edi
    mov dword [edi], 0x2003 ; PDP table, present, R/W
    add edi, 0x1000
    mov dword [edi], 0x3003 ; Page Directory table, present, R/W
    add edi, 0x1000
    ; Page Table setup
    mov esi, 0
    mov ecx, 512
.map_page_table:
    mov eax, 0x1000
    mul esi
    or eax, 3
    mov [edi + esi * 8], eax
    mov dword [edi + esi * 8 + 4], 0
    inc esi
    loop .map_page_table

    ; Enable PAE
    mov eax, cr4
    or eax, 0x20
    mov cr4, eax

    ; Enable Long Mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 0x100
    wrmsr

    ; Enable Paging
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    ; Copy kernel from temporary location to final destination
    mov esi, 0x8000
    mov edi, KERNEL_LOAD_ADDR
    mov ecx, 32768 / 4
    rep movsd

    ; Jump to long mode
    lgdt [gdt_descriptor]
    jmp LONG_MODE_SELECTOR:long_mode_start

[bits 64]
long_mode_start:
    ; Set up 64-bit data segments
    mov ax, DATA_SELECTOR
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax

    ; Jump to the kernel
    jmp KERNEL_LOAD_ADDR

[bits 16]
    times 510-($-$$) db 0
    dw 0xaa55
