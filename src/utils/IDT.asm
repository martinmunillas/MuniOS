[extern _idt]
idt_descriptor:
    dw 4095
    dq _idt

[extern isr1Handler]
isr1:
    push rax
    push rcx
    push rdx
    push r8
    push r9
    push r10
    push r11

    call isr1Handler

    pop r11
    pop r10
    pop r9
    pop r8
    pop rdx
    pop rcx
    pop rax
    
    iretq
    GLOBAL isr1

load_idt:
    lidt[idt_descriptor]
    sti
    ret
    GLOBAL load_idt