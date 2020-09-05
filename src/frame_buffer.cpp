// ^ Comment legend for this file
// ? Doubtful or buggy code
// ! Needs implementation (Urgently)
// * Old implmentation of function
// ~ New implementation of code
// TODO : for todos
// & To indicate you are working on something new that shoud not be touched by other contributors
// Normal comments

#include "../include/frame_buffer.h"
#include "../include/system.h"
#include "../include/windows.h"

// initialising cursor positions, foreground and background colours
int FrameBuffer::Writer::cursorX = 0;
int FrameBuffer::Writer::cursorY = 0;
unsigned char FrameBuffer::Writer::fg = FrameBuffer::Colours::BLACK;
unsigned char FrameBuffer::Writer::bg = FrameBuffer::Colours::WHITE;

// Todo : Add coords for implementing windows
FrameBuffer::Writer::Writer(const unsigned char &foreground, const unsigned char &background) // ! Add more new args for windows implimentation
{
	FrameBuffer::Writer::initScreen(foreground, background);
}

// clear out line and move the cursor to the start of the line
// * Old implimentation of clear line
/* void FrameBuffer::Writer::clearLine()
{
	char *vid_mem = (char *)START;

	for (int i = 0; i < s_width; i++)
	{
		vid_mem[((cursorY * s_width) + i) * 2] = ' ';
		vid_mem[((cursorY * s_width) + i) * 2 + 1] = ((bg & 0x0f) << 4) | (fg & 0x0f);
	}

	cursorX = 0;
	updateCursor();
} */


// ~ New implementation of clean line
void FrameBuffer::Writer::clearLine(unsigned char from,unsigned char to)
{
    unsigned int i = s_width * from * sd;
    char* vidmem=(char*)0xb8000;
    for(i;i<(s_width*to*sd);i++)
    {
        vidmem[(i / 2)*2 + 1 ] = 0x0F ;
        vidmem[(i / 2)*2 ] = 0;
    }
    // for (uint32 i = 0; i < 79*24*2; i++)
    // {
    //     vidmem[(cursorY*s_width) + (i*2)] = 0x00;
    // }
    cursorX=0;
    cursorY=from;
    updateCursor();
}


// Will clear the entire screen
// * Old implementation of clearScreen function
/* void FrameBuffer::Writer::clearScreen()
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
} */


// ~ New implementation of clearScreen function
void FrameBuffer::Writer::clearScreen() {
    clearLine(0, 24);
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

// ! Needs some bug fxes
// * Old implemention of writeString furnction
/* void FrameBuffer::Writer::writeString(char *str)
{
	char *vid_mem = START;

	for (int i = 0; str[i] != '\0'; i++)
	{
		// if screen ends
		if (cursorY >= 25)
		{
			FrameBuffer::Writer::clearScreen();
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
} */

// ~ New implemention of writeString furnction
void FrameBuffer::Writer::writeString(char *str)
{
	char* vidmem=(char*)0x000B8000;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] == '\n') {
            vidmem[((cursorY * s_width) + cursorX) * 2] = ' ';
			vidmem[((cursorY * s_width) + cursorX) * 2 + 1] = (((unsigned char)bg & 0x0f) << 4) | ((unsigned char)fg & 0x0f);
			cursorX = 0;
			cursorY += 1;
        }
		if(cursorY>=25) {
            clearLine(0, 25);
			vidmem[0] = '\t';
			vidmem[1] = (((unsigned char)fg & 0x0f) << 4 | ((unsigned char)bg) & 0x0F); // * It needs inverting of current color
            cursorX=1;
            cursorY=0;
            break;
        }
        if(str[i] == '\r') {
            cursorX-=1;
            vidmem[(cursorY*s_width + cursorX)*2] = 0;
			
			char *vid_mem = START;
			vid_mem[(cursorY * s_width + cursorX+1) * 2] = ' ';
			vid_mem[(cursorY * s_width + cursorX+1) * 2 + 1] = ((bg & 0x0f) << 4) | (fg & 0x0f);
        }
        else { 
            vidmem[(cursorY*s_width + cursorX)*2] = str[i];
            vidmem[(cursorY*s_width + cursorX)*2 + 1] = ((bg & 0x0f) << 4) | (fg & 0x0f);
            cursorX++;
        }
        if(cursorX >= s_width) {
            cursorY++;
            cursorX=1;
        } 
    }
    updateCursor();
}

// We use this function of debugging interrupts codes
void FrameBuffer::Writer::writeHex(unsigned char key)
{
	char *x = "00";
	char *hex = "0123456789ABCDEF";
	x[0] = hex[(key >> 4) & 0xF];
	x[1] = hex[key & 0xF];
	FrameBuffer::Writer::writeString(x);
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