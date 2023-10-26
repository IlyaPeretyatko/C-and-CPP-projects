#include <check.h>

#include "s21_matrix.h"

START_TEST(s21_eq_matrix_test) {
  matrix_t aboba = {NULL, 0, 0};
  s21_create_matrix(3, 3, &aboba);
  matrix_t bebra = {NULL, 0, 0};
  s21_create_matrix(3, 3, &bebra);
  aboba.matrix[0][0] = 2.0000002;
  aboba.matrix[0][1] = 5;
  aboba.matrix[0][2] = 7;
  aboba.matrix[1][0] = 6;
  aboba.matrix[1][1] = 3;
  aboba.matrix[1][2] = 4;
  aboba.matrix[2][0] = 5;
  aboba.matrix[2][1] = -2;
  aboba.matrix[2][2] = -3;
  bebra.matrix[0][0] = 2.0000002;
  bebra.matrix[0][1] = 5;
  bebra.matrix[0][2] = 7;
  bebra.matrix[1][0] = 6;
  bebra.matrix[1][1] = 3;
  bebra.matrix[1][2] = 4;
  bebra.matrix[2][0] = 5;
  bebra.matrix[2][1] = -2;
  bebra.matrix[2][2] = -3;
  int answer = s21_eq_matrix(&aboba, &bebra);
  ck_assert_int_eq(answer, 1);
  bebra.matrix[0][0] = 2.0000003;
  answer = s21_eq_matrix(&aboba, &bebra);
  ck_assert_int_eq(answer, 0);
  bebra.matrix[0][0] = 2.00000003;
  aboba.matrix[0][0] = 2.00000002;
  answer = s21_eq_matrix(&aboba, &bebra);
  ck_assert_int_eq(answer, 1);
  s21_remove_matrix(&aboba);
  s21_remove_matrix(&bebra);
}
END_TEST

START_TEST(s21_sum_matrix_test) {
  matrix_t aboba = {NULL, 0, 0};
  s21_create_matrix(3, 3, &aboba);
  matrix_t bebra = {NULL, 0, 0};
  s21_create_matrix(3, 3, &bebra);
  matrix_t need = {NULL, 0, 0};
  s21_create_matrix(3, 3, &need);
  aboba.matrix[0][0] = 2;
  aboba.matrix[0][1] = 5;
  aboba.matrix[0][2] = 7;
  aboba.matrix[1][0] = 6;
  aboba.matrix[1][1] = 3;
  aboba.matrix[1][2] = 4;
  aboba.matrix[2][0] = 5;
  aboba.matrix[2][1] = -2;
  aboba.matrix[2][2] = -3;
  //
  bebra.matrix[0][0] = 2;
  bebra.matrix[0][1] = 5;
  bebra.matrix[0][2] = 7;
  bebra.matrix[1][0] = 6;
  bebra.matrix[1][1] = 3;
  bebra.matrix[1][2] = 4;
  bebra.matrix[2][0] = 5;
  bebra.matrix[2][1] = -2;
  bebra.matrix[2][2] = -3;
  //
  need.matrix[0][0] = 4;
  need.matrix[0][1] = 10;
  need.matrix[0][2] = 14;
  need.matrix[1][0] = 12;
  need.matrix[1][1] = 6;
  need.matrix[1][2] = 8;
  need.matrix[2][0] = 10;
  need.matrix[2][1] = -4;
  need.matrix[2][2] = -6;
  matrix_t result = {NULL, 0, 0};
  s21_sum_matrix(&aboba, &bebra, &result);
  int answer = s21_eq_matrix(&result, &need);
  ck_assert_int_eq(answer, 1);
  s21_remove_matrix(&aboba);
  s21_remove_matrix(&bebra);
  s21_remove_matrix(&need);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test) {
  matrix_t aboba = {NULL, 0, 0};
  s21_create_matrix(3, 3, &aboba);
  matrix_t bebra = {NULL, 0, 0};
  s21_create_matrix(3, 3, &bebra);
  matrix_t need = {NULL, 0, 0};
  s21_create_matrix(3, 3, &need);
  aboba.matrix[0][0] = 2;
  aboba.matrix[0][1] = 5;
  aboba.matrix[0][2] = 7;
  aboba.matrix[1][0] = 6;
  aboba.matrix[1][1] = 3;
  aboba.matrix[1][2] = 4;
  aboba.matrix[2][0] = 5;
  aboba.matrix[2][1] = -2;
  aboba.matrix[2][2] = -3;
  //
  bebra.matrix[0][0] = 2;
  bebra.matrix[0][1] = 5;
  bebra.matrix[0][2] = 7;
  bebra.matrix[1][0] = 6;
  bebra.matrix[1][1] = 3;
  bebra.matrix[1][2] = 4;
  bebra.matrix[2][0] = 5;
  bebra.matrix[2][1] = -2;
  bebra.matrix[2][2] = -3;
  //
  need.matrix[0][0] = 0;
  need.matrix[0][1] = 0;
  need.matrix[0][2] = 0;
  need.matrix[1][0] = 0;
  need.matrix[1][1] = 0;
  need.matrix[1][2] = 0;
  need.matrix[2][0] = 0;
  need.matrix[2][1] = 0;
  need.matrix[2][2] = 0;
  matrix_t result = {NULL, 0, 0};
  s21_sub_matrix(&aboba, &bebra, &result);
  int answer = s21_eq_matrix(&result, &need);
  ck_assert_int_eq(answer, 1);
  s21_remove_matrix(&aboba);
  s21_remove_matrix(&bebra);
  s21_remove_matrix(&need);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_test) {
  matrix_t aboba = {NULL, 0, 0};
  s21_create_matrix(3, 3, &aboba);
  matrix_t need = {NULL, 0, 0};
  s21_create_matrix(3, 3, &need);
  aboba.matrix[0][0] = 2;
  aboba.matrix[0][1] = 5;
  aboba.matrix[0][2] = 7;
  aboba.matrix[1][0] = 6;
  aboba.matrix[1][1] = 3;
  aboba.matrix[1][2] = 4;
  aboba.matrix[2][0] = 5;
  aboba.matrix[2][1] = -2;
  aboba.matrix[2][2] = -3;
  //
  need.matrix[0][0] = 4;
  need.matrix[0][1] = 10;
  need.matrix[0][2] = 14;
  need.matrix[1][0] = 12;
  need.matrix[1][1] = 6;
  need.matrix[1][2] = 8;
  need.matrix[2][0] = 10;
  need.matrix[2][1] = -4;
  need.matrix[2][2] = -6;
  matrix_t result = {NULL, 0, 0};
  s21_mult_number(&aboba, 2, &result);
  int answer = s21_eq_matrix(&result, &need);
  ck_assert_int_eq(answer, 1);
  s21_remove_matrix(&aboba);
  s21_remove_matrix(&need);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_test) {
  matrix_t aboba = {NULL, 0, 0};
  s21_create_matrix(3, 3, &aboba);
  matrix_t need = {NULL, 0, 0};
  s21_create_matrix(3, 3, &need);
  aboba.matrix[0][0] = 2;
  aboba.matrix[0][1] = 5;
  aboba.matrix[0][2] = 7;
  aboba.matrix[1][0] = 6;
  aboba.matrix[1][1] = 3;
  aboba.matrix[1][2] = 4;
  aboba.matrix[2][0] = 5;
  aboba.matrix[2][1] = -2;
  aboba.matrix[2][2] = -3;
  //
  need.matrix[0][0] = 2;
  need.matrix[0][1] = 6;
  need.matrix[0][2] = 5;
  need.matrix[1][0] = 5;
  need.matrix[1][1] = 3;
  need.matrix[1][2] = -2;
  need.matrix[2][0] = 7;
  need.matrix[2][1] = 4;
  need.matrix[2][2] = -3;
  matrix_t result = {NULL, 0, 0};
  s21_transpose(&aboba, &result);
  int answer = s21_eq_matrix(&result, &need);
  ck_assert_int_eq(answer, 1);
  s21_remove_matrix(&aboba);
  s21_remove_matrix(&need);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix_test) {
  matrix_t aboba = {NULL, 0, 0};
  s21_create_matrix(3, 3, &aboba);
  matrix_t bebra = {NULL, 0, 0};
  s21_create_matrix(3, 3, &bebra);
  matrix_t need = {NULL, 0, 0};
  s21_create_matrix(3, 3, &need);
  aboba.matrix[0][0] = 9;
  aboba.matrix[0][1] = 3;
  aboba.matrix[0][2] = 5;
  aboba.matrix[1][0] = 2;
  aboba.matrix[1][1] = 0;
  aboba.matrix[1][2] = 3;
  aboba.matrix[2][0] = 0;
  aboba.matrix[2][1] = 1;
  aboba.matrix[2][2] = -6;
  //
  bebra.matrix[0][0] = 1;
  bebra.matrix[0][1] = -1;
  bebra.matrix[0][2] = -1;
  bebra.matrix[1][0] = -1;
  bebra.matrix[1][1] = 4;
  bebra.matrix[1][2] = 7;
  bebra.matrix[2][0] = 8;
  bebra.matrix[2][1] = 1;
  bebra.matrix[2][2] = -1;
  //
  need.matrix[0][0] = 46;
  need.matrix[0][1] = 8;
  need.matrix[0][2] = 7;
  need.matrix[1][0] = 26;
  need.matrix[1][1] = 1;
  need.matrix[1][2] = -5;
  need.matrix[2][0] = -49;
  need.matrix[2][1] = -2;
  need.matrix[2][2] = 13;
  matrix_t result = {NULL, 0, 0};
  s21_mult_matrix(&aboba, &bebra, &result);
  int answer = s21_eq_matrix(&result, &need);
  ck_assert_int_eq(answer, 1);
  s21_remove_matrix(&aboba);
  s21_remove_matrix(&bebra);
  s21_remove_matrix(&need);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_determinant_test) {
  matrix_t aboba = {NULL, 0, 0};
  s21_create_matrix(3, 3, &aboba);
  aboba.matrix[0][0] = 1;
  aboba.matrix[0][1] = -3;
  aboba.matrix[0][2] = 4;
  aboba.matrix[1][0] = 2;
  aboba.matrix[1][1] = 5;
  aboba.matrix[1][2] = -3;
  aboba.matrix[2][0] = 4;
  aboba.matrix[2][1] = -2;
  aboba.matrix[2][2] = 7;
  double determinant = 0;
  s21_determinant(&aboba, &determinant);
  ck_assert_int_eq(determinant, 11);
  s21_remove_matrix(&aboba);
}
END_TEST

START_TEST(s21_calc_complements_test) {
  matrix_t aboba = {NULL, 0, 0};
  s21_create_matrix(3, 3, &aboba);
  aboba.matrix[0][0] = 1;
  aboba.matrix[0][1] = 2;
  aboba.matrix[0][2] = 4;
  aboba.matrix[1][0] = 3;
  aboba.matrix[1][1] = 3;
  aboba.matrix[1][2] = 5;
  aboba.matrix[2][0] = 2;
  aboba.matrix[2][1] = 4;
  aboba.matrix[2][2] = 4;
  matrix_t need = {NULL, 0, 0};
  s21_create_matrix(3, 3, &need);
  need.matrix[0][0] = -8;
  need.matrix[0][1] = -2;
  need.matrix[0][2] = 6;
  need.matrix[1][0] = 8;
  need.matrix[1][1] = -4;
  need.matrix[1][2] = 0;
  need.matrix[2][0] = -2;
  need.matrix[2][1] = 7;
  need.matrix[2][2] = -3;
  matrix_t result = {NULL, 0, 0};
  s21_calc_complements(&aboba, &result);
  int answer = s21_eq_matrix(&result, &need);
  ck_assert_int_eq(answer, 1);
  s21_remove_matrix(&aboba);
  s21_remove_matrix(&need);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_test) {
  matrix_t aboba = {NULL, 0, 0};
  s21_create_matrix(3, 3, &aboba);
  aboba.matrix[0][0] = 2;
  aboba.matrix[0][1] = 5;
  aboba.matrix[0][2] = 7;
  aboba.matrix[1][0] = 6;
  aboba.matrix[1][1] = 3;
  aboba.matrix[1][2] = 4;
  aboba.matrix[2][0] = 5;
  aboba.matrix[2][1] = -2;
  aboba.matrix[2][2] = -3;
  matrix_t need = {NULL, 0, 0};
  s21_create_matrix(3, 3, &need);
  need.matrix[0][0] = 1;
  need.matrix[0][1] = -1;
  need.matrix[0][2] = 1;
  need.matrix[1][0] = -38;
  need.matrix[1][1] = 41;
  need.matrix[1][2] = -34;
  need.matrix[2][0] = 27;
  need.matrix[2][1] = -29;
  need.matrix[2][2] = 24;
  matrix_t result = {NULL, 0, 0};
  s21_inverse_matrix(&aboba, &result);
  int answer = s21_eq_matrix(&result, &need);
  ck_assert_int_eq(answer, 1);
  s21_remove_matrix(&aboba);
  s21_remove_matrix(&need);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_create_remove_test) {
  matrix_t A = {NULL, 0, 0};
  ck_assert(0 == s21_create_matrix(3, 3, &A));
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert(A.matrix[i][j] == 0);
    }
  }
  s21_remove_matrix(&A);
}
END_TEST

int main() {
  Suite *suite = suite_create("S21_MATRIX");
  SRunner *srunner = srunner_create(suite);

  TCase *s21_create_remove_tcase = tcase_create("s21_create_remove_test");
  suite_add_tcase(suite, s21_create_remove_tcase);
  tcase_add_test(s21_create_remove_tcase, s21_create_remove_test);

  TCase *s21_eq_matrix_tcase = tcase_create("s21_eq_matrix_test");
  suite_add_tcase(suite, s21_eq_matrix_tcase);
  tcase_add_test(s21_eq_matrix_tcase, s21_eq_matrix_test);

  TCase *s21_sum_matrix_tcase = tcase_create("s21_sum_matrix_test");
  suite_add_tcase(suite, s21_sum_matrix_tcase);
  tcase_add_test(s21_sum_matrix_tcase, s21_sum_matrix_test);

  TCase *s21_sub_matrix_tcase = tcase_create("s21_sub_matrix_test");
  suite_add_tcase(suite, s21_sub_matrix_tcase);
  tcase_add_test(s21_sub_matrix_tcase, s21_sub_matrix_test);

  TCase *s21_mult_number_tcase = tcase_create("s21_mult_number_test");
  suite_add_tcase(suite, s21_mult_number_tcase);
  tcase_add_test(s21_mult_number_tcase, s21_mult_number_test);

  TCase *s21_transpose_tcase = tcase_create("s21_transpose_test");
  suite_add_tcase(suite, s21_transpose_tcase);
  tcase_add_test(s21_transpose_tcase, s21_transpose_test);

  TCase *s21_mult_matrix_tcase = tcase_create("s21_mult_matrix_test");
  suite_add_tcase(suite, s21_mult_matrix_tcase);
  tcase_add_test(s21_mult_matrix_tcase, s21_mult_matrix_test);

  TCase *s21_determinant_tcase = tcase_create("s21_determinant_test");
  suite_add_tcase(suite, s21_determinant_tcase);
  tcase_add_test(s21_determinant_tcase, s21_determinant_test);

  TCase *s21_calc_complements_tcase = tcase_create("s21_calc_complements_test");
  suite_add_tcase(suite, s21_calc_complements_tcase);
  tcase_add_test(s21_calc_complements_tcase, s21_calc_complements_test);

  TCase *s21_inverse_matrix_tcase = tcase_create("s21_inverse_matrix_test");
  suite_add_tcase(suite, s21_inverse_matrix_tcase);
  tcase_add_test(s21_inverse_matrix_tcase, s21_inverse_matrix_test);

  srunner_run_all(srunner, CK_VERBOSE);
  srunner_free(srunner);

  return 0;
}
