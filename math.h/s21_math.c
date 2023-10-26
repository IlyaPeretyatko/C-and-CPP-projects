#include "s21_math.h"

#include <float.h>
#include <limits.h>
#include <stdio.h>

int s21_abs(int x) {
  if (x < 0) {
    x = -x;
  }
  return x;
}

long double s21_ceil(double x) {
  long double integer = (long int)x;
  if (x == -S21_INF) {
    integer = -S21_INF;
  } else if (x == S21_INF) {
    integer = S21_INF;
  } else if (s21_is_nan(x)) {
    integer = S21_NAN;
  } else if (integer != x && x > 0) {
    integer++;
  }
  return integer;
}

long double s21_asin(double x) {
  long double rv = 0;
  int sign = 0;
  if (x < -1 || x > 1) {
    rv = S21_NAN;
  } else {
    if (x < 0) {
      x = -x;
      sign = 1;
    }
    long double denominator = 1;
    long double high = 1;
    long double low = 1;
    long double element = (x * high) / (denominator * low);
    for (int i = 0; i < 500; ++i) {
      rv += element;
      if (low == 1) {
        low = 2;
      }
      if (denominator == 1) {
        denominator = 3;
      }
      element /= low;
      element *= high;
      element /= denominator;
      element *= denominator - 2;
      element *= x * x;
      denominator += 2;
      low += 2;
      high += 2;
    }
  }
  if (x == 1) {
    rv = S21_PI / 2;
  }
  if (sign) {
    rv = -rv;
  }
  return rv;
}

long double s21_acos(double x) {
  long double rv = S21_PI / 2 - s21_asin(x);
  return rv;
}

long double s21_atan(double x) {
  int sign = 0;
  long double rv = 0;
  if (s21_is_nan(x)) {
    rv = S21_NAN;
  } else if (x <= 1 && x >= -1) {
    if (x < 0) {
      sign = 1;
      x = -x;
    }
    long double denominator = 1;
    long double element = x;
    int sign_el = 1;
    for (int i = 0; i < 1000; ++i) {
      rv += sign_el * element;
      sign_el = -sign_el;
      element *= x * x;
      element *= denominator;
      denominator += 2;
      element /= denominator;
    }
    if (sign) {
      rv = -rv;
    }
  } else if (x > 1) {
    rv = S21_PI / 2 - s21_atan(1 / x);
  } else if (x < -1) {
    rv = -S21_PI / 2 - s21_atan(1 / x);
  }
  return rv;
}

long double s21_sin(double x) {
  long double rv = 0;
  int sign = 1;
  if (x == S21_INF) {
    rv = S21_NAN;
  } else if (x == -S21_INF) {
    rv = S21_NAN;
  } else {
    if (x < 0) {
      sign = -1;
      x = -x;
    }
    while (x - (2 * S21_PI) > 0) {
      x -= (2 * S21_PI);
    }
    if (x > S21_PI) {
      x -= S21_PI;
      sign *= -1;
    } else if (x > S21_PI / 2) {
      x = S21_PI - x;
    }
    long double element = x;
    for (int i = 3; i < 1000; i += 2) {
      rv += element;
      element *= x * x;
      element *= -1;
      element /= (i * (i - 1));
    }
  }
  return rv * sign;
}

long double s21_cos(double x) {
  long double rv = 0;
  int sign = 1;
  if (x == S21_INF) {
    rv = S21_NAN;
  } else if (x == -S21_INF) {
    rv = S21_NAN;
  } else {
    if (x < 0) {
      x = -x;
    }
    while (x - (2 * S21_PI) > 0) {
      x -= (2 * S21_PI);
    }
    if (x > S21_PI) {
      x -= S21_PI;
      sign *= -1;
    }
    long double element = 1;
    for (int i = 2; i < 1000; i += 2) {
      rv += element;
      element *= x * x;
      element *= -1;
      element /= (i * (i - 1));
    }
    if (x == S21_PI / 2) {
      rv = 0;
    }
  }
  return rv * sign;
}

long double s21_tan(double x) {
  long double rv = 0;
  if (x == S21_INF) {
    rv = S21_NAN;
  } else if (x == -S21_INF) {
    rv = S21_NAN;
  } else {
    while (x - S21_PI > 0) {
      x -= S21_PI;
    }
    if (x == S21_PI / 2 || x == -S21_PI / 2) {
      rv = TAN_PIBY2;
    } else {
      rv = s21_sin(x) / s21_cos(x);
    }
  }
  return rv;
}

long double s21_log(double x) {
  long double rv = 0;
  if (s21_is_nan(x)) {
    rv = x;
  } else if (x == S21_INF) {
    rv = x;
  } else if (x == -S21_INF) {
    rv = S21_NAN;
  } else if (x == 0) {
    rv = -S21_INF;
  } else if (x < 0) {
    rv = S21_NAN;
  } else if (x > 0) {
    long double count_exp = 0;
    while (x / S21_EXP > 1) {
      x /= S21_EXP;
      count_exp += 1;
    }
    long double y = (1 - x) / (1 + x);
    long double element = -2 * y;
    long double denominator = 1;
    for (int i = 0; i < 500; ++i) {
      rv += element;
      element *= y * y;
      denominator += 2;
      element /= denominator;
      element *= denominator - 2;
    }
    rv += count_exp;
  }
  return rv;
}

long double s21_pow(double base, double exp) {
  long double rv = 0;
  int parity = 0;
  if (s21_fmod(exp, 1) == 0) {
    if (s21_fmod(exp, 2) == 0) {
      parity = 1;
    } else {
      parity = -1;
    }
  }
  if (base == 1.0 || exp == 0.0) {
    rv = 1.0;
  } else if (s21_is_nan(base) || s21_is_nan(exp)) {
    rv = S21_NAN;
  } else if ((1 / base) == -S21_INF) {
    if (exp < 0) {
      if (parity == -1) {
        rv = -S21_INF;
      } else {
        rv = S21_INF;
      }
    } else {
      if (parity == -1) {
        rv = -1 * 0.0;
      } else {
        rv = 1 * 0.0;
      }
    }
  } else if (base == 0.0) {
    if (exp < 0) {
      rv = S21_INF;
    } else {
      rv = 0;
    }
  } else if (base == -1.0 && exp != S21_INF && exp != -S21_INF) {
    if (exp >= DBL_MAX) {
      rv = 1;
    } else if (parity == 0) {
      rv = S21_NAN;
    } else {
      rv = parity;
    }
  } else if (base == -1.0 && (exp == S21_INF || exp == -S21_INF)) {
    rv = 1;
  } else if (base == S21_INF) {
    if (exp > 0) {
      rv = S21_INF;
    } else {
      rv = 0;
    }
  } else if (base == -S21_INF) {
    if (exp > 0) {
      if (parity == -1) {
        rv = -S21_INF;
      } else {
        rv = S21_INF;
      }
    } else {
      if (parity == -1) {
        rv = -1 * 0.0;
      } else {
        rv = 1 * 0.0;
      }
    }
  } else if (exp == S21_INF) {
    if (s21_fabs(base) > 1) {
      rv = S21_INF;
    } else {
      rv = 0;
    }
  } else if (exp == -S21_INF) {
    if (s21_fabs(base) < 1) {
      rv = S21_INF;
    } else {
      rv = 0.0;
    }
  } else if (base < 0) {
    if (parity == 0) {
      rv = S21_NAN;
    } else {
      if (s21_fabs(exp) < LLONG_MAX) {
        int_power(base, (long long int)exp);
      } else {
        base = -base;
        long double log_base = s21_log(base);
        long double arg = log_base * exp;
        rv = parity * s21_exp(arg);
      }
    }
  } else {
    if (parity != 0 && s21_fabs(exp) < LLONG_MAX) {
      rv = int_power(base, (long long int)exp);
    } else {
      long double log_base = s21_log(base);
      long double arg = log_base * exp;
      rv = s21_exp(arg);
    }
  }
  return rv;
}

long double s21_exp(double x) {
  long double rv = 0;
  if (x == 0) {
    rv = 1;
  } else if (s21_is_nan(x)) {
    rv = S21_NAN;
  } else if (x == S21_INF) {
    rv = S21_INF;
  } else if (x == -S21_INF) {
    rv = 0;
  } else if (x > 710) {
    rv = S21_INF;
  } else if (x < -710) {
    rv = 0;
  } else {
    long long int count = s21_floor(x);
    x = x - (long double)count;
    long double element = 1;
    for (int i = 1; i < 300; ++i) {
      rv += element;
      element *= x;
      element /= i;
    }
    if (rv != 0) {
      rv *= int_power(S21_EXP, count);
    } else {
      rv = int_power(S21_EXP, count);
    }
  }
  return rv;
}

long double int_power(long double base, long long int exp) {
  long double rv = 1;
  int sign = 0;
  if (exp < 0) {
    exp = -exp;
    sign = 1;
  }
  while (exp != 0) {
    if (exp & 1) rv *= base;
    base *= base;
    exp >>= 1;
  }
  if (sign) {
    rv = 1.0 / rv;
  }
  return rv;
}

long double s21_sqrt(double x) {
  long double rv = 0;
  if (x < 0) {
    rv = S21_NAN;
  } else {
    rv = s21_pow(x, 0.5);
  }
  return rv;
}

long double s21_fabs(double x) { return (x >= 0 ? x : -x); }

long double s21_floor(double x) {
  long double int_x = (long long int)x;
  if (x == S21_INF) {
    int_x = S21_INF;
  } else if (x == -S21_INF) {
    int_x = -S21_INF;
  } else if (s21_is_nan(x)) {
    int_x = S21_NAN;
  } else if ((x != int_x) && x < 0) {
    if (x > -1) {
      int_x = -1;
    } else {
      int_x = int_x - 1;
    }
  }
  return int_x;
}
long double s21_fmod(double x, double y) {
  long double rv = 0;
  if ((x == DBL_MAX && y == DBL_MIN) || (x == DBL_MAX && y == -DBL_MIN)) {
    rv = 0;
  } else if ((x == -DBL_MAX && y == -DBL_MIN) ||
             (x == -DBL_MAX && y == DBL_MIN)) {
    rv = -0.0;
  } else if (s21_is_nan(x) || s21_is_nan(y) || x == S21_INF || x == -S21_INF ||
             y == 0) {
    rv = S21_NAN;
  } else if (y == S21_INF || y == -S21_INF) {
    rv = x;
  } else if (x == 0 && y != 0) {
    rv = 0;
  } else {
    rv = x / y;
    if (rv > 0) {
      rv = s21_floor(rv);
    } else {
      rv = s21_ceil(rv);
    }
    rv = x - y * rv;
  }
  return rv;
}

int s21_is_nan(double x) { return x != x; }
