#include "string_utils.h"

int mx_strlen(const char* s){
    int count = 0;
    const char *at = s;

    while(*at != '\0'){
        at++;
        count++;
    }

    return count;
}

char *mx_strnew(const int size){
    if(size < 0)
        return NULL;

    char *str;
    str = (char*) malloc((size + 1) * sizeof(char));
    if(str == NULL) return str;

    for(int i = 0; i < size + 1; ++i)
        *(str + i) = '\0';
    return str;
}

void mx_printstr(const char *s){
    write(STDOUT_FILENO, s, mx_strlen(s));
}

char *mx_strcpy(char *dst, const char *src){
    int i = 0;

    while(src[i] != '\0'){
        dst[i] = src[i];
        ++i;
    }
    dst[i] = '\0';
    return dst;
}

void mx_strdel(char **str){
    if(str && *str){
        free(*str);
        *str = NULL;
    }
}


