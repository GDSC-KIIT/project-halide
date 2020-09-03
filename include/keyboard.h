#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "../include/frame_buffer.h"

namespace KEYBOARD_DRIVER {
    char* readInput(FrameBuffer::Writer p);
}

#endif