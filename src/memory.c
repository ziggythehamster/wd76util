#include "wd76/memory.h"

#include "wd76/lock_unlock.h"
#include "wd76/io_ports.h"

#include <conio.h>

// Memory control bits 12-13
wd76_cache_mode wd76_get_cache_mode() {
  unsigned int result = (inpw(IO_MEMORY_CONTROL) & 0x3000) >> 12;

  return (wd76_cache_mode)result;
}

// Split start bits 10-11
wd76_dram_drive wd76_get_dram_drive() {
  unsigned int result = (inpw(IO_SPLIT_START_ADDRESS) & 0x0C00) >> 11;

  return (wd76_dram_drive)result;
}

// Memory control bits 8-10
wd76_interleave wd76_get_interleave() {
  unsigned int result = (inpw(IO_MEMORY_CONTROL) & 0x0700) >> 8;

  return (wd76_interleave)result;
}

wd76_memory_bank_size wd76_get_memory_bank_size(wd76_memory_bank bank) {
  /*int mask = 1 << (((int)bank * 2) + 1) | 1 << (((int)bank * 2) + 2);
  int result = (inpw(IO_MEMORY_CONTROL) & mask) >> ((int)bank * 2) + 1;*/

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
      return 0xFFFF;
      break;
  }

  //return (wd76_memory_bank_size)result;
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

// Bit 15
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

// Split start bits 8-9
wd76_split_size wd76_get_split_size() {
  unsigned int result = (inpw(IO_SPLIT_START_ADDRESS) & 0x0300) >> 8;

  return (wd76_split_size)result;
}

// Split start bits 2-7
unsigned int wd76_get_split_start_address() {
  return (inpw(IO_SPLIT_START_ADDRESS) & 0x00FC) >> 2;
}
