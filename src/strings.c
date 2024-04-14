#include "wd76/strings.h"

char * wd76_bool_to_enabled(int boolean) {
  if (boolean) {
    return "Enabled";
  } else {
    return "Disabled";
  }
}
