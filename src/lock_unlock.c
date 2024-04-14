#include "wd76/lock_unlock.h"

#include "wd76/io_ports.h"

#include <conio.h>

void wd76_lock() {
  outp(IO_LOCK_UNLOCK, LOCK_UNLOCK_CMD_LOCK);
}

void wd76_unlock() {
  outp(IO_LOCK_UNLOCK, LOCK_UNLOCK_CMD_UNLOCK);
}
