#include <wd76/config.h>
#include <wd76/lock_unlock.h>
#include <wd76/memory_str.h>
#include <wd76/strings.h>

#include <stdio.h>


int main(int argc, char* argv[]){
  unsigned long start_addr = 0L;

  printf("WD76UTIL v%s\n", WD76_VERSION);
  printf("%s\n\n", WD76_DESCRIPTION);

  // unlock registers
  wd76_unlock();

  unsigned long split_start_addr = (unsigned long)wd76_get_split_start_address() << 19L;

  printf("Memory Configuration:\n");
  printf("  BIOS Shadow: %s\n", wd76_get_bios_shadow_str());
  printf("  BIOS Shadow Extra Memory With 64 KiB/64 KiB Split: %s\n", wd76_bool_to_enabled(wd76_get_bios_shadow_extra_memory()));
  printf("  Cache Mode: %s\n", wd76_get_cache_mode_str());
  printf("  Disabled On-Board Memory: %s\n", wd76_get_disabled_memory_str());
  printf("  DRAM Drive Strength: %s\n", wd76_get_dram_drive_str());
  printf("  Interleave: %s\n", wd76_get_interleave_str());
  printf("  Invert Parity: %s\n", wd76_bool_to_enabled(wd76_get_invert_parity()));
  printf("  Mode: %s\n", wd76_get_page_mode_str());
  printf("  Page Mode CAS Width: %s\n", wd76_get_memory_page_mode_cas_width_str());
  printf("  Parity Status: %s\n", wd76_get_parity_status_str());
  printf("  ROM Type: %s\n", wd76_get_rom_type_str());
  printf("  Split Size: %s\n", wd76_get_split_size_str());
  printf("  Split Start: %08lXh (%ld)\n", split_start_addr, split_start_addr);
  printf("  Video BIOS Size: %s\n", wd76_get_video_bios_size_str());

  printf("  Write Protects:\n");
  printf("    BIOS Shadow: %s\n", wd76_bool_to_enabled(wd76_get_bios_shadow_write_protect()));
  printf("    High Memory: %s\n", wd76_bool_to_enabled(wd76_get_high_memory_write_protect()));

  for (short i = 0; i < 4; i++) {
    start_addr = (unsigned long)wd76_get_memory_bank_start_address((wd76_memory_bank)i) << 17L;

    printf("  Bank %d:\n", i);
    printf("    Status: %s\n", wd76_bool_to_enabled(wd76_get_memory_bank_status((wd76_memory_bank)i)));
    printf("    Size: %s\n", wd76_get_memory_bank_size_str((wd76_memory_bank)i));
    printf("    Start: %08lXh (%ld)\n", start_addr, start_addr);
  }

  // lock registers
  wd76_lock();
}
