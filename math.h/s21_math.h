#define S21_PI 3.1415926535897932384626433832795028841971
#define TAN_PIBY2 16331239353195370
#define S21_INF 1.0 / 0.0
#define S21_NAN 0.0 / 0.0
#define S21_EXP 2.718281828459045235360287471352

int s21_abs(int x);
long double s21_ceil(double x);
long double s21_asin(double x);
long double s21_acos(double x);
long double s21_atan(double x);
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_exp(double x);
long double s21_sqrt(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
int s21_is_nan(double x);
long double int_power(long double base, long long int exp);