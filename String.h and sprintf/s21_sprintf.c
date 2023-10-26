#include "s21_string.h"

void print_f(char *str, va_list args, int *n, flags *opt) {
  long double argument_ll;
  double argument = va_arg(args, double);
  argument_ll = (long double)argument;
  print_float(str, n, opt, argument_ll);
}

int s21_sprintf(char *str, const char *format, ...) {
  int rv_count = 0;
  int length = s21_strlen(format);
  va_list(args);
  va_start(args, format);
  flags opt;
  for (int index = 0; index < length; index++) {
    if (format[index] == '%') {
      update_opt(&opt);
      check_opt(&opt, &index, format);
      print_specificator(format, index, str, args, &rv_count, &opt);
    } else {
      str[rv_count] = format[index];
      rv_count++;
    }
  }
  str[rv_count] = '\0';
  va_end(args);
  return rv_count;
}

void update_opt(flags *opt) {
  opt->work = 1;
  opt->minus = 0;
  opt->plus = 0;
  opt->space = 0;
  opt->width = 0;
  opt->width_value = 0;
  opt->accuracy = 0;
  opt->accuracy_value = 0;
  opt->l = 0;
  opt->h = 0;
  opt->flag = 0;
}

void check_opt(flags *opt, int *index, const char *format) {
  while (opt->work != 0) {
    *index += 1;
    if (format[*index] == '-') {
      opt->minus = 1;
    } else if (format[*index] == '+') {
      opt->plus = 1;
    } else if (format[*index] == ' ') {
      opt->space = 1;
    } else if (format[*index] == '.') {
      opt->accuracy = 1;
      *index += 1;
      opt->accuracy_value = take_int(index, format);
    } else if (format[*index] >= '0' && format[*index] <= '9') {
      opt->width = 1;
      opt->width_value = take_int(index, format);

    } else if (format[*index] == 'h') {
      opt->h = 1;
    } else if (format[*index] == 'l') {
      opt->l = 1;
      if (format[*index + 1] == 'l') {
        opt->l = 2;
        *index += 1;
      }
    } else {
      opt->work = 0;
    }
  }
}

int take_int(int *index, const char *format) {
  int start = *index;
  int end = *index - 1;
  while (format[*index] >= '0' && format[*index] <= '9') {
    end++;
    *index += 1;
  }
  *index -= 1;
  int number = 0;
  int ten = 1;
  while (start <= end) {
    number += (format[end] - '0') * ten;
    ten *= 10;
    end--;
    if (number < 0) {
      break;
    }
  }
  return number;
}

void print_specificator(const char *format, int index, char *str, va_list args,
                        int *n, flags *opt) {
  switch (format[index]) {
    case 'd':
      print_d(str, args, n, opt);
      break;
    case 'i':
      print_d(str, args, n, opt);
      break;
    case 'f':
      print_f(str, args, n, opt);
      break;
    case 'c':
      print_c(str, args, n, opt);
      break;
    case 's':
      print_s(str, args, n, opt);
      break;
    case 'u':
      print_u(str, args, n, opt);
      break;
    case '%':
      paste_str_part("%", n, str);
      break;
  }
}

void print_d(char *str, va_list args, int *n, flags *opt) {
  long long int argument_ll;
  if (opt->l == 2) {
    long long int argument = va_arg(args, long long int);
    argument_ll = (long long int)argument;
  } else if (opt->l == 1) {
    long int argument = va_arg(args, long int);
    argument_ll = (long long int)argument;
  } else if (opt->h == 1) {
    short int argument = va_arg(args, int);
    argument_ll = (long long int)argument;
  } else {
    int argument = va_arg(args, int);
    argument_ll = (long long int)argument;
  }
  print_int(str, n, opt, argument_ll);
}

void paste_int(char *str_part, int *i, long long int len,
               long long int argument, flags *opt) {
  int count = 0;
  if (argument < 0) {
    argument = -argument;
  }
  int copy_i = *i;
  while (count <= len - 1) {
    if ((opt->flag) &&
        (count == (len - 1) && (str_part[copy_i + len - count - 2] == '.'))) {
      opt->flag = 0;
      argument /= 10;
    } else {
      str_part[copy_i + len - count - 1] = (int)(argument % 10) + '0';
      argument /= 10;
      *i += 1;
      count++;
    }
  }
}

long long int len_of_int(long long int x) {
  long long int rv = 0;
  if (x < 0) {
    x = -x;
  }
  while (x / 10 != 0) {
    x /= 10;
    rv += 1;
  }
  rv += 1;
  return rv;
}

int print_float(char *str, int *n, flags *opt, long double argument_ll) {
  long double first = 0, second = 0;
  second = modfl(fabsl(argument_ll), &first);
  int n_pw = opt->accuracy ? opt->accuracy_value : DEF_VAL;
  int pw = 1;
  long int s_digit = 0, f_digit = 0;

  if ((fabsl(second)) < 0.1) opt->flag = 1;
  while (pw <= n_pw) {
    s_digit = lroundl(second * pow(10, pw));
    if (opt->flag) s_digit += pow(10, pw - 1);
    pw++;
  }
  if ((!opt->accuracy_value) && (opt->accuracy)) {
    f_digit = (long int)(round(argument_ll));
  } else {
    f_digit = (long int)first;
  }
  long long int len_f = len_of_int(f_digit);
  long long int len_s;
  if ((!(opt->accuracy_value)) && (opt->accuracy)) {
    len_s = 0;
  } else {
    len_s = len_of_int(s_digit);
  }

  int i = 0;
  long long int len = len_f + len_s + 1;
  if ((!opt->accuracy_value) && (opt->accuracy)) len--;
  char str_part[1024] = {'\0'};
  if ((opt->width == 1) && (opt->width_value > len) &&
      (opt->minus == 0)) {  // func
    while (i < ((opt->width_value) - len)) {
      if (i == ((opt->width_value) - len) - 1) {
        if (opt->plus && argument_ll > 0) {
          str_part[i] = '+';
        } else if ((argument_ll < 0) || (argument_ll == -0.0)) {
          str_part[i] = '-';
        } else {
          str_part[i] = ' ';
        }
        i++;
        break;
      }
      str_part[i] = ' ';
      i++;
    }
    paste_int(str_part, &i, len_f, f_digit, opt);
    if (!((!(opt->accuracy_value)) && (opt->accuracy))) {
      s21_strcat(str_part, ".");
      i++;
      paste_int(str_part, &i, len_s, s_digit, opt);
    }
  } else if ((opt->width == 1) && (opt->width_value > len) &&
             (opt->minus == 1)) {
    print_flags_d(str_part, &i, argument_ll, opt);
    paste_int(str_part, &i, len_f, f_digit, opt);
    if (!((!(opt->accuracy_value)) && (opt->accuracy))) {
      s21_strcat(str_part, ".");
      i++;
      paste_int(str_part, &i, len_s, s_digit, opt);
    }
    while (i < opt->width_value) {
      str_part[i] = ' ';
      i++;
    }

  } else {
    print_flags_d(str_part, &i, argument_ll, opt);
    paste_int(str_part, &i, len_f, f_digit, opt);
    if (!((!(opt->accuracy_value)) && (opt->accuracy))) {
      s21_strcat(str_part, ".");
      i++;
      paste_int(str_part, &i, len_s, s_digit, opt);
    }
  }
  str_part[i] = '\0';
  paste_str_part(str_part, n, str);
  return 0;
}

void print_flags_i(char *str_part, int *i, long long int argument, flags *opt) {
  if (opt->plus && argument > 0) {
    str_part[*i] = '+';
    *i += 1;
  } else if (argument < 0) {
    str_part[*i] = '-';
    *i += 1;
  } else if (opt->space == 1) {
    str_part[*i] = ' ';
    *i += 1;
  }
}

void print_flags_d(char *str_part, int *i, long double argument, flags *opt) {
  if (opt->plus && argument > 0) {
    str_part[*i] = '+';
    *i += 1;
  } else if (argument < 0) {
    str_part[*i] = '-';
    *i += 1;
  } else if (opt->space == 1) {
    str_part[*i] = ' ';
    *i += 1;
  }
}

void print_int(char *str, int *n, flags *opt, long long int argument_ll) {
  char str_part[1024] = {'\0'};
  int i = 0;
  long long int len = len_of_int(argument_ll);
  if ((opt->width == 1) && (opt->width_value > len) && (opt->minus == 0)) {
    while (i < ((opt->width_value) - len)) {
      if (i == ((opt->width_value) - len) - 1) {
        if (opt->plus && argument_ll > 0) {
          str_part[i] = '+';
        } else if (argument_ll < 0) {
          str_part[i] = '-';
        } else {
          str_part[i] = ' ';
        }
        i++;
        break;
      }
      str_part[i] = ' ';
      i++;
    }
    paste_int(str_part, &i, len, argument_ll, opt);
  } else if ((opt->width == 1) && (opt->width_value > len) &&
             (opt->minus == 1)) {
    print_flags_i(str_part, &i, argument_ll, opt);
    paste_int(str_part, &i, len, argument_ll, opt);
    while (i < opt->width_value) {
      str_part[i] = ' ';
      i++;
    }
  } else {
    print_flags_i(str_part, &i, argument_ll, opt);
    paste_int(str_part, &i, len, argument_ll, opt);
  }
  str_part[i] = '\0';
  paste_str_part(str_part, n, str);
}

void print_u(char *str, va_list args, int *n, flags *opt) {
  unsigned long long int argument_ll;
  if (opt->l == 2) {
    unsigned long long int argument = va_arg(args, unsigned long long int);
    argument_ll = (unsigned long long int)argument;
  } else if (opt->l == 1) {
    unsigned long int argument = va_arg(args, unsigned long int);
    argument_ll = (unsigned long long int)argument;
  } else if (opt->h == 1) {
    unsigned short int argument = va_arg(args, unsigned int);
    argument_ll = (unsigned long long int)argument;
  } else {
    unsigned int argument = va_arg(args, unsigned int);
    argument_ll = (unsigned long long int)argument;
  }
  print_unsigned_int(str, n, opt, argument_ll);
}

void print_unsigned_int(char *str, int *n, flags *opt,
                        unsigned long long int argument_ll) {
  char str_part[1024] = {'\0'};
  int i = 0;
  long long int len = len_of_int(argument_ll);
  if ((opt->width == 1) && (opt->width_value > len) && (opt->minus == 0)) {
    while (i < ((opt->width_value) - len)) {
      if (i == ((opt->width_value) - len) - 1) {
        if (opt->plus && argument_ll > 0) {
          str_part[i] = '+';
        } else {
          str_part[i] = ' ';
        }
        i++;
        break;
      }
      str_part[i] = ' ';
      i++;
    }
    paste_int(str_part, &i, len, argument_ll, opt);
  } else if ((opt->width == 1) && (opt->width_value > len) &&
             (opt->minus == 1)) {
    print_flags_i(str_part, &i, argument_ll, opt);
    paste_int(str_part, &i, len, argument_ll, opt);
    while (i < opt->width_value) {
      str_part[i] = ' ';
      i++;
    }
  } else {
    print_flags_i(str_part, &i, argument_ll, opt);
    paste_int(str_part, &i, len, argument_ll, opt);
  }
  str_part[i] = '\0';
  paste_str_part(str_part, n, str);
}

void print_c(char *str, va_list args, int *n, flags *opt) {
  char argument = va_arg(args, int);
  char str_part[1024] = {'\0'};
  int i = 0;
  if (opt->width == 1 && opt->width_value > 1) {
    if (opt->minus == 1) {
      str_part[i] = argument;
      i++;
      for (int j = 0; j < (opt->width_value) - 1; ++j) {
        str_part[i] = ' ';
        i++;
      }
    } else {
      for (int j = 0; j < (opt->width_value) - 1; ++j) {
        str_part[i] = ' ';
        i++;
      }
      str_part[i] = argument;
      i++;
    }
  } else {
    str_part[i] = argument;
    i++;
  }
  str_part[i] = '\0';
  paste_str_part(str_part, n, str);
}

void print_s(char *str, va_list args, int *n, flags *opt) {
  char *argument = va_arg(args, char *);
  if (argument == S21_NULL) {
    argument = "(null)";
  }
  char str_part[2048];
  int len = s21_strlen(argument);
  if (opt->accuracy == 1 && opt->accuracy_value < len) {
    len = opt->accuracy_value;
  }
  int i = 0;
  if (opt->width == 1 && opt->width_value > len) {
    if (opt->minus == 1) {
      for (int j = 0; j < len; ++j) {
        str_part[i] = argument[j];
        i++;
      }
      for (int j = 0; j < (opt->width_value) - len; ++j) {
        str_part[i] = ' ';
        i++;
      }
    } else {
      for (int j = 0; j < (opt->width_value) - len; ++j) {
        str_part[i] = ' ';
        i++;
      }
      for (int j = 0; j < len; ++j) {
        str_part[i] = argument[j];
        i++;
      }
    }
  } else {
    for (int j = 0; j < len; ++j) {
      str_part[i] = argument[j];
      i++;
    }
  }
  str_part[i] = '\0';
  paste_str_part(str_part, n, str);
}

void paste_str_part(char *str_part, int *n, char *str) {
  int len_part = s21_strlen(str_part);
  for (int j = 0; j < len_part; ++j) {
    str[*n] = str_part[j];
    *n += 1;
  }
}
