#ifndef _HUYLANG_H
#include "include/huylang.h"
#endif

int intCreat() {
    for (int j=0;(buf = fgetc(fexec)) != ' ';++j) { // получение имени переменной
        __int[int_var_count].name[j] = buf;
    }
    if ((buf = fgetc(fexec)) == '=') {
        fseek(fexec,1,SEEK_CUR);
        for (int j=0;(buf = fgetc(fexec)) != '\n';++j) {
            if (buf >= '0' && buf <= '9') {
                tmp[j] = buf;
            } else {return 1;}
        }
        __int[int_var_count].value = atoi(tmp);
        tmp[0] = '\0';
        int_var_count++;
    } else {return 2;}
    clean_command(command,&i);
    return 0;
}
