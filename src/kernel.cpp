#include "../include/keyboard.h"
#include "../include/frame_buffer.h"
#include "../include/windows.h"

#define USE_BOOT_SCREEN_1 2

typedef void (*ctor)();
extern "C" ctor begin_constructors;
extern "C" ctor end_constructors;
extern "C" void call_ctors()
{
	for (ctor *i = &begin_constructors; i != &end_constructors; i++)
	{
		(*i)();
	}
}

extern "C" void k_main(const void *multiboot_structure, unsigned int multiboot_magic)
{
	Window win1(10,70,5,20);
	FrameBuffer::Writer p(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::BLACK);

	#if USE_BOOT_SCREEN_1 == 1
		#include "../include/bootscreen1.h"
	#elif USE_BOOT_SCREEN_1 == 0
		#include "../include/bootscreen2.h"
	#endif
	
	p.writeString("HalideOS, a experimental OS by dsc kiit");
	KEYBOARD_DRIVER::readInput(p);

	while (1);
}

                                                                                  
                                                                                  