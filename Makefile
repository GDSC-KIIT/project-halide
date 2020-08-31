clean:
	rm *.bin

simple_boot_complie:
	nasm -f bin *.asm -o simple_boot_sector.bin