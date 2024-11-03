.8086
.model tiny

inp           macro port
              mov dx, port
              in al, dx
              tick3
              endm

inpw          macro port
              mov dx, port
              in ax, dx
              tick3
              endm

movedataw     macro src, dest, size
              setds src           ; DS = source
              setes dest          ; ES = dest

              mov cx, size        ; CX = size in words

              rep movsw           ; copy!
              endm

outp          macro port, data
              mov al, data
              mov dx, port
              out dx, al
              tick3
              endm

outpw         macro port, data
              mov ax, data
              mov dx, port
              out dx, ax
              tick3
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

tick          macro
              db 0xeb, 0x00       ; jmp to the next instruction, as a delay
              endm

tick3         macro
              tick
              tick
              tick
              endm

wd76_lock     macro
              outp 0xf073, 0x00   ; lock registers
              endm

wd76_unlock   macro
              outp 0xf073, 0xda   ; unlock registers
              endm

.code

;
; internal_wd76_set_memory_size_with_reboot - sets the memory size register to whatever is passed in bx
;
; the WD76 should already be unlocked when calling this procedure
;

public internal_wd76_set_memory_size_with_reboot_
internal_wd76_set_memory_size_with_reboot_ proc near
              setds cs            ; set DS=CS
              setes 0xB800        ; set ES=B800
              mov ax, 0x0500
              mov di, ax          ; set ES:DI=B800:0500

              lea si, [setsize_vram] ; the start of the data to copy

              mov ax, end_setsize_code ;
              sub ax, setsize_vram     ; set ax to number of bytes to copy

              shr ax, 1           ;
              mov cx, ax          ; setup copy

              rep movsw           ; perform copy

              setds 0xB800        ; set DS=B800

              jmp 0xB800, 0x0500  ; jump to VRAM

              hlt                 ; you shouldn't get here

setsize_vram:
              cli                 ; clear interrupts
              tick3

              ;
              ; set our new memory size, which jumbles all RAM
              ; except VRAM
              ;

              outpw 0x3872, bx    ; write the new memory size
              setds 0xB800        ; set DS to B800

              ;
              ; disable BIOS shadowing and write protect
              ;

              inpw 0x6072         ; get current value of RAM shadow & WP register
              mov cx, ax          ; store original register in cx
              and ax, 0xECFF      ; mask out the shadow write protect and disable shadowing
              mov bx, ax          ; move to bx so I don't have to write another macro
              outpw 0x6072, bx    ; disable RAM shadow write protect + shadowing
              mov bx, cx          ; store original register in bx so we don't overwrite it

              wd76_lock

              ;
              ; backup the unshadowed BIOS
              ;

              movedataw 0xe000, 0x4000, 0x8000 ; backup VGA BIOS to 0x4000
              movedataw 0xf000, 0x5000, 0x8000 ; backup BIOS to 0x5000

              setds 0xB800        ; put DS back to this segment

              ;
              ; re-enable BIOS shadowing but keep write protect disabled
              ;

              wd76_unlock

              and bx, 0xEFFF      ; 
              outpw 0x6072, bx    ; mask out write protect but turn shadowing on

              wd76_lock

              ;
              ; re-shadow the BIOS
              ;

              movedataw 0x4000, 0xe000, 0x8000 ; restore VGA BIOS from 0x4000
              movedataw 0x5000, 0xf000, 0x8000 ; restore BIOS from 0x5000
              
              setds 0xB800        ; set DS once again back to this segment

              ;
              ; re-enable BIOS shadow write protect
              ;

              wd76_unlock
              
              inpw 0x6072         ; get current value of RAM shadow & WP register

              or ax, 0x1000       ;
              mov bx, ax          ;
              outpw 0x6072, bx    ; turn write protect back on

              wd76_lock

              ;
              ; set warm boot flag
              ;

              setes 0x40          ; set ES to BIOS data area

              mov ax, 0x72        ;
              mov di, ax          ; set DI to warm boot flag field of BDA

              mov word ptr es:[di], 0x1234 ; set warm boot flag

              ;
              ; reset via 8042
              ; https://wiki.osdev.org/Reboot
              ;

empty_kbd_buffer:
              inp 0x64            ; read 8042 status
              mov bl, al          ; we write al with outp

              test bl, 0x01       ; check for keyboard data
              jz short check_kbd_user_data ; no keyboard data

              inp 0x60            ; there was keyboard data, read port

check_kbd_user_data:
              test bl, 0x02       ; check for user data
              jz short reset      ; no more user data, reset this fucker

              jmp short empty_kbd_buffer ; another loop

reset:             
              outp 0x64, 0xFE     ; send reset command
              hlt                 ; wait for the keyboard controller
end_setsize_code:
              hlt                 ; you shouldn't get here

internal_wd76_set_memory_size_with_reboot_ endp

end
