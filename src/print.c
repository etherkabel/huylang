#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
        bool isVar = false;
        for (j=0;(buf = fgetc(f)) != ' ' && buf != EOF && buf != ')';++j) {
            var_name[j] = buf;
        }
        var_name[j+1] = '\0';
        for (int j=0;j < VAR_INT_COUNT;++j) {
            if (strcmp(__int[j].name,var_name)) {
                fprintf(stdout,"%d\n",__int[j].value);
                isVar = true;
                break;
            }
        }
        if (!isVar) {
            fprintf(stderr,"Ошибка! Не найдена переменная %s\n",var_name);
        }
        isVar = false;
        return;
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
