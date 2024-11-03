if(CMAKE_C_COMPILER_ID STREQUAL "OpenWatcom")
  # CMake support for Watcom assembler
  set(CMAKE_ASM_USE_WATCOM_QUOTE 1)

  foreach(type CREATE_SHARED_LIBRARY CREATE_SHARED_MODULE LINK_EXECUTABLE)
    set(CMAKE_ASM_${type}_USE_WATCOM_QUOTE 1)
  endforeach()

  set(CMAKE_ASM_COMPILE_OBJECT
    "<CMAKE_ASM_COMPILER> <DEFINES> <INCLUDES> -fo<OBJECT> -c <SOURCE>")

  # warning level
  string(APPEND CMAKE_ASM_FLAGS_INIT " -w3")
  # debug options
  string(APPEND CMAKE_ASM_FLAGS_DEBUG_INIT " -d2")
  string(APPEND CMAKE_ASM_FLAGS_MINSIZEREL_INIT " -s -os -d0 -dNDEBUG")
  string(APPEND CMAKE_ASM_FLAGS_RELEASE_INIT " -s -ot -d0 -dNDEBUG")
  string(APPEND CMAKE_ASM_FLAGS_RELWITHDEBINFO_INIT " -s -ot -d1 -dNDEBUG")
endif()

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

# -bt=dos   build target = DOS
# -mt       tiny model
# -zm       place each function into separate segment
# -ze       enable language extensions
target_compile_options(wd76 PUBLIC -bt=dos -mt -zm -ze)

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
