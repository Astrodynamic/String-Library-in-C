#include "castom_strerror.h"

int castom_digits_count(int digit) {
  int result = 0;
  while (digit) {
    digit /= 10;
    result++;
  }
  return result;
}

int castom_10_deg(int deg) {
  int result = 1;
  for (int i = 1; i < deg; i++) result *= 10;
  return result;
}

void castom_strpsh(char *str, char c) {
  while (*str) str++;
  *str = c;
  *(++str) = '\0';
}

void castom_add_digit_to_str(char *str, int digit) {
  while (*str != ' ') str++;
  ++str;
  while (*str != ' ') str++;
  *(++str) = '\0';
  int deg = castom_10_deg(castom_digits_count(digit));
  if (digit < 0) {
    castom_strpsh(str, '-');
    digit *= -1;
  }
  while (deg) {
    castom_strpsh(str, (char)(digit / deg) + '0');
    digit %= deg;
    deg /= 10;
  }
}
