if(CMAKE_C_COMPILER_ID STREQUAL "OpenWatcom")
  # Require all targets in this directory to specify their "system" explicitly
  string(REPLACE "system dos" "" CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
  string(REPLACE "system dos" "" CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
  string(REPLACE "system dos" "" CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS}")

  add_executable(tera8m tera8m.c)
  add_executable(wd76util wd76util.c)
  target_link_libraries(tera8m PRIVATE wd76)
  target_link_libraries(wd76util PRIVATE wd76)

  add_dependencies(wd76util tera8m)

  # Use the tiny memory model
  target_compile_options(tera8m PUBLIC -bt=dos -mt -zm)
  target_compile_options(wd76util PUBLIC -bt=dos -mt -zm)

  # We want to build a .com
  set_target_properties(
    tera8m
    PROPERTIES
      LINK_FLAGS "system com option eliminate" # NB: LINK_OPTIONS gets quoted and doesn't work
      SUFFIX     ".com"
  )

  # We want to build a .com
  set_target_properties(
    wd76util
    PROPERTIES
      LINK_FLAGS "system com option eliminate" # NB: LINK_OPTIONS gets quoted and doesn't work
      SUFFIX     ".com"
  )
endif()

set(CMAKE_VERBOSE_MAKEFILE ON)
