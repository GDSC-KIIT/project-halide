#include "../include/mm.h"

void Paging::blankOutPageDirectory(Paging::page_directory *pd){
	unsigned int i=0;

	for(i=0; i<PAGE_DIR_SIZE; i++) {
		pd->pdir_entries[i] = Paging::PT_FLAGS::WRITABLE;
	}
}

void Paging::initPageTable(Paging::page_table *pt) {
	unsigned int i = 0;

	for(int i=0; i<PAGE_TABLE_SIZE; i++){
		pt->ptable_entries[i] = (0x1000 * i) | Paging::PT_FLAGS::PRESENT | Paging::PT_FLAGS::WRITABLE;
	}
}