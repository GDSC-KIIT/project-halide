#include "../../include/vesa_drivers/window.h"
#include "../../include/mem.h"
#include "../../include/vesa_drivers/vesa.h"
// #include <kernel/text.h>

void draw_window(window_t * self)
{
	putrectsfi(self->x, self->y, self->x + self->w, self->y + self->h, self->border_color, self->background_color);
}

void draw_button(window_t * self)
{
	putrectsfi(self->x, self->y, self->x + self->w, self->y + self->h, self->border_color, self->background_color);
}

void draw_textfield(window_t * self)
{
	putrectsfi(self->x, self->y, self->x + self->w, self->y + self->h, self->border_color, self->background_color);
}

void draw_label(window_t * self)
{

}

window_t *window(window_t *parent, char * text, int x, int y, int w, int h)
{
	window_t *self = (window_t *) kalloc(sizeof(window_t));
	self->parent = parent;
	self->title = text;
	self->x = x;
	self->y = y;
	self->w = w;
	self->h = h;
	self->draw = draw_textfield;
}

window_t *moveWindow   (window_t * parent, int x, int y, int w, int h) {
	window_t *self = (window_t *) kalloc(sizeof(window_t));
	self->parent = parent;
	self->title = parent->title;
	self->x = x;
	self->y = y;
	self->w = w;
	self->h = h;
	self->draw = draw_textfield;
}

window_t *button(window_t *parent, char * text, int x, int y, int w, int h)
{

}

window_t *textfield(window_t *parent, char * text, int x, int y, int w, int h)
{

}

window_t *label(window_t *parent, char * text, int x, int y, int w, int h)
{

}

window_t *custom_window(window_t *parent, char * text, int x, int y, int w, int h, void (*draw)(window_t *))
{

}
