#ifndef _LOCK_UNLOCK_H
#define _LOCK_UNLOCK_H

#define LOCK_UNLOCK_CMD_LOCK 0x00
#define LOCK_UNLOCK_CMD_UNLOCK 0xDA

void wd76_lock();
void wd76_unlock();
#endif
