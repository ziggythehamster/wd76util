#include "wd76/memory.h"

#include "wd76/lock_unlock.h"
#include "wd76/io_ports.h"

#include <conio.h>

// RAM shadow bits 8-9
wd76_bios_shadow wd76_get_bios_shadow() {
  unsigned int result = (inpw(IO_RAM_SHADOW) & 0x0300) >> 8;

  return (wd76_bios_shadow)result;
}

// RAM shadow bit 7
wd76_bios_shadow_extra_memory wd76_get_bios_shadow_extra_memory() {
  if (inpw(IO_RAM_SHADOW) & 0x0200) {
    return WD76_X_MEM_ENABLED;
  } else {
    return WD76_X_MEM_DISABLED;
  }
}

// RAM shadow bit 12
wd76_bios_shadow_write_protect wd76_get_bios_shadow_write_protect() {
  if (inpw(IO_RAM_WRITE_PROTECT) & 0x1000) {
    return WD76_SHD_WP_ENABLED;
  } else {
    return WD76_SHD_WP_DISABLED;
  }
}

// Memory control bits 12-13
wd76_cache_mode wd76_get_cache_mode() {
  unsigned int result = (inpw(IO_MEMORY_CONTROL) & 0x3000) >> 12;

  return (wd76_cache_mode)result;
}

// RAM shadow bits 14-15
wd76_disabled_memory wd76_get_disabled_memory() {
  unsigned int result = (inpw(IO_RAM_SHADOW) & 0xC000) >> 14;

  return (wd76_disabled_memory)result;
}

// Split start bits 10-11
wd76_dram_drive wd76_get_dram_drive() {
  unsigned int result = (inpw(IO_SPLIT_START_ADDRESS) & 0x0C00) >> 11;

  return (wd76_dram_drive)result;
}

// RAM shadow bit 13
wd76_high_memory_write_protect wd76_get_high_memory_write_protect() {
  if (inpw(IO_RAM_WRITE_PROTECT) & 0x2000) {
    return WD76_HM_WP_ENABLED;
  } else {
    return WD76_HM_WP_DISABLED;
  }
}

// Memory control bits 8-10
wd76_interleave wd76_get_interleave() {
  unsigned int result = (inpw(IO_MEMORY_CONTROL) & 0x0700) >> 8;

  return (wd76_interleave)result;
}

// RAM shadow bit 11
wd76_invert_parity wd76_get_invert_parity() {
  if (inpw(IO_RAM_SHADOW) & 0x0800) {
    return WD76_INV_PAR_ENABLED;
  } else {
    return WD76_INV_PAR_DISABLED;
  }
}

wd76_memory_bank_size wd76_get_memory_bank_size(wd76_memory_bank bank) {
  unsigned int result = inpw(IO_MEMORY_CONTROL);
  unsigned int mask;

  switch (bank) {
    case WD76_BANK0:
      mask = 0x0003;
      return (result & mask);
      break;
    
    case WD76_BANK1:
      mask = 0x000C;
      return (result & mask) >> 2;
      break;
    
    case WD76_BANK2:
      mask = 0x0030;
      return (result & mask) >> 4;
      break;
    
    case WD76_BANK3:
      mask = 0x00C0;
      return (result & mask) >> 6;
      break;
    
    default:
      return WD76_BNK_UNKNOWN;
      break;
  }
}

unsigned int wd76_get_memory_bank_start_address(wd76_memory_bank bank) {
  switch (bank) {
    case WD76_BANK0:
      return inpw(IO_BANK01_START_ADDRESS) & 0x00FF;
      break;
    
    case WD76_BANK1:
      return (inpw(IO_BANK01_START_ADDRESS) & 0xFF00) >> 8;
      break;
    
    case WD76_BANK2:
      return inpw(IO_BANK23_START_ADDRESS) & 0x00FF;
      break;
    
    case WD76_BANK3:
      return (inpw(IO_BANK23_START_ADDRESS) & 0xFF00) >> 8;
      break;

    default:
      return 0xFFFF;
      break;
  }
}

// Split start bits 12-15
wd76_memory_bank_status wd76_get_memory_bank_status(wd76_memory_bank bank) {
  unsigned int mask = 1 << (12 + bank);

  if (inpw(IO_SPLIT_START_ADDRESS) & mask) {
    return WD76_BANK_ENABLED;
  } else {
    return WD76_BANK_DISABLED;
  }
}

// Memory control bit 15
wd76_page_mode_cas_width wd76_get_memory_page_mode_cas_width() {
  if (inpw(IO_MEMORY_CONTROL) & 0x8000) {
    return WD76_PG_CAS_TWO_CPUCLKS;
  } else {
    return WD76_PG_CAS_TWO_AND_A_HALF_CPUCLKS;
  }
}

// Memory control bit 11
wd76_page_mode wd76_get_page_mode() {
  if (inpw(IO_MEMORY_CONTROL) & 0x0800) {
    return WD76_PAGE_MODE_ENABLED;
  } else {
    return WD76_PAGE_MODE_DISABLED;
  }
}

// RAM shadow bit 10
wd76_parity_status wd76_get_parity_status() {
  if (inpw(IO_RAM_SHADOW) & 0x0400) {
    return WD76_PAR_DISABLED;
  } else {
    return WD76_PAR_PORT061H;
  }
}

// RAM shadow bits 2-3
wd76_rom_type wd76_get_rom_type() {
  unsigned int result = (inpw(IO_RAM_SHADOW) & 0x000C) >> 2;

  return (wd76_rom_type)result;
}

// Split start bits 8-9
wd76_split_size wd76_get_split_size() {
  unsigned int result = (inpw(IO_SPLIT_START_ADDRESS) & 0x0300) >> 8;

  return (wd76_split_size)result;
}

// Split start bits 2-7
unsigned int wd76_get_split_start_address() {
  return (inpw(IO_SPLIT_START_ADDRESS) & 0x00FC) >> 2;
}

// RAM shadow bits 4-5
wd76_video_bios_size wd76_get_video_bios_size() {
  unsigned int result = (inpw(IO_RAM_SHADOW) & 0x0030);

  return (wd76_video_bios_size)result;
}
