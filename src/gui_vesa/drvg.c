#include "../../include/vesa_drivers/vesa.h"

uint32_t *framebuffer;
uint32_t fb_w, fb_h, fb_p, fb_bpp;

void set_framebuffer(uint32_t *mb) {
	framebuffer = (uint32_t *) mb[22];
	fb_p = mb[24];
	fb_w = mb[25];
	fb_h = mb[26];
	fb_bpp = mb[27] >> 24;
}

inline uint32_t *get_framebuffer()
{
	return framebuffer;
}

inline uint32_t get_width()
{
	return fb_w;
}

inline uint32_t get_height()
{
	return fb_h;
}

inline uint32_t get_pitch()
{
	return fb_p;
}

inline uint32_t get_bpp()
{
	return fb_bpp;
}