[org 0x7c00]

mov [boot_disk], dl

mov bp, 0x7c00
mov sp, bp

call read_disk

jmp PROGRAM_SPACE

%include "print_string.asm"
%include "print_hex.asm"
%include "disk_read.asm"

times 510-($-$$) db 0
dw 0xaa55