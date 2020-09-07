#include <globaldescriptortable.h>

GLOBAL_DESCRIPTOR_TABLE::GlobalDescriptorTable::GlobalDescriptorTable()
    : null(0,0,0), unused(0, 0, 0), code(0, 64*1024*1024, 0x9A), data(0, 64*1024*1024, 0x92)
{
    unsigned int i[2];
    i[0] = (unsigned int)this;
    i[1] = sizeof(GlobalDescriptorTable) << 16;
    asm volatile("lgdt (%0)": :"p" (((unsigned char*)i)+2));
}

GLOBAL_DESCRIPTOR_TABLE::GlobalDescriptorTable::~GlobalDescriptorTable() {}

unsigned short GLOBAL_DESCRIPTOR_TABLE::GlobalDescriptorTable::codeSegment()
{
    return (unsigned char*)&code - (unsigned char*)this;
}

unsigned short GLOBAL_DESCRIPTOR_TABLE::GlobalDescriptorTable::dataSegment()
{
    return (unsigned char*)&data - (unsigned char*)this;
}