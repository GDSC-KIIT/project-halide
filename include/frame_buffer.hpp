/*
Abstraction for console output using the framebuffer

The framebuffer starts from address 0x0B8000
Each word is 16 bits, 
First byte is for the ASCII Character, 
next 4 bits for the foreground colour and
the next 4 bits for the background colour
*/

#pragma once

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
		char *START = (char *)0x0B8000;
		unsigned char fg;
		unsigned char bg;

	public:
		Writer(const unsigned char &foreground, const unsigned char &background)
		{
			fg = foreground;
			bg = background;
		}

		void print(char *str)
		{
			char *vid_mem = START;
			for (int i = 0; str[i] != '\0'; i++)
			{
				vid_mem[i * 2] = str[i];
				vid_mem[(i * 2) + 1] = ((bg & 0x0f) << 4) | (fg & 0x0f);
			}
		}
	};
} // namespace FrameBuffer
