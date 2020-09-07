#include "../../include/vesa_drivers/vesa.h"
void putpixeli(int x, int y, uint32_t c) {
	get_framebuffer()[x + (y * get_pitch() / 4)] = c;
}
void putlinehi(int x, int y, int w, uint32_t c) {
	int p = x + y * get_pitch() / 4;
	for (int i = 0; i < w; i++)
		get_framebuffer()[p++] = c;
}
void putlinevi(int x, int y, int h, uint32_t c) {
	int p = x + (y) * get_pitch() / 4;
	for (int i = 0; i < h; i++)
		get_framebuffer()[p += get_pitch() / 4] = c;
}
void putrectsi (int x1, int y1, int x2, int y2, uint32_t c) {
	putlinehi(x1, y1, x2 - x1, c);
	putlinehi(x1, y2, x2 - x1, c);
	putlinevi(x1, y1, y2 - y1, c);
	putlinevi(x2, y1, y2 - y1, c);
}
void putrectfi (int x1, int y1, int x2, int y2, uint32_t c) {
	for (int y = y1; y < y2; y++)
		putlinehi(x1, y, (x2-x1), c);
}
void putrectsfi(int x1, int y1, int x2, int y2, uint32_t sc, uint32_t fc) {
	putrectsi(x1, y1, x2, y2, sc);
	putrectfi(x1+1, y1+1, x2, y2, fc);
}
