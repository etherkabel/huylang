#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef _HUYLANG_H
#include "include/huylang.h"
#endif

extern void clean_command(char *command, int* i) {
    command[0] = '\0';
    *i=0;
}

integerVar __int[VAR_INT_COUNT];

char tmp[BUFFER_SIZE];

static FILE *fexec;
static char buf;
static char command[BUFFER_SIZE];
static int i=0;

int int_var_count = 0;


int main(int argc, char* argv[]) {
    if (!argv[1]) {
        printf("Ошибка! Введите имя файла.\n");
        exit(EXIT_FAILURE);
    }

    if (!strcmp(argv[1],"-v") || !strcmp(argv[1], "--version")) {
        fprintf(stdout,"HUYLANG INTERPRETATOR\nVERSION 1.0\n");
        exit(EXIT_SUCCESS);
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
            print(fexec);
            printf("\n");
            clean_command(command,&i);
        }
        if (!strcmp(command, "int")) {
            fseek(fexec,1,SEEK_CUR);
            clean_command(command,&i);
            for (int j=0;(buf = fgetc(fexec)) != ' ';++j) { // получение имени переменной
                __int[int_var_count].name[j] = buf;
            }
            if ((buf = fgetc(fexec)) == '=') {
                fseek(fexec,1,SEEK_CUR);
                for (int j=0;(buf = fgetc(fexec)) != '\n';++j) {
                    if (buf >= '0' && buf <= '9') {
                        tmp[j] = buf;
                    } else {
                        fprintf(stderr,"Ошибка! В числовой переменной замечен строковый литерал\n");
                        fclose(fexec);
                        exit(EXIT_FAILURE);
                    }
                }
                __int[int_var_count].value = atoi(tmp);
                tmp[0] = '\0';
                int_var_count++;
            } else {
                fprintf(stderr,"Ошибка! Пропущен '='\n");
                fclose(fexec);
                exit(EXIT_FAILURE);
            }
            clean_command(command,&i);
        }

        if (buf == '\n') {
            clean_command(command,&i);
        }
    }

    fclose(fexec);

    return 0;
}
