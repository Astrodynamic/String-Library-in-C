#ifndef STRING_STRING_H
#define STRING_STRING_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#undef NULL
#define NULL CASTOM_NULL
#define CASTOM_NULL (void *)0
typedef unsigned long long castom_size_t;

#include "castom_strerror.h"
#include "castom_sprintf.h"

void *castom_memchr(const void *str, int c, castom_size_t n);
int castom_memcmp(const void *str1, const void *str2, castom_size_t n);
void *castom_memcpy(void *dest, const void *src, castom_size_t n);
void *castom_memmove(void *dest, const void *src, castom_size_t n);
void *castom_memset(void *str, int c, castom_size_t n);
char *castom_strcat(char *dest, const char *src);
char *castom_strncat(char *dest, const char *src, castom_size_t n);
char *castom_strchr(const char *str, int c);
int castom_strcmp(const char *str1, const char *str2);
int castom_strncmp(const char *str1, const char *str2, castom_size_t n);
char *castom_strcpy(char *dest, const char *src);
char *castom_strncpy(char *dest, const char *src, castom_size_t n);
castom_size_t castom_strcspn(const char *str1, const char *str2);
char *castom_strerror(int errnum);
castom_size_t castom_strlen(const char *str);
char *castom_strpbrk(const char *str1, const char *str2);
char *castom_strrchr(const char *str, int c);
castom_size_t castom_strspn(const char *str1, const char *str2);
char *castom_strstr(const char *haystack, const char *needle);
char *castom_strtok(char *str, const char *delim);

void *castom_to_upper(const char *str);
void *castom_to_lower(const char *str);
void *castom_insert(const char *src, const char *str, castom_size_t start_index);
void *castom_trim(const char *src, const char *trim_chars);

int castom_sprintf(char *str, const char *format, ...);

#endif  // STRING_STRING_H
