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

namespace FrameBuffer
{
	namespace Colours
	{
		static const unsigned char BLACK = (unsigned char)0x0;
		static const unsigned char BLUE = (unsigned char)0x1;
		static const unsigned char GREEN = (unsigned char)0x2;
		static const unsigned char CYAN = (unsigned char)0x3;
		static const unsigned char RED = (unsigned char)0x4;
		static const unsigned char MAGENTA = (unsigned char)0x5;
		static const unsigned char BROWN = (unsigned char)0x6;
		static const unsigned char LIGHT_GREY = (unsigned char)0x7;
		static const unsigned char DARK_GREY = (unsigned char)0x8;
		static const unsigned char LIGHT_BLUE = (unsigned char)0x9;
		static const unsigned char LIGHT_GREEN = (unsigned char)0xa;
		static const unsigned char LIGHT_CYAN = (unsigned char)0xb;
		static const unsigned char LIGHT_RED = (unsigned char)0xc;
		static const unsigned char LIGHT_MAGENTA = (unsigned char)0xd;
		static const unsigned char LIGHT_BROWN = (unsigned char)0xe;
		static const unsigned char WHITE = (unsigned char)0xf;
	} // namespace Colours


	class Writer
	{
	private:
		char *START = (char *)0xB8000;
		static unsigned char fg, bg;
		static int cursorX, cursorY;
		const unsigned char s_width = 80, s_height = 25, sd = 2;

	public:
		Writer(const unsigned char &foreground, const unsigned char &background);
		void print(char *str);

		void clearLine();
		void clearScreen();
		void initScreen(const unsigned char &foreground, const unsigned char &background);
		void setColorTheme(const unsigned char &foreground, const unsigned char &background);
		void writeString(char *str);
		void writeChar(char c);
		void writeHex(unsigned char key);
		void scrolling();
		void clearCursor();
		void updateCursor();
	};
} // namespace FrameBuffer

#endif