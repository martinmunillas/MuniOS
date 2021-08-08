[org 0x7e00]

mov bx, welcome_msg
call print_string


enter_protected_mode:
    call enableA20
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp codeseg:start_protected_mode

%include "gdt.asm"
%include "print_string.asm"
%include "print_hex.asm"

enableA20:
    in al, 0x92
    or al, 0x2
    out 0x92, al
    ret

welcome_msg:
    db "Hello World, welcome to MuniOS", 0xa, 0x0

[bits 32]

%include "cpu_id.asm"
%include "simple_paging.asm"

start_protected_mode:
    mov ax, dataseg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov [0xb8000], byte "M"
    mov [0xb8002], byte "u"
    mov [0xb8004], byte "n"
    mov [0xb8006], byte "i"
    mov [0xb8008], byte "O"
    mov [0xb800a], byte "S"
    mov [0xb800c], byte " "

    call detect_cpu_id
    call detect_long_mode
    call setup_identity_paging
    call edit_gdt

    jmp codeseg:start_64bit

[bits 64]
start_64bit:
    mov edi, 0xb8000
    mov rax, 0xe520e520e520e520
    mov ecx, 500
    rep stosq
    jmp $
times 2048-($-$$) db 0