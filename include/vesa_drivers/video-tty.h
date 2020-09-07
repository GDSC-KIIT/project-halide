#ifndef _KERNEL_VIDEO_TTY_H
#define _KERNEL_VIDEO_TTY_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void terminal_setcolor(uint8_t);
void terminal_setbgcolor(uint8_t);
void terminal_goto(uint32_t, uint32_t);

void terminal_initialize();
void terminal_free();

void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);

#ifdef __cplusplus
}
#endif

#endif
