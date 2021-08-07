gdt_nulldesc:
    dd 0x0
    dd 0x0
gdt_codedesc:
    dw 0xffff ; Limit
    dw 0x0 ; Base low
    db 0x0 ; Base medium
    db 10011010b ; Flags
    db 11001111b ; Flags + upperlimit
    db 0x0 ; Base high
gdt_datadesc:
    dw 0xffff ; Limit
    dw 0x0 ; Base low
    db 0x0 ; Base medium
    db 10010010b ; Flags
    db 11001111b ; Flags + upperlimit
    db 0x0 ; Base high

gdt_end:

gdt_descriptor:
    gdt_size:
        dw gdt_end - gdt_nulldesc - 1
        dd gdt_nulldesc

codeseg equ gdt_codedesc - gdt_nulldesc
dataseg equ gdt_datadesc - gdt_nulldesc
