[org 0x7c00]

mov bx, welcome_str
call print_string

jmp $

%include "print_string.asm"

welcome_str:
    db "Hello World, welcome to MuniOS", 0
times 2048-($-$$) db 0