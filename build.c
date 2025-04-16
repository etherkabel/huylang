#include "bibin.h"
#include <string.h>

int main(int argc, char *argv[]) {
  if(argc == 2) {
    if(!strcmp(argv[1], "clean")) {
      RM("huylang.o", "huylang");
    }
    return 0;
  }
  chdir("./src");
  puts("Starting build");
  CC("../build/huylang.o", "huylang.c");
  chdir("../build");
  LD("huylang", "huylang.o");
  puts("Build finished");
  return 0;
}
