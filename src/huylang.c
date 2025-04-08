#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    FILE *fexec;
    //char buf[BUFFER_SIZE];
    char buf;
    char command[BUFFER_SIZE];
    int i=0;

    if (!argv[1]) {
        printf("Ошибка! Введите имя файла.\n");
        exit(EXIT_FAILURE);
    }

    if (!(fexec = fopen(argv[1],"r"))) {
        perror("Не удалось открыть файл");
        exit(EXIT_FAILURE);
    }

    while ((buf = fgetc(fexec)) != EOF) {
        if (i < BUFFER_SIZE - 1) {
            command[i] = buf;
            ++i;
            command[i] = '\0';
        } else {
            fprintf(stderr, "Ошибка! Превышен размер команды.\n");
            fclose(fexec);
            exit(EXIT_FAILURE);
        }
        if (!strcmp(command, "print")) {
            if ((buf = fgetc(fexec)) != '(') {
                fprintf(stderr,"Ошибка! Отсутствует '(' после PRINT");
                fclose(fexec);
                exit(EXIT_FAILURE);
            }
            while ((buf = fgetc(fexec)) != ')' && buf != EOF) {
                printf("%c",buf);
            }
            if (buf != ')') {
                fprintf(stderr, "Ошибка! Отсутствует ')' после аргумента PRINT\n");
                fclose(fexec);
                exit(EXIT_FAILURE);
            }
            printf("\n");
            i=0;
            command[0] = '\0';
        }
        if (buf == '\n') {
            i = 0;
            command[0] = '\0';
        }
    }

    fclose(fexec);

    return 0;
}
