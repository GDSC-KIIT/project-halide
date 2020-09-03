#include "../include/keyboard.h"
#include "../include/frame_buffer.h"
#include "../include/system.h"

extern unsigned char inportb (unsigned short _port);
static FrameBuffer::Writer p(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::BLUE);

void KEYBOARD_DRIVER::readInput()
{
    int receiving = 20;
    while(receiving)
    {
        if(inportb(0x64) & 0x1)                 
        {
            switch(inportb(0x60))
            {
                default: p.print((char*)inportb(0x60));
                         receiving--;
                         break;
            }
        }
    }
}