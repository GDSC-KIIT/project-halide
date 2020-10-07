#include <frame_buffer.h>
#include <keyboard.h>
#include <system.h>
#include <utils.h>

#include "../include/vesa_drivers/vesa.h"
#include <mem.h>
#include <vesa_drivers/window.h>

#include <vesa_drivers/text.h>
#include <vesa_drivers/video-tty.h>

extern unsigned char inportb(unsigned short _port);

char *KEYBOARD_DRIVER::readInput() {
	int receiving = 1;
	int i = 0, max_limit, mode = 1;
	bool shift = false;
	char *buffstr = (char *)mem_alloc(200);
	while (receiving) {
		if ((Port8Bit::Read8(0x64) & 0x1) && mode == 1) {
			switch (Port8Bit::Read8(0x60)) {
				/*case 1:
				put_char('*'har)27);           Escape button Dont use it please
				buffstr[i] = 'c'ar)27;
				i++;
				break;*/
			case 2:
				if (shift == true) {
					put_char('!');
					buffstr[i] = '!';
				} else {
					put_char('1');
					buffstr[i] = '1';
				}
				i++;
				break;
			case 3:
				if (shift == true) {
					put_char('@');
					buffstr[i] = '@';
				} else {
					put_char('2');
					buffstr[i] = '2';
				}
				i++;
				break;
			case 4:
				if (shift == true) {
					put_char('#');
					buffstr[i] = '#';
				} else {
					put_char('3');
					buffstr[i] = '3';
				}
				i++;
				break;
			case 5:
				if (shift == true) {
					put_char('$');
					buffstr[i] = '$';
				} else {
					put_char('4');
					buffstr[i] = '4';
				}
				i++;
				break;
			case 6:
				if (shift == true) {
					put_char('%');
					buffstr[i] = '%';
				} else {
					put_char('5');
					buffstr[i] = '5';
				}
				i++;
				break;
			case 7:
				if (shift == true) {
					put_char('^');
					buffstr[i] = '^';
				} else {
					put_char('6');
					buffstr[i] = '6';
				}
				i++;
				break;
			case 8:
				if (shift == true) {
					put_char('&');
					buffstr[i] = '&';
				} else {
					put_char('7');
					buffstr[i] = '7';
				}
				i++;
				break;
			case 9:
				if (shift == true) {
					put_char('*');
					buffstr[i] = '*';
				} else {
					put_char('8');
					buffstr[i] = '8';
				}
				i++;
				break;
			case 10:
				if (shift == true) {
					put_char('(');
					buffstr[i] = '(';
				} else {
					put_char('9');
					buffstr[i] = '9';
				}
				i++;
				break;
			case 11:
				if (shift == true) {
					put_char(')');
					buffstr[i] = ')';
				} else {
					put_char('0');
					buffstr[i] = '0';
				}
				i++;
				break;
			case 12:
				put_char('-');
				buffstr[i] = '-';
				i++;
				break;
			case 13:
				put_char('=');
				buffstr[i] = '=';
				i++;
				break;
			case 14: // Case for back space
				if (i > 0) {
					put_char('\r');
				}
				i--;
				if (i < 0) {
					i = 0;
				}
				// buffstr[i+1] = 0;
				buffstr[i] = ';';
				break;
			/* case 15:
				put_char('\'"); //Tab button
				buffstr[i] = '\t';
				i++;
				break; */
			case 16:
				put_char('Q');
				buffstr[i] = 'q';
				i++;
				break;
			case 17:
				put_char('w');
				buffstr[i] = 'w';
				i++;
				break;
			case 18:
				put_char('e');
				buffstr[i] = 'e';
				i++;
				break;
			case 19:
				put_char('r');
				buffstr[i] = 'r';
				i++;
				break;
			case 20:
				put_char('t');
				buffstr[i] = 't';
				i++;
				break;
			case 21:
				put_char('y');
				buffstr[i] = 'y';
				i++;
				break;
			case 22:
				put_char('u');
				buffstr[i] = 'u';
				i++;
				break;
			case 23:
				put_char('i');
				buffstr[i] = 'i';
				i++;
				break;
			case 24:
				put_char('o');
				buffstr[i] = 'o';
				i++;
				break;
			case 25:
				put_char('p');
				buffstr[i] = 'p';
				i++;
				break;
			case 26:
				put_char('[');
				buffstr[i] = '[';
				i++;
				break;
			case 27:
				put_char(']');
				buffstr[i] = ']';
				i++;
				break;
			case 28: // Case for return key
				put_char('\n');
				buffstr[i] = '\0';
				// buffstr[i+1] = '\0';
				i++;
				receiving = 0;
				i = 0;
				break;
			/* case 29:
				put_char('"'; //Left Control
				buffstr[i] = 'q';
				i++;
				break; */
			case 30:
				put_char('a');
				buffstr[i] = 'a';
				i++;
				break;
			case 31:
				put_char('s');
				buffstr[i] = 's';
				i++;
				break;
			case 32:
				put_char('d');
				buffstr[i] = 'd';
				i++;
				break;
			case 33:
				put_char('f');
				buffstr[i] = 'f';
				i++;
				break;
			case 34:
				put_char('g');
				buffstr[i] = 'g';
				i++;
				break;
			case 35:
				put_char('h');
				buffstr[i] = 'h';
				i++;
				break;
			case 36:
				put_char('j');
				buffstr[i] = 'j';
				i++;
				break;
			case 37:
				put_char('k');
				buffstr[i] = 'k';
				i++;
				break;
			case 38:
				put_char('l');
				buffstr[i] = 'l';
				i++;
				break;
			case 39:
				put_char(';');
				buffstr[i] = ';';
				i++;
				break;
			case 40:
				put_char((char)44); //   Single quote (")
				buffstr[i] = '\'';
				i++;
				break;
			case 41:
				put_char((char)44); // Back tick (`)
				buffstr[i] = '`';
				i++;
				break;
				/*   case 43:                                 \ (< for somekeyboards)
				put_char('c'ar)92);
				buffstr[i] = 'q';
				i++;
				break;*/
			case 44:
				put_char('z');
				buffstr[i] = 'z';
				i++;
				break;
			case 45:
				put_char('x');
				buffstr[i] = 'x';
				i++;
				break;
			case 46:
				put_char('c');
				buffstr[i] = 'c';
				i++;
				break;
			case 47:
				put_char('v');
				buffstr[i] = 'v';
				i++;
				break;
			case 48:
				put_char('b');
				buffstr[i] = 'b';
				i++;
				break;
			case 49:
				put_char('n');
				buffstr[i] = 'n';
				i++;
				break;
			case 50:
				put_char('m');
				buffstr[i] = 'm';
				i++;
				break;
			case 51:
				put_char(',');
				buffstr[i] = ',';
				i++;
				break;
			case 52:
				put_char('.');
				buffstr[i] = '.';
				i++;
				break;
			case 53:
				put_char('/');
				buffstr[i] = '/';
				i++;
				break;
			case 54:
				put_char('.');
				buffstr[i] = '.';
				i++;
				break;
			case 55:
				put_char('/');
				buffstr[i] = '/';
				i++;
				break;
			case 57:
				put_char(' ');
				buffstr[i] = ' ';
				i++;
				break;
				//}

			// Implementing shift
			case 42:
				shift = true;
				break;

			case 0xAA:
				shift = false;
				break;

			case 0x4B:
				if (i > 0) {
					char *newMem = (char *)mem_alloc(200);
					newMem[0] = (buffstr[i]);
					// p.shiftCursor(-1, newMem);
					i--;
				}
				break;

			case 0x4D:
				if (i >= 0) {
					char *newMem = (char *)mem_alloc(200);
					newMem[0] = (buffstr[i]);
					// p.shiftCursor(1, newMem);
					i++;
				}
				break;

			default: // p.writeHex(inportb(0x60));
				// receiving--;
				break;
			}
		} else {
			if ((inportb(0x64) & 0x1) && mode == 0) // Password mode
			{
				switch (inportb(0x60)) {
					/*case 1:
					put_char('('har)27);           Escape button Dont use it please
					buffstr[i] = 'c'ar)27;
					i++;
					break;*/
				case 2:
					if (shift == true) {
						put_char('*');
						buffstr[i] = '!';
					} else {
						put_char('*');
						buffstr[i] = '1';
					}
					i++;
					break;
				case 3:
					if (shift == true) {
						put_char('*');
						buffstr[i] = '@';
					} else {
						put_char('*');
						buffstr[i] = '2';
					}
					i++;
					break;
				case 4:
					if (shift == true) {
						put_char('*');
						buffstr[i] = '#';
					} else {
						put_char('*');
						buffstr[i] = '3';
					}
					i++;
					break;
				case 5:
					if (shift == true) {
						put_char('*');
						buffstr[i] = '$';
					} else {
						put_char('*');
						buffstr[i] = '4';
					}
					i++;
					break;
				case 6:
					if (shift == true) {
						put_char('*');
						buffstr[i] = '%';
					} else {
						put_char('*');
						buffstr[i] = '5';
					}
					i++;
					break;
				case 7:
					if (shift == true) {
						put_char('*');
						buffstr[i] = '^';
					} else {
						put_char('*');
						buffstr[i] = '6';
					}
					i++;
					break;
				case 8:
					if (shift == true) {
						put_char('*');
						buffstr[i] = '&';
					} else {
						put_char('*');
						buffstr[i] = '7';
					}
					i++;
					break;
				case 9:
					if (shift == true) {
						put_char('*');
						buffstr[i] = '*';
					} else {
						put_char('*');
						buffstr[i] = '8';
					}
					i++;
					break;
				case 10:
					if (shift == true) {
						put_char('*');
						buffstr[i] = '(';
					} else {
						put_char('*');
						buffstr[i] = '9';
					}
					i++;
					break;
				case 11:
					if (shift == true) {
						put_char('*');
						buffstr[i] = ')';
					} else {
						put_char('*');
						buffstr[i] = '0';
					}
					i++;
					break;
				case 12:
					put_char('*');
					buffstr[i] = '-';
					i++;
					break;
				case 13:
					put_char('*');
					buffstr[i] = '=';
					i++;
					break;
				case 14:
					if (i > 0) {
						put_char('\r');
					}
					i--;
					if (i < 0) {
						i = 0;
					}
					// buffstr[i+1] = 0;
					buffstr[i] = ';';
					break;
				/* case 15:
					put_char('*'"); //Tab button
					buffstr[i] = '\t';
					i++;
					break; */
				case 16:
					put_char('*');
					buffstr[i] = 'q';
					i++;
					break;
				case 17:
					put_char('*');
					buffstr[i] = 'w';
					i++;
					break;
				case 18:
					put_char('*');
					buffstr[i] = 'e';
					i++;
					break;
				case 19:
					put_char('*');
					buffstr[i] = 'r';
					i++;
					break;
				case 20:
					put_char('*');
					buffstr[i] = 't';
					i++;
					break;
				case 21:
					put_char('*');
					buffstr[i] = 'y';
					i++;
					break;
				case 22:
					put_char('*');
					buffstr[i] = 'u';
					i++;
					break;
				case 23:
					put_char('*');
					buffstr[i] = 'i';
					i++;
					break;
				case 24:
					put_char('*');
					buffstr[i] = 'o';
					i++;
					break;
				case 25:
					put_char('*');
					buffstr[i] = 'p';
					i++;
					break;
				case 26:
					put_char('*');
					buffstr[i] = '[';
					i++;
					break;
				case 27:
					put_char('*');
					buffstr[i] = ']';
					i++;
					break;
				case 28: // Case for return key
					put_char('\n');
					buffstr[i] = '\0';
					// buffstr[i+1] = '\0';
					i++;
					receiving = 0;
					i = 0;
					break;
				/* case 29:
					put_char('*'; //Left Control
					buffstr[i] = 'q';
					i++;
					break; */
				case 30:
					put_char('*');
					buffstr[i] = 'a';
					i++;
					break;
				case 31:
					put_char('*');
					buffstr[i] = 's';
					i++;
					break;
				case 32:
					put_char('*');
					buffstr[i] = 'd';
					i++;
					break;
				case 33:
					put_char('*');
					buffstr[i] = 'f';
					i++;
					break;
				case 34:
					put_char('*');
					buffstr[i] = 'g';
					i++;
					break;
				case 35:
					put_char('*');
					buffstr[i] = 'h';
					i++;
					break;
				case 36:
					put_char('*');
					buffstr[i] = 'j';
					i++;
					break;
				case 37:
					put_char('*');
					buffstr[i] = 'k';
					i++;
					break;
				case 38:
					put_char('*');
					buffstr[i] = 'l';
					i++;
					break;
				case 39:
					put_char('*');
					buffstr[i] = ';';
					i++;
					break;
				case 40:
					put_char('*'); //   Single quote (")
					buffstr[i] = '\'';
					i++;
					break;
				case 41:
					put_char('*'); // Back tick (`)
					buffstr[i] = '`';
					i++;
					break;
					/*   case 43:                                 \ (< for somekeyboards)
					put_char('*'ar)92);
					buffstr[i] = 'q';
					i++;
					break;*/
				case 44:
					put_char('*');
					buffstr[i] = 'z';
					i++;
					break;
				case 45:
					put_char('*');
					buffstr[i] = 'x';
					i++;
					break;
				case 46:
					put_char('*');
					buffstr[i] = 'c';
					i++;
					break;
				case 47:
					put_char('*');
					buffstr[i] = 'v';
					i++;
					break;
				case 48:
					put_char('*');
					buffstr[i] = 'b';
					i++;
					break;
				case 49:
					put_char('*');
					buffstr[i] = 'n';
					i++;
					break;
				case 50:
					put_char('*');
					buffstr[i] = 'm';
					i++;
					break;
				case 51:
					put_char('*');
					buffstr[i] = ',';
					i++;
					break;
				case 52:
					put_char('*');
					buffstr[i] = '.';
					i++;
					break;
				case 53:
					put_char('*');
					buffstr[i] = '/';
					i++;
					break;
				case 54:
					put_char('*');
					buffstr[i] = '.';
					i++;
					break;
				case 55:
					put_char('*');
					buffstr[i] = '/';
					i++;
					break;
				case 57:
					put_char('*');
					buffstr[i] = ' ';
					i++;
					break;
					//}

				// Implementing shift
				case 42:
					shift = true;
					break;

				case 0xAA:
					shift = false;
					break;

				case 0x4B:
					if (i > 0) {
						char *newMem = (char *)mem_alloc(200);
						newMem[0] = (buffstr[i]);
						// p.shiftCursor(-1, newMem);
						i--;
					}
					break;

				case 0x4D:
					if (i >= 0) {
						char *newMem = (char *)mem_alloc(200);
						newMem[0] = (buffstr[i]);
						// p.shiftCursor(1, newMem);
						i++;
					}
					break;

				default: // p.writeHex(inportb(0x60));
					// receiving--;
					break;
				}
			}
		}
	}

	return buffstr;
}
