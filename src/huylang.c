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
        command[i] = buf;
        if (!strcmp(command, "PRINT ")) {
            while ((buf = fgetc(fexec)) != '\n') {
                printf("%c",buf);
            }
            printf("\n");
            i=0;
            strcpy(command, "");
            buf = 0;
            continue;
        }
        if (buf == '\n') {
            i=0;
            buf = 0;
            strcpy(command, "");
        }
        ++i;
    }

    fclose(fexec);

    return 0;
}
