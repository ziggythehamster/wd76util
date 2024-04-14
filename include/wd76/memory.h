#ifndef _MEMORY_H
#define _MEMORY_H

// RAM shadow bits 8-9
typedef enum wd76_bios_shadow {
  WD76_SHD_DISABLED   = 0,
  WD76_SHD_64KB       = 1, // 0F0000-0FFFFF
  WD76_SHD_128KB      = 2, // 0E0000-0FFFFF
  WD76_SHD_SPLIT_64KB = 3  // 0C0000-0CFFFF, 0F0000-0FFFFF
} wd76_bios_shadow;

// RAM shadow bit 7
typedef enum wd76_bios_shadow_extra_memory {
  WD76_X_MEM_DISABLED = 0,
  WD76_X_MEM_ENABLED  = 1
} wd76_bios_shadow_extra_memory;

// RAM shadow bit 12
typedef enum wd76_bios_shadow_write_protect {
  WD76_SHD_WP_DISABLED = 0,
  WD76_SHD_WP_ENABLED  = 1
} wd76_bios_shadow_write_protect;

// Memory control bits 12-13
typedef enum wd76_cache_mode {
  WD76_CACHE_MODE_DISABLED                    = 0,
  WD76_CACHE_MODE_ENABLED                     = 1,
  WD76_CACHE_MODE_EXTERNAL_PIN51_PARITY_ERROR = 2,
  WD76_CACHE_MODE_EXTERNAL_PIN51_ALT_CLOCK    = 3
} wd76_cache_mode;

// RAM shadow bits 14-15
typedef enum wd76_disabled_memory {
  WD76_DIS_MEM_NONE  = 0,
  WD76_DIS_MEM_512KB = 1,
  WD76_DIS_MEM_256KB = 2,
  WD76_DIS_MEM_128KB = 3
} wd76_disabled_memory;

// Split start bits 10-11
typedef enum wd76_dram_drive {
  WD76_DRAM_DRV_FULL   = 0,
  WD76_DRAM_DRV_LOW    = 1,
  WD76_DRAM_DRV_MEDIUM = 2,
  WD76_DRAM_DRV_HIGH   = 3
} wd76_dram_drive;

// RAM shadow bit 13
typedef enum wd76_high_memory_write_protect {
  WD76_HM_WP_DISABLED = 0,
  WD76_HM_WP_ENABLED  = 1
} wd76_high_memory_write_protect;

// Memory control bits 8-10
typedef enum wd76_interleave {
  WD76_ILV_DISABLED        = 0,
  WD76_ILV_BANK01          = 1,
  WD76_ILV_BANK23          = 2,
  WD76_ILV_BANK0123        = 3,
  WD76_ILV_PAGE_MODE_4_WAY = 4
} wd76_interleave;

// RAM shadow bit 11
typedef enum wd76_invert_parity {
  WD76_INV_PAR_DISABLED = 0,
  WD76_INV_PAR_ENABLED  = 1
} wd76_invert_parity;

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
  WD76_BNK_4MBIT   = 3,
  WD76_BNK_UNKNOWN = 255
} wd76_memory_bank_size;

 // Bit 11
typedef enum wd76_page_mode {
  WD76_PAGE_MODE_DISABLED = 0,
  WD76_PAGE_MODE_ENABLED  = 1
} wd76_page_mode;

// Memory control bit 15
typedef enum wd76_page_mode_cas_width {
  WD76_PG_CAS_TWO_AND_A_HALF_CPUCLKS = 0,
  WD76_PG_CAS_TWO_CPUCLKS            = 1
} wd76_page_mode_cas_width;

// RAM shadow bit 10
typedef enum wd76_parity_status {
  WD76_PAR_PORT061H = 0,
  WD76_PAR_DISABLED = 1
} wd76_parity_status;

// RAM shadow bits 2-3
typedef enum wd76_rom_type {
  WD76_ROM_TYP_128KB      = 0,
  WD76_ROM_TYP_64KB       = 1,
  WD76_ROM_TYP_SPLIT_64KB = 2
} wd76_rom_type;

// split start bits 8-9
typedef enum wd76_split_size {
  WD76_SPLIT_NONE  = 0,
  WD76_SPLIT_256KB = 1,
  WD76_SPLIT_320KB = 2,
  WD76_SPLIT_384KB = 3
} wd76_split_size;

// RAM shadow bits 4-5
typedef enum wd76_video_bios_size {
  WD76_VB_SIZ_16KB = 0,
  WD76_VB_SIZ_32KB = 1,
  WD76_VB_SIZ_48KB = 2,
  WD76_VB_SIZ_64KB = 3
} wd76_video_bios_size;

wd76_bios_shadow wd76_get_bios_shadow();
wd76_bios_shadow_extra_memory wd76_get_bios_shadow_extra_memory();
wd76_bios_shadow_write_protect wd76_get_bios_shadow_write_protect();
wd76_cache_mode wd76_get_cache_mode();
wd76_disabled_memory wd76_get_disabled_memory();
wd76_dram_drive wd76_get_dram_drive();
wd76_high_memory_write_protect wd76_get_high_memory_write_protect();
wd76_interleave wd76_get_interleave();
wd76_invert_parity wd76_get_invert_parity();
wd76_memory_bank_size wd76_get_memory_bank_size(wd76_memory_bank bank);
unsigned int wd76_get_memory_bank_start_address(wd76_memory_bank bank);
wd76_memory_bank_status wd76_get_memory_bank_status(wd76_memory_bank bank);
wd76_page_mode_cas_width wd76_get_memory_page_mode_cas_width();
wd76_page_mode wd76_get_page_mode();
wd76_parity_status wd76_get_parity_status();
wd76_rom_type wd76_get_rom_type();
wd76_split_size wd76_get_split_size();
unsigned int wd76_get_split_start_address();
wd76_video_bios_size wd76_get_video_bios_size();

#endif
