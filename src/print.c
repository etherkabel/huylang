#include <stdio.h>
#include <stdlib.h>
void print(FILE *f) {
    char buf;
    if ((buf = fgetc(f)) != '(') {
        fprintf(stderr,"Ошибка! Отсутствует '(' после PRINT");
        fclose(f);
        exit(EXIT_FAILURE);
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
