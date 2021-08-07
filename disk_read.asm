PROGRAM_SPACE equ 0x7c00

read_disk:

    mov bx, came
    call print_string

    mov ah, 0x2
    mov bx, PROGRAM_SPACE
    mov al, 1
    mov dl, [boot_disk]
    mov ch, 0x0
    mov dh, 0x0
    mov cl, 0x2
    int 0x13

    mov bx, came
    call print_string


    jc disk_error
    
    ret
disk_error:
    mov bx, disk_error_msg
    call print_string
    jmp $



boot_disk:
    db 0


came:
    db 'Out of reading', 0
disk_error_msg:
    db 'There was an error trying to read the disk', 0