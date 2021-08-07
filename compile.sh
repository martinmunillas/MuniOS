nasm bootloader.asm -f bin -o build/bootloader.bin
nasm kernel_entry.asm -f bin -o build/kernel_entry.bin
cat build/bootloader.bin build/kernel_entry.bin > build/bootloader.flp
rm build/bootloader.bin build/kernel_entry.bin