#include <wd76/lock_unlock.h>
#include <wd76/memory.h>

#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <string.h>

#define SPLIT_START_ADDR 0x44 // A23=1, A19=1
#define SPLIT_START_MASK 0xFF00 // high byte needs left alone
#define START_ADDR 0x0040 // A23=1 for bank0, bank1=0

unsigned int get_extended_size();
#pragma aux get_extended_size = \
  "mov ax, 0x8800" \
  "int 0x15" \
  value [ax];

int main(int argc, char* argv[]) {
  printf("TERA8M init\n");

  printf("Extended memory size: %d\n", get_extended_size());

  printf("Determining new register values ...\n");

  // unlock registers
  wd76_unlock();

  unsigned int orig_start = inpw(0x4872);
  unsigned int orig_split = inpw(0x5872);
  unsigned int new_start = START_ADDR;
  unsigned int new_split = (orig_split & SPLIT_START_MASK) | SPLIT_START_ADDR;

  wd76_memory_bank_size bank0 = wd76_get_memory_bank_size(WD76_BANK0);
  wd76_memory_bank_size bank1 = WD76_BNK_4MBIT;
  wd76_memory_bank_size bank2 = wd76_get_memory_bank_size(WD76_BANK2);
  wd76_memory_bank_size bank3 = wd76_get_memory_bank_size(WD76_BANK3);

  printf("0 = %04X  1 = %04X  2 = %04X  3 = %04X\n", bank0, bank1, bank2, bank3);

  printf("4872h %04X => %04X\n", orig_start, new_start);
  printf("5872h %04X => %04X\n", orig_split, new_split);

  getch(); // wait for a key

  printf("Running ...\n");

  outpw(0x5872, new_split);
  outpw(0x4872, new_start);

  // set size
  wd76_set_memory_size_with_reboot(bank0, bank1, bank2, bank3);
}
