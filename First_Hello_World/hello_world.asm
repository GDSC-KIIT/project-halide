;This is the same code as before with some changes

mov ah, 0x0e ;(teletype)
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