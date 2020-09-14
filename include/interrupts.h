#ifndef __IDT_H
#define __IDT_H

#include <globaldescriptortable.h>
#include <system.h>

class InterruptManager {

protected:
	struct GateDescriptor {
		unsigned short handlerAddressLowBits;
		unsigned short gdt_codeSegmentSelector;
		unsigned char reserved;
		unsigned char access;
		unsigned short handlerAddressHighBits;
	} __attribute__((packed));

	static GateDescriptor interruptDescriptorTable[256];
	struct interruptDescriptorTablePointer {
		unsigned char size;
		unsigned int base;
	} __attribute__((packed));

	static void SetInterruptDescriptorTableEntry(unsigned char interruptNumber, unsigned short codeSegmentSelectorOffset, void (*handler)(),
												 unsigned char DescriptorPrivilageLevel, unsigned char DescriptorType);
	__8bitportSlow picMasterCommand;
	__8bitportSlow picMasterData;
	__8bitportSlow picSlaveCommand;
	__8bitportSlow picSlaveData;

public:
	InterruptManager(GLOBAL_DESCRIPTOR_TABLE::GlobalDescriptorTable *globalDescriptorTable);

	void Activate();
	static unsigned int HandleInterrupt(unsigned char interruptNumber, unsigned int esp);
	static void IgnoreInterruptRequest();
	static void HandleInterruptRequest0x00();
	static void HandleInterruptRequest0x01();

	~InterruptManager();
};
#endif