;A bootloader needs to be of 512 bytes in size

;Infinite loop (e9 fd ff)
inf_loop:
    jmp inf_loop

times 510-($-$$) db 0 ;Fill with 510 zeros minus the size of the previous code

dw 0xaa55 ;declare word(dw) to Magic number(sector address for targeted arch)

;e9 fd ff 00 00 00 00 00 00 00 00 00 00 00 00 00
;00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
;29 more lines with sixteen zero-bytes each
;00 00 00 00 00 00 00 00 00 00 00 00 00 00 55 aa