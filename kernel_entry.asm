[org 0x7e00]

mov bx, welcome_msg
call print_string



enter_protected_mode:
    mov bx, protected_mode_start
    call print_string

    cli
    call enableA20
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, ea

    jmp codeseg:start_protected_mode

%include "gdt.asm"
%include "print_string.asm"
%include "print_hex.asm"

enableA20:
    in al, 0x92
    or al, 0x2
    out 0x92 al
    ret


[bits 32]
start_protected_mode:
    mov ax, dataseg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov [0xb8000], byte "H"

    jmp $
welcome_msg:
    db "Hello World, welcome to MuniOS", 0xa, 0

protected_mode_start:
    db "Starting protected mode...", 0xa, 0

protected_mode_end:
    db "Protected mode started", 0xa, 0
times 2048-($-$$) db 0