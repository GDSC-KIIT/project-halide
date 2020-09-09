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

InterruptManager::InterruptManager(GLOBAL_DESCRIPTOR_TABLE::GlobalDescriptorTable *gdt) : picMasterCommand(0x20), picMasterData(0x21), picSlaveCommand(0xA0), picSlaveData(0xA1) {
	unsigned short CodeSegment = gdt->codeSegment();
	const unsigned char IDT_INTERRUPT_GATE = 0x0e;
	for (unsigned short i = 0; i < 256; i++) {
		SetInterruptDescriptorTableEntry(i, CodeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE);
	}

	SetInterruptDescriptorTableEntry(0x20, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x21, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);

    picMasterData.Write(0x11);
    picSlaveCommand.Write(0x11);

    picMasterData.Write(0x20);
    picSlaveData.Write(0x28);
    //
    picMasterData.Write(0x04);
    picSlaveData.Write(0x02);

    picMasterData.Write(0x01);
    picSlaveData.Write(0x01);

    picMasterData.Write(0x00);
    picSlaveData.Write(0x00);

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