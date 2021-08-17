jmp enter_protected_mode

%include "./gdt.asm"
%include "../utils/print_string.asm"
%include "./detect_memory.asm"
enter_protected_mode:
    mov bx, welcome_msg
    call print_string

    call detect_memory
    call enableA20
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp codeseg:start_protected_mode


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
[extern _start]

%include "../utils/IDT.asm"

start_64bit:
    mov edi, 0xb8000
    mov rax, 0xe020e020e020e020
    mov ecx, 500
    rep stosq

    call activate_sse
    call _start
    jmp $

activate_sse:
    mov rax, cr0
    and ax, 0b11111101
    or ax, 0b00000001
    mov cr0, rax

    mov rax, cr4
    or ax, 0b1100000000
    mov cr4, rax
    ret