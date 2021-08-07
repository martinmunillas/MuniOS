nasm bootloader.asm -f bin -o build/bootloader.bin
nasm sector_test.asm -f bin -o build/sector_test.bin
cat build/bootloader.bin build/sector_test.bin > build/bootloader.flp
rm build/bootloader.bin build/sector_test.bin