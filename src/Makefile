compilerflags = -m32 
assemblerflags = --32
linkerflags = -melf_i386

objects = loader.o kernel.o

%.o: %.cpp
	g++ $(compilerflags) -o $@ -c $<

%.o: %.s
	as $(assemblerflags) -o $@ $<

kernel.bin: linker.ld $(objects)
	make clean | ls
	ld $(linkerflags) -T $< -o $@ $(objects)
	mkdir -p objs/
	mv *.o objs/

clean:
	rm ./objs/*.o *.bin