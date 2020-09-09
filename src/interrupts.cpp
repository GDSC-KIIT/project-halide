#include <interrupts.h>

void printf(char *) {}

InterruptHandler::InterruptHandler(InterruptManager *interruptManager, unsigned char InterruptNumber) {
	this->InterruptNumber = InterruptNumber;
	this->interruptManager = interruptManager;
	interruptManager->handlers[InterruptNumber] = this;
}

InterruptHandler::~InterruptHandler() {
	if (interruptManager->handlers[InterruptNumber] == this) interruptManager->handlers[InterruptNumber] = 0;
}

unsigned int InterruptHandler::HandleInterrupt(unsigned int esp) { return esp; }

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];
InterruptManager *InterruptManager::ActiveInterruptManager = 0;

void InterruptManager::SetInterruptDescriptorTableEntry(unsigned char interrupt, unsigned short CodeSegment, void (*handler)(), unsigned char DescriptorPrivilegeLevel, unsigned char DescriptorType) {
	// address of pointer to code segment (relative to global descriptor table)
	// and address of the handler (relative to segment)
	interruptDescriptorTable[interrupt].handlerAddressLowBits = ((unsigned int)handler) & 0xFFFF;
	interruptDescriptorTable[interrupt].handlerAddressHighBits = (((unsigned int)handler) >> 16) & 0xFFFF;
	interruptDescriptorTable[interrupt].gdt_codeSegmentSelector = CodeSegment;

	const unsigned char IDT_DESC_PRESENT = 0x80;
	interruptDescriptorTable[interrupt].access = IDT_DESC_PRESENT | ((DescriptorPrivilegeLevel & 3) << 5) | DescriptorType;
	interruptDescriptorTable[interrupt].reserved = 0;
}

InterruptManager::InterruptManager(unsigned short hardwareInterruptOffset, GLOBAL_DESCRIPTOR_TABLE::GlobalDescriptorTable *globalDescriptorTable)
	: programmableInterruptControllerMasterCommandPort(0x20), programmableInterruptControllerMasterDataPort(0x21), programmableInterruptControllerSlaveCommandPort(0xA0),
	  programmableInterruptControllerSlaveDataPort(0xA1) {
	this->hardwareInterruptOffset = hardwareInterruptOffset;
	unsigned int CodeSegment = globalDescriptorTable->codeSegment();

	const unsigned char IDT_INTERRUPT_GATE = 0xE;
	for (unsigned char i = 255; i > 0; --i) {
		SetInterruptDescriptorTableEntry(i, CodeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE);
		handlers[i] = 0;
	}
	SetInterruptDescriptorTableEntry(0, CodeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE);
	handlers[0] = 0;

	SetInterruptDescriptorTableEntry(0x00, CodeSegment, &HandleException0x00, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x01, CodeSegment, &HandleException0x01, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x02, CodeSegment, &HandleException0x02, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x03, CodeSegment, &HandleException0x03, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x04, CodeSegment, &HandleException0x04, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x05, CodeSegment, &HandleException0x05, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x06, CodeSegment, &HandleException0x06, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x07, CodeSegment, &HandleException0x07, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x08, CodeSegment, &HandleException0x08, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x09, CodeSegment, &HandleException0x09, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x0A, CodeSegment, &HandleException0x0A, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x0B, CodeSegment, &HandleException0x0B, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x0C, CodeSegment, &HandleException0x0C, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x0D, CodeSegment, &HandleException0x0D, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x0E, CodeSegment, &HandleException0x0E, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x0F, CodeSegment, &HandleException0x0F, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x10, CodeSegment, &HandleException0x10, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x11, CodeSegment, &HandleException0x11, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x12, CodeSegment, &HandleException0x12, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x13, CodeSegment, &HandleException0x13, 0, IDT_INTERRUPT_GATE);

	SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x00, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x01, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x02, CodeSegment, &HandleInterruptRequest0x02, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x03, CodeSegment, &HandleInterruptRequest0x03, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x04, CodeSegment, &HandleInterruptRequest0x04, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x05, CodeSegment, &HandleInterruptRequest0x05, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x06, CodeSegment, &HandleInterruptRequest0x06, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x07, CodeSegment, &HandleInterruptRequest0x07, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x08, CodeSegment, &HandleInterruptRequest0x08, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x09, CodeSegment, &HandleInterruptRequest0x09, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0A, CodeSegment, &HandleInterruptRequest0x0A, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0B, CodeSegment, &HandleInterruptRequest0x0B, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0C, CodeSegment, &HandleInterruptRequest0x0C, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0D, CodeSegment, &HandleInterruptRequest0x0D, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0E, CodeSegment, &HandleInterruptRequest0x0E, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0F, CodeSegment, &HandleInterruptRequest0x0F, 0, IDT_INTERRUPT_GATE);

	SetInterruptDescriptorTableEntry(0x80, CodeSegment, &HandleInterruptRequest0x80, 0, IDT_INTERRUPT_GATE);

	programmableInterruptControllerMasterCommandPort.Write(0x11);
	programmableInterruptControllerSlaveCommandPort.Write(0x11);

	// remap
	programmableInterruptControllerMasterDataPort.Write(hardwareInterruptOffset);
	programmableInterruptControllerSlaveDataPort.Write(hardwareInterruptOffset + 8);

	programmableInterruptControllerMasterDataPort.Write(0x04);
	programmableInterruptControllerSlaveDataPort.Write(0x02);

	programmableInterruptControllerMasterDataPort.Write(0x01);
	programmableInterruptControllerSlaveDataPort.Write(0x01);

	programmableInterruptControllerMasterDataPort.Write(0x00);
	programmableInterruptControllerSlaveDataPort.Write(0x00);

	InterruptDescriptorTablePointer idt_pointer;
	idt_pointer.size = 256 * sizeof(GateDescriptor) - 1;
	idt_pointer.base = (unsigned int)interruptDescriptorTable;
	asm volatile("lidt %0" : : "m"(idt_pointer));
}

InterruptManager::~InterruptManager() { Deactivate(); }

unsigned short InterruptManager::HardwareInterruptOffset() { return hardwareInterruptOffset; }

void InterruptManager::Activate() {
	if (ActiveInterruptManager != 0) ActiveInterruptManager->Deactivate();

	ActiveInterruptManager = this;
	asm("sti");
}

void InterruptManager::Deactivate() {
	if (ActiveInterruptManager == this) {
		ActiveInterruptManager = 0;
		asm("cli");
	}
}

unsigned int InterruptManager::HandleInterrupt(unsigned char interrupt, unsigned int esp) {
	if (ActiveInterruptManager != 0) return ActiveInterruptManager->DoHandleInterrupt(interrupt, esp);
	return esp;
}

unsigned int InterruptManager::DoHandleInterrupt(unsigned char interrupt, unsigned int esp) {
	if (handlers[interrupt] != 0) {
		esp = handlers[interrupt]->HandleInterrupt(esp);
	} else if (interrupt != hardwareInterruptOffset) {
		printf("UNHANDLED INTERRUPT 0x");
		// printfHex(interrupt);
	}

	// hardware interrupts must be acknowledged
	if (hardwareInterruptOffset <= interrupt && interrupt < hardwareInterruptOffset + 16) {
		programmableInterruptControllerMasterCommandPort.Write(0x20);
		if (hardwareInterruptOffset + 8 <= interrupt) programmableInterruptControllerSlaveCommandPort.Write(0x20);
	}

	return esp;
}