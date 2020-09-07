#include <mem.h>

struct mem_mgr* active = 0;

struct mem_mgr *new_mem_mgr(size_t start, size_t sz)
{
	mem_chunk_t *first = (sz < sizeof(mem_chunk_t) ? 0 : (mem_chunk_t*) start);
	mem_mgr_t self = {
		.first = first
	};

	first->allocated = false;
	first->prev = 0;
	first->next = 0;
	first->size = sz - sizeof(mem_chunk_t);

	active = &self;
	return active;
}

struct mem_mgr *get_active_mem_mgr()
{
	return active;
}

void* kalloc(size_t sz)
{
	mem_chunk_t *res = 0;
	for (mem_chunk_t *c = active->first; c != 0 && res == 0; c = c->next)
		if (c->size > sz && !c->allocated)
			res = c;

	if (res == 0)
		return 0;

	if (res->size >= sz + sizeof(mem_chunk_t) + 1)
	{
		mem_chunk_t *temp = (mem_chunk_t*)((size_t)res + sizeof(mem_chunk_t) + sz);
		temp->allocated = false;
		temp->size = res->size - sz - sizeof(mem_chunk_t);
		temp->prev = res;
		temp->next = res->next;
		if (temp->next != 0)
			temp->next->prev = temp;
		res->size = sz;
		res->next = temp;
	}

	res->allocated = true;
	return (void*)(((size_t)res) + sizeof(mem_chunk_t));
}

void kfree(void *ptr)
{
	mem_chunk_t* chunk = (mem_chunk_t*)((size_t)ptr - sizeof(mem_chunk_t));
	
	chunk -> allocated = false;
	
	if(chunk->prev != 0 && !chunk->prev->allocated)
	{
		chunk->prev->next = chunk->next;
		chunk->prev->size += chunk->size + sizeof(mem_chunk_t);
		if(chunk->next != 0)
			chunk->next->prev = chunk->prev;
		
		chunk = chunk->prev;
	}
	
	if(chunk->next != 0 && !chunk->next->allocated)
	{
		chunk->size += chunk->next->size + sizeof(mem_chunk_t);
		chunk->next = chunk->next->next;
		if(chunk->next != 0)
			chunk->next->prev = chunk;
	}
}

void* operator new(size_t size)
{
    if(get_active_mem_mgr() == 0)
        return 0;
    return kalloc(size);
}

void* operator new[](size_t size)
{
    if(get_active_mem_mgr() == 0)
        return 0;
    return kalloc(size);
}
void operator delete(void* ptr)
{
    if(get_active_mem_mgr() != 0)
        kfree(ptr);
}

void operator delete[](void* ptr)
{
    if(get_active_mem_mgr() != 0)
        kfree(ptr);
}