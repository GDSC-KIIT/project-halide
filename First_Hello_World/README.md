# First Hello World
**Goal : Make your previous boot sector print some text on screen**

*important concepts : [CPU Registers](https://www.geeksforgeeks.org/different-classes-of-cpu-registers/) [BIOS](https://ecomputernotes.com/fundamental/introduction-to-computer/what-is-bios-basic-input-output-system)*

**Next Steps:**
Now you are some what familiar with whats going on with the boot sector

We will now edit the previous boot sector assembly to print **Hello World** to our screen
Changes to be made:
```
mov ah, 0x0e
mov al, 'H'
int 0x10
mov al, 'e'
int 0x10
mov al, 'l'
int 0x10
int 0x10
mov al, 'o'
int 0x10
mov al, ' '
int 0x10
mov al, 'W'
int 0x10
mov al, 'o'
int 0x10
mov al, 'r'
int 0x10
mov al, 'l'
int 0x10
mov al, 'd'
int 0x10 

jmp $

times 510-($-$$) db 0 ;db (declate byte) Fill with 510 zeros minus the size of the previous code

dw 0xaa55 ;declare word(dw) to Magic number(sector address for targeted arch)
``` 

### What happened here ?
<h4> <em>Adding explanation later ...</em> </h4>