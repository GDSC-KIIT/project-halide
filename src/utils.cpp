#include <utils.h>

void *mem_alloc(int nbytes) {
	char variable[nbytes];
	return &variable;
}