#pragma once

#include <frame_buffer.h>

namespace KEYBOARD_DRIVER {
	char *readInput(FrameBuffer::Writer &p, int mode = 1);
}
