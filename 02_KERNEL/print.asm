[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

global _print_string_pm
global _clear_screen_pm

_print_string_pm:
    push ebp
    mov ebp, esp

    mov edx, [ebp + 12] ; row
    mov ecx, [ebp + 8]  ; col
    imul edx, 160
    add ecx, edx

    mov edi, [ebp + 16] ; string

    mov edx, VIDEO_MEMORY
    add edx, ecx

.loop:
    mov al, [edi]
    cmp al, 0
    je .done
    mov ah, WHITE_ON_BLACK
    mov [edx], ax
    add edx, 2
    inc edi
    jmp .loop

.done:
    pop ebp
    ret

_clear_screen_pm:
    pusha
    mov edi, VIDEO_MEMORY
    mov ecx, 80 * 25
    mov ah, WHITE_ON_BLACK
    mov al, ' '
.clear_loop:
    mov [edi], ax
    add edi, 2
    loop .clear_loop
    popa
    ret
