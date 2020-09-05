#include "../include/keyboard.h"
#include "../include/frame_buffer.h"

#define USE_BOOT_SCREEN_1 0

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
	FrameBuffer::Writer p(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::BLACK);

	#if USE_BOOT_SCREEN_1
		#include "../include/bootscreen1.h"
	#else
		#include "../include/bootscreen2.h"
	#endif
	
	KEYBOARD_DRIVER::readInput(p);

	while (1);
}

                                                                                  
                                                                                  