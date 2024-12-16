;
; Macros used for interacting with the MS-DOS API.
; Matches the MS-DOS Programmer's Reference when logical
; (see: https://archive.org/details/microsoft-ms-dos-3.2-programmers-reference-1986)
;

display       macro string
              mov dx, offset string
              mov ah, 0x09
              int 0x21
              endm

get_vector    macro interrupt
              mov al, interrupt
              mov ah, 0x35
              int 0x21
              endm

set_vector    macro interrupt, handler_start
              mov al, interrupt
              mov dx, offset handler_start
              mov ah, 0x25
              int 0x21
              endm
