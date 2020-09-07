cppcompilerflags = -c -I../include/ -ffreestanding -fno-stack-protector -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings -fpermissive
ccompilerflags = -c -I../include/ -ffreestanding -fno-stack-protector -m32 -Iinclude -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore -Wno-write-strings
assemblerflags = --32
nasm-flags = -f elf32
linkerflags = -melf_i386

args = `arg="$(filter-out $@,$(MAKECMDGOALS))" && echo $${arg:-${1}}`

objects = loader.o kernel.o frame_buffer.o system.o keyboard.o utils.o mouse.o halidestdlib.o globaldescriptortable.o \
		  drvg.o mem.o window.o drvi.o drvs.o colors.o vtty.o

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

run-full-screen: kernel.iso
	qemu-system-i386 -boot d -cdrom kernel.iso -full-screen

archive:
	mkdir -p ../Archives/${args}
	cp ../include/ ../Archives/${args} -rf
	cp ../src/ ../Archives/${args} -rf
	cp ../.gitignore ../Archives/${args} -rf
	cp ../LICENSE ../Archives/${args} -rf
	cp ../README.md ../Archives/${args} -rf
	@echo Saved current copy of os in Archives/${args}

cleararchives:
	rm ../Archives/* -rf
	@echo removed all saved archives

clean:
	rm ./objs/*.o *.iso *.bin