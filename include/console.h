#ifndef __CONSOLE_H
#define __CONSOLE_H

#include <frame_buffer.h>
#include <keyboard.h>
#include <windows.h>

int init_console(FrameBuffer::Writer&, Window&);

#endif