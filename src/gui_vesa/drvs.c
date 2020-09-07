#include "../../include/vesa_drivers/vesa.h"
void putpixels(int x, int y, argb_t *c) {
	get_framebuffer()[x + y * get_pitch()] = argb_to_color(c);
}
void putlinehs(int x, int y, int w, argb_t *c) {
	int p = x-1 + y * get_pitch();
	for (int i = 0; i < w; i++)
		get_framebuffer()[p++] = argb_to_color(c);
}
void putlinevs(int x, int y, int h, argb_t *c) {
	int p = x + (y-1) * get_pitch();
	for (int i = 0; i < h; i++)
		get_framebuffer()[p += get_pitch()] = argb_to_color(c);
}
void putrectss (int x1, int y1, int x2, int y2, argb_t *c) {
	putlinehs(x1, y1, x2 - x1, c);
	putlinehs(x1, y2, x2 - x1, c);
	putlinevs(x1, y1, y2 - y1, c);
	putlinevs(x2, y1, y2 - y1, c);
}
void putrectfs (int x1, int y1, int x2, int y2, argb_t *c) {
	for (int y = y1; y < y2; y++)
		putlinehs(x1, y, (x2-x1), c);
}
void putrectsfs(int x1, int y1, int x2, int y2, argb_t *sc, argb_t *fc) {
	putlinehs(x1+0, y1, x2 - x1, sc);
	putlinehs(x1-0, y2, x2 - x1, sc);
	putlinevs(x1+1, y1, y2 - y1, sc);
	putlinevs(x2-1, y1, y2 - y1, sc);
	int x = x1+1;
	int x3= x2;
	for (int y = y1+1; y < (y2); y++)
		putlinehs(x, y, x3-x, fc);
}
