#ifndef _KERNEL_TEXT
#define _KERNEL_TEXT

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void put_char(char);
void set_fg_color(uint32_t);
void set_bg_color(uint32_t);
void put_string(char*);
void set_printing_coords(int, int);

#ifdef __cplusplus
}
#endif

#endif