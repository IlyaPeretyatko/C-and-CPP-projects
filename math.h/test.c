#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_math.h"

START_TEST(s21_abs_test) {
  ck_assert_int_eq(s21_abs(-1), abs(-1));
  ck_assert_int_eq(s21_abs(5), abs(5));
  ck_assert_int_eq(s21_abs(-15), abs(-15));
  ck_assert_int_eq(s21_abs(378), abs(378));
  ck_assert_int_eq(s21_abs(0), abs(0));
}
END_TEST

START_TEST(s21_ceil_test) {
  ck_assert_ldouble_eq_tol(s21_ceil(5), ceill(5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(-33), ceill(-33), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(55.33), ceill(55.33), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(155.87), ceill(155.87), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(-155.87), ceill(-155.87), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(-55.33), ceill(-55.33), 1e-6);
  ck_assert_ldouble_infinite(s21_ceil(S21_INF));
  ck_assert_ldouble_infinite(s21_ceil(-S21_INF));
  ck_assert_ldouble_nan(s21_ceil(S21_NAN));
}
END_TEST

START_TEST(s21_asin_test) {
  ck_assert_ldouble_eq_tol(s21_asin(0.456123), asinl(0.456123), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(0.216875), asinl(0.216875), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(0.978464), asinl(0.978464), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(1), asinl(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(-1), asinl(-1), 1e-6);
  for (long double i = -1; i < 1; i += 0.01) {
    ck_assert_ldouble_eq_tol(s21_asin(i), asinl(i), 1e-6);
  }
  ck_assert_ldouble_eq_tol(s21_asin(0.532), asinl(0.532), 1e-6);
  ck_assert_ldouble_nan(s21_asin(5));
  ck_assert_ldouble_nan(s21_asin(-10));
  ck_assert_ldouble_nan(s21_asin(S21_INF));
  ck_assert_ldouble_nan(s21_asin(-S21_INF));
  ck_assert_ldouble_nan(s21_asin(S21_NAN));
}
END_TEST

START_TEST(s21_acos_test) {
  ck_assert_ldouble_eq_tol(s21_acos(0.456123), acosl(0.456123), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(0.216875), acosl(0.216875), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(0.978464), acosl(0.978464), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(1), acosl(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(-1), acosl(-1), 1e-6);
  for (long double i = -1; i < 1; i += 0.01) {
    ck_assert_ldouble_eq_tol(s21_acos(i), acosl(i), 1e-6);
  }
  ck_assert_ldouble_eq_tol(s21_acos(0.532), acosl(0.532), 1e-6);
  ck_assert_ldouble_nan(s21_acos(5));
  ck_assert_ldouble_nan(s21_acos(-10));
  ck_assert_ldouble_nan(s21_acos(S21_INF));
  ck_assert_ldouble_nan(s21_acos(-S21_INF));
  ck_assert_ldouble_nan(s21_acos(S21_NAN));
}
END_TEST

START_TEST(s21_atan_test) {
  ck_assert_ldouble_eq_tol(s21_atan(0.456123), atanl(0.456123), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(0.216875), atanl(0.216875), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(0.978464), atanl(0.978464), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(500), atanl(500), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-3000), atanl(-3000), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(S21_PI / 2), atanl(S21_PI / 2), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(0), atanl(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(0.3), atanl(0.3), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-0.84), atanl(-0.84), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-S21_INF), atanl(-S21_INF), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(S21_INF), atanl(S21_INF), 1e-6);
  ck_assert_ldouble_nan(s21_atan(S21_NAN));
}
END_TEST

START_TEST(s21_sin_test) {
  ck_assert_ldouble_eq_tol(s21_sin(0.456123), sinl(0.456123), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(0.216875), sinl(0.216875), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(0.978464), sinl(0.978464), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(1), sinl(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(-1), sinl(-1), 1e-6);
  for (long double i = -5; i < 5; i += 0.03) {
    ck_assert_ldouble_eq_tol(s21_sin(i), sinl(i), 1e-6);
  }
  ck_assert_ldouble_eq_tol(s21_sin(0), sinl(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(S21_PI), sinl(S21_PI), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(S21_PI / 2), sinl(S21_PI / 2), 1e-6);
  ck_assert_ldouble_nan(s21_sin(S21_NAN));
  ck_assert_ldouble_nan(s21_sin(S21_INF));
  ck_assert_ldouble_nan(s21_sin(-S21_INF));
}
END_TEST

START_TEST(s21_cos_test) {
  ck_assert_ldouble_eq_tol(s21_cos(0.456123), cosl(0.456123), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(0.216875), cosl(0.216875), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(0.978464), cosl(0.978464), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(1), cosl(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(-1), cosl(-1), 1e-6);
  for (long double i = -5; i < 5; i += 0.03) {
    ck_assert_ldouble_eq_tol(s21_cos(i), cosl(i), 1e-6);
  }
  ck_assert_ldouble_eq_tol(s21_cos(0), cosl(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(S21_PI), cosl(S21_PI), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(S21_PI / 2), cosl(S21_PI / 2), 1e-6);
  ck_assert_ldouble_nan(s21_cos(S21_NAN));
  ck_assert_ldouble_nan(s21_cos(S21_INF));
  ck_assert_ldouble_nan(s21_cos(-S21_INF));
}
END_TEST

START_TEST(s21_tan_test) {
  ck_assert_ldouble_eq_tol(s21_tan(0.456123), tanl(0.456123), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(0.216875), tanl(0.216875), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(0.978464), tanl(0.978464), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(1), tanl(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(-1), tanl(-1), 1e-6);
  for (long double i = -5; i < 5; i += 0.03) {
    ck_assert_ldouble_eq_tol(s21_tan(i), tanl(i), 1e-6);
  }
  ck_assert_ldouble_eq_tol(s21_tan(0), tanl(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(S21_PI), tanl(S21_PI), 1e-6);
  ck_assert_ldouble_nan(s21_tan(S21_NAN));
  ck_assert_ldouble_nan(s21_tan(S21_INF));
  ck_assert_ldouble_nan(s21_tan(-S21_INF));
}
END_TEST

START_TEST(s21_log_test) {
  ck_assert_ldouble_eq_tol(s21_log(0.456123), logl(0.456123), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(0.216875), logl(0.216875), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(0.978464), logl(0.978464), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(1), logl(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(2.71), logl(2.71), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(0.6), logl(0.6), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(3000), logl(3000), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(535.64), logl(535.64), 1e-6);
  ck_assert_ldouble_infinite(s21_log(S21_INF));
  ck_assert_ldouble_nan(s21_log(-S21_INF));
  ck_assert_ldouble_nan(s21_log(S21_NAN));
}
END_TEST

START_TEST(s21_pow_test) {
  ck_assert_ldouble_eq_tol(s21_pow(10, 1.5), powl(10, 1.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(1.5, 1.5), powl(1.5, 1.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(0, 1), powl(0, 1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(1, 0), powl(1, 0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(1.000, 0.000), powl(1.000, 0.000), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(0.215, 0.215), powl(0.215, 0.215), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(0.215, S21_INF), powl(0.215, S21_INF), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(1.215, -S21_INF), powl(1.215, -S21_INF),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(62, 3), powl(62, 3), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(2, 10), powl(2, 10), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(2.6, 10), powl(2.6, 10), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(6.325, 5.623632), powl(6.325, 5.623632),
                           1e-6);
  ck_assert_ldouble_nan(s21_pow(-6.325, 5.623632));
  ck_assert_ldouble_infinite(s21_pow(-S21_INF, 5));
  ck_assert_ldouble_infinite(s21_pow(S21_INF, 5));
  ck_assert_ldouble_infinite(s21_pow(0.5, -S21_INF));
  ck_assert_ldouble_infinite(s21_pow(2, S21_INF));
  ck_assert_ldouble_nan(s21_pow(S21_NAN, 5));
  ck_assert_ldouble_nan(s21_pow(5, S21_NAN));
}
END_TEST

START_TEST(s21_exp_test) {
  ck_assert_ldouble_eq_tol(s21_exp(0.456123), expl(0.456123), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(0.216875), expl(0.216875), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(0.978464), expl(0.978464), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(0), expl(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(1), expl(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(11.09), expl(11.09), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(5), expl(5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(3.756), expl(3.756), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(-1), expl(-1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(-5.5), expl(-5.5), 1e-6);
  // ck_assert_ldouble_eq_tol(s21_exp(-S21_INF), expl(-S21_INF), 1e-6);
  // ck_assert_ldouble_infinite(s21_exp(S21_INF));
  ck_assert_ldouble_nan(s21_exp(S21_NAN));
}
END_TEST

START_TEST(s21_sqrt_test) {
  ck_assert_ldouble_eq_tol(s21_sqrt(0.456123), sqrtl(0.456123), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(0.216875), sqrtl(0.216875), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(0.978464), sqrtl(0.978464), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(5.5), sqrtl(5.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(0), sqrtl(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(1), sqrtl(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(0.35), sqrtl(0.35), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(25), sqrtl(25), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(532.3), sqrtl(532.3), 1e-6);
  ck_assert_ldouble_infinite(s21_sqrt(S21_INF));
  ck_assert_ldouble_nan(s21_sqrt(S21_NAN));
  ck_assert_ldouble_nan(s21_sqrt(-S21_INF));
  ck_assert_ldouble_nan(s21_sqrt(-5));
}
END_TEST

START_TEST(s21_fabs_test) {
  ck_assert_ldouble_eq_tol(s21_fabs(-1), fabsl(-1.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(5), fabsl(5.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(-15), fabsl(-15.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(378), fabsl(378.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(0), fabsl(0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(-1.375), fabsl(-1.375), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(5.698), fabsl(5.698), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(-15.1), fabsl(-15.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(378.555), fabsl(378.555), 1e-6);
  ck_assert_ldouble_infinite(s21_fabs(S21_INF));
  ck_assert_ldouble_infinite(s21_fabs(-S21_INF));
  ck_assert_ldouble_nan(s21_fabs(S21_NAN));
}
END_TEST

START_TEST(s21_floor_test) {
  ck_assert_ldouble_eq_tol(s21_floor(5), floorl(5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(-33), floorl(-33), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(55.33), floorl(55.33), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(155.87), floorl(155.87), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(-155.87), floorl(-155.87), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(-55.33), floorl(-55.33), 1e-6);
  ck_assert_ldouble_infinite(s21_floor(S21_INF));
  ck_assert_ldouble_infinite(s21_floor(-S21_INF));
  ck_assert_ldouble_nan(s21_floor(S21_NAN));
}
END_TEST

START_TEST(s21_fmod_test) {
  ck_assert_ldouble_eq_tol(s21_fmod(-5.3, 3.3), fmodl(-5.3, 3.3), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(9874.785, 15.15), fmodl(9874.785, 15.15),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(-9874.785, 15.15), fmodl(-9874.785, 15.15),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(-3465.001, 8.8), fmodl(-3465.001, 8.8),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(3465.001, 8.8), fmodl(3465.001, 8.8), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(0.215, 0.215), fmodl(0.215, 0.215), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(0.978464, 5), fmodl(0.978464, 5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(6.325, 5.623632), fmodl(6.325, 5.623632),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(-6.325, 5.623632), fmodl(-6.325, 5.623632),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(6.325, -5.623632), fmodl(6.325, -5.623632),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(6.325, 15.623632), fmodl(6.325, 15.623632),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(-6.325, 15.623632),
                           fmodl(-6.325, 15.623632), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(6.325, -15.623632),
                           fmodl(6.325, -15.623632), 1e-6);
  ck_assert_ldouble_nan(s21_fmod(6.325, S21_NAN));
  ck_assert_ldouble_nan(s21_fmod(S21_NAN, 4));
  ck_assert_ldouble_nan(s21_fmod(S21_INF, S21_INF));
}
END_TEST

int main() {
  Suite *suite = suite_create("S21_MATH");
  SRunner *srunner = srunner_create(suite);

  TCase *s21_abs_tcase = tcase_create("s21_abs_test");
  suite_add_tcase(suite, s21_abs_tcase);
  tcase_add_test(s21_abs_tcase, s21_abs_test);

  TCase *s21_ceil_tcase = tcase_create("s21_ceil_test");
  suite_add_tcase(suite, s21_ceil_tcase);
  tcase_add_test(s21_ceil_tcase, s21_ceil_test);

  TCase *s21_asin_tcase = tcase_create("s21_asin_test");
  suite_add_tcase(suite, s21_asin_tcase);
  tcase_add_test(s21_asin_tcase, s21_asin_test);

  TCase *s21_acos_tcase = tcase_create("s21_acos_test");
  suite_add_tcase(suite, s21_acos_tcase);
  tcase_add_test(s21_acos_tcase, s21_acos_test);

  TCase *s21_atan_tcase = tcase_create("s21_atan_test");
  suite_add_tcase(suite, s21_atan_tcase);
  tcase_add_test(s21_atan_tcase, s21_atan_test);

  TCase *s21_sin_tcase = tcase_create("s21_sin_test");
  suite_add_tcase(suite, s21_sin_tcase);
  tcase_add_test(s21_sin_tcase, s21_sin_test);

  TCase *s21_cos_tcase = tcase_create("s21_cos_test");
  suite_add_tcase(suite, s21_cos_tcase);
  tcase_add_test(s21_cos_tcase, s21_cos_test);

  TCase *s21_tan_tcase = tcase_create("s21_tan_test");
  suite_add_tcase(suite, s21_tan_tcase);
  tcase_add_test(s21_tan_tcase, s21_tan_test);

  TCase *s21_exp_tcase = tcase_create("s21_exp_test");
  suite_add_tcase(suite, s21_exp_tcase);
  tcase_add_test(s21_exp_tcase, s21_exp_test);

  TCase *s21_fabs_tcase = tcase_create("s21_fabs_test");
  suite_add_tcase(suite, s21_fabs_tcase);
  tcase_add_test(s21_fabs_tcase, s21_fabs_test);

  TCase *s21_floor_tcase = tcase_create("s21_floor_test");
  suite_add_tcase(suite, s21_floor_tcase);
  tcase_add_test(s21_floor_tcase, s21_floor_test);

  TCase *s21_log_tcase = tcase_create("s21_log_test");
  suite_add_tcase(suite, s21_log_tcase);
  tcase_add_test(s21_log_tcase, s21_log_test);

  TCase *s21_pow_tcase = tcase_create("s21_pow_test");
  suite_add_tcase(suite, s21_pow_tcase);
  tcase_add_test(s21_pow_tcase, s21_pow_test);

  TCase *s21_sqrt_tcase = tcase_create("s21_sqrt_test");
  suite_add_tcase(suite, s21_sqrt_tcase);
  tcase_add_test(s21_sqrt_tcase, s21_sqrt_test);

  TCase *s21_fmod_tcase = tcase_create("s21_fmod_test");
  suite_add_tcase(suite, s21_fmod_tcase);
  tcase_add_test(s21_fmod_tcase, s21_fmod_test);

  srunner_run_all(srunner, CK_VERBOSE);
  srunner_free(srunner);

  return 0;
}
