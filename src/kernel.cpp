#include <console.h>
#include <windows.h>
int Window::instances = 0;
int Window::buffer_data[3][2];
#include <frame_buffer.h>
#include <globaldescriptortable.h>
#include <halidestdlib.h>
#include <interrupts.h>
#include <keyboard.h>

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

extern "C" void k_main() {
	// * instantiate globaldescriptortable here
	GLOBAL_DESCRIPTOR_TABLE::GlobalDescriptorTable globaldescriptortable;
	InterruptManager interrupts( &globaldescriptortable);
	{
		Window win;
		FrameBuffer::Writer p(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::LIGHT_BLUE, &win);
		initScreen(p, win);
#if USE_BOOT_SCREEN_1 == 1
#include "../include/bootscreen1.h"
#elif USE_BOOT_SCREEN_1 == 0
#include "../include/bootscreen2.h"
#endif
		p.writeString((char *)"\n\n\n\n\nEnter password : ");
		while (true) {
			char *input_buffer = KEYBOARD_DRIVER::readInput(p, 0);
			int access = hldstd::stringCompare(input_buffer, (char *)"dsc-kiit");
			if (access == 1) {
				break;
			} else {
				p.writeString("Incorrect password enter again : \nEnter the password again : ");
			}
		}
		p.writeString("Loading OS ...");
		/* int timer=1000000000;
		while (timer)
		{
			timer--;
		} */
	}

	Window win1(10, 70, 0, 9, (char *)"Basic window title v.0.2 instance 1 instance_id(a.0.1)");
	FrameBuffer::Writer p(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::LIGHT_BLUE, &win1);
	win1.storeBuffer(0, 9);
	initScreen(p, win1);

	Window win2(10, 70, 9, 16, (char *)"Basic window title v.0.2 instance 2 instance_id(b.0.1)");
	FrameBuffer::Writer p1(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::LIGHT_RED, &win2);
	initScreen(p1, win2);
	win2.storeBuffer(9, 16);

	Window win3(10, 70, 16, 25, (char *)"Basic window title v.0.2 instance 3 instance_id(c.0.1)");
	FrameBuffer::Writer p2(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::LIGHT_CYAN, &win3);
	initScreen(p2, win3);
	win3.storeBuffer(16, 25);

	int consoleRunning = 1;

	while (true && consoleRunning) {
		p.switchWindow(p);
		int x = init_console(p, win1);
		if (x == 2) {
			win3.DestroyWindow(&win2);
			p1.Rerender(&win2);
			x = 1;
		}
		if (x == 3) {
			win2.DestroyWindow(&win1);
			p.Rerender(&win1);
			x = 1;
		}
		if (x == 1) {
			if (win2.isDestroyed == false) {
				p1.switchWindow(p1);
				int y = init_console(p1, win2);
			}
			if ((win3.isDestroyed == false)) {
				p2.switchWindow(p2);
				int z = init_console(p2, win3);
			}
		}
		if (x == 0) {
			consoleRunning = 0;
		}
	}
	while (1)
		;
}
