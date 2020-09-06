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


//initializing static data members of the Writer class
int FrameBuffer::Writer::cursorX=0;
int FrameBuffer::Writer::cursorY=0;

#include "../include/utils.h"

// Todo : Add coords for implementing windows
FrameBuffer::Writer::Writer(const unsigned char &foreground, const unsigned char &background, Window win) // ! Add more new args for windows implimentation
{
	//current_window = &win;
	x_min = win.m_x1;
	x_max = win.m_x2;
	y_upper = win.m_y1;
	y_lower = win.m_y2;
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
        vidmem[(i / 2)*2 + 1 ] =  (((unsigned char)bg & 0x0f) << 4) | ((unsigned char)fg & 0x0f);
        vidmem[(i / 2)*2 ] = ' ';
    }
    // for (uint32 i = 0; i < 79*24*2; i++)
    // {
    //     vidmem[(cursorY*s_width) + (i*2)] = 0x00;
    // }
    cursorX=0;
    cursorY=from;
    updateCursor();
}

void FrameBuffer::Writer::fillRemeaning(char* fill_character, bool n_line)
{
	for (int i = cursorX; i < 79; i++)
	{
		writeString(fill_character);
	}
	//(n_line) ? writeString("\n") : void();
	if(n_line) {
		writeString("\n");
	}
	else {
		framesDrawn=true;
	}
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
    clearLine(y_upper, y_lower);
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

void FrameBuffer::Writer::write_at_index(int x)
{
	int temp = cursorX;
	int temp1 = cursorY;
	cursorY = x;
	updateCursor();
	fillRemeaning("=", false);
	cursorX = temp;
	cursorY = temp1;
	updateCursor();
	writeString("halideos $ ");
}

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
		// Case when we reach bottom of the current window
		if(cursorY >= y_lower-1 && framesDrawn) {
            clearLine(y_upper+1, y_lower-1);
			// vidmem[0] = '\t';
			// vidmem[1] = (((unsigned char)fg & 0x0f) << 4 | ((unsigned char)bg) & 0x0F); // * It needs inverting of current color
            cursorX=0;
            cursorY=y_upper+1;
			//break;
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

// & Shift cursor (impliment arrow keys) Make append functions for that
char* localStorage = (char*)mem_alloc(200);
int pointer=0;
void FrameBuffer::Writer::shiftCursor(int axis, char* buffer) {
	int y = axis;
	char *vid_mem = START;
	if(axis == -1) {
		cursorX-=1;
		vid_mem[(cursorY * s_width + cursorX+1) * 2 + 1] = ((bg & 0x0f) << 4) | (fg & 0x0f);
		updateCursor();
	}
	else if (axis == 1) {
		cursorX+=1;
		vid_mem[(cursorY * s_width + cursorX-1) * 2 + 1] = ((bg & 0x0f) << 4) | (fg & 0x0f);
		updateCursor();
	}
}

void FrameBuffer::Writer::switchWindow(FrameBuffer::Writer& p)
{
	p.cursorX = 0;
	p.cursorY = p.y_upper+1;
	p.updateCursor();
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
	//vid_mem[(cursorY * s_width + cursorX) * 2] = '_';
	vid_mem[(cursorY * s_width + cursorX) * 2 + 1] = ((fg & 0x0f) << 4) | (bg & 0x0f);
}