    org 0x7c00  ; cs:ip -> cs:7c00h
BaseOfStack equ 0x7c00
LableStart:
    call Init
    call ClearScreen
    call SetFocus
    call DispStr
    call ResetFloppy
    jmp $ ; $ -> this.location
Init:
    mov ax, cs
    mov ds, ax ; ds -> cs
    mov es, ax ; es -> cs
    mov ss, ax ; sp -> cs
    mov sp, BaseOfStack
    ret
DispStr:
    mov ax, msg
    mov bp, ax     ; bp -> msg.location
    mov cx, len    ; cx -> msg.length
    mov ax, 0x1301 ; ah=13h, al=01h
    mov bx, 0x000c ; bh -> page, bl -> value 1. 0 black 1 blue 2. c red
    mov dx, 0x0d20 ; dh -> row, dl -> column
    int 10h        ; -> Video Service es:bp
    ret            ; return
ClearScreen:
    mov     ax,     0x0600
    mov     bx,     0x0700
    mov     cx,     0x0000
    mov     dx,     0x184f
    int     10h
    ret
SetFocus:
    mov     ax,     0x0200
    mov     bx,     0x0000
    mov     dx,     0x0000
    int     10h
ResetFloppy:
    xor     ah,     ah
    xor     dl,     dl
    int     13h
    ret
msg:
    db "Hello, os world!"
    len equ $ - msg
    times 510-($-$$) db 0    ; 512byte
    dw 0xaa55                ; end
