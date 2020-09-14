cppcompilerflags = -c -I../include/ -ffreestanding -fno-stack-protector -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings -fpermissive
ccompilerflags = -c -I../include/ -ffreestanding -fno-stack-protector -m32 -Iinclude -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore -Wno-write-strings
assemblerflags = --32
nasm-flags = -f elf32
linkerflags = -melf_i386

args = `arg="$(filter-out $@,$(MAKECMDGOALS))" && echo $${arg:-${1}}`
objects = loader.o kernel.o frame_buffer.o system.o keyboard.o utils.o halidestdlib.o globaldescriptortable.o interrupts.o console.o interruptsasm.o

%.o: %.cpp
	g++ --std=c++17 $(cppcompilerflags) -o $@ -c $<

%.o: %.c
	gcc $(ccompilerflags) -o $@ -c $<

%.o: %.s
	as $(assemblerflags) -o $@ $<

kernel.bin: linker.ld $(objects)
	ld $(linkerflags) -T $< -o $@ $(objects)
	mkdir -p objs/
	mv *.o objs/

kernel.iso: kernel.bin
	mkdir -p diskImage
	mkdir -p diskImage/boot
	mkdir -p diskImage/boot/grub
	cp kernel.bin diskImage/boot/kernel.bin
	echo 'set timeout=0'                      > diskImage/boot/grub/grub.cfg
	echo 'set default=0'                     >> diskImage/boot/grub/grub.cfg
	echo ''                                  >> diskImage/boot/grub/grub.cfg
	echo 'menuentry "HalideOS" {' >> diskImage/boot/grub/grub.cfg
	echo '  multiboot /boot/kernel.bin'      >> diskImage/boot/grub/grub.cfg
	echo '  boot'                            >> diskImage/boot/grub/grub.cfg
	echo '}'                                 >> diskImage/boot/grub/grub.cfg
	grub-mkrescue --output=kernel.iso diskImage || grub2-mkrescue --output=kernel.iso diskImage
	rm -rf diskImage

run: kernel.iso
	qemu-system-i386 -boot d -cdrom kernel.iso

run-full-screen: kernel.iso
	qemu-system-i386 -boot d -cdrom kernel.iso -full-screen

run-vb: kernel.iso
	VBoxManage startvm "HalideOS v.0.1"


install_deps_debian:
	sudo apt install qemu virtualbox nasm gcc g++ xorriso

install_deps_arch:
	
install_deps_openSUSE:
	sudo zypper install gcc qemu virtualbox nasm grub xorriso mtools
	@echo You have to install gcc-g++ form yor browser for your SUSE
install_deps_RedHat:

archive:
	mkdir -p ../Archives/${args}
	cp ../include/ ../Archives/${args} -rf
	cp ../src/ ../Archives/${args} -rf
	cp ../.gitignore ../Archives/${args} -rf
	cp ../LICENSE ../Archives/${args} -rf
	cp ../README.md ../Archives/${args} -rf
	@echo Saved current copy of os in Archives/${args}

clear-archives:
	rm ../Archives/* -rf
	@echo removed all saved archives

clean:
	rm ./objs/*.o *.iso *.bin


help:
	@echo HalideOS - List of all the make commands and their functions
	@echo Usage: make [option]
	@echo Options: 
	
	@echo run - Compile and launch iso in qemu [windowed mode]
	@echo run-full-screen - Compile and launch iso in qemu [full screen mode]
	@echo run-vb - Compile and launch iso in Oracle VM Virtual Box, make sure you have it installed
	@echo kernel.bin - Compile into a binary executable
	@echo kernel.iso - Compile and just build the .iso image
	@echo clean - Delete object files and the iso [run this before pushing your code]
	@echo archive - Create an archive of the current source code
	@echo clear-archives - Delete the archives
