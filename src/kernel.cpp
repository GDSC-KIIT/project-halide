#include <console.h>
#include <frame_buffer.h>
#include <globaldescriptortable.h>
#include <halidestdlib.h>
#include <keyboard.h>
#include <windows.h>

#include "../include/vesa_drivers/vesa.h"
#include <mem.h>
#include <vesa_drivers/window.h>

#include <vesa_drivers/text.h>
#include <vesa_drivers/video-tty.h>

#define USE_BOOT_SCREEN_1 1

typedef void (*ctor)();
extern "C" ctor begin_constructors;
extern "C" ctor end_constructors;
extern "C" void call_ctors() {
	for (ctor *i = &begin_constructors; i != &end_constructors; i++) {
		(*i)();
	}
}

static void initScreen(FrameBuffer::Writer &p, Window &win) {
	int x = win.m_y2;
	x = win.m_y2 - 1;
	p.writeString(win.m_title);
	p.fillRemeaning("=", true);
	p.writeAtIndex(x);
}

extern struct mem_mgr *new_mem_mgr(unsigned long start, unsigned long sz);
extern void set_framebuffer(unsigned int *);

void setup_memmgr(unsigned int *multiboot) {
	unsigned int *memupper = (unsigned int *)multiboot[2];
	new_mem_mgr(*memupper, 64 * 1048576);
}

extern "C" void k_main(unsigned int multiboot) {
	// window_t *wnd = window(desktop, "Hello world", 12, 10, 1000, 600);
	// wnd->border_color = 0xff000000;
	// wnd->background_color = 0xff00ffff;
	// wnd->draw(wnd);

	// // * instantiate globaldescriptortable here
	// GLOBAL_DESCRIPTOR_TABLE::GlobalDescriptorTable globaldescriptortable;
	// {
	// 	Window win;
	// 	FrameBuffer::Writer p(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::BLUE, win);
	// 	initScreen(p, win);
	// 	#if USE_BOOT_SCREEN_1 == 1
	// 	#include "../include/bootscreen1.h"
	// 	#elif USE_BOOT_SCREEN_1 == 0
	// 	#include "../include/bootscreen2.h"
	// 	#endif
	// 	p.writeString("\n\n\n\n\nEnter password : ");
	// 	while (true) {
	// 		char *input_buffer = KEYBOARD_DRIVER::readInput(p, 0);
	// 		int access = hldstd::stringCompare(input_buffer, (char *)"dsc-kiit");
	// 		if (access == 1) {
	// 			break;
	// 		} else {
	// 			p.writeString("Incorrect password enter again : \nEnter the password again : ");
	// 		}
	// 	}
	// 	p.writeString("Loading OS ...");
	// 	/* int timer=1000000000;
	// 	while (timer)
	// 	{
	// 		timer--;
	// 	} */
	// }
	//
	// Window win1(10, 70, 0, 9, (char *)"Basic window title v.0.2 instance 1 instance_id(a.0.1)");
	// FrameBuffer::Writer p(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::RED, win1);
	//
	// initScreen(p, win1);
	// /* int x = win1.m_y2;
	// x=win1.m_y2-1;
	// p.writeString(win1.m_title);
	// p.fillRemeaning("=", true);
	// p.write_at_index(x); */
	//
	// Window win2(10, 70, 9, 16, (char *)"Basic window title v.0.2 instance 2 instance_id(b.0.1)");
	// FrameBuffer::Writer p1(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::BLUE, win2);
	//
	// initScreen(p1, win2);
	// /* int y = win2.m_y2;
	// y=win2.m_y2-1;
	// p1.writeString(win2.m_title);
	// p1.fillRemeaning("=", true);
	// p1.write_at_index(y); */
	//
	// Window win3(10, 70, 16, 25, (char *)"Basic window title v.0.2 instance 3 instance_id(c.0.1)");
	// FrameBuffer::Writer p2(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::GREEN, win3);
	//
	// initScreen(p2, win3);
	// /* int z = win3.m_y2;
	// z=win3.m_y2-1;
	// p2.writeString(win3.m_title);
	// p2.fillRemeaning("=", true);
	// p2.write_at_index(z); */
	//
	// /* #if USE_BOOT_SCREEN_1 == 1
	// 	#include "../include/bootscreen1.h"
	// #elif USE_BOOT_SCREEN_1 == 0
	// 	#include "../include/bootscreen2.h"
	// #endif */
	// while (true) {
	// 	p.switchWindow(p);
	// 	while (true) {
	// 		char *input_buffer = KEYBOARD_DRIVER::readInput(p);
	// 		break;
	// 	}
	// 	p1.switchWindow(p1);
	// 	while (true) {
	// 		char *input_buffer = KEYBOARD_DRIVER::readInput(p1);
	// 		break;
	// 	}
	// 	p2.switchWindow(p2);
	// 	while (true) {
	// 		char *input_buffer = KEYBOARD_DRIVER::readInput(p2);
	// 		break;
	// 	}
	// }
	while (1)
		;
}
