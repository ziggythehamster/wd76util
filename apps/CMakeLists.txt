if(CMAKE_C_COMPILER_ID STREQUAL "OpenWatcom")
  # Require all targets in this directory to specify their "system" explicitly
  string(REPLACE "system dos" "" CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
  string(REPLACE "system dos" "" CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
  string(REPLACE "system dos" "" CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS}")

  add_executable(tera8m tera8m_sys.asm tera8m.c)
  add_executable(wd76util wd76util.c)
  target_link_libraries(tera8m PRIVATE wd76)
  target_link_libraries(wd76util PRIVATE wd76)

  add_dependencies(wd76util tera8m)

  # -0        8088/8086
  # -bt=dos   build target = DOS
  # -mt       tiny model
  # -oi       inline certain library functions
  # -os       space is favoured over time when generating code
  # -s        disable stack overflow checks
  # -zcm      assembly compatibility mode (watcom, masm, tasm)
  # -zm       place each function into separate segment
  # -ze       enable language extensions
  target_compile_options(tera8m PUBLIC -bt=dos -mt -ze -s -0 -os -oi)
  target_compile_options(wd76util PUBLIC -bt=dos -mt -zm -ze)

  # We want to build a .sys
  set_target_properties(
    tera8m
    PROPERTIES
      LINK_FLAGS "system dos output raw order clname HEADER clname DATA clname STACK clname BSS clname CODE option showdead, stack=1024, statics" # NB: LINK_OPTIONS gets quoted and doesn't work
      SUFFIX     ".sys"
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
