#ifndef _HUYLANG_H
#define _HUYLANG_H
#endif

#include <string.h>

#ifndef _STDIO_H
#include <stdio.h>
#endif

#define BUFFER_SIZE 1024
#define VAR_NAME_SIZE 50
#define VAR_INT_COUNT 1024

extern void print(FILE *f);

extern void clean_command(char *command, int* i);

typedef struct Int_Var {
    char name[50];
    int value;
} integerVar;
extern integerVar __int[VAR_INT_COUNT];
