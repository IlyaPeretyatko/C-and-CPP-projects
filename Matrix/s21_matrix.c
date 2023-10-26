#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int rv = 0;
  result->rows = rows;
  result->columns = columns;
  if (rows < 1 || columns < 1) {
    rv = 1;
  } else {
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      rv = 1;
    } else {
      for (int i = 0; i < rows; ++i) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          rv = 0;
          break;
        }
      }
    }
    if (rv == 1) {
      s21_remove_matrix(result);
    }
  }
  return rv;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; ++i) {
      if (A->matrix[i] != NULL) {
        free(A->matrix[i]);
      } else {
        break;
      }
    }
    free(A->matrix);
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int rv = SUCCESS;
  if (A->rows != B->rows || A->columns != B->columns) {
    rv = FAILURE;
  } else {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          rv = FAILURE;
        }
      }
    }
  }
  return rv;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int rv = 1;
  if (A->rows == B->rows && A->columns == B->columns) {
    rv = s21_create_matrix(A->rows, A->columns, result);
  } else {
    rv = 2;
  }
  if (rv == 0) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return rv;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int rv = 0;
  if (A->rows == B->rows && A->columns == B->columns) {
    rv = s21_create_matrix(A->rows, A->columns, result);
  } else {
    rv = 2;
  }
  if (rv == 0) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return rv;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int rv = 0;
  rv = s21_create_matrix(A->rows, A->columns, result);
  if (rv == 0) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return rv;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int rv = 0;
  if ((A == NULL) || (B == NULL) || (A->rows <= 0) || (A->columns <= 0) ||
      (B->rows <= 0) || (B->columns <= 0)) {
    rv = 1;
  } else if (A->columns == B->rows) {
    rv = s21_create_matrix(A->rows, B->columns, result);
  } else {
    rv = 2;
  }
  if (rv == 0) {
    for (int i = 0; i < result->rows; ++i) {
      for (int j = 0; j < result->columns; ++j) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return rv;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int rv = 0;
  rv = s21_create_matrix(A->columns, A->rows, result);
  if (rv == 0) {
    for (int i = 0; i < result->rows; ++i) {
      for (int j = 0; j < result->columns; ++j) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return rv;
}

int get_determinant(matrix_t *A) {
  double determinant = 0;
  if (A->rows == 1) {
    determinant = A->matrix[0][0];
  } else {
    determinant =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  }
  return determinant;
}

int get_minor(matrix_t *A, int row, int column, matrix_t *result) {
  int rv = 0;
  rv = s21_create_matrix(A->rows - 1, A->columns - 1, result);
  if (rv == 0) {
    int i_res = 0;
    int j_res = 0;
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        if (i != row && j != column) {
          result->matrix[i_res][j_res] = A->matrix[i][j];
          j_res++;
          if (j_res == result->columns) {
            i_res++;
            j_res = 0;
          }
        }
      }
    }
  }
  return rv;
}

int s21_determinant(matrix_t *A, double *result) {
  int rv = 0;
  *result = 0;
  if (A->rows != A->columns) {
    rv = 2;
  } else {
    if (A->rows <= 2) {
      *result = get_determinant(A);
    } else {
      for (int i = 0; i < A->columns; ++i) {
        matrix_t minor;
        rv = get_minor(A, 0, i, &minor);
        if (rv != 0) {
          break;
        }
        double value_minor = 0;
        rv = s21_determinant(&minor, &value_minor);
        if (rv != 0) {
          s21_remove_matrix(&minor);
          break;
        }
        *result +=
            A->matrix[0][i] * ((1 + i + 1) % 2 == 0 ? 1 : -1) * value_minor;
        s21_remove_matrix(&minor);
      }
    }
  }
  return rv;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int rv = 0;
  if (A->rows != A->columns) {
    rv = 2;
  } else {
    rv = s21_create_matrix(A->rows, A->columns, result);
  }
  if (rv == 0) {
    if (A->rows == 1) {
      result->matrix[0][0] = A->matrix[0][0];
    } else {
      for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < A->columns; ++j) {
          matrix_t minor;
          rv = get_minor(A, i, j, &minor);
          if (rv != 0) {
            break;
          }
          double value_minor = 0;
          rv = s21_determinant(&minor, &value_minor);
          if (rv != 0) {
            s21_remove_matrix(&minor);
            break;
          }
          if (value_minor == 0) {
            result->matrix[i][j] = 0;
          } else {
            result->matrix[i][j] =
                ((i + j + 2) % 2 == 0 ? 1 : -1) * value_minor;
          }
          s21_remove_matrix(&minor);
        }
        if (rv != 0) {
          break;
        }
      }
    }
  }
  if (rv != 0) {
    s21_remove_matrix(result);
  }
  return rv;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int rv = 0;
  double determinant = 0.0;
  rv = s21_determinant(A, &determinant);
  if (!rv) {
    if (fabs(determinant) > 1e-7) {
      matrix_t minor = {NULL, 0, 0};
      rv = s21_calc_complements(A, &minor);
      if (!rv) {
        matrix_t transp_minor = {NULL, 0, 0};
        rv = s21_transpose(&minor, &transp_minor);
        if (!rv) {
          if (!rv) rv = s21_mult_number(&transp_minor, 1 / determinant, result);
          s21_remove_matrix(&transp_minor);
        }
        s21_remove_matrix(&minor);
      }
    } else {
      rv = 2;
    }
  }
  return rv;
}
