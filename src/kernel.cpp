typedef void (*ctor)();
extern "C" ctor begin_constructors;
extern "C" ctor end_constructors;
extern "C" void call_ctors() {
    for(ctor* i = &begin_constructors; i != &end_constructors; i++) {
        (*i)();
    }
}

void print(char* str) {
    char* vid_mem = (char*)0x0B8000;
    for (int i = 0; str[i]!='\0'; i++)
    {
        vid_mem[i*2] = str[i];
        vid_mem[(i*2)+1] = 0x0f;
    }
}

extern "C" void k_main(const void* multiboot_structure, unsigned int multiboot_magic) {
    print("Hello world!!");
    while(1);
}