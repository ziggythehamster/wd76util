#include <wd76/config.h>
#include <wd76/lock_unlock.h>
#include <wd76/memory_str.h>
#include <wd76/strings.h>

#include <stdio.h>


int main(int argc, char* argv[]){
  unsigned int start_addr = 0;
  unsigned long start_addr_dec = 0L;

  printf("WD76UTIL v%s\n", WD76_VERSION);
  printf("%s\n\n", WD76_DESCRIPTION);

  // unlock registers
  wd76_unlock();

  unsigned int split_start_addr = wd76_get_split_start_address();
  unsigned long split_start_addr_dec = (long)split_start_addr << 18;

  printf("Memory Configuration:\n");
  printf("  Cache Mode: %s\n", wd76_get_cache_mode_str());
  printf("  DRAM Drive Strength: %s\n", wd76_get_dram_drive_str());
  printf("  Interleave: %s\n", wd76_get_interleave_str());
  printf("  Mode: %s\n", wd76_get_page_mode_str());
  printf("  Page Mode CAS Width: %s\n", wd76_get_memory_page_mode_cas_width_str());
  printf("  Split Size: %s\n", wd76_get_split_size_str());
  printf("  Split Start: %03X00000h (%ld)\n", split_start_addr, split_start_addr_dec);

  for (short i = 0; i < 4; i++) {
    start_addr = wd76_get_memory_bank_start_address((wd76_memory_bank)i);
    start_addr_dec = (long)start_addr << 16;

    printf("  Bank %d:\n", i);
    printf("    Status: %s\n", wd76_bool_to_enabled(wd76_get_memory_bank_status((wd76_memory_bank)i)));
    printf("    Size: %s\n", wd76_get_memory_bank_size_str((wd76_memory_bank)i));
    printf("    Start: %04X0000h (%ld)\n", start_addr, start_addr_dec);
  }

  // lock registers
  wd76_lock();
}
