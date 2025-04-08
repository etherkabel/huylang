project(huylang)

set(SOURCES
    src/huylang.c
    src/print.c)

add_library(objfiles OBJECT ${SOURCES})

add_executable(huylang $<TARGET_OBJECTS:objfiles>)
