#ifndef _KERNEL_VESA_DRIVER
#define _KERNEL_VESA_DRIVER

#include <stdint.h>

typedef struct argb
{
	uint8_t a, r, g, b;
} argb_t __attribute__((packed));

uint32_t argb_to_color(argb_t *);
uint32_t vga_to_color(uint8_t);

void set_framebuffer(uint32_t *);
uint32_t *get_framebuffer();
uint32_t get_width();
uint32_t get_height();
uint32_t get_pitch();
uint32_t get_bpp();

void putpixels (int, int, argb_t *);
void putrectss (int, int, int, int, argb_t *);
void putrectfs (int, int, int, int, argb_t *);
void putrectsfs(int, int, int, int, argb_t *, argb_t *);

void putpixeli (int, int, uint32_t);
void putrectsi (int, int, int, int, uint32_t);
void putrectfi (int, int, int, int, uint32_t);
void putrectsfi(int, int, int, int, uint32_t, uint32_t);

#endif