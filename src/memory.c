#include "wd76/memory.h"

#include "wd76/lock_unlock.h"
#include "wd76/io_ports.h"

#include <conio.h>

#pragma aux internal_wd76_set_memory_size_with_reboot \
  parm [bx] \
  modify [ax bx cx dx di es si] \
  aborts

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

unsigned int wd76_get_split_start_address() {
  return (inpw(IO_SPLIT_START_ADDRESS) & 0x00FC) >> 2;
}

// RAM shadow bits 4-5
wd76_video_bios_size wd76_get_video_bios_size() {
  unsigned int result = (inpw(IO_RAM_SHADOW) & 0x0030);

  return (wd76_video_bios_size)result;
}

unsigned int wd76_set_memory_bank_start_address(wd76_memory_bank bank, unsigned long address) {
  // validate the passed argument
  if (address < (1L << 17L) || address > ((1L << 24L) | (1L << 23L) | (1L << 22L) | (1L << 21L) | (1L << 20L) | (1L << 19L) | (1L << 18L) | (1L << 17L))) {
    return 1;
  } else {
    unsigned int old_value = 0;
    unsigned int old_value_masked = 0;

    switch (bank) {
      case WD76_BANK0:
        old_value = inpw(IO_BANK01_START_ADDRESS);
        old_value_masked = old_value & 0xFF00;

        outpw(IO_BANK01_START_ADDRESS, old_value_masked | (address >> 17L));

        return 0;
        break;
      
      case WD76_BANK1:
        old_value = inpw(IO_BANK01_START_ADDRESS);
        old_value_masked = old_value & 0x00FF;

        outpw(IO_BANK01_START_ADDRESS, old_value_masked | ((address >> 17L) << 8));

        return 0;
        break;
      
      case WD76_BANK2:
        old_value = inpw(IO_BANK23_START_ADDRESS);
        old_value_masked = old_value & 0xFF00;

        outpw(IO_BANK23_START_ADDRESS, old_value_masked | (address >> 17L));

        return 0;
        break;
      
      case WD76_BANK3:
        old_value = inpw(IO_BANK23_START_ADDRESS);
        old_value_masked = old_value & 0x00FF;

        outpw(IO_BANK23_START_ADDRESS, old_value_masked | ((address >> 17L) << 8));

        return 0;
        break;

      default:
        return 1;
        break;
    }
  }
}

unsigned int wd76_set_memory_size_with_reboot(wd76_memory_bank_size bank0, wd76_memory_bank_size bank1, wd76_memory_bank_size bank2, wd76_memory_bank_size bank3) {
  // validate the arguments
  if (bank0 < 0 || bank0 > 3 || bank1 < 0 || bank1 > 3 || bank2 < 0 || bank2 > 3 || bank3 < 0 || bank3 > 3) {
    return 1;
  } else {
    unsigned int old_reg = inpw(IO_MEMORY_CONTROL);
    unsigned int old_reg_masked = old_reg & 0xFF00;
    unsigned int new_size = (unsigned int)bank0 | ((unsigned int)bank1 << 2) | ((unsigned int)bank2 << 4) | ((unsigned int)bank3 << 6);
    unsigned int new_reg = old_reg_masked | new_size;

    /*
      when setting the memory size bits in the memory control register (3872h),
      the effect is immediate, which causes the memory to be mapped to totally
      different locations than before. this is no good if we want to keep running
      code, so we have to copy the code we want to run to VRAM and then execute it
      from there. VRAM never gets relocated within the memory map, so this works.

      after setting up the new RAM size, we have to reshadow the BIOSes
    */

    internal_wd76_set_memory_size_with_reboot(new_reg);

    return 0; // technically this is impossible to reach
  }
}

// Split start bits 2-7 - A19 through A24
unsigned int wd76_set_split_start_address(unsigned long address) {
  // validate the passed argument
  if (address < (1L << 19L) || address > ((1L << 24L) | (1L << 23L) | (1L << 22L) | (1L << 21L) | (1L << 20L) | (1L << 19L))) {
    return 1;
  } else {
    unsigned int old_value = inpw(IO_SPLIT_START_ADDRESS);
    unsigned int old_value_masked = old_value & 0xFF03; // zero the bits we're setting

    outpw(IO_SPLIT_START_ADDRESS, old_value_masked | ((address >> 19L) << 2));

    return 0;
  }
}
