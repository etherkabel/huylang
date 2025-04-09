project(huylang)

set(SOURCES
    src/huylang.c
    src/print.c
    src/include/huylang.h)

add_library(objfiles OBJECT ${SOURCES})

add_executable(huylang $<TARGET_OBJECTS:objfiles>)
