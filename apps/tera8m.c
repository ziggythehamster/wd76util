#include <wd76/lock_unlock.h>
#include <wd76/memory.h>
#include <wd76/util.h>

#include <conio.h>
#include <dos.h>
#include <i86.h>
#include <stdio.h>

#pragma data_seg("_CODE")

// this is to work around VSCode shenanigans
#ifdef __WATCOMC__
#define INTERRUPT_FUNCTION void interrupt far
#define INTERRUPT_POINTER(name) void(interrupt far *name)()
#else
#define INTERRUPT_FUNCTION void
#define INTERRUPT_POINTER(name) void (*name)()
#endif

#define EXTENDED_MEMORY_SIZE (256 /* memory split */ + 512 /* on-board memory */ + 7168 /* 8 MiB - 1 MiB */)
#define SPLIT_START_ADDR 0x00880000 // 8912896 bytes (8388608 + 524288)
#define BANK0_START_ADDR 0x00800000 // 8388608 bytes (note the Tera Drive's onboard RAM is 512KiB)

static unsigned long start_bank0;
static unsigned long split_start;
static wd76_memory_bank_size size_bank0 = WD76_BNK_UNKNOWN;
static wd76_memory_bank_size size_bank1 = WD76_BNK_UNKNOWN;
static wd76_memory_bank_size size_bank2 = WD76_BNK_64KBIT; // not present on this hw
static wd76_memory_bank_size size_bank3 = WD76_BNK_64KBIT; // not present on this hw

extern INTERRUPT_POINTER(orig_int15h);

extern char * msg_banner;
extern char * msg_cfg_now;
extern char * msg_cfg_ok;
extern char * msg_hooked;

// void print(const char *);
// #pragma aux print = \
//   "mov ax, 0x0900" \
//   "int 0x21" \
//   parm caller [dx] \
//   modify [ax di es];

// INTERRUPT_FUNCTION int15h(union REGPACK r) {
//   if (r.h.ah == 0x88) {
//     r.w.ax = EXTENDED_MEMORY_SIZE;
//   } else {
//     _chain_intr(orig_int15h);
//   }
// }

// #pragma aux dev_init value [ax];
// int dev_init() {
//   size_bank0 = wd76_get_memory_bank_size(WD76_BANK0);
//   size_bank1 = wd76_get_memory_bank_size(WD76_BANK1);

//   start_bank0 = wd76_get_memory_bank_start_address(WD76_BANK0);

//   split_start = wd76_get_split_start_address();

//   if (size_bank1 == WD76_BNK_4MBIT && start_bank0 == BANK0_START_ADDR && split_start == SPLIT_START_ADDR) {
//     print(msg_cfg_ok);

//     // orig_int15h = _dos_getvect(0x15);
//     // _dos_setvect(0x15, int15h);

//     // print(hooked);
//   } else {
//     print(msg_cfg_now);

//     wd76_set_split_start_address(SPLIT_START_ADDR);
//     wd76_set_memory_bank_start_address(WD76_BANK0, BANK0_START_ADDR);
//     wd76_set_memory_size_with_reboot(WD76_BNK_256KBIT, WD76_BNK_4MBIT, WD76_BNK_64KBIT, WD76_BNK_64KBIT);
//   }

//   return 0;
// }

int main(int argc, char* argv[]) {
  //dev_init();
}
