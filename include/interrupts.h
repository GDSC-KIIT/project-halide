#ifndef __IDT_H
#define __IDT_H

#include <globaldescriptortable.h>
#include <system.h>

class InterruptManager;

class InterruptHandler {
protected:
	unsigned char InterruptNumber;
	InterruptManager *interruptManager;
	InterruptHandler(InterruptManager *interruptManager, unsigned char InterruptNumber);
	~InterruptHandler();

public:
	virtual unsigned int HandleInterrupt(unsigned int esp);
};

class InterruptManager {
	friend class InterruptHandler;

protected:
	static InterruptManager *ActiveInterruptManager;
	InterruptHandler *handlers[256];

	struct GateDescriptor {
		unsigned short handlerAddressLowBits;
		unsigned short gdt_codeSegmentSelector;
		unsigned char reserved;
		unsigned char access;
		unsigned short handlerAddressHighBits;
	} __attribute__((packed));

	static GateDescriptor interruptDescriptorTable[256];

	struct InterruptDescriptorTablePointer {
		unsigned short size;
		unsigned int base;
	} __attribute__((packed));

	unsigned short hardwareInterruptOffset;
	static void SetInterruptDescriptorTableEntry(unsigned char interrupt, unsigned short codeSegmentSelectorOffset, void (*handler)(), unsigned char DescriptorPrivilegeLevel,
												 unsigned char DescriptorType);

	static void InterruptIgnore();

	static void HandleInterruptRequest0x00();
	static void HandleInterruptRequest0x01();
	static void HandleInterruptRequest0x02();
	static void HandleInterruptRequest0x03();
	static void HandleInterruptRequest0x04();
	static void HandleInterruptRequest0x05();
	static void HandleInterruptRequest0x06();
	static void HandleInterruptRequest0x07();
	static void HandleInterruptRequest0x08();
	static void HandleInterruptRequest0x09();
	static void HandleInterruptRequest0x0A();
	static void HandleInterruptRequest0x0B();
	static void HandleInterruptRequest0x0C();
	static void HandleInterruptRequest0x0D();
	static void HandleInterruptRequest0x0E();
	static void HandleInterruptRequest0x0F();
	static void HandleInterruptRequest0x31();

	static void HandleInterruptRequest0x80();

	static void HandleException0x00();
	static void HandleException0x01();
	static void HandleException0x02();
	static void HandleException0x03();
	static void HandleException0x04();
	static void HandleException0x05();
	static void HandleException0x06();
	static void HandleException0x07();
	static void HandleException0x08();
	static void HandleException0x09();
	static void HandleException0x0A();
	static void HandleException0x0B();
	static void HandleException0x0C();
	static void HandleException0x0D();
	static void HandleException0x0E();
	static void HandleException0x0F();
	static void HandleException0x10();
	static void HandleException0x11();
	static void HandleException0x12();
	static void HandleException0x13();

	static unsigned int HandleInterrupt(unsigned char interrupt, unsigned int esp);
	unsigned int DoHandleInterrupt(unsigned char interrupt, unsigned int esp);

	Port8BitSlow programmableInterruptControllerMasterCommandPort;
	Port8BitSlow programmableInterruptControllerMasterDataPort;
	Port8BitSlow programmableInterruptControllerSlaveCommandPort;
	Port8BitSlow programmableInterruptControllerSlaveDataPort;

public:
	InterruptManager(unsigned short hardwareInterruptOffset, GLOBAL_DESCRIPTOR_TABLE::GlobalDescriptorTable *globalDescriptorTable);
	~InterruptManager();
	unsigned short HardwareInterruptOffset();
	void Activate();
	void Deactivate();
};
#endif