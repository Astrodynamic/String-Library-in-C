# String library

This is a C library that implements various operations on strings, including copying, concatenation, tokenization, and searching. The library is developed in C language of C11 standard using gcc compiler and follows the POSIX.1-2017 standard. 

## Build

To build the library, run the following command:

```
make
```

This command will run cmake to generate the build files and then build the library. The library will be located in the `lib` folder.

To clean the build files and the library, run:

```
make clean
```

To rebuild the library, run:

```
make rebuild
```

## Usage

To use the library in your project, add the following include statement to your source code:

```
#include <castom_string.h>
```

Then link your project against the library, using the following flag:

```
-L./lib -lString
```

The custom_string.h library in C is a library that provides a set of functions for working with strings. Below are a few examples of using the functions and types defined in this library:

1. Function `custom_strlen(const char *str)` - calculates the length of the string `str`, not including the terminating null character. Usage example:

```c
#include <stdio.h>
#include <castom_string.h>

int main() {
    char str[] = "Hello, world!";
    castom_printf("Length of string: %ld", castom_strlen(str)); // Output: Length of string: 13
    return 0;
}
```

2. Function `custom_strcpy(char *dest, const char *src)` - copies the string `src` to the string `dest`. Usage example:

```c
#include <stdio.h>
#include <castom_string.h>

int main() {
    char src[] = "Hello, world!";
    char dest[50];
    castom_strcpy(dest, src);
    castom_printf("Copied string: %s", dest); // Output: Copied string: Hello, world!
    return 0;
}
```

3. Function `custom_strcat(char *dest, const char *src)` - adds the string `src` to the end of the string `dest`. Usage example:

```c
#include <stdio.h>
#include <castom_string.h>

int main() {
    char str1[50] = "Hello, ";
    char str2[] = "world!";
    castom_strcat(str1, str2);
    castom_printf("Concatenated string: %s", str1); // Output: Concatenated string: Hello, world!
    return 0;
}
```

4. Function `custom_strcmp(const char *str1, const char *str2)` - compares two strings `str1` and `str2`. Usage example:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "Hello, world!";
    char str2[] = "Hello, everyone!";
    int result = castom_strcmp(str1, str2);
    if (result == 0) {
        castom_printf("Strings are equal");
    } else {
        castom_printf("Strings are not equal");
    }
    // Output: Strings are not equal
    return 0;
}
```

5. Function `custom_strstr(const char *haystack, const char *needle)` - looks for the first occurrence of the substring `needle` in the string `haystack`. Usage example:

```c
#include <stdio.h>
#include <castom_string.h>

int main() {
    char haystack[] = "Hello, world!";
    char needle[] = "world";
    char *result = castom_strstr(haystack, needle);
    if (result == NULL) {
        castom_printf("Substring not found");
    } else {
        castom_printf("Substring found at position %ld", result - haystack); // Output: Substring found at position 7
    }
    return 0;
}
```

### castom_string.h Types

| No. | Variable | Description |
| ------ | ------ | ------ |
| 1 | castom_size_t | This is the unsigned integral type and is the result of the sizeof keyword. |
	
### castom_string.h Macro

| No. | Macro | Description |
| ------ | ------ | ------ |
| 1 | NULL | This macro is the value of a null pointer constant. |

### castom_string.h Functions

| No. | Function | Description |
| ------ | ------ | ------ |
| 1 | void *castom_memchr(const void *str, int c, castom_size_t n) | Searches for the first occurrence of the character c (an unsigned char) in the first n bytes of the string pointed to, by the argument str. |
| 2 | int castom_memcmp(const void *str1, const void *str2, castom_size_t n) | Compares the first n bytes of str1 and str2. |
| 3 | void *castom_memcpy(void *dest, const void *src, castom_size_t n) | Copies n characters from src to dest. |
| 4 | void *castom_memmove(void *dest, const void *src, castom_size_t n) | Another function to copy n characters from str2 to str1. |
| 5 | void *castom_memset(void *str, int c, castom_size_t n) | Copies the character c (an unsigned char) to the first n characters of the string pointed to, by the argument str. |
| 6 | char *castom_strcat(char *dest, const char *src) | Appends the string pointed to, by src to the end of the string pointed to by dest. |
| 7 | char *castom_strncat(char *dest, const char *src, castom_size_t n) | Appends the string pointed to, by src to the end of the string pointed to, by dest up to n characters long. |
| 8	| char *castom_strchr(const char *str, int c) | Searches for the first occurrence of the character c (an unsigned char) in the string pointed to, by the argument str. |
| 9 | int castom_strcmp(const char *str1, const char *str2) | Compares the string pointed to, by str1 to the string pointed to by str2. |
| 10 | int castom_strncmp(const char *str1, const char *str2, castom_size_t n) | Compares at most the first n bytes of str1 and str2. |
| 11 | char *castom_strcpy(char *dest, const char *src) | Copies the string pointed to, by src to dest. |
| 12 | char *castom_strncpy(char *dest, const char *src, castom_size_t n) | Copies up to n characters from the string pointed to, by src to dest. |
| 13 | castom_size_t castom_strcspn(const char *str1, const char *str2) | Calculates the length of the initial segment of str1 which consists entirely of characters not in str2. |
| 14 | char *castom_strerror(int errnum) | Searches an internal array for the error number errnum and returns a pointer to an error message string. You need to declare macros containing arrays of error messages for mac and linux operating systems. Error descriptions are available in the original library. Checking the current OS is carried out using directives. |
| 15 | castom_size_t strlen(const char *str) | Computes the length of the string str up to but not including the terminating null character. |
| 16 | char *castom_strpbrk(const char *str1, const char *str2) | Finds the first character in the string str1 that matches any character specified in str2. |
| 17 | char *castom_strrchr(const char *str, int c) | Searches for the last occurrence of the character c (an unsigned char) in the string pointed to by the argument str. |
| 18 | castom_size_t castom_strspn(const char *str1, const char *str2) | Calculates the length of the initial segment of str1 which consists entirely of characters in str2. |
| 19 | char *castom_strstr(const char *haystack, const char *needle) | Finds the first occurrence of the entire string needle (not including the terminating null character) which appears in the string haystack. |
| 20 | char *castom_strtok(char *str, const char *delim) | Breaks string str into a series of tokens separated by delim. |

### castom_sprintf and castom_sscanf

- int castom_sscanf(const char *str, const char *format, ...) - reads formatted input from a string.
- int castom_sprintf(char *str, const char *format, ...) - sends formatted output to a string pointed to, by str.

where:
- str − This is the C string that the function processes as its source to retrieve the data;
- format − This is the C string that contains one or more of the following items: Whitespace character, Non-whitespace character and Format specifiers. A format specifier for print functions follows this prototype: %[flags][width][.precision][length]specifier. A format specifier for scan functions follows this prototype: %[*][width][length]specifier.

### castom_sprintf And castom_sscanf Specifiers

| No. | Specifier | castom_sprintf output | castom_sscanf output |
| --- | --- | --- | --- |
| 1 | c | Character | Character |
| 2 | d | Signed decimal integer | Signed decimal integer |
| 3 | i | Signed decimal integer | Signed integer (may be decimal, octal or hexadecimal) |
| 4 | e | Scientific notation (mantissa/exponent) using e character (the output of the numbers must match up to e-6) | Decimal floating point or scientific notation (mantissa/exponent) |
| 5 | E | Scientific notation (mantissa/exponent) using E character | Decimal floating point or scientific notation (mantissa/exponent) |
| 6 | f | Decimal floating point | Decimal floating point or scientific notation (mantissa/exponent) |
| 7 | g | Uses the shortest representation of decimal floating point | Decimal floating point or scientific notation (mantissa/exponent) |
| 8 | G | Uses the shortest representation of decimal floating point | Decimal floating point or scientific notation (mantissa/exponent) |
| 9 | o | Unsigned octal | Unsigned octal |
| 10 | s | String of characters | String of characters |
| 11 | u | Unsigned decimal integer | Unsigned decimal integer |
| 12 | x | Unsigned hexadecimal integer | Unsigned hexadecimal integer (any letters) |
| 13 | X | Unsigned hexadecimal integer (capital letters) | Unsigned hexadecimal integer (any letters) |
| 14 | p | Pointer address | Pointer address |
| 15 | n | Number of characters printed until %n occurs | Number of characters scanned until %n occurs |
| 16 | % | Character % | Character % |

### castom_sprintf Flags

| No. | Flags | Description |
| --- | --- | --- |
| 1 | - | Left-justify within the given field width; Right justification is the default (see width sub-specifier). |
| 2 | + | Forces to precede the result with a plus or minus sign (+ or -) even for positive numbers. By default, only negative numbers are preceded with a -ve sign. |
| 3 | (space) | If no sign is going to be written, a blank space is inserted before the value. |
| 4 | # | Used with o, x or X specifiers the value is preceded with 0, 0x or 0X respectively for values different than zero. Used with e, E and f, it forces the written output to contain a decimal point even if no digits would follow. By default, if no digits follow, no decimal point is written. Used with g or G the result is the same as with e or E but trailing zeros are not removed. |
| 5 | 0 | Left-pads the number with zeroes (0) instead of spaces, where padding is specified (see width sub-specifier). |

### castom_sprintf And castom_sscanf Width Description

| No. |	Width | Description |
| --- | --- | --- |
| 1	| (number) | Minimum number of characters to be printed. If the value to be printed is shorter than this number, the result is padded with blank spaces. The value is not truncated even if the result is larger. |
| 2 | * | In castom_sprintf the * sign means, that the width is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted. In castom_sscanf the * sign placed after % and before the format specifier reads data of the specified type, but suppresses their assignment. |

### castom_sprintf Precision Description

| No. |	.precision | Description |
| --- | --- | --- |
| 1	| .number | For integer specifiers (d, i, o, u, x, X) − precision specifies the minimum number of digits to be written. If the value to be written is shorter than this number, the result is padded with leading zeros. The value is not truncated even if the result is longer. A precision of 0 means that no character is written for the value 0. For e, E and f specifiers − this is the number of digits to be printed after the decimal point. For g and G specifiers − This is the maximum number of significant digits to be printed. For s − this is the maximum number of characters to be printed. By default all characters are printed until the ending null character is encountered. For c type − it has no effect. When no precision is specified for specifiers e, E, f, g and G, the default one is 6. When no precision is specified for all other kind of specifiers, the default is 1. If the period is specified without an explicit value for precision, 0 is assumed. |
| 2	| .* | The precision is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted. |

### castom_sprintf And castom_sscanf Length Description

| No. |	Length | Description |
| --- | --- | --- |
| 1 | h | The argument is interpreted as a short int or unsigned short int (only applies to integer specifiers: i, d, o, u, x and X). |
| 2 | l | The argument is interpreted as a long int or unsigned long int for integer specifiers (i, d, o, u, x and X), and as a wide character or wide character string for specifiers c and s. |
| 3 | L | The argument is interpreted as a long double (only applies to floating point specifiers − e, E, f, g and G). |

### Special string processing functions (from the String class in C#)

| No. | Function | Description |
| ------ | ------ | ------ |
| 1 | void *to_upper(const char *str) | Returns a copy of string (str) converted to uppercase. In case of any error, return NULL |
| 2 | void *to_lower(const char *str) | Returns a copy of string (str) converted to lowercase. In case of any error, return NULL |
| 3 | void *insert(const char *src, const char *str, castom_size_t start_index) | Returns a new string in which a specified string (str) is inserted at a specified index position (start_index) in the given string (src). In case of any error, return NULL |
| 4 | void *trim(const char *src, const char *trim_chars) | Returns a new string in which all leading and trailing occurrences of a set of specified characters (trim_chars) from the given string (src) are removed. In case of any error, return NULL |



## Dependencies

The library has the following dependencies:

- gcc compiler
- cmake
- Check library (for unit testing)

## Development

The library is located in the `src` folder on the develop branch. The code includes headers, a makefile, and the library itself. The library is a static library, with the header file `castom_string.h`.

The library's functions are implemented in accordance with the principles of structured programming, avoiding code duplication.

The Makefile provides targets:
- for building the library and tests (`all`)
- cleaning the build files and the library (`clean`)
- rebuilding the library (`rebuild`)
- running the cppcheck and clang-format tools (`cppcheck` and `clang-format`, respectively).

## License

This library is released under the MIT license. Please see the [LICENSE](LICENSE) file for more information.
