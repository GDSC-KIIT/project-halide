#include <console.h>
#include <halidestdlib.h>
static void writeString_man();

int init_console() {
	// p.writeString("Now running console instance : \n");
	/* p.writeString("root", (string)0x76);
	p.writeString("@", (string)0x0a);
	p.writeString("night_os ", (string)0x0a); */
	unsigned int loop = 1;
	int _id = 0;
	char *command;
	while (loop) {

		command = KEYBOARD_DRIVER::readInput();
		if (hldstd::stringCompare(command, "help")) {
			writeString_man();
		} else if (hldstd::stringCompare(command, "clear")) {
		} else if (hldstd::stringCompare(command, "switch console")) {
			_id = 1;
			loop = 0;

		} else if (hldstd::stringCompare(command, "greet")) {
		} else if (hldstd::stringCompare(command, "exit")) {
			loop = 0;
		} else {
		}
	}
	return _id;
}

void writeString_man() {}