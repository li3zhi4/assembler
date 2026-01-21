[bits 32]
global _start
extern main

_start:
    mov esp, 0x10000
    mov ebp, esp
    call main
    cli
    hlt
