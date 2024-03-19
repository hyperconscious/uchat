#pragma once

#include <unistd.h>
#include <stdlib.h>

int mx_strlen(const char* s);
char *mx_strnew(const int size);
void mx_printstr(const char *s);
char *mx_strcpy(char *dst, const char *src);
void mx_strdel(char **str);

