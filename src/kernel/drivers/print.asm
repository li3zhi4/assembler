[bits 64]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

global _print_string_pm
global _clear_screen_pm

; void _print_string_pm(long col, long row, char* s);
; rdi: col, rsi: row, rdx: s
_print_string_pm:
    push rbp
    mov rbp, rsp

    ; Calculate the video memory offset in bytes: offset = (row * 80 + col) * 2
    mov rax, rsi ; row
    mov rbx, 160 ; 80 columns * 2 bytes/char
    mul rbx      ; rax = row * 160
    mov rbx, rdi ; col
    shl rbx, 1   ; rbx = col * 2
    add rax, rbx ; rax = row * 160 + col * 2

    mov rdi, rdx ; string pointer is in rdx (3rd arg)
    mov rdx, VIDEO_MEMORY
    add rdx, rax ; rdx now points to the correct screen location

.loop:
    mov al, byte [rdi]
    cmp al, 0
    je .done
    mov ah, WHITE_ON_BLACK
    mov word [rdx], ax
    add rdx, 2
    inc rdi
    jmp .loop

.done:
    pop rbp
    ret

; void _clear_screen_pm();
_clear_screen_pm:
    push rax
    push rdi
    push rcx
    mov rdi, VIDEO_MEMORY
    mov rcx, 80 * 25
    mov ah, WHITE_ON_BLACK
    mov al, ' '
.clear_loop:
    mov word [rdi], ax
    add rdi, 2
    loop .clear_loop
    pop rcx
    pop rdi
    pop rax
    ret
