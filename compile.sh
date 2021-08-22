cd src/lib/boot/
nasm bootloader.asm -f bin -o ../../../build/bootloader.bin

cd ../kernel/
nasm kernel_entry.asm -f elf64 -o ../../../build/kernel_entry.o
nasm binaries.asm -f elf64 -o ../../../build/binaries.o

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "kernel.cpp" -o "../../../build/kernel.o"

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "keyboard.cpp" -o "../../../build/keyboard.o"

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "memoryMap.cpp" -o "../../../build/memoryMap.o"

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "heap.cpp" -o "../../../build/heap.o"

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "memory.cpp" -o "../../../build/memory.o"

cd ../utils/

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "IDT.cpp" -o "../../../build/IDT.o"

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "IO.cpp" -o "../../../build/IO.o"

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "textPrint.cpp" -o "../../../build/textPrint.o"

cd parsers/

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "intToString.cpp" -o "../../../../build/intToString.o"

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "floatToString.cpp" -o "../../../../build/floatToString.o"

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "hexToString.cpp" -o "../../../../build/hexToString.o"

cd ../../../../
x86_64-elf-ld -T"link.ld"

cat build/bootloader.bin build/kernel.bin > build/munios.flp

rm build/*.bin build/*.o