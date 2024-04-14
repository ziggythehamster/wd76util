#ifndef _MEMORY_H
#define _MEMORY_H

// Bits 12-13
typedef enum wd76_cache_mode {
  WD76_CACHE_MODE_DISABLED                    = 0,
  WD76_CACHE_MODE_ENABLED                     = 1,
  WD76_CACHE_MODE_EXTERNAL_PIN51_PARITY_ERROR = 2,
  WD76_CACHE_MODE_EXTERNAL_PIN51_ALT_CLOCK    = 3
} wd76_cache_mode;

typedef enum wd76_dram_drive {
  WD76_DRAM_DRV_FULL   = 0,
  WD76_DRAM_DRV_LOW    = 1,
  WD76_DRAM_DRV_MEDIUM = 2,
  WD76_DRAM_DRV_HIGH   = 3
} wd76_dram_drive;

// Memory control bits 8-10
typedef enum wd76_interleave {
  WD76_ILV_DISABLED        = 0,
  WD76_ILV_BANK01          = 1,
  WD76_ILV_BANK23          = 2,
  WD76_ILV_BANK0123        = 3,
  WD76_ILV_PAGE_MODE_4_WAY = 4
} wd76_interleave;

typedef enum wd76_memory_bank {
  WD76_BANK0 = 0,
  WD76_BANK1 = 1,
  WD76_BANK2 = 2,
  WD76_BANK3 = 3
} wd76_memory_bank;

typedef enum wd76_memory_bank_status {
  WD76_BANK_DISABLED = 0,
  WD76_BANK_ENABLED  = 1
} wd76_memory_bank_status;

// Bank 3: Bits 6-7
// Bank 2: Bits 4-5
// Bank 1: Bits 2-3
// Bank 0: Bits 0-1
typedef enum wd76_memory_bank_size {
  WD76_BNK_64KBIT  = 0,
  WD76_BNK_256KBIT = 1,
  WD76_BNK_1MBIT   = 2,
  WD76_BNK_4MBIT   = 3
} wd76_memory_bank_size;

 // Bit 11
typedef enum wd76_page_mode {
  WD76_PAGE_MODE_DISABLED = 0,
  WD76_PAGE_MODE_ENABLED  = 1
} wd76_page_mode;

// Bit 15
typedef enum wd76_page_mode_cas_width {
  WD76_PG_CAS_TWO_AND_A_HALF_CPUCLKS = 0,
  WD76_PG_CAS_TWO_CPUCLKS            = 1
} wd76_page_mode_cas_width;

// split start bits 8-9
typedef enum wd76_split_size {
  WD76_SPLIT_NONE  = 0,
  WD76_SPLIT_256KB = 1,
  WD76_SPLIT_320KB = 2,
  WD76_SPLIT_384KB = 3
} wd76_split_size;

wd76_cache_mode wd76_get_cache_mode();
wd76_dram_drive wd76_get_dram_drive();
wd76_interleave wd76_get_interleave();
wd76_memory_bank_size wd76_get_memory_bank_size(wd76_memory_bank bank);
unsigned int wd76_get_memory_bank_start_address(wd76_memory_bank bank);
wd76_memory_bank_status wd76_get_memory_bank_status(wd76_memory_bank bank);
wd76_page_mode_cas_width wd76_get_memory_page_mode_cas_width();
wd76_page_mode wd76_get_page_mode();
wd76_split_size wd76_get_split_size();
unsigned int wd76_get_split_start_address();

#endif
