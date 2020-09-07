#ifndef _KERNEL_UI_WINDOW
#define _KERNEL_UI_WINDOW

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct window;

enum window_type
{
	WINDOW,
	BUTTON,
	TEXT,
	LABEL,
	CUSTOM_WINDOW
};

typedef struct window
{
	int x, y;
	int w, h;

	char *title;

	struct window *parent;

	int type;

	void (*draw)(struct window *);

	uint32_t border_color;
	uint32_t text_color;
	uint32_t background_color;
} window_t;

window_t *window       (window_t *, char *, int, int, int, int);
window_t *button       (window_t *, char *, int, int, int, int);
window_t *textfield    (window_t *, char *, int, int, int, int);
window_t *label        (window_t *, char *, int, int, int, int);
window_t *custom_window(window_t *, char *, int, int, int, int, void (*)(window_t *));

#ifdef __cplusplus
}
#endif

#endif