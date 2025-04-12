//huylang.h
#ifndef _HUYLANG_H
#define _HUYLANG_H
#endif
#ifndef	_STRING_H
#include <string.h>
#endif
#ifndef _STDIO_H
#include <stdio.h>
#endif
#ifndef _GLIBCXX_STDLIB_H
#include <stdlib.h>
#endif

#define BUFFER_SIZE 1024
#define VAR_NAME_SIZE 50
#define VAR_COUNT 1024

extern void print();
extern int intCreat();
extern void clean_command(char* command, int* i);

typedef struct Int_Var {
    char name[VAR_NAME_SIZE];
    int value;
} integerVar;
extern integerVar __int[VAR_COUNT];

typedef struct Char_Var {
    char name[VAR_NAME_SIZE];
    char value[BUFFER_SIZE];
} charVar;
extern charVar __char[VAR_COUNT];

extern FILE *fexec;
extern char buf;
extern char command[BUFFER_SIZE];
extern int i;

extern int int_var_count;
extern int char_var_count;
extern char tmp[BUFFER_SIZE];
