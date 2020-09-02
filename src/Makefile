compilerflags = -m32 
assemblerflags = --32
linkerflags = -melf_i386

objects = loader.o kernel.o frame_buffer.o

%.o: %.cpp
	g++ --std=c++17 $(compilerflags) -o $@ -c $<

%.o: %.s
	as $(assemblerflags) -o $@ $<

kernel.bin: linker.ld $(objects)
	ld $(linkerflags) -T $< -o $@ $(objects)
	mkdir -p objs/
	mv *.o objs/

kernel.iso: kernel.bin
	mkdir -p iso
	mkdir -p iso/boot
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/kernel.bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "HalideOS" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/kernel.bin'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=kernel.iso iso
	rm -rf iso

run: kernel.iso
	qemu-system-i386 -boot d -cdrom kernel.iso

clean:
	rm ./objs/*.o *.iso *.bin