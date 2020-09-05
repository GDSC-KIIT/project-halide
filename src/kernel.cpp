#include "../include/keyboard.h"
#include "../include/frame_buffer.h"

#include "../include/exp/types.h"
#include "../include/exp/gdt.h"
#include "../include/exp/interrupts.h"
#include "../include/exp/mouse.h"
#include "../include/exp/multitasking.h"
#include "../include/exp/driver.h"
#include "../include/exp/port.h"

#define USE_BOOT_SCREEN_1 0

using namespace myos;
using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;

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

class MouseToConsole : public MouseEventHandler
{
    int8_t x, y;
public:
    
    MouseToConsole()
    {
        uint16_t* VideoMemory = (uint16_t*)0xb8000;
        x = -1;
        y = -1;
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);        
    }
    
    virtual void OnMouseMove(int xoffset, int yoffset)
    {
        
        static uint16_t* VideoMemory = (uint16_t*)0xb8000;
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);

        x += xoffset;
        if(x >= 80) x = 79;
        if(x < 0) x = 0;
        y += yoffset;
        if(y >= 25) y = 24;
        if(y < 0) y = 0;

        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);
    }
    
};

extern "C" void k_main(const void *multiboot_structure, unsigned int multiboot_magic)
{
    // Imported section
    GlobalDescriptorTable gdt;
    TaskManager taskManager;
    InterruptManager interrupts(0x20, &gdt, &taskManager);
    DriverManager drvManager;
    MouseToConsole mousehandler;
    MouseDriver mouse(&interrupts, &mousehandler);
    drvManager.AddDriver(&mouse);
    drvManager.ActivateAll();
    interrupts.Activate();
    // Imported section

	FrameBuffer::Writer p(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::BLACK);

	#if USE_BOOT_SCREEN_1
		#include "../include/bootscreen1.h"
	#else
		#include "../include/bootscreen2.h"
	#endif
	
	KEYBOARD_DRIVER::readInput(p);

	while (1);
}

                                                                                  
                                                                                  