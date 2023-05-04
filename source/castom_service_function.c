#include "castom_sprintf.h"

int castom_atoi(const char **str) {
  int i = 0;
  do {
    i = i * 10 + *((*str)++) - '0';
  } while (isdigit(**str));
  return i;
}

void check_default_collision(castom_printf_spec *spec) {
  if (spec->flags & PLUS) spec->flags &= ~(SPACE);
  if (spec->type != FORMAT_TYPE_FLOAT)
    if (spec->precision != -1 || spec->flags & LEFT) spec->flags &= ~(ZEROPAD);
}

void set_ast_print_parameter(castom_printf_spec *spec, va_list args) {
  if (spec->flags & AST_FLAG_WIDTH) {
    if ((spec->field_width = va_arg(args, int)) < 0) {
      spec->field_width = -spec->field_width;
      spec->flags |= LEFT;
    }
  }
  if (spec->flags & AST_FLAG_PRECISION) {
    if ((spec->precision = va_arg(args, int)) < 0) {
      spec->precision = 0;
    }
  }
}

void cat_type_default_to_str(char **str, const char *end, const char *fmt,
                             int read) {
  if (*str < end) {
    if (read > end - *str) read = end - *str;
    castom_memcpy(*str, fmt, read);
    *str += read;
  }
}

void cat_type_char_to_str(char **str, char **end, castom_printf_spec *spec,
                          va_list args) {
  if (spec->flags & LONG_FLAG_INT) {
    cat_wide_char(str, end, spec, args);
  } else {
    cat_short_char(str, end, spec, args);
  }
}

void cat_short_char(char **str, char **end, castom_printf_spec *spec,
                    va_list args) {
  if (!(spec->flags & LEFT)) {
    cat_symbol_in_str(str, *end, spec->field_width - 1, ' ');
    spec->field_width = 0;
  }

  char c = (unsigned char)va_arg(args, int);

  if (*str < *end) **str = c;
  ++*str;

  cat_symbol_in_str(str, *end, spec->field_width - 1, ' ');
}

void cat_wide_char(char **str, char **end, castom_printf_spec *spec,
                   va_list args) {
  if (!(spec->flags & LEFT)) {
    cat_symbol_in_str(str, *end, spec->field_width - 1, ' ');
    spec->field_width = 0;
  }

  castom_size_t read = wctomb(*str, va_arg(args, wchar_t));

  *str += read;

  cat_symbol_in_str(str, *end, spec->field_width - read, ' ');
}

void cat_symbol_in_str(char **str, const char *end, int width, char ch) {
  while (width-- > 0) {
    if (*str < end) **str = ch;
    ++*str;
  }
}

void cat_type_str_to_str(char **str, char **end, castom_printf_spec *spec,
                         va_list args) {
  if (spec->flags & LONG_FLAG_INT) {
    cat_wide_str(str, end, spec, va_arg(args, wchar_t *));
  } else {
    cat_short_str(str, end, spec, va_arg(args, char *));
  }
}

void cat_short_str(char **str, char **end, castom_printf_spec *spec,
                   const char *s) {
  int lim = castom_strlen(s);
  if (spec->precision >= 0 && spec->precision < lim) lim = spec->precision;

  if (lim > *end - *str) {
    lim = *end - *str;
    spec->field_width = lim;
  }

  if (!(spec->flags & LEFT)) {
    cat_symbol_in_str(str, *end, spec->field_width - lim, ' ');
    spec->field_width = 0;
  }

  cat_type_default_to_str(str, *end, s, lim);

  cat_symbol_in_str(str, *end, spec->field_width - lim, ' ');
}

void cat_wide_str(char **str, char **end, castom_printf_spec *spec,
                  const wchar_t *s) {
  int lim = (int)wcstombs(*str, s, INT_MAX);
  if (spec->precision >= 0 && spec->precision < lim) lim = spec->precision;

  if (lim > *end - *str) {
    lim = *end - *str;
    spec->field_width = lim;
  }

  if (!(spec->flags & LEFT)) {
    cat_symbol_in_str(str, *end, spec->field_width - lim, ' ');
    spec->field_width = 0;
  }

  int write = lim;
  while (*s && write--) {
    *str += wctomb(*str, *s);
    ++s;
  }

  cat_symbol_in_str(str, *end, spec->field_width - lim, ' ');
}

void cat_integer_to_str(char **str, char **end, castom_printf_spec *spec,
                        va_list args) {
  if (spec->base == 10)
    transform_integer_10_to_str(str, end, spec, args);
  else if (spec->base == 8)
    transform_integer_8_to_str(str, end, spec, args);
  else if (spec->base == 16)
    transform_integer_16_to_str(str, end, spec, args);
}

void transform_integer_10_to_str(char **str, char **end,
                                 castom_printf_spec *spec, va_list args) {
  unsigned long num;
  get_integer_from_parameter(&num, spec, args);

  int lim = count_digit_in_num((signed long)num, 10);

  if (spec->flags & PLUS || spec->flags & SPACE || (signed long)num < 0) ++lim;

  if (lim > *end - *str) {
    lim = *end - *str;
    spec->field_width = lim;
  }

  if ((signed long)num < 0) spec->flags &= ~(PLUS | SPACE);

  if (spec->precision < lim && spec->precision >= 0)
    spec->precision = spec->field_width;
  else if (spec->precision < 0)
    spec->precision = lim;

  if (!(spec->flags & LEFT) && !(spec->flags & ZEROPAD))
    cat_symbol_in_str(str, *end, spec->field_width - spec->precision, ' ');

  if (spec->flags & PLUS) {
    spec->flags &= ~(SPACE);
    cat_symbol_in_str(str, *end, 1, '+');
  } else if (spec->flags & SPACE) {
    cat_symbol_in_str(str, *end, 1, ' ');
  } else if ((signed long)num < 0) {
    cat_symbol_in_str(str, *end, 1, '-');
    num = -num;
  }

  if (spec->flags & ZEROPAD)
    cat_symbol_in_str(str, *end, spec->field_width - lim, '0');
  else if (spec->precision - lim > 0)
    cat_symbol_in_str(str, *end, spec->precision - lim, '0');

  if (spec->flags & SIGN) {
    cat_signed_int_to_str((signed long)num, str, 10, spec);
  } else {
    cat_unsigned_int_to_str(num, str, 10, spec);
  }

  if (spec->flags & LEFT)
    cat_symbol_in_str(str, *end, spec->field_width - spec->precision, ' ');
}

void get_integer_from_parameter(unsigned long *n, castom_printf_spec *spec,
                                va_list args) {
  if (spec->base == 8 || spec->base == 16) {
    *n = (unsigned long)va_arg(args, long int);
  } else if (spec->flags & SIGN) {
    if (spec->flags & LONG_FLAG_INT)
      *n = (unsigned long)va_arg(args, long int);
    else
      *n = (unsigned long)va_arg(args, int);
  } else {
    if (spec->flags & LONG_FLAG_INT)
      *n = (unsigned long)va_arg(args, unsigned long);
    else
      *n = (unsigned long)va_arg(args, unsigned);
  }
}

#define NUMBER_OF_DIGITS 32

void cat_unsigned_int_to_str(unsigned long value, char **string, int radix,
                             castom_printf_spec *spec) {
  unsigned char index;
  char buffer[NUMBER_OF_DIGITS];

  index = NUMBER_OF_DIGITS;

  do {
    buffer[--index] = '0' + (value % radix);
    if (buffer[index] > '9') {
      if (spec->flags & SMALL)
        buffer[index] += 'a' - ':';
      else
        buffer[index] += 'A' - ':';
    }
    value /= radix;
  } while (value != 0);

  do {
    **string = buffer[index++];
    ++*string;
  } while (index < NUMBER_OF_DIGITS);
}

void cat_signed_int_to_str(long value, char **string, int radix,
                           castom_printf_spec *spec) {
  if (value < 0 && radix == 10) {
    cat_unsigned_int_to_str(-value, string, radix, spec);
  } else {
    cat_unsigned_int_to_str(value, string, radix, spec);
  }
}

void transform_integer_8_to_str(char **str, char **end,
                                castom_printf_spec *spec, va_list args) {
  unsigned long num;
  get_integer_from_parameter(&num, spec, args);

  int lim = count_digit_in_num(num, 8);

  if (spec->flags & SPECIAL) ++lim;

  if (spec->precision < lim && spec->precision >= 0)
    spec->precision = spec->field_width;
  else if (spec->precision < 0)
    spec->precision = lim;

  if (!(spec->flags & LEFT) && !(spec->flags & ZEROPAD))
    cat_symbol_in_str(str, *end, spec->field_width - spec->precision, ' ');

  if (spec->flags & SPECIAL) cat_symbol_in_str(str, *end, 1, '0');

  if (spec->flags & ZEROPAD)
    cat_symbol_in_str(str, *end, spec->field_width - lim, '0');
  else if (spec->precision - lim > 0)
    cat_symbol_in_str(str, *end, spec->precision - lim, '0');

  cat_signed_int_to_str((signed long)num, str, 8, spec);

  if (spec->flags & LEFT)
    cat_symbol_in_str(str, *end, spec->field_width - spec->precision, ' ');
}

int count_digit_in_num(signed long n, int base) {
  int res = 0;
  do {
    ++res;
  } while (n /= base);
  return res;
}

void transform_integer_16_to_str(char **str, char **end,
                                 castom_printf_spec *spec, va_list args) {
  unsigned long num;
  get_integer_from_parameter(&num, spec, args);

  int lim = count_digit_in_num(num, 16);

  if (spec->flags & SPECIAL) spec->field_width -= 2;

  if (spec->precision < lim && spec->precision > 0)
    spec->precision = spec->field_width;
  else if (spec->precision <= 0)
    spec->precision = lim;

  if (!(spec->flags & LEFT) && !(spec->flags & ZEROPAD))
    cat_symbol_in_str(str, *end, spec->field_width - spec->precision, ' ');

  if (spec->flags & SPECIAL) {
    cat_symbol_in_str(str, *end, 1, '0');
    if (spec->flags & SMALL)
      cat_symbol_in_str(str, *end, 1, 'x');
    else
      cat_symbol_in_str(str, *end, 1, 'X');
  }

  if (spec->flags & ZEROPAD)
    cat_symbol_in_str(str, *end, spec->field_width - lim, '0');
  else if (spec->precision - lim > 0)
    cat_symbol_in_str(str, *end, spec->precision - lim, '0');

  cat_signed_int_to_str((signed long)num, str, 16, spec);

  if (spec->flags & LEFT)
    cat_symbol_in_str(str, *end, spec->field_width - spec->precision, ' ');
}

void cat_ptr_int_to_str(char **str, char **end, castom_printf_spec *spec,
                        va_list args) {
  unsigned long long num = va_arg(args, long long);

  int lim = count_digit_in_num(num, 16);

  spec->field_width -= 2;

  if (spec->precision < lim && spec->precision > 0)
    spec->precision = spec->field_width;
  else if (spec->precision <= 0)
    spec->precision = lim;

  if (!(spec->flags & LEFT) && !(spec->flags & ZEROPAD))
    cat_symbol_in_str(str, *end, spec->field_width - spec->precision, ' ');

  cat_symbol_in_str(str, *end, 1, '0');
  cat_symbol_in_str(str, *end, 1, 'x');

  if (spec->flags & ZEROPAD)
    cat_symbol_in_str(str, *end, spec->field_width - lim, '0');
  else if (spec->precision - lim > 0)
    cat_symbol_in_str(str, *end, spec->precision - lim, '0');

  cat_unsigned_int_to_str(num, str, 16, spec);

  if (spec->flags & LEFT)
    cat_symbol_in_str(str, *end, spec->field_width - spec->precision, ' ');
}

void cat_float_to_str(char **str, char **end, castom_printf_spec *spec,
                      va_list args) {
  if (spec->flags & SCIENTIFIC_NOTE)
    cat_scientific_float_to_str(str, end, spec, args);
  else if (spec->flags & SHORT_REPRES)
    cat_shrepres_float_to_str(str, end, spec, args);
  else
    cat_default_float_to_str(str, end, spec, args);
}

void get_float_from_parameter(long double *n, castom_printf_spec *spec,
                              va_list args) {
  if (spec->flags & LONG_FLAG_FLOAT)
    *n = (long double)va_arg(args, double long);
  else
    *n = (long double)va_arg(args, double);
}

void cat_default_float_to_str(char **str, char **end, castom_printf_spec *spec,
                              va_list args) {
  long double num;
  get_float_from_parameter(&num, spec, args);

  int lim = count_digit_in_num((signed long)num, 10);

  if (spec->precision < 0) spec->precision = 6;
  if (spec->precision > 0) lim += spec->precision + 1;

  if (spec->flags & PLUS || spec->flags & SPACE || (double)num < 0) ++lim;

  if ((double)num < 0) spec->flags &= ~(PLUS | SPACE);

  if (!(spec->flags & LEFT) && !(spec->flags & ZEROPAD))
    cat_symbol_in_str(str, *end, spec->field_width - lim, ' ');

  if (spec->flags & PLUS) {
    spec->flags &= ~(SPACE);
    cat_symbol_in_str(str, *end, 1, '+');
  } else if (spec->flags & SPACE) {
    cat_symbol_in_str(str, *end, 1, ' ');
  } else if ((double)num < 0) {
    cat_symbol_in_str(str, *end, 1, '-');
    num = -num;
  }

  if (spec->flags & ZEROPAD)
    cat_symbol_in_str(str, *end, spec->field_width - lim, '0');

  double round = 5;
  int t_prec = spec->precision;

  while (t_prec-- >= 0) round /= 10;

  if ((num >= 0.5 && ((long)num % 2 && spec->precision == 0)) ||
      (num >= 0.5 && spec->precision != 0) ||
      ((num - (long)num > 0.5) && (long)num % 2 == 0 && spec->precision == 0))
    num += round;

  cat_unsigned_int_to_str((unsigned long)num, str, 10, spec);
  if (spec->precision > 0 || spec->flags & SPECIAL) {
    cat_symbol_in_str(str, *end, 1, '.');
    while (spec->precision-- > 0) {
      num -= (unsigned long)num;
      num *= 10;
      cat_symbol_in_str(str, *end, 1, (unsigned long)num % 10 + '0');
    }
  }

  if (spec->flags & LEFT)
    cat_symbol_in_str(str, *end, spec->field_width - lim, ' ');
}

void cat_scientific_float_to_str(char **str, char **end,
                                 castom_printf_spec *spec, va_list args) {
  long double num;
  get_float_from_parameter(&num, spec, args);

  if (spec->precision < 0) spec->precision = 6;

  int lim = spec->precision + 1;

  if (spec->flags & PLUS || spec->flags & SPACE || (double)num < 0) ++lim;

  if ((double)num < 0) spec->flags &= ~(PLUS | SPACE);

  int decimal, sign;
  char *buffer = ecvt((double)num, spec->precision + 1, &decimal, &sign);

  int l_dec_num = count_digit_in_num((signed long)decimal, 10);

  lim += (5 + (l_dec_num > 2 ? l_dec_num - 2 : 0));

  if (!(spec->flags & LEFT) && !(spec->flags & ZEROPAD))
    cat_symbol_in_str(str, *end, spec->field_width - lim, ' ');

  if (spec->flags & PLUS) {
    spec->flags &= ~(SPACE);
    cat_symbol_in_str(str, *end, 1, '+');
  } else if (spec->flags & SPACE) {
    cat_symbol_in_str(str, *end, 1, ' ');
  } else if ((double)num < 0) {
    cat_symbol_in_str(str, *end, 1, '-');
    num = -num;
  }

  if (spec->flags & ZEROPAD && !(spec->flags & LEFT))
    cat_symbol_in_str(str, *end, spec->field_width - lim, '0');

  cat_symbol_in_str(str, *end, 1, buffer[0]);

  if (spec->precision > 0) {
    cat_symbol_in_str(str, *end, 1, '.');
    cat_type_default_to_str(str, *end, &buffer[1], spec->precision);
  }
  if (spec->flags & SMALL)
    cat_symbol_in_str(str, *end, 1, 'e');
  else
    cat_symbol_in_str(str, *end, 1, 'E');

  if (decimal >= 0)
    cat_symbol_in_str(str, *end, 1, '+');
  else
    cat_symbol_in_str(str, *end, 1, '-');

  if (decimal < 10) cat_symbol_in_str(str, *end, 1, '0');

  cat_signed_int_to_str((signed long)decimal - 1, str, 10, spec);

  if (spec->flags & LEFT)
    cat_symbol_in_str(str, *end, spec->field_width - lim, ' ');
}

void cat_shrepres_float_to_str(char **str, char **end, castom_printf_spec *spec,
                               va_list args) {
  long double num;
  get_float_from_parameter(&num, spec, args);

  if (spec->precision < 0) spec->precision = 6;

  if (num < 10 || spec->precision == 0) spec->precision++;

  char buffer[128];
  gcvt((double)num, spec->precision, buffer);

  int lim = castom_strlen(buffer);

  if ((double)num < 0) spec->flags &= ~(PLUS | SPACE);

  if (!(spec->flags & LEFT) && !(spec->flags & ZEROPAD))
    cat_symbol_in_str(str, *end, spec->field_width - lim, ' ');

  if (spec->flags & PLUS && !(spec->flags & LEFT)) {
    spec->flags &= ~(SPACE);
    cat_symbol_in_str(str, *end, 1, '+');
  } else if (spec->flags & SPACE) {
    cat_symbol_in_str(str, *end, 1, ' ');
  }

  if ((double)num < 0) {
    cat_symbol_in_str(str, *end, 1, '-');
    castom_memcpy(&buffer[0], &buffer[1], castom_strlen(buffer));
  }

  if (spec->flags & ZEROPAD && !(spec->flags & LEFT))
    cat_symbol_in_str(str, *end, spec->field_width - lim, '0');

  for (int i = 0; buffer[i]; ++i) {
    if (num > 9 && spec->precision < 2 && i == 1) ++i;
    cat_symbol_in_str(str, *end, 1, buffer[i]);
  }

  if (spec->flags & LEFT)
    cat_symbol_in_str(str, *end, spec->field_width - lim, ' ');
}

void return_str_index_arg(const char *start, const char *current,
                          va_list args) {
  int *index = va_arg(args, int *);
  *index = (current - start);
}
