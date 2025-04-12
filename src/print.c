#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef _HUYLANG_H
#include "include/huylang.h"
#endif

void print() {
    char buf;
    if ((buf = fgetc(fexec)) != '(') {
        fprintf(stderr,"Ошибка! Отсутствует '(' после PRINT");
        fclose(fexec);
        exit(EXIT_FAILURE);
    }
    if ((buf = fgetc(fexec)) == '$') {
        char var_name[BUFFER_SIZE];
        int j;
        bool isVar = false;
        for (j=0;(buf = fgetc(fexec)) != ' ' && buf != EOF && buf != ')';++j) {
            var_name[j] = buf;
        }
        var_name[j+1] = '\0';
        for (int j=0;j < VAR_COUNT;++j) {
            if (strcmp(__int[j].name,var_name)) {
                fprintf(stdout,"%d",__int[j].value);
                isVar = true;
                break;
            }
        }
        if (!isVar) {
            fprintf(stderr,"Ошибка! Не найдена переменная %s\n",var_name);
        }
        isVar = false;
        return;
    } else{fseek(fexec,-1,SEEK_CUR);}
    while ((buf = fgetc(fexec)) != ')' && buf != EOF) {
        printf("%c",buf);
    }
    if (buf != ')') {
        fprintf(stderr, "Ошибка! Отсутствует ')' после аргумента PRINT\n");
        fclose(fexec);
        exit(EXIT_FAILURE);
    }
}
