#ifndef _KERNEL_MEM_H
#define _KERNEL_MEM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mem_chunk
{
	struct mem_chunk *prev;
	struct mem_chunk *next;
	bool allocated;
	size_t size;
} mem_chunk_t;

typedef struct mem_mgr
{
	mem_chunk_t *first;
} mem_mgr_t;

struct mem_mgr *new_mem_mgr(size_t start, size_t sz);

struct mem_mgr *get_active_mem_mgr();
void *kalloc(size_t);
void kfree(void*);

#ifdef __cplusplus
}

void* operator new(size_t size);
void* operator new[](size_t size);

// placement new
// void* operator new(size_t size, void* ptr);
// void* operator new[](size_t size, void* ptr);

void operator delete(void* ptr);
void operator delete[](void* ptr);

#endif

#endif