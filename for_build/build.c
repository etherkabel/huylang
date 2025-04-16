#include "bibin.h"
#include <string.h>

int main(int argc, char *argv[]) {
  if(argc == 2) {
    if(!strcmp(argv[1], "clean")) {
      RM("huylang.o", "huylang");
    }
    return 0;
  }

  puts("Starting build");
  puts("Compiling huylang.c");
  CC("huylang.o", "src/huylang.c");
  puts("Linking huylang.o");
  LD("huylang", "huylang.o");
  puts("Build finished");
  return 0;
}
