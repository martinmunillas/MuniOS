PROGRAM_SPACE equ 0x7e00

read_disk:
    mov ah, 0x2
    mov bx, PROGRAM_SPACE
    mov al, 2
    mov dl, [boot_disk]
    mov ch, 0x0
    mov dh, 0x0
    mov cl, 0x2
    int 0x13

    jc disk_error
    
    ret
disk_error:
    mov bx, disk_error_msg
    call print_string
    jmp $



boot_disk:
    db 0

disk_error_msg:
    db 'There was an error trying to read the disk', 0