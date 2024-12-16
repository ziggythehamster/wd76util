.8086
.model small

include dosapi.inc

;
; macros
;

inp           macro port
              mov dx, port
              in al, dx
              endm

outp          macro port, data
              mov al, data
              mov dx, port
              out dx, al
              endm

print         macro string
              mov dx, ds:[offset string]
              mov ax, 0x0900
              int 0x21
              endm

print_convmem macro
              print _dbg_convmem
              int 0x12
              print_hexasc
              endm

print_hexasc  macro
              mov bx, offset _hexasc_addr
              call hexasc
              print _hexasc_addr
              endm

restoreregs   macro
              pop bp
              pop si
              pop di
              pop es
              pop ds
              pop dx
              pop cx
              pop bx
              pop ax
              popf
              endm

saveregs      macro
              pushf
              push ax
              push bx
              push cx
              push dx
              push ds
              push es
              push di
              push si
              push bp
              endm

setborder     macro color
              inp 0x3DA           ; clear VGA attribute flip-flop
              outp 0x3C0, 0x11    ; select VGA register 0x11 (overscan color)
              outp 0x3C0, color   ; set color
              endm

setds         macro seg
              mov ax, seg         ; 
              mov ds, ax          ; set DS to provided segment

              xor si, si          ; set DS:SI = seg:0000
              endm

setes         macro seg
              mov ax, seg         ; 
              mov es, ax          ; set ES to provided segment

              xor di, di          ; set ES:DI = seg:0000
              endm

stack_setup   macro
              cli

              mov word ptr cs:[_orig_stack], sp
              mov word ptr cs:[_orig_stack+2], ss
              push cs
              pop ss
              mov sp, word ptr cs:[_local_stack+STACK_SIZE]
              mov bp, sp

              sti
              endm

stack_restore macro
              cli

              mov sp, word ptr cs:[_orig_stack]
              mov ss, word ptr cs:[_orig_stack+2]
              mov bp, sp

              sti
              endm

; watcall puts longs in DX:AX
storelongrtn  macro location
              mov word ptr [location], ax   ; low word
              mov word ptr [location+2], dx ; high word
              endm

;
; equates
;

CRLF          equ 0x0D, 0x0A  ; line terminator
DEVICE_NAME   equ "TERA8M  "  ; the device name
MAX_CMD       equ 0           ; we only support init
STACK_SIZE    equ 1024        ; our stack size

;                  memory split + on board memory + 8 MiB - 1 MiB
EXT_MEM_KB    equ (256          + 512             + 7168)

WD76_BNK_64K  equ 0
WD76_BNK_256K equ 1
WD76_BNK_1M   equ 2
WD76_BNK_4M   equ 3
WD76_BNK_UNK  equ -1

;
; segments
;

DGROUP        group _BSS, _HEADER, _TEXT, STACK

_HEADER       segment word public 'HEADER'
              org 0

; from Ralf Brown's Interrupt List, INT 21h/AH=52h
;
; Format of DOS device driver header:
; Offset  Size  Description	(Table 01646)
; 00h	    DWORD   pointer to next driver, offset=FFFFh if last driver
; 04h     WORD    device attributes (see #01647,#01648)
; 06h     WORD    device strategy entry point
;	                  call with ES:BX -> request header (see #02597 at INT 2F/AX=0802h)
; 08h     WORD    device interrupt entry point
; 0Ah     8 BYTEs blank-padded character device name
;
; Bitfields for device attributes (character device):
; Bit(s)  Description	(Table 01647)
; 15      set (indicates character device)
; 14      IOCTL supported (see AH=44h)
; 13      (DOS 3.0+) output until busy supported
; 12      reserved
; 11      (DOS 3.0+) OPEN/CLOSE/RemMedia calls supported
; 10-8    reserved
; 7       (DOS 5.0+) Generic IOCTL check call supported (driver command 19h)
;           (see AX=4410h,AX=4411h)
; 6       (DOS 3.2+) Generic IOCTL call supported (driver command 13h)
;           (see AX=440Ch,AX=440Dh"DOS 3.2+")
; 5       reserved
; 4       device is special (use INT 29 "fast console output")
; 3       device is CLOCK$ (all reads/writes use transfer record described below)
; 2       device is NUL
; 1       device is standard output
; 0       device is standard input
;
; Note: for European MS-DOS 4.0, bit 11 also indicates that bits 8-6 contain a
;   version code (000 = DOS 3.0,3.1; 001 = DOS 3.2; 010 = European DOS 4.0)

              dw 0xFFFF, 0xFFFF     ; last driver in file
              dw 0x8000             ; character device
              dw dev_strategy       ; device strategy entrypoint
              dw dev_interrupt      ; device interrupt entrypoint
              db DEVICE_NAME        ; device name

_HEADER       ends

;
; _DATA section - unused because we need data in CS
;

_DATA         segment word public 'DATA'
_DATA         ends

;
; _TEXT section - our code
;

_TEXT         segment word public 'CODE'
              extrn wd76_get_memory_bank_size_          :PROC
              extrn wd76_get_memory_bank_start_address_ :PROC
              extrn wd76_get_split_start_address_       :PROC
              extrn wd76_set_memory_bank_start_address_ :PROC
              extrn wd76_set_memory_size_with_reboot_   :PROC
              extrn wd76_set_split_start_address_       :PROC
              extrn wd76_unlock_                        :PROC

              public _msg_banner
              public _msg_cfg_now
              public _msg_cfg_ok
              public _msg_hooked

_rhdr_ptr     dword ?             ; pointer to request header, set by strategy routine
_orig_stack   dword ?             ; the original SP:SS from when our interrupt is called

_split_start  dword 0x00880000    ; the split start we want
_bank0_size   byte  WD76_BNK_256K ; the bank0 size we want
_bank0_start  dword 0x00800000    ; the bank0 start we want
_bank1_size   byte  WD76_BNK_4M   ; the bank1 size we want
_bank1_start  dword ?             ; the bank1 start we want
_bank2_size   byte  WD76_BNK_64K  ; the bank2 size we want
_bank2_start  dword ?             ; the bank2 start we want
_bank3_size   byte  WD76_BNK_64K  ; the bank3 size we want
_bank3_start  dword ?             ; the bank3 start we want

_dbg_convmem  byte "int12 conventional memory: $"

dispatch_table:
              dw dev_init           ; 0 - init
              ; no other command codes supported

;
; dev_strategy - called by MS-DOS kernel with ES:BX = address of request header
;
dev_strategy  proc far
              mov word ptr cs:[_rhdr_ptr], bx
              mov word ptr cs:[_rhdr_ptr+2], es

              ret
dev_strategy  endp

;
; int15_handler - our special int15h handler
;
int15_handler proc far
              sti

              ; NB: The Tera Drive's BIOS has a very simple implementation of
              ; int 15h that will deal with saving registers and whatnot in
              ; the rare case where it needs to care, so presumably all IBM
              ; BIOSes do the same. thus, we won't bother.

              cmp ah, 0x88          ; are we asking for int15h/AH=88h?
              je short int15_extmem ; handle extmem if so

              ; self-modifying code - the original interrupt vector's address
              ; gets shoved here, and we manually encode a far jump that will
              ; far jump to the original vector

              db 0xEA ; jmpf
_orig_int15h  dd 0    ; far pointer to original int 15h

              hlt     ; we should never get here

int15_extmem:
              ; Return: CF clear if successful
              ; AX = number of contiguous KB starting at absolute address 100000h
              mov ax, EXT_MEM_KB
              clc
              iret
int15_handler endp

;
; dev_interrupt - called by MS-DOS kernel immediately after strategy routine
;
dev_interrupt proc far
              saveregs
              ;stack_setup

              setds cs                          ; make local data addressable by setting DS=CS

              les di, dword ptr [_rhdr_ptr]     ; set ES:DI = request header
              mov bl, es:[di+2]                 ; set BL = command code
              xor bh, bh                        ; zero BH

              cmp bx, MAX_CMD                   ; check if we support the command code
              jle command_ok                    ; code was OK
              call dev_error                    ; code not supported
              jmp exit_interrupt                ; exit the procedure

command_ok:
              shl bx, 1                         ; index into the dispatch table
              call word ptr [dispatch_table+bx] ; branch into the dispatch table

              les di, dword ptr [_rhdr_ptr]     ; ES:DI = request header

exit_interrupt:
              or ax, 0x0100                     ; merge done bit into status
              mov es:[di+3], ax                 ; store status into request header

              ;stack_restore
              restoreregs

              sti
              ret                               ; hasta la vista
;
; dev_error - bad command code in request header
;
dev_error     proc near
              mov ax, 0x8003 ; error bit + unknown command code
              ret
dev_error     endp

;
; dev_init - driver is being initialized
;
dev_init      proc near
              print _msg_banner

              cli
              call wd76_unlock_   ; unlock registers
              sti

              ; get bank 0 start address

              cli
              xor ax, ax                                ; bank 0
              call wd76_get_memory_bank_start_address_
              storelongrtn start_bank0
              sti

              ; get split start address

              cli
              call wd76_get_split_start_address_
              storelongrtn split_start
              sti

              ; get bank 1 memory size

              cli
              mov ax, 0x01                      ; bank 1
              call wd76_get_memory_bank_size_
              mov byte ptr [size_bank1], al
              sti

              ; check if we need to do anything
              mov ax, word ptr [start_bank0]                       ; check low word
              mov bx, word ptr [_bank0_start]                      ;
              cmp ax, bx                                           ; 
              jne needs_configured                                 ; bank 0 should start after bank 1

              mov ax, word ptr [start_bank0+2]                     ; check high word
              mov bx, word ptr [_bank0_start+2]                    ;
              cmp ax, bx                                           ; 
              jne needs_configured                                 ; bank 0 should start after bank 1

              mov ax, word ptr [split_start]                       ; check low word
              mov bx, word ptr [_split_start]                      ;
              cmp ax, bx                                           ; 
              jne needs_configured                                 ; split start should be after bank 0

              mov ax, word ptr [split_start+2]                     ; check high word
              mov bx, word ptr [_split_start+2]                    ;
              cmp ax, bx                                           ;
              jne needs_configured                                 ; split start should be after bank 0

              mov al, byte ptr [size_bank1]                        ;
              mov bl, byte ptr [_bank1_size]                       ;
              xor ah, ah                                           ;
              xor bh, bh                                           ;
              cmp ax, bx                                           ; 
              jne needs_configured                                 ; bank 1 should be 4MBit

              print _msg_cfg_ok
              jmp init_done

needs_configured:
              print _msg_cfg_now

              ; set the split start address

              cli
              mov ax, word ptr [_split_start]          ; low word
              mov dx, word ptr [_split_start+2]        ; high word
              call wd76_set_split_start_address_       ; set start address
              cmp ax, 0                                ; did it work?
              jne cfg_failure                          ; bail if not
              sti

              ; set bank 0's start address

              cli
              mov al, 0                                ; bank number
              mov bx, word ptr [_bank0_start]          ; low word
              mov cx, word ptr [_bank0_start+2]        ; high word
              call wd76_set_memory_bank_start_address_ ; set start address
              cmp ax, 0                                ; did it work?
              jne cfg_failure                          ; bail if not
              sti

              ; set memory size with reboot

              cli

              ; watcall args are [al dl bl cl]
              mov al, byte ptr [_bank0_size]           ; set bank 0 size
              xor ah, ah                               ;
              mov dl, byte ptr [_bank1_size]           ; set bank 1 size
              xor dh, dh                               ; 
              mov bl, byte ptr [_bank2_size]           ; set bank 2 size
              xor bh, bh                               ;
              mov cl, byte ptr [_bank3_size]           ; set bank 3 size
              xor ch, ch                               ;

              call wd76_set_memory_size_with_reboot_   ; set memory size
              cmp ax, 0                                ; did it work?
              jne cfg_failure                          ; bail if not
              sti

              hlt                                      ; we should have rebooted anyways

cfg_failure:
              print _msg_cfg_fail

init_done:
              ;
              ; hook int15h to lie about extended memory installed
              ;

              ; get original int 15h

              get_vector 0x15

              cli

              ; update our routine to far jump there
              mov word ptr cs:[_orig_int15h+0], bx
              mov word ptr cs:[_orig_int15h+2], es

              push cs
              pop ds

              set_vector 0x15, int15_handler

              sti

              display _msg_hooked

              ;
              ; brick init command in case driver re-executed
              ;

              mov ax, offset dev_error              ; get address of dev_error
              mov word ptr [dispatch_table], ax     ; make init an error
 
              ;
              ; tell DOS to reclaim memory from the driver
              ;

              les di, dword ptr [_rhdr_ptr]         ; load ES:DI with the request header
              mov ax, offset dev_init               ; tell DOS to end at dev_init offset
              mov word ptr es:[di+14], ax           ;
              mov word ptr es:[di+16], cs           ; and this segment

              xor ax, ax ; return value

              ret

; messages used in this procedure

_msg_banner   db CRLF
              db "TERA8M v0.1 - Tera Drive 8MB Enabler"
              db CRLF
              db "by Ziggy the Hamster and Stealth"
              db CRLF
              db "$"
_msg_cfg_fail db "ERROR reconfiguring WD76C10!"
              db CRLF
              db "$"
_msg_cfg_now  db "Reconfiguring WD76C10 and rebooting..."
              db CRLF
              db "$"
_msg_cfg_ok   db "WD76C10 successfully configured!"
              db CRLF
              db "$"
_msg_hooked   db "INT15h/AH=88h hooked!"
              db CRLF
              db "$"

; variables used in this procedure

start_bank0   dword ?
split_start   dword ?
size_bank0    byte  ?
size_bank1    byte  ?

dev_init      endp

hexasc        proc near
              push cx
              push dx

              mov dx, 4

hexasc1:
              mov cx, 4
              rol ax, cl
              mov cx, ax
              and cx, 0x0F
              add cx, '0'
              cmp cx, '9'
              jbe hexasc2
              add cx, 'A'-'9'-1

hexasc2:
              mov [bx], cl
              inc bx

              dec dx
              jnz hexasc1

              pop dx
              pop cx
              ret

_hexasc_addr  db "XXXX"
              db CRLF
              db "$"

hexasc        endp

eof:
dev_interrupt endp

_TEXT         ends

_BSS          segment word public 'BSS'
_BSS          ends

;
; STACK section - our local stack
;

STACK         segment para stack 'STACK'
_local_stack  byte STACK_SIZE dup (?)
STACK         ends

end
