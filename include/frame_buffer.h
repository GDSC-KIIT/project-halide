/*
Abstraction for console output using the framebuffer

The framebuffer starts from address 0x0B8000
Each word is 16 bits,
First byte is for the ASCII Character,
next 4 bits for the foreground colour and
the next 4 bits for the background colour
*/

#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <windows.h>

namespace FrameBuffer {
	namespace Colours {
		constexpr unsigned char BLACK = (unsigned char)0x0;
		constexpr unsigned char BLUE = (unsigned char)0x1;
		constexpr unsigned char GREEN = (unsigned char)0x2;
		constexpr unsigned char CYAN = (unsigned char)0x3;
		constexpr unsigned char RED = (unsigned char)0x4;
		constexpr unsigned char MAGENTA = (unsigned char)0x5;
		constexpr unsigned char BROWN = (unsigned char)0x6;
		constexpr unsigned char LIGHT_GREY = (unsigned char)0x7;
		constexpr unsigned char DARK_GREY = (unsigned char)0x8;
		constexpr unsigned char LIGHT_BLUE = (unsigned char)0x9;
		constexpr unsigned char LIGHT_GREEN = (unsigned char)0xa;
		constexpr unsigned char LIGHT_CYAN = (unsigned char)0xb;
		constexpr unsigned char LIGHT_RED = (unsigned char)0xc;
		constexpr unsigned char LIGHT_MAGENTA = (unsigned char)0xd;
		constexpr unsigned char LIGHT_BROWN = (unsigned char)0xe;
		constexpr unsigned char WHITE = (unsigned char)0xf;
	} // namespace Colours

	class Writer {
	private:
		char *START = (char *)0xB8000;
		const unsigned int s_width = 80, s_height = 25, sd = 2;
		
		unsigned char fg, bg;
		static int cursorX, cursorY;
		int x_min, x_max, y_upper, y_lower;
		
		bool framesDrawn = false; // & Used for preventing buffer_clearing when initializing window

	public:
		Window *current_window;

		Writer(const unsigned char &foreground, const unsigned char &background, Window*);
		void clearLine(unsigned char from, unsigned char to);
		void clearScreen();
		void initScreen(const unsigned char &foreground, const unsigned char &background);
		void setColorTheme(const unsigned char &foreground, const unsigned char &background);
		void writeString(char *str, unsigned char = FrameBuffer::Colours::WHITE);
		void writeHex(unsigned char key);
		void fillRemeaning(char *, bool);
		void writeAtIndex(int);
		void switchWindow(Writer &);
		void clearCursor();
		void shiftCursor(int, char *);
		void updateCursor();
		void Rerender(Window*);
	};
} // namespace FrameBuffer

#endif