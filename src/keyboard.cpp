#include "../include/keyboard.h"
#include "../include/frame_buffer.h"
#include "../include/system.h"
#include "../include/utils.h"

extern unsigned char inportb (unsigned short _port);
static FrameBuffer::Writer p(FrameBuffer::Colours::WHITE, FrameBuffer::Colours::BLUE);

char* KEYBOARD_DRIVER::readInput()
{
    int receiving = 1;
    int i=0;
    char* buffstr = (char*)mem_alloc(200);
    while(receiving)
    {
        if(inportb(0x64) & 0x1)                 
        {
            switch(inportb(0x60))
            {
                /*case 1:
                p.print("(char)27);           Escape button Dont use it please
                buffstr[i] = 'c'ar)27;
                i++;
                break;*/
        case 2:
                p.print("1");
                buffstr[i] = '1';
                i++;
                break;
        case 3:
                p.print("2");
                buffstr[i] = '2';
                i++;
                break;
        case 4:
                p.print("3");
                buffstr[i] = '3';
                i++;
                break;
        case 5:
                p.print("4");
                buffstr[i] = '4';
                i++;
                break;
        case 6:
                p.print("5");
                buffstr[i] = '5';
                i++;
                break;
        case 7:
                p.print("6");
                buffstr[i] = '6';
                i++;
                break;
        case 8:
                p.print("7");
                buffstr[i] = '7';
                i++;
                break;
        case 9:
                p.print("8");
                buffstr[i] = '8';
                i++;
                break;
        case 10:
                p.print("9");
                buffstr[i] = '9';
                i++;
                break;
        case 11:
                p.print("0");
                buffstr[i] = '0';
                i++;
                break;
        case 12:
                p.print("-");
                buffstr[i] = '-';
                i++;
                break;
        case 13:
                p.print("=");
                buffstr[i] = '=';
                i++;
                break;
        case 14:
                if(i>0) {
                        p.print("\r");
                }
                i--;
                if(i<0)
                {
                	i = 0;
                }
                //buffstr[i+1] = 0;
                buffstr[i] = ';';
                break;
       case 15:
                p.print("\t");          //Tab button
                buffstr[i] = '\t';
                i++;
                break;
        case 16:
                p.print("q");
                buffstr[i] = 'q';
                i++;
                break;
        case 17:
                p.print("w");
                buffstr[i] = 'w';
                i++;
                break;
        case 18:
                p.print("e");
                buffstr[i] = 'e';
                i++;
                break;
        case 19:
                p.print("r");
                buffstr[i] = 'r';
                i++;
                break;
        case 20:
                p.print("t");
                buffstr[i] = 't';
                i++;
                break;
        case 21:
                p.print("y");
                buffstr[i] = 'y';
                i++;
                break;
        case 22:
                p.print("u");
                buffstr[i] = 'u';
                i++;
                break;
        case 23:
                p.print("i");
                buffstr[i] = 'i';
                i++;
                break;
        case 24:
                p.print("o");
                buffstr[i] = 'o';
                i++;
                break;
        case 25:
                p.print("p");
                buffstr[i] = 'p';
                i++;
                break;
        case 26:
                p.print("[");
                buffstr[i] = '[';
                i++;
                break;
        case 27:
                p.print("]");
                buffstr[i] = ']';
                i++;
                break;
        case 28:                                                // Case for return key
               p.print("\n");
               //buffstr[i] = '\'";
                i++;
                receiving = 0;
                break;
       case 29:
                p.print("Left Ctrl");           //Left Control
                buffstr[i] = 'q';
                i++;
                break;
        case 30:
                p.print("a");
                buffstr[i] = 'a';
                i++;
                break;
        case 31:
                p.print("s");
                buffstr[i] = 's';
                i++;
                break;
        case 32:
                p.print("d");
                buffstr[i] = 'd';
                i++;
                break;
        case 33:
                p.print("f");
                buffstr[i] = 'f';
                i++;
                break;
        case 34:
                p.print("g");
                buffstr[i] = 'g';
                i++;
                break;
        case 35:
                p.print("h");
                buffstr[i] = 'h';
                i++;
                break;
        case 36:
                p.print("j");
                buffstr[i] = 'j';
                i++;
                break;
        case 37:
                p.print("k");
                buffstr[i] = 'k';
                i++;
                break;
        case 38:
                p.print("l");
                buffstr[i] = 'l';
                i++;
                break;
        case 39:
                p.print(";");
                buffstr[i] = ';';
                i++;
                break;
        case 40:
                p.print((char*)(char)44);               //   Single quote (")
                buffstr[i] = '"';
                i++;
                break;
        case 41:
                p.print((char*)(char)44);               // Back tick (`)
                buffstr[i] = '`';
                i++;
                break;
     /*   case 43:                                 \ (< for somekeyboards)   
                p.print((char)92);
                buffstr[i] = 'q';
                i++;
                break;*/
        case 44:
                p.print("z");
                buffstr[i] = 'z';
                i++;
                break;
        case 45:
                p.print("x");
                buffstr[i] = 'x';
                i++;
                break;
        case 46:
                p.print("c");
                buffstr[i] = 'c';
                i++;
                break;
        case 47:
                p.print("v");
                buffstr[i] = 'v';
                i++;
                break;                
        case 48:
                p.print("b");
                buffstr[i] = 'b';
                i++;
                break;               
        case 49:
                p.print("n");
                buffstr[i] = 'n';
                i++;
                break;                
        case 50:
                p.print("m");
                buffstr[i] = 'm';
                i++;
                break;               
        case 51:
                p.print(",");
                buffstr[i] = ',';
                i++;
                break;                
        case 52:
                p.print(".");
                buffstr[i] = '.';
                i++;
                break;            
        case 53:
                p.print("/");
                buffstr[i] = '/';
                i++;
                break;            
        case 54:
                p.print(".");
                buffstr[i] = '.';
                i++;
                break;            
        case 55:
                p.print("/");
                buffstr[i] = '/';
                i++;
                break;                       
        case 57:
                p.print(" ");
                buffstr[i] = ' ';
                i++;
                break;
            //}
        
        // Implementing shift
        case 42:                                        // Left shift
                break;                                 

        default: //p.print("~Unhandeled interrupt");
                 //receiving--;
                 break;
            }
        }
    }

    return buffstr;
}