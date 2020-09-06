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
	Window win1(10,70,0,8, (char*)"Basic window title v.0.2 instance 1 instance_id(a.0.1)");
	FrameBuffer::Writer p(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::BLACK, win1);

	int x = win1.m_y2;
	x=win1.m_y2-1;
	p.writeString(win1.m_title);
	p.fillRemeaning("=", true);
	p.write_at_index(x);

	Window win2(10,70,9,16, (char*)"Basic window title v.0.2 instance 2 instance_id(b.0.1)");
	FrameBuffer::Writer p1(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::BLACK, win2);

	int y = win2.m_y2;
	y=win2.m_y2-1;
	p1.writeString(win2.m_title);
	p1.fillRemeaning("=", true);
	p1.write_at_index(y);

	Window win3(10,70,17,25, (char*)"Basic window title v.0.2 instance 3 instance_id(c.0.1)");
	FrameBuffer::Writer p3(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::BLACK, win3);

	int z = win3.m_y2;
	z=win3.m_y2-1;
	p3.writeString(win3.m_title);
	p3.fillRemeaning("=", true);
	p3.write_at_index(z);

	#if USE_BOOT_SCREEN_1 == 1
		#include "../include/bootscreen1.h"
	#elif USE_BOOT_SCREEN_1 == 0
		#include "../include/bootscreen2.h"
	#endif

	while(true)
	{
	char* input_buffer = KEYBOARD_DRIVER::readInput(p);
	//p.writeString(input_buffer);	
	}

	
	while (1);
}

                                                                                  
                                                                                  