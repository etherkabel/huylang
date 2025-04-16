#include "include/huylang.h"

void clean_command(char *command, int* i) {
    command[0] = '\0';
    *i=0;
}

integerVar __int[VAR_COUNT];
charVar __char[VAR_COUNT];


char tmp[BUFFER_SIZE];

FILE *fexec;
char buf;
char command[BUFFER_SIZE];
int i=0;

int int_var_count = 0;
int char_var_count = 0;

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
            print();
            putchar('\n');
            clean_command(command,&i);
        }
        if (!strcmp(command, "int")) {
            if (intCreat() == 1) {
                fprintf(stderr,"Ошибка! В числовой переменной замечен строковый литерал\n");
                fclose(fexec);
                exit(EXIT_FAILURE);
            } else if (intCreat() == 2) {
                fprintf(stderr,"Ошибка! Пропущен '='\n");
                fclose(fexec);
                exit(EXIT_FAILURE);
            }
        }
        if (buf == '\n') {
            clean_command(command,&i);
        }
    }

    fclose(fexec);

    return 0;
}
