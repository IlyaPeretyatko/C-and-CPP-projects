#include "./s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *rez = S21_NULL;
  int breakFlag = 0;
  for (s21_size_t i = 0; i < n && breakFlag == 0; i++) {
    if (*((char *)str + i) == c) {
      rez = (char *)str + i;
      breakFlag = 1;
    }
  }
  return rez;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *s1 = (unsigned char *)str1;
  unsigned char *s2 = (unsigned char *)str2;
  int rez = 0;
  for (s21_size_t i = 0; i < n; i++) {
    rez = *s1 - *s2;
    if (*s1 != *s2) break;
    s1++;
    s2++;
  }
  return rez;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  void *startDest = dest;
  char *ptrdest = dest;
  const char *ptrsrc = src;
  while (n--) {
    *ptrdest = *ptrsrc;
    ptrdest++;
    ptrsrc++;
  }
  return startDest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *ptrdest = dest;
  const char *ptrsrc = src;
  s21_size_t i;
  for (i = 0; i < n; i++) {
    ptrdest[i] = ptrsrc[i];
  }
  return ptrdest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  char *istr = str;
  int i = 0;
  while (n > 0) {
    istr[i] = c;
    i++;
    n--;
  }
  return istr;
}

int s21_strcmp(const char *str1, const char *str2) {
  unsigned char *str_1 = (unsigned char *)str1;
  unsigned char *str_2 = (unsigned char *)str2;
  for (; *str_1 && *str_1 == *str_2; str_1++, str_2++)
    ;
  return *str_1 - *str_2;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int rv = 0;
  char *str_1 = (char *)str1;
  char *str_2 = (char *)str2;
  for (s21_size_t i = 0; i < n && *str_1 && *str_1 == *str_2;
       str_1++, str_2++, i++)
    ;
  if (n == 0) {
    rv = 0;
  } else {
    rv = *str_1 - *str_2;
  }
  return rv;
}

char *s21_strchr(const char *str, int c) {
  int have = 0;
  while (*str != '\0') {
    if (*str == (unsigned char)c) {
      have = 1;
      break;
    }
    str++;
  }
  char *rv = (char *)str;
  if (*str == '\0' && c == '\0') {
    rv = (char *)str;
  } else if (have == 0) {
    rv = S21_NULL;
  }
  return rv;
}

char *s21_strcat(char *dest, const char *src) {
  char *ptr = dest;
  while (*ptr) {
    ptr++;
  }
  while (*src != '\0') {
    *ptr = *src;
    ptr++;
    src++;
  }
  *ptr = '\0';
  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest;
  while (*ptr) {
    ptr++;
  }
  s21_size_t i = 0;
  while (*src != '\0' && i < n) {
    *ptr = *src;
    ptr++;
    src++;
    i++;
  }
  *ptr = '\0';
  return dest;
}

char *s21_strcpy(char *dest, const char *src) {
  char *cp = dest;
  while (*src) {
    *(dest++) = *(src++);
  }
  *dest = '\0';
  return cp;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *cp = dest;
  int i = 0;
  while (i < (int)n) {
    if (*(src)) {
      *(dest++) = *(src++);
    } else {
      *(dest++) = '\0';
    }
    i++;
  }
  return cp;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  while (*(str++)) {
    len++;
  }
  return len;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t rez = 0;
  s21_size_t cnt = 0;
  int i = 0, j = 0;
  while ((str1[i]) && ((int)cnt != -1)) {
    j = 0;
    while ((str2[j]) && ((int)cnt != -1)) {
      if (str1[i] == str2[j]) {
        rez = cnt;
        cnt = -1;
      }
      j++;
    }
    if ((int)cnt != -1) cnt++;
    i++;
  }
  rez = s21_strlen(str2) ? rez : s21_strlen(str1);
  return rez;
}

char *s21_strerror(int errnum) {
  char *err[] = ERRORLIST;
  static char rez[100];
  int max = (*err[0] == 'S') ? 133 : 106;
  if (errnum >= 0 && errnum <= max) {
    s21_strcpy(rez, err[errnum]);
  } else {
#if defined(__APPLE__)
    s21_sprintf(rez, "%s%d", "Unknown error: ", errnum);
#elif defined(__linux__)
    s21_sprintf(rez, "%s%d", "Unknown error ", errnum);
#endif
  }
  return rez;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  int exit_flag = 0;
  for (int i = 0; str1[i] != '\0' && exit_flag == 0; i++) {
    for (int j = 0; str2[j] != 0; j++) {
      if (str1[i] == str2[j]) {
        result = (char *)str1 + 1;
        exit_flag = 1;
        break;
      }
    }
  }
  return result;
}

char *s21_strrchr(const char *str, int c) {
  char tp = c;
  char *result = S21_NULL;
  for (; *str != '\0'; str++) {
    if (*str == tp) {
      result = (char *)str;
    }
  }
  if (result == S21_NULL) {
    result = (char *)str;
  }
  return *result == c ? (char *)result : S21_NULL;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t result = 0;
  int exit_flag = 0;
  const char *ptr1;
  const char *ptr2;

  for (ptr1 = str1; *ptr1 && exit_flag == 0; ptr1++) {
    for (ptr2 = str2;; ptr2++) {
      if (*ptr2 == '\0') {
        result = (ptr1 - str1);
        exit_flag = 1;
        break;
      } else {
        if (*ptr1 == *ptr2) {
          break;
        }
      }
    }
  }
  return result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;
  int exit_flag = 0;

  if (*needle == '\0') {
    result = (char *)haystack;
    exit_flag = 1;
  }
  if (exit_flag == 0) {
    for (int i = 0; haystack[i] != '\0' && exit_flag == 0; i++) {
      int temp = i;
      int j = 0;
      while (haystack[i++] == needle[j++]) {
        if (needle[j] == '\0') {
          result = (char *)&haystack[temp];
          exit_flag = 1;
          break;
        }
      }
      i = temp;
    }
  }
  return result;
}

char *s21_strtok(char *str, const char *delim) {
  char *result = S21_NULL;
  static char *last = S21_NULL;

  if (str == S21_NULL && delim != S21_NULL) {
    str = last;
  }
  if (str != S21_NULL && delim != S21_NULL) {
    s21_size_t str1 = 0, str2 = 0;
    for (; str[str1] && str[str1] != delim[str2]; str2++) {
      if (delim[str2] == '\0') {
        str1++;
        str2 = -1;
      }
    }
    if ((str[str1] == '\0') || (str[str1 + 1] == '\0')) {
      str[str1] = '\0';
      last = S21_NULL;
    } else {
      str[str1] = '\0';
      last = (char *)&str[str1 + 1];
    }
    result = str;
  }
  return result;
}

// доп функции

void *s21_trim(const char *src, const char *trim_chars) {
  char *rv = S21_NULL;
  if (src != S21_NULL && trim_chars != S21_NULL) {
    char *start_ptr = (char *)src;
    char *end_ptr = (char *)src + s21_strlen(src);
    while (start_ptr != S21_NULL && s21_strchr(trim_chars, *start_ptr)) {
      start_ptr++;
    }
    while (end_ptr != S21_NULL && s21_strchr(trim_chars, *(end_ptr - 1))) {
      end_ptr--;
    }
    rv = (char *)malloc(end_ptr - start_ptr + 1);
    if (rv != S21_NULL) {
      s21_strncpy(rv, start_ptr, end_ptr - start_ptr);
      *(rv + (end_ptr - start_ptr)) = '\0';
    }
  }
  return rv;
}

void *s21_to_upper(const char *str) {
  char *rv = S21_NULL;
  if (str != S21_NULL) {
    int len = s21_strlen(str);
    rv = (char *)malloc((len + 1));
    if (rv != S21_NULL) {
      s21_strcpy(rv, str);
      char *ptr = rv;
      while (*ptr) {
        if (*ptr >= 'a' && *ptr <= 'z') {
          *ptr -= 32;
        }
        ptr++;
      }
    }
  }
  return rv;
}

void *s21_to_lower(const char *str) {
  char *rv = S21_NULL;
  if (str != S21_NULL) {
    int len = s21_strlen(str);
    rv = (char *)malloc((len + 1));
    if (rv != S21_NULL) {
      s21_strcpy(rv, str);
      char *ptr = rv;
      while (*ptr) {
        if (*ptr >= 'A' && *ptr <= 'Z') {
          *ptr += 32;
        }
        ptr++;
      }
    }
  }
  return rv;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *rv = S21_NULL;
  if (src != S21_NULL && str != S21_NULL) {
    int len_src = s21_strlen(src);
    int len_str = s21_strlen(str);
    if (len_src >= (int)start_index) {
      rv = malloc(len_src + len_str + 1);
    }
    char *ptr = rv;
    if (rv) {
      s21_strncpy(rv, src, start_index);
      ptr += start_index;
      s21_strcpy(ptr, str);
      ptr += len_str;
      s21_strcpy(ptr, src + start_index);
    }
  }
  return rv;
}
