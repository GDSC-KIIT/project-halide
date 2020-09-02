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
		static const unsigned char BLUE = (unsigned char) 0x1;
		static const unsigned char WHITE = (unsigned char) 0xf;
	}

	class Writer
	{
	private:
		char *START = (char *)0x0B8000;
		unsigned char fg;
		unsigned char bg;
	public:
		Writer(const unsigned char& foreground, const unsigned char& background) {
			fg = foreground;
			bg = background;
		}

		void print(char *str)
		{
			char *vid_mem = START;
			for (int i = 0; str[i] != '\0'; i++)
			{
				vid_mem[i * 2] = str[i];
				vid_mem[(i * 2) + 1] = ((fg & 0x0f) << 4) | (bg & 0x0f);
			}
		}
	};
} // namespace FrameBuffer
