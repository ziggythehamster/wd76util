#ifndef _MEMORY_STR_H
#define _MEMORY_STR_H

#include "memory.h"

char * wd76_get_cache_mode_str();
char * wd76_get_dram_drive_str();
char * wd76_get_interleave_str();
char * wd76_get_memory_bank_size_str(wd76_memory_bank bank);
char * wd76_get_memory_page_mode_cas_width_str();
char * wd76_get_page_mode_str();
char * wd76_get_split_size_str();
#endif
