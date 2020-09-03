#include "../include/keyboard.h"
#include "../include/frame_buffer.h"

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
	FrameBuffer::Writer p(FrameBuffer::Colours::BLACK, FrameBuffer::Colours::WHITE);
	p.print("HalideOS, an experimental OS by DSC KIIT\n");
	p.print("HalideOS, an experimental OS by DSC KIIT\n");
	p.print("HalideOS, an experimental OS by DSC KIIT\n");
	p.print("HalideOS, an experimental OS by DSC KIIT\n");
	p.print("HalideOS, an experimental OS by DSC KIIT\n");
	p.print("HalideOS, an experimental OS by DSC KIIT\n");
	char* input_buffer = KEYBOARD_DRIVER::readInput(p);
	//p.colorTheme(FrameBuffer::Colours::BLACK, FrameBuffer::Colours::WHITE);
	//p.print("echoed ");
	//p.print(input_buffer);
	
	while (1);
}