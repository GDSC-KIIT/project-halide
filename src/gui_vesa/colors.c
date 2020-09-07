#include "../../include/vesa_drivers/vesa.h"

uint32_t argb_to_color(argb_t *c)
{
	return (       \
		c->a << 24 \
	  | c->r << 16 \
	  | c->g <<  8 \
	  | c->b <<  0 \
	);
}

uint32_t vga_to_color(uint8_t vga)
{
	switch (vga)
	{
		case 0: return 0xff000000;
		case 1: return 0xff0000ff;
		case 2: return 0xff00ff00;
		case 3: return 0xff00ffff;
		case 4: return 0xffff0000;
		case 5: return 0xffff00ff;
		case 6: return 0xff8b4513;
		case 7: return 0xffd3d3d3;
		case 8: return 0xffa9a9a9;
		case 9: return 0xff00bfff;
		case 10:return 0xff7cfc00;
		case 11:return 0xffe0ffff;
		case 12:return 0xfff08080;
		case 13:return 0xffff80ff;
		case 14:return 0xffcd8032;
		case 15:return 0xffffffff;
	}
}