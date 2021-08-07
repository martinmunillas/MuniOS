print_jump_line:
    mov bx, new_line
    call print_string
    ret

new_line:
    db 0xa, 0