#include <system.h>

//& Old implimentation
unsigned char inportb(unsigned short _port) {
	unsigned char rv;
	__asm__ __volatile__("inb %1, %0" : "=a"(rv) : "dN"(_port));
	return rv;
}

void outportb(unsigned short _port, unsigned char _data) { __asm__ __volatile__("outb %1, %0" : : "dN"(_port), "a"(_data)); }

// & New implimentation
Port::Port(unsigned short portnumber) { this->portnumber = portnumber; }

Port::~Port() {}

__8bitport::__8bitport(unsigned short portnumber) : Port(portnumber) {}

__8bitport::~__8bitport() {}

void __8bitport::Write(unsigned char data) { Write8(portnumber, data); }

unsigned char __8bitport::Read() { return Read8(portnumber); }

__8bitportSlow::__8bitportSlow(unsigned short portnumber) : __8bitport(portnumber) {}

__8bitportSlow::~__8bitportSlow() {}

void __8bitportSlow::Write(unsigned char data) { Write8Slow(portnumber, data); }

__16bitPort::__16bitPort(unsigned short portnumber) : Port(portnumber) {}

__16bitPort::~__16bitPort() {}

void __16bitPort::Write(unsigned short data) { Write16(portnumber, data); }

unsigned short __16bitPort::Read() { return Read16(portnumber); }

__32bitPort::__32bitPort(unsigned short portnumber) : Port(portnumber) {}

__32bitPort::~__32bitPort() {}

void __32bitPort::Write(unsigned int data) { Write32(portnumber, data); }

unsigned int __32bitPort::Read() { return Read32(portnumber); }
