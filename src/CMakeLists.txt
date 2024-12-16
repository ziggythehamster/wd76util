set(GENERATED_HEADER_LIST
  "${wd76util_BINARY_DIR}/include/wd76/config.h"
)

set(HEADER_LIST
"${wd76util_SOURCE_DIR}/include/wd76/io_ports.h"
"${wd76util_SOURCE_DIR}/include/wd76/lock_unlock.h"
"${wd76util_SOURCE_DIR}/include/wd76/memory.h"
"${wd76util_SOURCE_DIR}/include/wd76/memory_str.h"
"${wd76util_SOURCE_DIR}/include/wd76/strings.h"
)

set(SOURCE_LIST
  "internal_wd76_set_memory_size_with_reboot.asm"
  "lock_unlock.c"
  "memory.c"
  "memory_str.c"
  "strings.c"
)

configure_file(
  "${wd76util_SOURCE_DIR}/include/wd76/config.h.in"
  "${wd76util_BINARY_DIR}/include/wd76/config.h"
)

add_library(wd76 ${SOURCE_LIST} ${HEADER_LIST} ${GENERATED_HEADER_LIST})

# -0        8086 only code
# -bt=dos   build target = DOS
# -mt       tiny model
# -oi       inline certain library functions
# -os       space is favoured over time when generating code
# -s        disable stack overflow checks
# -zm       place each function into separate segment
# -ze       enable language extensions
target_compile_options(wd76 PUBLIC -0 -bt=dos -mt -s -ze -zm -oi -os)

target_include_directories(wd76 PUBLIC
  "${wd76util_SOURCE_DIR}/include"
  "${wd76util_BINARY_DIR}/include"
)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)

source_group(
  TREE "${PROJECT_BINARY_DIR}/include"
  PREFIX "Generated Header Files"
  FILES ${GENERATED_HEADER_LIST}
)

set(CMAKE_VERBOSE_MAKEFILE ON)
