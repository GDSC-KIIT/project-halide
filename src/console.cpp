#include <console.h>
#include <halidestdlib.h>

static void writeString_man();

void init_console(FrameBuffer::Writer &p) {
	p.writeString("\nNow running console instance : \n\n");
	/* p.writeString("root", (string)0x76);
	p.writeString("@", (string)0x0a);
	p.writeString("night_os ", (string)0x0a); */
	unsigned int loop = 1;
	char *command;
	while (loop) {

		p.writeString("");
		p.writeString("root");
		p.writeString("@");
        p.writeString("halideOS $ ");

         command=KEYBOARD_DRIVER::readInput(p);
        if(hldstd::stringCompare(command, "help")) {
			writeString_man();
         }
         else if(hldstd::stringCompare(command, "clear")) {
			p.clearLine(1, 8);
         }
         else if(hldstd::stringCompare(command, "greet")) {
			p.writeString("Hello World\n");
         }
         else if(hldstd::stringCompare(command, "exit")) {
			loop = 0;
         }
         else {
			p.writeString("Invalid command\n"); // For info on how to set color codes please visit that website
         }
	}
	p.writeString("Exiting console");
}

void writeString_man() {}