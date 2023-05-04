#include "castom_string.h"

void *castom_memchr(const void *str, int c, castom_size_t n) {
  void *ptr = CASTOM_NULL;
  if (str != CASTOM_NULL) {
    char *temp = (char *)str;
    int flag = 0;
    for (castom_size_t i = 0; (i < n || i < castom_strlen(temp)) && !flag; ++i) {
      if (*(temp + i) == (char)c) {
        ptr = (char *)str + i;
        flag = 1;
      }
    }
  }
  return ptr;
}

int castom_memcmp(const void *str1, const void *str2, castom_size_t n) {
  int result = 0;
  char *s1 = (char *)str1;
  char *s2 = (char *)str2;
  int flag = 0;
  for (castom_size_t i = 0; i < n && !flag; i++, s1++, s2++) {
    if (*s1 != *s2) {
      result = *s1 - *s2;
      flag = 1;
    }
  }
  return result;
}

void *castom_memcpy(void *dest, const void *src, castom_size_t n) {
  if (dest != CASTOM_NULL && src != CASTOM_NULL) {
    char *d = (char *)dest;
    char *s = (char *)src;
    for (castom_size_t i = 0; i < n; ++i) {
      *(d + i) = *(s + i);
    }
  }
  return dest;
}

void *castom_memmove(void *dest, const void *src, castom_size_t n) {
  char *temp = (char *)dest;
  char *head = (char *)src;
  for (castom_size_t i = 0; (i < n); i++, head++, temp++) {
    *temp = *head;
  }
  return dest;
}

void *castom_memset(void *str, int c, castom_size_t n) {
  char *temp = (char *)str;
  for (castom_size_t i = 0; i < n; i++, temp++) {
    *temp = c;
  }
  return str;
}

char *castom_strcat(char *dest, const char *src) {
  char *tmp = dest;
  if (dest != CASTOM_NULL) {
    while (*dest) {
      dest++;
    }
    while (*src != '\0') {
      *dest++ = *src++;
    }
    *dest = '\0';
  }
  return tmp;
}

char *castom_strncat(char *dest, const char *src, castom_size_t n) {
  char *head = dest + castom_strlen(dest);
  char *tail = (char *)src;
  for (castom_size_t i = 0; i < n && (*tail != '\0'); i++, head++, tail++) {
    *head = *tail;
  }
  *head = '\0';
  return dest;
}

char *castom_strchr(const char *str, int c) {
  char *res = CASTOM_NULL;
  int flag = 0;
  while (*str && !flag) {
    if (*str == c) {
      res = (char *)str;
      flag = 1;
    }
    str++;
  }
  return res;
}

int castom_strcmp(const char *str1, const char *str2) {
  while ((*str1 != '\0' && *str2 != '\0') && *str1 == *str2) {
    str1++;
    str2++;
  }
  return *str1 - *str2;
}

int castom_strncmp(const char *str1, const char *str2, castom_size_t n) {
  int result = 0;
  castom_size_t i = 0;
  int flag = 0;
  while (i < n && !flag) {
    if (*(str1 + i) != *(str2 + i)) {
      result = *(str1 + i) - *(str2 + i);
      flag = 1;
    }
    ++i;
  }
  return result;
}

char *castom_strcpy(char *dest, const char *src) {
  char *tmp = dest;
  if (dest != CASTOM_NULL) {
    while (*src != '\0') {
      *dest = *src;
      dest++;
      src++;
    }
    *dest = '\0';
  }
  return tmp;
}

char *castom_strncpy(char *dest, const char *src, castom_size_t n) {
  int flag = 0;
  castom_size_t i = 0;
  while (i < n) {
    if (*(src + i) != '\0') {
      *(dest + i) = *(src + i);
    } else {
      flag = 1;
    }
    if (flag) {
      *(dest + i) = '\0';
    }
    ++i;
  }
  return dest;
}

castom_size_t castom_strcspn(const char *str1, const char *str2) {
  castom_size_t count = 0;
  int flag = 0;
  for (castom_size_t i = 0; i < castom_strlen(str1) && !flag; i++) {
    for (castom_size_t j = 0; j < castom_strlen(str2) && !flag; j++) {
      if (str1[i] == str2[j]) {
        flag = 1;
      }
    }
    if (!flag) {
      count++;
    }
  }
  return count;
}

char *castom_strerror(int errnum) {
  CASTOM_DEF_ERR_STR;
  CASTOM_ERRORS;
  static char *result = CASTOM_NULL;
  CASTOM_GET_ERR_BY_NUMBER(result, errnum);
  return result;
}

castom_size_t castom_strlen(const char *str) {
  castom_size_t count = 0;
  if (str) {
    for (; *str; str++) {
      count++;
    }
  }
  return count;
}

char *castom_strpbrk(const char *str1, const char *str2) {
  castom_size_t count = 0;
  char *temp = (char *)str1;
  int flag = 0;
  for (castom_size_t i = 0; i < castom_strlen(str1) && !flag; i++) {
    for (castom_size_t j = 0; j < castom_strlen(str2) && !flag; j++) {
      if (str1[i] == str2[j]) {
        flag = 1;
      }
    }
    if (!flag) {
      count++;
    }
  }
  return (count == castom_strlen(str1)) ? CASTOM_NULL : (temp + count);
}

char *castom_strrchr(const char *str, int c) {
  char *result = CASTOM_NULL;
  if (str == CASTOM_NULL) {
    result = (char *)str;
  } else {
    int flag = 0;
    for (castom_size_t i = castom_strlen(str) - 1; (int)i >= 0 && !flag; i--) {
      if (str[i] == c) {
        result = (char *)str + i;
        flag = 1;
      } else {
        result = CASTOM_NULL;
      }
    }
  }
  return result;
}

castom_size_t castom_strspn(const char *str1, const char *str2) {
  castom_size_t count = 0;
  int flag = 1;
  for (castom_size_t i = 0; i < castom_strlen(str1) && flag; ++i) {
    flag = 0;
    for (castom_size_t j = 0; j < castom_strlen(str2) && !flag; ++j) {
      if (*(str1 + i) == *(str2 + j)) {
        ++count;
        flag = 1;
      }
    }
  }
  return count;
}

char *castom_strstr(const char *haystack, const char *needle) {
  char *pstr = CASTOM_NULL;
  if (castom_strlen(needle) == 0) {
    pstr = (char *)haystack;
  } else {
    castom_size_t count = 0;
    int flag = 0;
    for (castom_size_t i = 0; i < castom_strlen(haystack) && !flag; ++i) {
      int flag2 = 0;
      for (castom_size_t j = 0; j < castom_strlen(needle) && !flag2; ++j) {
        if (count != castom_strlen(needle)) {
          if (*(haystack + i + j) == *(needle + j)) {
            ++count;
            if (pstr == CASTOM_NULL) {
              pstr = (char *)(haystack + i);
            }
          } else {
            count = 0;
            pstr = CASTOM_NULL;
            flag2 = 1;
          }
        } else {
          flag = 1;
        }
      }
    }
  }
  return pstr;
}

char *castom_strtok(char *str, const char *delim) {
  static char *save;
  int ch, flag = 1;

  if (str == CASTOM_NULL)
    str = save;
  do {
    if ((ch = *str++) == '\0')
      flag = 0;
  } while (castom_strchr(delim, ch) && flag);
  if (flag) {
    --str;
    save = str + castom_strcspn(str, delim);
    if (*save != '\0') *save++ = '\0';
  }
  return flag ? str : CASTOM_NULL;
}

void *castom_to_upper(const char *str) {
  char *temp = CASTOM_NULL;
  if (str != CASTOM_NULL) {
    castom_size_t length_str = castom_strlen(str);
    temp = (char *)malloc((length_str + 1) * sizeof(char));
    castom_strcpy(temp, str);
    for (castom_size_t i = 0; i < length_str; ++i) {
      if (*(temp + i) >= 97 && *(temp + i) <= 122) {
        *(temp + i) -= 32;
      }
    }
  }
  return temp;
}

void *castom_to_lower(const char *str) {
  char *result = CASTOM_NULL;
  if (str != CASTOM_NULL) {
    castom_size_t n = castom_strlen(str);
    result = calloc(n + 1, sizeof(char));
    for (castom_size_t i = 0; i < n; i++) {
      if (str[i] > 64 && str[i] < 91) {
        result[i] = str[i] + 32;
      } else {
        result[i] = str[i];
      }
    }
    result[n] = '\0';
  }
  return result;
}

void *castom_insert(const char *src, const char *str, castom_size_t start_index) {
  char *result = CASTOM_NULL;
  if (start_index <= castom_strlen(src)) {
    char *temp = calloc((castom_strlen(src) - start_index + 1), sizeof(char));
    castom_size_t j = 0;
    for (castom_size_t i = start_index; i < castom_strlen(src); i++, j++) {
      temp[j] = src[i];
    }
    temp[j] = '\0';
    result = calloc(castom_strlen(str) + castom_strlen(src) + 1, sizeof(char));
    char *tt = result;
    for (castom_size_t i = 0; i < start_index; i++, tt++) {
      *tt = src[i];
    }
    for (j = 0; j < castom_strlen(str); j++, tt++) {
      *tt = str[j];
    }
    for (j = 0; j < castom_strlen(temp); j++, tt++) {
      *tt = temp[j];
    }
    if (temp != CASTOM_NULL) {
      free(temp);
    }
  }
  return result;
}

void *castom_trim(const char *src, const char *trim_chars) {
  char *temp = CASTOM_NULL;
  if (src != CASTOM_NULL) {
    castom_size_t length_str = castom_strlen(src);
    temp = (char *)malloc((length_str + 1) * sizeof(char));
    castom_strcpy(temp, src);
    if (trim_chars != CASTOM_NULL) {
      for (int i = castom_strlen(temp) - 1;
           i >= 0 && castom_strchr(trim_chars, *(temp + i)) != CASTOM_NULL; --i) {
        *(temp + i) = '\0';
      }
      while (*temp != '\0' && castom_strchr(trim_chars, *temp) != CASTOM_NULL) {
        castom_memmove(temp, temp + 1, castom_strlen(temp));
      }
    }
  }
  return temp;
}

int castom_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  int status = castom_vsnprintf(str, INT_MAX, format, args);

  va_end(args);
  return status;
}
