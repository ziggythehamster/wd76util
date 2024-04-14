#include "wd76/memory_str.h"

char * wd76_get_bios_shadow_str() {
  switch (wd76_get_bios_shadow()) {
    case WD76_SHD_DISABLED:
      return "Disabled";
      break;
    
    case WD76_SHD_64KB:
      return "64KB (0F0000h-0FFFFFh)";
      break;
    
    case WD76_SHD_128KB:
      return "128KB (0E0000h-0FFFFFh)";
      break;
    
    case WD76_SHD_SPLIT_64KB:
      return "64KB + 64KB (0C0000h-0CFFFFh, 0F0000h-0FFFFFh)";
      break;
    
    default:
      return "Unknown";
  }
}

char * wd76_get_cache_mode_str() {
  switch (wd76_get_cache_mode()) {
    case WD76_CACHE_MODE_DISABLED:
      return "Disabled. Pin 51 = Alt Clock";
      break;
    
    case WD76_CACHE_MODE_ENABLED:
      return "Enabled. Pin 51 = /RDYIN";
      break;
    
    case WD76_CACHE_MODE_EXTERNAL_PIN51_PARITY_ERROR:
      return "External memory controller. Pin 51 = Parity Error";
      break;
    
    case WD76_CACHE_MODE_EXTERNAL_PIN51_ALT_CLOCK:
      return "External memory controller. Pin 51 = Alt Clock";
      break;
    
    default:
      return "Unknown";
  }
}

char * wd76_get_disabled_memory_str() {
  switch (wd76_get_disabled_memory()) {
    case WD76_DIS_MEM_NONE:
      return "None";
      break;
    
    case WD76_DIS_MEM_512KB:
      return "512KB - 640KB";
      break;
    
    case WD76_DIS_MEM_256KB:
      return "256KB - 640KB";
      break;
    
    case WD76_DIS_MEM_128KB:
      return "128KB - 640KB";
      break;
    
    default:
      return "Unknown";
  }
}

char * wd76_get_dram_drive_str() {
  switch (wd76_get_dram_drive()) {
    case WD76_DRAM_DRV_FULL:
      return "Full (350 pF)";
      break;
    
    case WD76_DRAM_DRV_LOW:
      return "Low (100 pF)";
      break;
    
    case WD76_DRAM_DRV_MEDIUM:
      return "Medium (180 pF)";
      break;
    
    case WD76_DRAM_DRV_HIGH:
      return "High (260 pF)";
      break;
    
    default:
      return "Unknown";
      break;
  }
}

char * wd76_get_interleave_str() {
  switch (wd76_get_interleave()) {
    case WD76_ILV_DISABLED:
      return "Disabled";
      break;
    
    case WD76_ILV_BANK01:
      return "Bank 0+1";
      break;
    
    case WD76_ILV_BANK23:
      return "Bank 2+3";
      break;

    case WD76_ILV_BANK0123:
      return "Bank 0+1 and Bank 2+3";
      break;
    
    case WD76_ILV_PAGE_MODE_4_WAY:
      return "Page Mode 4-Way";
      break;
    
    default:
      return "Unknown";
  }
}

char * wd76_get_memory_bank_size_str(wd76_memory_bank bank) {
  switch (wd76_get_memory_bank_size(bank)) {
    case WD76_BNK_64KBIT:
      return "64Kbit X 16 = 128 KiB";
      break;

    case WD76_BNK_256KBIT:
      return "256Kbit X 16 = 512 KiB";
      break;

    case WD76_BNK_1MBIT:
      return "1Mbit X 16 = 2 MiB";
      break;
    
    case WD76_BNK_4MBIT:
      return "4Mbit X 16 = 8 MiB";
      break;
    
    default:
      return "Unknown";
  }
}

char * wd76_get_memory_page_mode_cas_width_str() {
  switch (wd76_get_memory_page_mode_cas_width()) {
    case WD76_PG_CAS_TWO_AND_A_HALF_CPUCLKS:
      return "2.5 CPUCLKs";
      break;
    
    case WD76_PG_CAS_TWO_CPUCLKS:
      return "2 CPUCLKs";
      break;
    
    default:
      return "Unknown";
      break;
  }
}

char * wd76_get_page_mode_str() {
  switch (wd76_get_page_mode()) {
    case WD76_PAGE_MODE_ENABLED:
      return "Page Mode";
      break;
    
    case WD76_PAGE_MODE_DISABLED:
      return "Non-Page Mode";
      break;

    default:
      return "Unknown";
  }
}

char * wd76_get_parity_status_str() {
  switch (wd76_get_parity_status()) {
    case WD76_PAR_PORT061H:
      return "Controlled by port 061h";
      break;
    
    case WD76_PAR_DISABLED:
      return "Force Disabled";
      break;
    
    default:
      return "Unknown";
  }
}

char * wd76_get_split_size_str() {
  switch (wd76_get_split_size()) {
    case WD76_SPLIT_NONE:
      return "None";
      break;
    
    case WD76_SPLIT_256KB:
      return "256KB - 0A0000h to 0DFFFFh";
      break;
    
    case WD76_SPLIT_320KB:
      return "320KB - 0A0000h to 0EFFFFh";
      break;
    
    case WD76_SPLIT_384KB:
      return "384KB - 0A0000h to 0FFFFFh";
      break;
    
    default:
      return "Unknown";
  }
}
