;显示静态文字
    org 07c00h ; cs:ip -> 0h:7c00h
    mov ax, cs
    mov ds, ax ; ds -> cs
    mov es, ax ; es -> cs
    call display
    jmp $ ; $ -> this.location
display:
    mov ax, msgstart
    mov bp, ax ; bp -> msg.location
    mov cx, msgend-msgstart ; cx -> msg.length
    mov ax, 01301h ; ah=13h, al=01h
    mov bx, 000ch ; bh -> page, bl -> attribute
    mov dx, 0D20h ; dh -> row, dl -> column
    int 10h ; -> Video Service es:bp
    ret ; return
msgstart:
    db "Hello, os world!" ; msg
msgend:
    times 510-($-$$) db 0    ; 512byte
    dw 0xaa55                ; end
