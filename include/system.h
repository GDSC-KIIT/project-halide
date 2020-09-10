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

class Port8Bit : public Port {
public:
	Port8Bit(unsigned short portnumber);
	~Port8Bit();

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

class Port8BitSlow : public Port8Bit {
public:
	Port8BitSlow(unsigned short portnumber);
	~Port8BitSlow();

	virtual void Write(unsigned char data);

protected:
	static inline void Write8Slow(unsigned short _port, unsigned char _data) { __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a"(_data), "Nd"(_port)); }
};

class Port16Bit : public Port {
public:
	Port16Bit(unsigned short portnumber);
	~Port16Bit();

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

class Port32Bit : public Port {
public:
	Port32Bit(unsigned short portnumber);
	~Port32Bit();

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