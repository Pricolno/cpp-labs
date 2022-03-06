#ifndef __STR_H__

#define __STR_H__

#include <stddef.h>

char* my_strcpy(char* restrict , const char* restrict );

char* my_strcat(char* restrict , const char* restrict );

int my_strcmp(const char* , const char* );

size_t my_strlen(const char* );

#endif // __STR_H__

