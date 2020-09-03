#include "../include/frame_buffer.h"
#include "../include/system.h"

// initialising cursor positions, foreground and background colours
int FrameBuffer::Writer::cursorX = 0;
int FrameBuffer::Writer::cursorY = 0;
unsigned char FrameBuffer::Writer::fg = FrameBuffer::Colours::BLACK;
unsigned char FrameBuffer::Writer::bg = FrameBuffer::Colours::WHITE;

// Implementation need to be done so that when we write new data it begin with cursor position
void FrameBuffer::Writer::print(char *str)
{
	// Experimental implementation
	char *vid_mem = START;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (cursorY >= 25)
		{
			cursorX = 0;
			cursorY = 0;
			break;
		}
		if (str[i] == '\n')
		{
			// If possible i woud like to reduce these two lines
			vid_mem[((cursorY * s_width) + cursorX) * 2] = ' ';
			vid_mem[((cursorY * s_width) + cursorX) * 2 + 1] = (((unsigned char)bg & 0x0f) << 4) | ((unsigned char)fg & 0x0f);
			// If possible i woud like to reduce these two lines
			cursorY += 1;
			cursorX = 0;
		}
		else if (str[i] == '\r')
		{
			cursorX -= 1;
			vid_mem[(cursorY * s_width + cursorX) * 2] = 0;
			// If possible i woud like to reduce these two lines
			vid_mem[((cursorY * s_width) + cursorX + 1) * 2] = ' ';
			vid_mem[((cursorY * s_width) + cursorX + 1) * 2 + 1] = (((unsigned char)bg & 0x0f) << 4) | ((unsigned char)fg & 0x0f);
		}
		else
		{
			vid_mem[(cursorY * s_width + cursorX) * 2] = str[i];
			vid_mem[(cursorY * s_width + cursorX) * 2 + 1] = ((bg & 0x0f) << 4) | (fg & 0x0f);

			cursorX++;
		}
		if (cursorX >= s_width)
		{
			cursorY++;
			cursorX = 0;
		}
	}
	updateCursor();
}

// New Functions

FrameBuffer::Writer::Writer(const unsigned char &foreground, const unsigned char &background) {
	FrameBuffer::Writer::initScreen(foreground, background);
}


// clear out line and move the cursor to the start of the line
void FrameBuffer::Writer::clearLine()
{
	char *vid_mem = (char *)START;

	for (int i = 0; i < s_width; i++)
	{
		vid_mem[((cursorY * s_width) + i) * 2] = ' ';
		vid_mem[((cursorY * s_width) + i) * 2 + 1] = ((bg & 0x0f) << 4) | (fg & 0x0f);
	}

	cursorX = 0;
	updateCursor();
}

// Will clear the entire screen
void FrameBuffer::Writer::clearScreen()
{
	char *vid_mem = (char *)START;
	cursorY = 0;
	cursorX = 0;

	for (int i = 0; i < s_height; i++)
	{
		clearLine();
		clearCursor();
		cursorY++;
	}

	cursorY = 0;
	cursorX = 0;
	updateCursor();
}

void FrameBuffer::Writer::initScreen(const unsigned char &foreground, const unsigned char &background)
{
	fg = foreground;
	bg = background;
	clearScreen();
}

void FrameBuffer::Writer::setColorTheme(const unsigned char &foreground, const unsigned char &background)
{
	fg = foreground;
	bg = background;
}

void FrameBuffer::Writer::writeString(char *str)
{
	char *vid_mem = START;

	for (int i = 0; str[i] != '\0'; i++)
	{
		// if screen ends
		if (cursorY >= 24)
		{
			cursorX = 0;
			cursorY = 0;
			break;
		}

		// if enter is pressed
		if (str[i] == '\n')
		{
			vid_mem[((cursorY * s_width) + cursorX) * 2] = ' ';
			vid_mem[((cursorY * s_width) + cursorX) * 2 + 1] = (((unsigned char)bg & 0x0f) << 4) | ((unsigned char)fg & 0x0f);
			
			cursorY += 1;
			cursorX = 0;
		}
		else if (str[i] == '\r')
		{
			cursorX -= 1;
			vid_mem[(cursorY * s_width + cursorX) * 2] = 0;
			vid_mem[((cursorY * s_width) + cursorX + 1) * 2] = ' ';
			vid_mem[((cursorY * s_width) + cursorX + 1) * 2 + 1] = (((unsigned char)bg & 0x0f) << 4) | ((unsigned char)fg & 0x0f);
		}
		else
		{
			vid_mem[(cursorY * s_width + cursorX) * 2] = str[i];
			vid_mem[(cursorY * s_width + cursorX) * 2 + 1] = ((bg & 0x0f) << 4) | (fg & 0x0f);

			cursorX++;
		}

		// if line ends
		if (cursorX >= s_width)
		{
			cursorY++;
			cursorX = 0;
		}
	}

	updateCursor();
}


void FrameBuffer::Writer::writeHex(unsigned char key){
	char *x = "00";
	char *hex = "0123456789ABCDEF";
	x[0] = hex[(key >> 4) & 0xF];
	x[1] = hex[key & 0xF];
	FrameBuffer::Writer::print(x);
}

// Clears the current cursorX and cursorY
void FrameBuffer::Writer::clearCursor()
{
	char *vid_mem = START;
	vid_mem[(cursorY * s_width + cursorX) * 2] = ' ';
	vid_mem[(cursorY * s_width + cursorX) * 2 + 1] = ((bg & 0x0f) << 4) | (fg & 0x0f);
}

// Move the cursor to the current cursorX and cursorY
void FrameBuffer::Writer::updateCursor()
{
	unsigned int position;

	position = cursorY * s_width + cursorX;

	outportb(0x3D4, 14);
	outportb(0x3D5, position >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, position);

	char *vid_mem = START;
	vid_mem[(cursorY * s_width + cursorX) * 2] = '_';
	vid_mem[(cursorY * s_width + cursorX) * 2 + 1] = ((bg & 0x0f) << 4) | (fg & 0x0f);
}