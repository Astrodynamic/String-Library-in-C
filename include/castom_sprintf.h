#ifndef STRING_INCLUDE_CASTOM_SPRINTF_H_
#define STRING_INCLUDE_CASTOM_SPRINTF_H_

#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>

#include "castom_string.h"

#define SIGN 1 << 0
#define LEFT 1 << 1
#define PLUS 1 << 2
#define SPACE 1 << 3
#define ZEROPAD 1 << 4
#define SMALL 1 << 5
#define SPECIAL 1 << 6

#define AST_FLAG_WIDTH 1 << 7
#define AST_FLAG_PRECISION 1 << 8

#define SHORT_FLAG_INT 1 << 9
#define LONG_FLAG_INT 1 << 10
#define LONG_FLAG_FLOAT 1 << 11

#define SCIENTIFIC_NOTE 1 << 12
#define SHORT_REPRES 1 << 13

#define MULTY_BASE 1 << 14

enum format_type {
  FORMAT_TYPE_DEFAULT,
  FORMAT_TYPE_CHAR,
  FORMAT_TYPE_STR,
  FORMAT_TYPE_PTR,
  FORMAT_TYPE_PERCENT_CHAR,
  FORMAT_TYPE_INVALID,
  FORMAT_TYPE_FLOAT,
  FORMAT_TYPE_INTEGER,
  FORMAT_TYPE_INDEX
};

typedef struct {
  unsigned int type : 8;
  signed int field_width : 24;
  unsigned int flags : 16;
  unsigned int base : 8;
  signed int precision : 16;
} castom_printf_spec;

int castom_fmt_decode(const char *fmt, castom_printf_spec *spec);

int castom_vsnprintf(char *buf, castom_size_t size, const char *fmt,
                     va_list args);
void set_ast_print_parameter(castom_printf_spec *spec, va_list args);

int castom_atoi(const char **str);
void check_default_collision(castom_printf_spec *spec);
void def_constructor_pr_spec(castom_printf_spec *spec);
void cat_type_default_to_str(char **str, const char *end, const char *fmt,
                             int read);
void cat_type_char_to_str(char **str, char **end, castom_printf_spec *spec,
                          va_list args);
void cat_short_char(char **str, char **end, castom_printf_spec *spec,
                    va_list args);
void cat_wide_char(char **str, char **end, castom_printf_spec *spec,
                   va_list args);
void cat_symbol_in_str(char **str, const char *end, int width, char ch);
void cat_type_str_to_str(char **str, char **end, castom_printf_spec *spec,
                         va_list args);
void cat_short_str(char **str, char **end, castom_printf_spec *spec,
                   const char *s);
void cat_wide_str(char **str, char **end, castom_printf_spec *spec,
                  const wchar_t *s);
void cat_integer_to_str(char **str, char **end, castom_printf_spec *spec,
                        va_list args);
void transform_integer_10_to_str(char **str, char **end,
                                 castom_printf_spec *spec, va_list args);
void transform_integer_8_to_str(char **str, char **end,
                                castom_printf_spec *spec, va_list args);
void transform_integer_16_to_str(char **str, char **end,
                                 castom_printf_spec *spec, va_list args);
void get_integer_from_parameter(unsigned long *n, castom_printf_spec *spec,
                                va_list args);
void cat_unsigned_int_to_str(unsigned long value, char **string, int radix,
                             castom_printf_spec *spec);
void cat_scientific_float_to_str(char **str, char **end,
                                 castom_printf_spec *spec, va_list args);
void cat_ptr_int_to_str(char **str, char **end, castom_printf_spec *spec,
                        va_list args);
void cat_signed_int_to_str(long value, char **string, int radix,
                           castom_printf_spec *spec);
void cat_float_to_str(char **str, char **end, castom_printf_spec *spec,
                      va_list args);
void get_float_from_parameter(long double *n, castom_printf_spec *spec,
                              va_list args);
void cat_default_float_to_str(char **str, char **end, castom_printf_spec *spec,
                              va_list args);
void cat_scientific_float_to_str(char **str, char **end,
                                 castom_printf_spec *spec, va_list args);
void cat_shrepres_float_to_str(char **str, char **end, castom_printf_spec *spec,
                               va_list args);
void return_str_index_arg(const char *start, const char *current, va_list args);
void cat_index_to_str(char **str, char **end);
int count_digit_in_num(signed long n, int base);

char *gcvt(double x, int ndigit, char *buf);
char *ecvt(double x, int ndigit, int *__restrict__ decpt,
           int *__restrict__ sign);

#endif  // STRING_INCLUDE_CASTOM_SPRINTF_H_
