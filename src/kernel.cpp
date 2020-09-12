#include <console.h>
#include <frame_buffer.h>
#include <globaldescriptortable.h>
#include <halidestdlib.h>
#include <interrupts.h>
#include <keyboard.h>
#include <windows.h>

#define CONSOLES 1

int Window::instances = 0;
int Window::buffer_data[3][2];
char Window::name[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

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

extern "C" void k_main(const void *multiboot_structure, unsigned int multiboot) {
	// * instantiate globaldescriptortable here
	GLOBAL_DESCRIPTOR_TABLE::GlobalDescriptorTable globaldescriptortable;
	InterruptManager interrupts(&globaldescriptortable); 
	{
		Window win;
		FrameBuffer::Writer p(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::LIGHT_BLUE, &win);
		initScreen(p, win);
#if USE_BOOT_SCREEN_1 == 1
#include "../include/bootscreen1.h"
#elif USE_BOOT_SCREEN_1 == 0
#include "../include/bootscreen2.h"
#endif
		p.writeString((char *)"\n\n\n\nEnter user name : ");
		char *user_name = KEYBOARD_DRIVER::readInput(p, 1);
		for (int i = 0; user_name[i] != '\0'; i++) {
			win.name[i] = user_name[i];
			win.name[i + 1] = '\0';
		}
		p.writeString((char *)"Enter password : ");
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
	}

	int widthWin1 = 15, widthWin2 = 20;

#if CONSOLES >= 1
	widthWin1 = 25;
#if CONSOLES >= 2
	widthWin1 = 20;
	widthWin2 = 25;
#if CONSOLES >= 3
	widthWin1 = 15;
	widthWin2 = 20;
#endif
#endif
#endif

#if CONSOLES >= 1

	Window win1(10, 70, 0, widthWin1, (char *)"Window 1");
	FrameBuffer::Writer p(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::BLACK, &win1);
	initScreen(p, win1);
	win1.storeBuffer(0, widthWin1);

#if CONSOLES >= 2

	Window win2(10, 70, widthWin1, widthWin2, (char *)"Window 2");
	FrameBuffer::Writer p1(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::BLUE, &win2);
	initScreen(p1, win2);
	win2.storeBuffer(widthWin1, widthWin2);

#if CONSOLES == 3

	Window win3(10, 70, widthWin2, 25, (char *)"Window 3");
	FrameBuffer::Writer p2(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::DARK_GREY, &win3);
	initScreen(p2, win3);
	win3.storeBuffer(widthWin2, 25);

#endif
#endif
#endif

	while (true) {
#if CONSOLES >= 1
		p.switchWindow(p);
		int x = init_console(p, win1);
#if CONSOLES >= 2
		if (x == 3) {
			win2.DestroyWindow(&win1);
			p.Rerender(&win1);
		}
#if CONSOLES != 3
		if (x == 1) {
			if (win2.isDestroyed == false) {
				p1.switchWindow(p1);
				int y = init_console(p1, win2);
			}
		}
#endif
#if CONSOLES == 3
		if (x == 2) {
			win3.DestroyWindow(&win2);
			p1.Rerender(&win2);
		}
		if (x == 1) {
			if (win2.isDestroyed == false) {
				p1.switchWindow(p1);
				int y = init_console(p1, win2);
			}
			if (win3.isDestroyed == false) {
				p2.switchWindow(p2);
				int z = init_console(p2, win3);
			}
		}
#endif
#endif
#endif
	}
	interrupts.Activate();
	while (1)
		;
}
