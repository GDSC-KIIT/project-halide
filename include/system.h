#ifndef __SYSTEM_H
#define __SYSTEM_H

// & Old implimentation
unsigned char inportb(unsigned short _port);

void outportb(unsigned short _port, unsigned char _data);

// & New implimentation
class Port {
protected:
	Port(unsigned short portnumber);
	~Port();
	unsigned short portnumber;
};

class __8bitport : public Port {
public:
	__8bitport(unsigned short portnumber);
	~__8bitport();

	virtual unsigned char Read();
	virtual void Write(unsigned char data);
	// ! Public for now
public:
	static inline unsigned char Read8(unsigned short _port) {
		unsigned char result;
		__asm__ volatile("inb %1, %0" : "=a"(result) : "Nd"(_port));
		return result;
	}

	static inline void Write8(unsigned short _port, unsigned char _data) { __asm__ volatile("outb %0, %1" : : "a"(_data), "Nd"(_port)); }
};

class __8bitportSlow : public __8bitport {
public:
	__8bitportSlow(unsigned short portnumber);
	~__8bitportSlow();

	virtual void Write(unsigned char data);

protected:
	static inline void Write8Slow(unsigned short _port, unsigned char _data) { __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a"(_data), "Nd"(_port)); }
};

class __16bitPort : public Port {
public:
	__16bitPort(unsigned short portnumber);
	~__16bitPort();

	virtual unsigned short Read();
	virtual void Write(unsigned short data);
	// ! Public for now
public:
	static inline unsigned short Read16(unsigned short _port) {
		unsigned short result;
		__asm__ volatile("inw %1, %0" : "=a"(result) : "Nd"(_port));
		return result;
	}

	static inline void Write16(unsigned short _port, unsigned short _data) { __asm__ volatile("outw %0, %1" : : "a"(_data), "Nd"(_port)); }
};

class __32bitPort : public Port {
public:
	__32bitPort(unsigned short portnumber);
	~__32bitPort();

	virtual unsigned int Read();
	virtual void Write(unsigned int data);

protected:
	static inline unsigned int Read32(unsigned short _port) {
		unsigned int result;
		__asm__ volatile("inl %1, %0" : "=a"(result) : "Nd"(_port));
		return result;
	}

	static inline void Write32(unsigned short _port, unsigned int _data) { __asm__ volatile("outl %0, %1" : : "a"(_data), "Nd"(_port)); }
};

#endif