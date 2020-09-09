#include <interrupts.h>

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];

void InterruptManager::SetInterruptDescriptorTableEntry(unsigned char interruptNumber, unsigned short codeSegmentSelectorOffset, void (*handler)(), unsigned char DescriptorPrivilageLevel,
														unsigned char DescriptorType) {
	const unsigned char IDT_DESC_PRESENT = 0x80;
	interruptDescriptorTable[interruptNumber].handlerAddressLowBits = ((unsigned int)handler) & 0xFFFF;
	interruptDescriptorTable[interruptNumber].handlerAddressHighBits = ((unsigned int)handler >> 16) & 0xFFFF;
	interruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = codeSegmentSelectorOffset;
	interruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | DescriptorType | ((DescriptorPrivilageLevel & 3) << 5);
	interruptDescriptorTable[interruptNumber].reserved = 0;
}

InterruptManager::InterruptManager(GLOBAL_DESCRIPTOR_TABLE::GlobalDescriptorTable *gdt) {
	unsigned short CodeSegment = gdt->codeSegment();
	const unsigned char IDT_INTERRUPT_GATE = 0x0e;
	for (unsigned short i = 0; i < 256; i++) {
		SetInterruptDescriptorTableEntry(i, CodeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE);
	}

	SetInterruptDescriptorTableEntry(0x20, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x21, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);

	interruptDescriptorTablePointer idt;
	idt.size = 256 * (sizeof(GateDescriptor) - 1);
	idt.base = (unsigned int)interruptDescriptorTable;
	asm volatile("lidt %0" : : "m"(idt));
}
InterruptManager::~InterruptManager() {}

void InterruptManager::Activate() { asm("sti"); }

unsigned int InterruptManager::HandleInterrupt(unsigned char interruptNumber, unsigned int esp) {
	// printf("INTERRUPT : ");

	return esp;
}