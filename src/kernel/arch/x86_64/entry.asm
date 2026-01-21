[bits 64]
global _start
extern main

_start:
    mov rsp, 0x90000
    call main
    cli
    hlt
