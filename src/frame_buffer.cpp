#include "../include/frame_buffer.h"

FrameBuffer::Writer::Writer(const unsigned char &foreground, const unsigned char &background)
{
    fg = foreground;
	bg = background;
}

void FrameBuffer::Writer::print(char* str)
{
    char *vid_mem = START;
	for (int i = 0; str[i] != '\0'; i++)
	{
		vid_mem[i * 2] = str[i];
		vid_mem[(i * 2) + 1] = ((bg & 0x0f) << 4) | (fg & 0x0f);
	}
}