#include "castom_sprintf.h"

int castom_fmt_decode(const char *fmt, castom_printf_spec *spec) {
  const char *start = fmt;

  def_constructor_pr_spec(spec);

  while (*fmt != '%' && *fmt) ++fmt;

  if (fmt != start || !*fmt) return fmt - start;

  ++fmt;

  bool found = true;
  while (found) {
    switch (*fmt) {
      case '-':
        spec->flags |= LEFT;
        ++fmt;
        break;
      case '+':
        spec->flags |= PLUS;
        ++fmt;
        break;
      case ' ':
        spec->flags |= SPACE;
        ++fmt;
        break;
      case '#':
        spec->flags |= SPECIAL;
        ++fmt;
        break;
      case '0':
        spec->flags |= ZEROPAD;
        ++fmt;
        break;
      default:
        found = false;
    }
  }

  if (isdigit(*fmt)) {
    spec->field_width = castom_atoi(&fmt);
  } else if (*fmt == '*') {
    spec->flags |= AST_FLAG_WIDTH;
    ++fmt;
  }

  if (*fmt == '.') {
    ++fmt;
    spec->precision = 0;
    if (isdigit(*fmt)) {
      spec->precision = castom_atoi(&fmt);
    } else if (*fmt == '*') {
      spec->flags |= AST_FLAG_PRECISION;
      ++fmt;
    }
  }

  switch (*fmt) {
    case 'h':
      spec->flags |= SHORT_FLAG_INT;
      ++fmt;
      break;
    case 'l':
      spec->flags |= LONG_FLAG_INT;
      ++fmt;
      break;
    case 'L':
      spec->flags |= LONG_FLAG_FLOAT;
      ++fmt;
      break;
  }

  switch (*fmt) {
    case 'c':
      spec->type = FORMAT_TYPE_CHAR;
      break;
    case 's':
      spec->type = FORMAT_TYPE_STR;
      break;
    case '%':
      spec->type = FORMAT_TYPE_PERCENT_CHAR;
      break;
    case 'f':
      spec->type = FORMAT_TYPE_FLOAT;
      break;
    case 'g':
    case 'G':
      spec->type = FORMAT_TYPE_FLOAT;
      spec->flags |= SHORT_REPRES;
      break;
    case 'e':
      spec->flags |= SMALL;
      spec->type = FORMAT_TYPE_FLOAT;
      spec->flags |= SCIENTIFIC_NOTE;
      break;
    case 'E':
      spec->type = FORMAT_TYPE_FLOAT;
      spec->flags |= SCIENTIFIC_NOTE;
      break;
    case 'o':
      spec->type = FORMAT_TYPE_INTEGER;
      spec->base = 8;
      break;
    case 'x':
      spec->flags |= SMALL;
      spec->type = FORMAT_TYPE_INTEGER;
      spec->base = 16;
      break;
    case 'X':
      spec->type = FORMAT_TYPE_INTEGER;
      spec->base = 16;
      break;
    case 'p':
      spec->type = FORMAT_TYPE_PTR;
      spec->flags |= SMALL;
      spec->base = 16;
      break;
    case 'i':
      spec->flags |= MULTY_BASE;
      spec->type = FORMAT_TYPE_INTEGER;
      spec->flags |= SIGN;
      break;
    case 'd':
      spec->type = FORMAT_TYPE_INTEGER;
      spec->flags |= SIGN;
      break;
    case 'u':
      spec->type = FORMAT_TYPE_INTEGER;
      break;
    case 'n':
      spec->type = FORMAT_TYPE_INDEX;
      break;
    default:
      spec->type = FORMAT_TYPE_INVALID;
  }

  return ++fmt - start;
}

void def_constructor_pr_spec(castom_printf_spec *spec) {
  spec->type = FORMAT_TYPE_DEFAULT;
  spec->flags = 0;
  spec->field_width = -1;
  spec->precision = -1;
  spec->base = 10;
}
