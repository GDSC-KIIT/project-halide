#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <frame_buffer.h>

namespace KEYBOARD_DRIVER
{
	char *readInput(FrameBuffer::Writer &p, int mode=1);
}

#endif