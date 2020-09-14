#include <frame_buffer.h>
#include <keyboard.h>
#include <system.h>
#include <utils.h>

extern unsigned char inportb(unsigned short _port);

char *KEYBOARD_DRIVER::readInput(FrameBuffer::Writer &p, int mode) {
	int receiving = 1;
	int i = 0, max_limit;
	bool shift = false;
	char *buffstr = (char *)mem_alloc(200);
	while (receiving) {
		if ((__8bitport::Read8(0x64) & 0x1) && mode == 1) {
			switch (__8bitport::Read8(0x60)) {
				/*case 1:
				p.writeString("*char)27);           Escape button Dont use it please
				buffstr[i] = 'c'ar)27;
				i++;
				break;*/
			case 2:
				if (shift == true) {
					p.writeString("!");
					buffstr[i] = '!';
				} else {
					p.writeString("1");
					buffstr[i] = '1';
				}
				i++;
				break;
			case 3:
				if (shift == true) {
					p.writeString("@");
					buffstr[i] = '@';
				} else {
					p.writeString("2");
					buffstr[i] = '2';
				}
				i++;
				break;
			case 4:
				if (shift == true) {
					p.writeString("#");
					buffstr[i] = '#';
				} else {
					p.writeString("3");
					buffstr[i] = '3';
				}
				i++;
				break;
			case 5:
				if (shift == true) {
					p.writeString("$");
					buffstr[i] = '$';
				} else {
					p.writeString("4");
					buffstr[i] = '4';
				}
				i++;
				break;
			case 6:
				if (shift == true) {
					p.writeString("%");
					buffstr[i] = '%';
				} else {
					p.writeString("5");
					buffstr[i] = '5';
				}
				i++;
				break;
			case 7:
				if (shift == true) {
					p.writeString("^");
					buffstr[i] = '^';
				} else {
					p.writeString("6");
					buffstr[i] = '6';
				}
				i++;
				break;
			case 8:
				if (shift == true) {
					p.writeString("&");
					buffstr[i] = '&';
				} else {
					p.writeString("7");
					buffstr[i] = '7';
				}
				i++;
				break;
			case 9:
				if (shift == true) {
					p.writeString("*");
					buffstr[i] = '*';
				} else {
					p.writeString("8");
					buffstr[i] = '8';
				}
				i++;
				break;
			case 10:
				if (shift == true) {
					p.writeString("(");
					buffstr[i] = '(';
				} else {
					p.writeString("9");
					buffstr[i] = '9';
				}
				i++;
				break;
			case 11:
				if (shift == true) {
					p.writeString(")");
					buffstr[i] = ')';
				} else {
					p.writeString("0");
					buffstr[i] = '0';
				}
				i++;
				break;
			case 12:
				if (shift == true) {
					p.writeString("_");
					buffstr[i] = '_';
				} else {
					p.writeString("-");
					buffstr[i] = '-';
				}
				i++;
				break;
			case 13:
				if (shift) {
					p.writeString("+");
					buffstr[i] = '+';
				} else {
					p.writeString("=");
					buffstr[i] = '=';
				}
				i++;
				break;
			case 14:
				if (i > 0) {
					p.writeString("\r");
				}
				i--;
				if (i < 0) {
					i = 0;
				}
				// buffstr[i+1] = 0;
				buffstr[i] = ';';
				break;
			/* case 15:
				p.writeString("\t"); //Tab button
				buffstr[i] = '\t';
				i++;
				break; */
			case 16:
				p.writeString("q");
				buffstr[i] = 'q';
				i++;
				break;
			case 17:
				p.writeString("w");
				buffstr[i] = 'w';
				i++;
				break;
			case 18:
				p.writeString("e");
				buffstr[i] = 'e';
				i++;
				break;
			case 19:
				p.writeString("r");
				buffstr[i] = 'r';
				i++;
				break;
			case 20:
				p.writeString("t");
				buffstr[i] = 't';
				i++;
				break;
			case 21:
				p.writeString("y");
				buffstr[i] = 'y';
				i++;
				break;
			case 22:
				p.writeString("u");
				buffstr[i] = 'u';
				i++;
				break;
			case 23:
				p.writeString("i");
				buffstr[i] = 'i';
				i++;
				break;
			case 24:
				p.writeString("o");
				buffstr[i] = 'o';
				i++;
				break;
			case 25:
				p.writeString("p");
				buffstr[i] = 'p';
				i++;
				break;
			case 26:
				p.writeString("[");
				buffstr[i] = '[';
				i++;
				break;
			case 27:
				p.writeString("]");
				buffstr[i] = ']';
				i++;
				break;
			case 28: // Case for return key
				p.writeString("\n");
				buffstr[i] = '\0';
				// buffstr[i+1] = '\0';
				i++;
				receiving = 0;
				break;
			/* case 29:
				p.writeString(""); //Left Control
				buffstr[i] = 'q';
				i++;
				break; */
			case 30:
				p.writeString("a");
				buffstr[i] = 'a';
				i++;
				break;
			case 31:
				p.writeString("s");
				buffstr[i] = 's';
				i++;
				break;
			case 32:
				p.writeString("d");
				buffstr[i] = 'd';
				i++;
				break;
			case 33:
				p.writeString("f");
				buffstr[i] = 'f';
				i++;
				break;
			case 34:
				p.writeString("g");
				buffstr[i] = 'g';
				i++;
				break;
			case 35:
				p.writeString("h");
				buffstr[i] = 'h';
				i++;
				break;
			case 36:
				p.writeString("j");
				buffstr[i] = 'j';
				i++;
				break;
			case 37:
				p.writeString("k");
				buffstr[i] = 'k';
				i++;
				break;
			case 38:
				p.writeString("l");
				buffstr[i] = 'l';
				i++;
				break;
			case 39:
				p.writeString(";");
				buffstr[i] = ';';
				i++;
				break;
			case 40:
				p.writeString((char *)(char)44); //   Single quote (")
				buffstr[i] = '\'';
				i++;
				break;
			case 41:
				p.writeString((char *)(char)44); // Back tick (`)
				buffstr[i] = '`';
				i++;
				break;
				/*   case 43:                                 \ (< for somekeyboards)
				p.writeString((char)92);
				buffstr[i] = 'q';
				i++;
				break;*/
			case 44:
				p.writeString("z");
				buffstr[i] = 'z';
				i++;
				break;
			case 45:
				p.writeString("x");
				buffstr[i] = 'x';
				i++;
				break;
			case 46:
				p.writeString("c");
				buffstr[i] = 'c';
				i++;
				break;
			case 47:
				p.writeString("v");
				buffstr[i] = 'v';
				i++;
				break;
			case 48:
				p.writeString("b");
				buffstr[i] = 'b';
				i++;
				break;
			case 49:
				p.writeString("n");
				buffstr[i] = 'n';
				i++;
				break;
			case 50:
				p.writeString("m");
				buffstr[i] = 'm';
				i++;
				break;
			case 51:
				p.writeString(",");
				buffstr[i] = ',';
				i++;
				break;
			case 52:
				p.writeString(".");
				buffstr[i] = '.';
				i++;
				break;
			case 53:
				p.writeString("/");
				buffstr[i] = '/';
				i++;
				break;
			case 54:
				p.writeString(".");
				buffstr[i] = '.';
				i++;
				break;
			case 55:
				p.writeString("/");
				buffstr[i] = '/';
				i++;
				break;
			case 57:
				p.writeString(" ");
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
					p.shiftCursor(-1, newMem);
					i--;
				}
				break;

			case 0x4D:
				if (i >= 0) {
					char *newMem = (char *)mem_alloc(200);
					newMem[0] = (buffstr[i]);
					p.shiftCursor(1, newMem);
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
					p.writeString("(char)27);           Escape button Dont use it please
					buffstr[i] = 'c'ar)27;
					i++;
					break;*/
				case 2:
					if (shift == true) {
						p.writeString("*");
						buffstr[i] = '!';
					} else {
						p.writeString("*");
						buffstr[i] = '1';
					}
					i++;
					break;
				case 3:
					if (shift == true) {
						p.writeString("*");
						buffstr[i] = '@';
					} else {
						p.writeString("*");
						buffstr[i] = '2';
					}
					i++;
					break;
				case 4:
					if (shift == true) {
						p.writeString("*");
						buffstr[i] = '#';
					} else {
						p.writeString("*");
						buffstr[i] = '3';
					}
					i++;
					break;
				case 5:
					if (shift == true) {
						p.writeString("*");
						buffstr[i] = '$';
					} else {
						p.writeString("*");
						buffstr[i] = '4';
					}
					i++;
					break;
				case 6:
					if (shift == true) {
						p.writeString("*");
						buffstr[i] = '%';
					} else {
						p.writeString("*");
						buffstr[i] = '5';
					}
					i++;
					break;
				case 7:
					if (shift == true) {
						p.writeString("*");
						buffstr[i] = '^';
					} else {
						p.writeString("*");
						buffstr[i] = '6';
					}
					i++;
					break;
				case 8:
					if (shift == true) {
						p.writeString("*");
						buffstr[i] = '&';
					} else {
						p.writeString("*");
						buffstr[i] = '7';
					}
					i++;
					break;
				case 9:
					if (shift == true) {
						p.writeString("*");
						buffstr[i] = '*';
					} else {
						p.writeString("*");
						buffstr[i] = '8';
					}
					i++;
					break;
				case 10:
					if (shift == true) {
						p.writeString("*");
						buffstr[i] = '(';
					} else {
						p.writeString("*");
						buffstr[i] = '9';
					}
					i++;
					break;
				case 11:
					if (shift == true) {
						p.writeString("*");
						buffstr[i] = ')';
					} else {
						p.writeString("*");
						buffstr[i] = '0';
					}
					i++;
					break;
				case 12:
					p.writeString("*");
					buffstr[i] = '-';
					i++;
					break;
				case 13:
					p.writeString("*");
					buffstr[i] = '=';
					i++;
					break;
				case 14:
					if (i > 0) {
						p.writeString("\r");
					}
					i--;
					if (i < 0) {
						i = 0;
					}
					// buffstr[i+1] = 0;
					buffstr[i] = ';';
					break;
				/* case 15:
					p.writeString("*t"); //Tab button
					buffstr[i] = '\t';
					i++;
					break; */
				case 16:
					p.writeString("*");
					buffstr[i] = 'q';
					i++;
					break;
				case 17:
					p.writeString("*");
					buffstr[i] = 'w';
					i++;
					break;
				case 18:
					p.writeString("*");
					buffstr[i] = 'e';
					i++;
					break;
				case 19:
					p.writeString("*");
					buffstr[i] = 'r';
					i++;
					break;
				case 20:
					p.writeString("*");
					buffstr[i] = 't';
					i++;
					break;
				case 21:
					p.writeString("*");
					buffstr[i] = 'y';
					i++;
					break;
				case 22:
					p.writeString("*");
					buffstr[i] = 'u';
					i++;
					break;
				case 23:
					p.writeString("*");
					buffstr[i] = 'i';
					i++;
					break;
				case 24:
					p.writeString("*");
					buffstr[i] = 'o';
					i++;
					break;
				case 25:
					p.writeString("*");
					buffstr[i] = 'p';
					i++;
					break;
				case 26:
					p.writeString("*");
					buffstr[i] = '[';
					i++;
					break;
				case 27:
					p.writeString("*");
					buffstr[i] = ']';
					i++;
					break;
				case 28: // Case for return key
					p.writeString("\n");
					buffstr[i] = '\0';
					// buffstr[i+1] = '\0';
					i++;
					receiving = 0;
					i = 0;
					break;
				/* case 29:
					p.writeString("*); //Left Control
					buffstr[i] = 'q';
					i++;
					break; */
				case 30:
					p.writeString("*");
					buffstr[i] = 'a';
					i++;
					break;
				case 31:
					p.writeString("*");
					buffstr[i] = 's';
					i++;
					break;
				case 32:
					p.writeString("*");
					buffstr[i] = 'd';
					i++;
					break;
				case 33:
					p.writeString("*");
					buffstr[i] = 'f';
					i++;
					break;
				case 34:
					p.writeString("*");
					buffstr[i] = 'g';
					i++;
					break;
				case 35:
					p.writeString("*");
					buffstr[i] = 'h';
					i++;
					break;
				case 36:
					p.writeString("*");
					buffstr[i] = 'j';
					i++;
					break;
				case 37:
					p.writeString("*");
					buffstr[i] = 'k';
					i++;
					break;
				case 38:
					p.writeString("*");
					buffstr[i] = 'l';
					i++;
					break;
				case 39:
					p.writeString("*");
					buffstr[i] = ';';
					i++;
					break;
				case 40:
					p.writeString("*"); //   Single quote (")
					buffstr[i] = '\'';
					i++;
					break;
				case 41:
					p.writeString("*"); // Back tick (`)
					buffstr[i] = '`';
					i++;
					break;
					/*   case 43:                                 \ (< for somekeyboards)
					p.writeString((*har)92);
					buffstr[i] = 'q';
					i++;
					break;*/
				case 44:
					p.writeString("*");
					buffstr[i] = 'z';
					i++;
					break;
				case 45:
					p.writeString("*");
					buffstr[i] = 'x';
					i++;
					break;
				case 46:
					p.writeString("*");
					buffstr[i] = 'c';
					i++;
					break;
				case 47:
					p.writeString("*");
					buffstr[i] = 'v';
					i++;
					break;
				case 48:
					p.writeString("*");
					buffstr[i] = 'b';
					i++;
					break;
				case 49:
					p.writeString("*");
					buffstr[i] = 'n';
					i++;
					break;
				case 50:
					p.writeString("*");
					buffstr[i] = 'm';
					i++;
					break;
				case 51:
					p.writeString("*");
					buffstr[i] = ',';
					i++;
					break;
				case 52:
					p.writeString("*");
					buffstr[i] = '.';
					i++;
					break;
				case 53:
					p.writeString("*");
					buffstr[i] = '/';
					i++;
					break;
				case 54:
					p.writeString("*");
					buffstr[i] = '.';
					i++;
					break;
				case 55:
					p.writeString("*");
					buffstr[i] = '/';
					i++;
					break;
				case 57:
					p.writeString("*");
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
						p.shiftCursor(-1, newMem);
						i--;
					}
					break;

				case 0x4D:
					if (i >= 0) {
						char *newMem = (char *)mem_alloc(200);
						newMem[0] = (buffstr[i]);
						p.shiftCursor(1, newMem);
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