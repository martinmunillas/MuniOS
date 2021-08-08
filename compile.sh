nasm bootloader.asm -f bin -o build/bootloader.bin

nasm kernel_entry.asm -f elf64 -o build/kernel_entry.o

x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c "kernel.cpp" -o "build/kernel.o"
x86_64-elf-ld -o build/kernel.tmp -Ttext 0x7e00 build/kernel_entry.o build/kernel.o

objcopy -O binary build/kernel.tmp build/kernel.bin

cat build/bootloader.bin build/kernel.bin > build/munios.flp

rm build/bootloader.bin build/kernel.bin build/kernel.tmp build/kernel.o build/kernel_entry.o