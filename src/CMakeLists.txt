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
target_compile_options(wd76 PUBLIC -bt=dos -ms -zm)

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
