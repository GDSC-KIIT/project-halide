#include "../../include/vesa_drivers/font.h"
#include "../../include/vesa_drivers/vesa.h"
#include "../../include/vesa_drivers/vga.h"
// #include <string.h>
#include "../../include/vesa_drivers/text.h"

int x = 0;
int x2 = 0;
int y = 0;

uint32_t fg = 0xffffffff;
uint32_t bg = 0xff000000;

void set_printing_coords(int dx, int dy)
{
	x = dx;
	x2 = x;
	y = dy;
}

void print_ch(char c)
{
	int lx; int ly;
	uint8_t *bitmap = font8x8_basic[c % 128];
	for (lx = 0; lx < GLYPH_WIDTH; lx++) {
		for (ly = 0; ly < GLYPH_HEIGHT; ly++) {
			uint8_t row = bitmap[ly];
			if ((row >> lx) & 1)
				putpixeli(x+lx, y+ly, fg);
			else
				putpixeli(x+lx, y+ly, bg);
		}
	}
}

void put_char(char c)
{
	if (c == '\n')
	{
		y += GLYPH_HEIGHT;
		x = x2;
	} else if (c == '\b')
	{
		x -= GLYPH_WIDTH;
	} else if (c == '\r')
	{
		x = x2;
	} else
	{
		print_ch(c);
		x += GLYPH_WIDTH;
	}
}

void set_fg_color(uint32_t fgc)
{
	fg = fgc;
}
void set_bg_color(uint32_t bgc)
{
	bg = bgc;
}

// void put_string(char *s)
// {
// 	size_t l = strlen(s);
// 	for (size_t i = 0; i < l; i++)
// 	{
// 		char c = s[i];
// 		put_char(c);
// 	}
// }