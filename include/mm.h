#ifndef __MM_VMEM_H
#define __MM_VMEM_H

#define PAGE_SIZE 4096
#define PAGE_TABLE_SIZE 1024
#define PAGE_DIR_SIZE 1024

namespace Paging {

	namespace PD_FLAGS {
		constexpr unsigned int PRESENT = 1;		   // 0000000000000000000000000000001
		constexpr unsigned int WRITABLE = 2;	   // 0000000000000000000000000000010
		constexpr unsigned int USER = 4;		   // 0000000000000000000000000000100	
		constexpr unsigned int PWT = 8;			   // 0000000000000000000000000001000
		constexpr unsigned int PCD = 0x10;		   // 0000000000000000000000000010000
		constexpr unsigned int ACCESSED = 0x20;	   // 0000000000000000000000000100000
		constexpr unsigned int DIRTY = 0x40;	   // 0000000000000000000000001000000
		constexpr unsigned int FOUR_MB = 0x80;	   // 0000000000000000000000010000000
		constexpr unsigned int CPU_GLOBAL = 0x100; // 0000000000000000000000100000000
		constexpr unsigned int LV4_GLOBAL = 0x200; // 0000000000000000000001000000000
		constexpr unsigned int FRAME = 0x7FFFF000; // 1111111111111111111000000000000
	}											   // namespace PD_FLAGS

	namespace PT_FLAGS {
		constexpr unsigned int PRESENT = 1;			 // 0000000000000000000000000000001
		constexpr unsigned int WRITABLE = 2;		 // 0000000000000000000000000000010
		constexpr unsigned int USER = 4;			 // 0000000000000000000000000000100
		constexpr unsigned int WRITETHOUGH = 8;		 // 0000000000000000000000000001000
		constexpr unsigned int NOT_CACHEABLE = 0x10; // 0000000000000000000000000010000
		constexpr unsigned int ACCESSED = 0x20;		 // 0000000000000000000000000100000
		constexpr unsigned int DIRTY = 0x40;		 // 0000000000000000000000001000000
		constexpr unsigned int PAT = 0x80;			 // 0000000000000000000000010000000
		constexpr unsigned int CPU_GLOBAL = 0x100;	 // 0000000000000000000000100000000
		constexpr unsigned int LV4_GLOBAL = 0x200;	 // 0000000000000000000001000000000
		constexpr unsigned int FRAME = 0x7FFFF000;	 // 11111111111111111110000000000000
	};												 // namespace PT_FLAGS

	struct page_directory {
		unsigned int pdir_entries[PAGE_DIR_SIZE] __attribute__((aligned(4096)));
	} __attribute__((packed));

	struct page_table {
		unsigned int ptable_entries[PAGE_TABLE_SIZE] __attribute__((aligned(4096)));
	} __attribute__((packed));

	void blankOutPageDirectory(page_directory *pd);
	void initPageTable(page_table *pt);
} // namespace Paging

#endif