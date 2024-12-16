#include <wd76/config.h>
#include <wd76/io_ports.h>
#include <wd76/lock_unlock.h>
#include <wd76/memory_str.h>
#include <wd76/strings.h>

#include <conio.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  unsigned long start_addr = 0L;

  printf("WD76UTIL v%s\n", WD76_VERSION);
  printf("%s\n\n", WD76_DESCRIPTION);

  // unlock registers
  wd76_unlock();

  unsigned long split_start_addr = wd76_get_split_start_address();

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
    start_addr = wd76_get_memory_bank_start_address((wd76_memory_bank)i);

    printf("  Bank %d:\n", i);
    printf("    Status: %s\n", wd76_bool_to_enabled(wd76_get_memory_bank_status((wd76_memory_bank)i)));
    printf("    Size: %s\n", wd76_get_memory_bank_size_str((wd76_memory_bank)i));
    printf("    Start: %08lXh (%ld)\n", start_addr, start_addr);
  }

  printf("\n");
  printf("Raw Register Values:\n");
  printf("  1072 CPU Clock Control: %04X\n", inpw(IO_CPU_CLOCK_CONTROL));
  printf("  1872 Bus Timing & Power Down Control: %04X\n", inpw(IO_BUS_TIMING));
  printf("  2072 Refresh Control, Serial/Parallel Chip Selects: %04X\n", inpw(IO_REFRESH_CONTROL));
  printf("  2872 Chip Selects: %04X\n", inpw(IO_CHIP_SELECT_2));
  printf("  3072 Programmable Chip Select Address: %04X\n", inpw(IO_CHIP_SELECT_ADDRESS));
  printf("  3872 Memory Control: %04X\n", inpw(IO_MEMORY_CONTROL));
  printf("  4072 Non-Page Mode DRAM Timing: %04X\n", inpw(IO_NONPAGE_DRAM_TIMING));
  printf("  4872 Bank 1/0 Start Address: %04X\n", inpw(IO_BANK01_START_ADDRESS));
  printf("  5072 Bank 3/2 Start Address: %04X\n", inpw(IO_BANK23_START_ADDRESS));
  printf("  5872 Split Start Address: %04X\n", inpw(IO_SPLIT_START_ADDRESS));
  printf("  6072 RAM Shadow & Write Protect: %04X\n", inpw(IO_RAM_SHADOW));
  printf("  6872 EMS Control & Lower EMS Boundary: %04X\n", inpw(IO_EMS_CONTROL));
  printf("  7072 PMC Output Control 7:0: %04X\n", inpw(IO_PMC_OUTPUT_CONTROL_L));
  printf("  7872 PMC Output Control 15:8: %04X\n", inpw(IO_PMC_OUTPUT_CONTROL_H));
  printf("  8072 PMC Timers: %04X\n", inpw(IO_PMC_TIMERS));
  printf("  8872 PMC Inputs: %04X\n", inpw(IO_PMC_INPUTS));
  printf("  9072 NMI Status: %04X\n", inpw(IO_NMI_STATUS));
  printf("  9872 Diagnostic: %04X\n", inpw(IO_DIAGNOSTIC));
  printf("  A072 Delay Line: %04X\n", inpw(IO_DELAY_LINE));
  printf("  A872 Test Enable: %04X\n", inpw(IO_TEST_ENABLE));
  printf("  B072 Activity Monitor Control: %04X\n", inpw(IO_ACTIVITY_MONITOR_CONTROL));
  printf("  B872 DMA Control Shadow: %04X\n", inpw(IO_DMA_CONTROL_SHADOW));
  printf("  C072 High Memory Write Protect Boundary: %04X\n", inpw(IO_HIGHMEM_WRITE_PROTECT_BOUNDARY));
  printf("  C872 PMC Interrupt Enables: %04X\n", inpw(IO_PMC_INTERRUPT_ENABLES));
  printf("  D872 Activity Monitor Mask: %04X\n", inpw(IO_ACTIVITY_MONITOR_MASK));
  printf("  DC72 Test Status: %04X\n", inpw(IO_TEST_STATUS));
  printf("  E072 EMS Page Register Pointer: %04X\n", inpw(IO_EMS_PAGE_REGISTER_POINTER));
  printf("  E872 EMS Page Register: %04X\n", inpw(IO_EMS_PAGE_REGISTER));

  // lock registers
  wd76_lock();
}
