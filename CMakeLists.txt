cmake_minimum_required(VERSION 3.18)
project(wd76util
  VERSION 0.1.0
  DESCRIPTION "Provides low-level inspection/control over WD76C10 chipsets"
  LANGUAGES C ASM
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(wd76util_AUTHOR "ZiggyTheHamster")
set(wd76util_LICENSE "MIT")

if(CMAKE_C_COMPILER_ID STREQUAL "OpenWatcom") 
  add_compile_options(-d2 -zq)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -za99")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ze")
  include(Compiler/OpenWatcom-ASM)
endif()

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(apps)
add_subdirectory(src)

set(CMAKE_VERBOSE_MAKEFILE ON)
