#include <stdio.h>
#include <stdlib.h>
#ifndef _HUYLANG_H
#include "include/huylang.h"
#endif


void print(FILE *f) {
    char buf;
    if ((buf = fgetc(f)) != '(') {
        fprintf(stderr,"Ошибка! Отсутствует '(' после PRINT");
        fclose(f);
        exit(EXIT_FAILURE);
    }
    if ((buf = fgetc(f)) == '$') {
        char var_name[BUFFER_SIZE];
        int j;
        for (j=0;(buf = fgetc(f)) != ')' && buf != EOF;++j) {
            var_name[j] = buf;
        }
        var_name[j+1] = '\0';
        for (int j=0;j < VAR_INT_COUNT;++j) {
            if (strcmp(__int[j].name,var_name)) {
                fprintf(stdout,"%s\n",__int[j].name);
                break;
            }
        }
    }
    while ((buf = fgetc(f)) != ')' && buf != EOF) {
        printf("%c",buf);
    }
    if (buf != ')') {
        fprintf(stderr, "Ошибка! Отсутствует ')' после аргумента PRINT\n");
        fclose(f);
        exit(EXIT_FAILURE);
    }
}
