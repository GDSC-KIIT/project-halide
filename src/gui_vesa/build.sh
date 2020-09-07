gcc -c -I../include/ -ffreestanding -fno-stack-protector -m32 -Iinclude -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore -Wno-write-strings drvg.c -o drvg.o
gcc -c -I../include/ -ffreestanding -fno-stack-protector -m32 -Iinclude -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore -Wno-write-strings window.c -o window.o
gcc -c -I../include/ -ffreestanding -fno-stack-protector -m32 -Iinclude -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore -Wno-write-strings drvi.c -o drvi.o
gcc -c -I../include/ -ffreestanding -fno-stack-protector -m32 -Iinclude -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore -Wno-write-strings drvs.c -o drvs.o
gcc -c -I../include/ -ffreestanding -fno-stack-protector -m32 -Iinclude -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore -Wno-write-strings colors.c -o colors.o

mv *.o ../