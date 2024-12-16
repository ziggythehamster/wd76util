#ifndef _UTIL_H
#define _UTIL_H

// a relative jump to the next instruction
void wd76_delay();
#pragma aux wd76_delay = \
  "db 0xEB, 0x00";

#define wd76_delay3() wd76_delay(); wd76_delay(); wd76_delay();

#endif
