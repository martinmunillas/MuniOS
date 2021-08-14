cd src/boot/
nasm bootloader.asm -f bin -o ../../build/bootloader.bin

cd ../kernel/
nasm kernel_entry.asm -f elf64 -o ../../build/kernel_entry.o
nasm binaries.asm -f elf64 -o ../../build/binaries.o

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "kernel.cpp" -o "../../build/kernel.o"

cd ../../
x86_64-elf-ld -T"link.ld"

cat build/bootloader.bin build/kernel.bin > build/munios.flp

rm build/bootloader.bin build/kernel.bin build/kernel.o build/kernel_entry.o build/binaries.o