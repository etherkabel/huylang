#include "bibin.h"
#include <string.h>

int main(int argc, char *argv[]) {
  if(argc == 2) {
    if(!strcmp(argv[1], "clean")) {
      RM("huylang.o", "huylang");
    }
    return 0;
  }
  chdir("./build");
  puts("Starting build");
  CC("huylang.o", "../src/huylang.c");
  LD("huylang", "huylang.o");
  puts("Build finished");
  return 0;
}
