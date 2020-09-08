#include <console.h>
#include <halidestdlib.h>

void writeAbout(FrameBuffer::Writer &);
void writeString_man(FrameBuffer::Writer &);
void calculator(FrameBuffer::Writer &, hldstd::string &expression);

int init_console(FrameBuffer::Writer &p, Window &win) {
	p.writeString("Now running console instance : \n");
	unsigned int loop = 1;
	int _id = 0;
	char *command;
	while (loop) {

		p.writeString("");
		p.writeString(" root", FrameBuffer::Colours::WHITE);
		p.writeString("@");
		p.writeString("halideOS $ ");

		hldstd::string command = KEYBOARD_DRIVER::readInput(p);

		if (hldstd::stringCompare(command.c_ptr(), "help")) {
			writeString_man(p);
		}

		else if (hldstd::stringCompare(command.c_ptr(), "about")) {
			writeAbout(p);
		}

		else if (hldstd::stringCompare(command.c_ptr(), "calculator")) {
			p.writeString("\nHalideOS - Basic Calculator\n");
			p.writeString("Enter an Expression (only +, -, *, /): ");
			hldstd::string c = KEYBOARD_DRIVER::readInput(p);
			p.writeString(c.c_ptr());
			p.writeString("\n");
			calculator(p, c);
		}

		else if (hldstd::stringCompare(command.c_ptr(), "clear")) {
			p.clearLine(win.m_y1 + 1, win.m_y2 - 1);
		}

		else if (hldstd::stringCompare(command.c_ptr(), "switch console")) {
			p.writeString("switchched console\n");
			p.clearLine(win.m_y1 + 1, win.m_y2 - 1); // Use this line of code till we impliment local state storage
			_id = 1;
			loop = 0;
			break;
		}

		else if (hldstd::stringCompare(command.c_ptr(), "greet")) {
			p.writeString("Hello User, Welcome to HalideOS\n");
		}

		else if (hldstd::stringCompare(command.c_ptr(), "exit")) {
			loop = 0;
		}

		else {
			p.writeString("Invalid command\n"); // For info on how to set color codes please visit that website
		}
	}
	p.writeString("Exiting console\n");
	return _id;
}

inline void writeAbout(FrameBuffer::Writer &p) {
	p.writeString("\n     Welcome to HalideOS v1.0 \n");
	p.writeString("     An experimental OS by DSC KIIT \n");
	p.writeString("     github.com/DSC-KIIT/project-halide \n", FrameBuffer::Colours::GREEN);
	p.writeString("     Developed by Ujjwal Shekhawat and Junaid Rahim\n\n");
}

inline void writeString_man(FrameBuffer::Writer &p) {
	// ! Add new line protectors if man creates window over flow
	p.writeString("List of commands :\ngreet\nclear\nswitch console\nexit\n", FrameBuffer::Colours::BLACK);
}

void calculator(FrameBuffer::Writer &p, hldstd::string &expression) {
	hldstd::stack<int> st(10, 0);

	for (int i = 1; i <= 5; i++) {
		st.push(i);
	}

	hldstd::string t1 = st.top();
	p.writeString(t1.c_ptr());
	p.writeString("\n");
	
	st.pop();
	
	hldstd::string t2 = st.top();
	p.writeString(t2.c_ptr());
	p.writeString("\n");
}