section	.text
   global _start	 ;must be declared for linker (gcc)
	
_start:	         ;tell linker entry point
   mov	edx,len  ;message length
   mov	ecx,msg  ;message to write
   mov	ebx,1    ;file descriptor (stdout)
   mov	eax,4    ;system call number (sys_write)
   int	0x80     ;call kernel
	
   mov	edx,lena    ;message length
   mov	ecx,aa   ;message to write
   mov	ebx,1    ;file descriptor (stdout)
   mov	eax,4    ;system call number (sys_write)
   int	0x80     ;call kernel
	
   mov	eax,1    ;system call number (sys_exit)
   int	0x80     ;call kernel
	
section	.data
msg db 'Martin is the best',0xa ;a message
len equ $ - msg  ;length of message
aa times 20 db '-'
lena equ $ - aa