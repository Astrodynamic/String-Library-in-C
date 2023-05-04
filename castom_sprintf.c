#include "castom_sprintf.h"

int castom_vsnprintf(char *buf, castom_size_t size, const char *fmt, va_list args) {
  if (size > INT_MAX) return 0;

  char *str = buf;
  char *end = (buf + size);

  if (end < buf) {
    end = ((void *)-1);
    size = end - buf;
  }

  castom_printf_spec spec = {0};

  while (*fmt) {
    const char *prev_fmt = fmt;
    int read = castom_fmt_decode(fmt, &spec);

    fmt += read;

    set_ast_print_parameter(&spec, args);
    check_default_collision(&spec);

    switch (spec.type) {
      case FORMAT_TYPE_DEFAULT:
        cat_type_default_to_str(&str, end, prev_fmt, read);
        break;
      case FORMAT_TYPE_CHAR:
        cat_type_char_to_str(&str, &end, &spec, args);
        break;
      case FORMAT_TYPE_STR:
        cat_type_str_to_str(&str, &end, &spec, args);
        break;
      case FORMAT_TYPE_PERCENT_CHAR:
        cat_symbol_in_str(&str, end, 1, '%');
        break;
      case FORMAT_TYPE_INTEGER:
        cat_integer_to_str(&str, &end, &spec, args);
        break;
      case FORMAT_TYPE_INDEX:
        return_str_index_arg(buf, str, args);
        break;
      case FORMAT_TYPE_PTR:
        cat_ptr_int_to_str(&str, &end, &spec, args);
        break;
      case FORMAT_TYPE_FLOAT:
        cat_float_to_str(&str, &end, &spec, args);
        break;
      case FORMAT_TYPE_INVALID:
        return -1;
    }
  }

  if (size > 0) {
    if (str < end)
      *str = '\0';
    else
      end[-1] = '\0';
  }

  return str - buf;
}
