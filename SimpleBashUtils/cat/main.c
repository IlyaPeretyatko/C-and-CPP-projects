#include <stdio.h>
#include <string.h>

#define COUNT_FLAGS 6
#define b 0
#define e 1
#define n 2
#define s 3
#define t 4
#define v 5

int check_flags(char *argv[], int argc, int *flags);
int cat(int argc, char *argv[], int *flags);
void output(FILE *f, int *flags);

int main(int argc, char *argv[]) {
  int flags[COUNT_FLAGS];
  if (check_flags(argv, argc, flags)) {
    if (!cat(argc, argv, flags)) {
      fprintf(stderr, "No files");
    }
  } else {
    fprintf(stderr, "bad input flags");
  }
  return 0;
}

int check_flags(char *argv[], int argc, int *flags) {
  int correct = 1;
  int have_file = 0;
  for (int i = 0; i < COUNT_FLAGS; ++i) {
    flags[i] = 0;
  }
  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-' && argv[i][1] == '-') {
      if (have_file) {
        correct = 0;
      }
      if (!strcmp(argv[i], "--number-nonblank")) {
        flags[b] = 1;
      } else if (!strcmp(argv[i], "--number")) {
        flags[n] = 1;
      } else if (!strcmp(argv[i], "--squeeze-blank")) {
        flags[s] = 1;
      } else {
        correct = 0;
      }
    } else if (argv[i][0] == '-' && argv[i][1] != '-') {
      if (have_file) {
        correct = 0;
      }
      int j = 1;
      while (argv[i][j] != '\0') {
        if (argv[i][j] == 'b') {
          flags[b] = 1;
        } else if (argv[i][j] == 'e') {
          flags[e] = 1;
          flags[v] = 1;
        } else if (argv[i][j] == 'n') {
          flags[n] = 1;
        } else if (argv[i][j] == 's') {
          flags[s] = 1;
        } else if (argv[i][j] == 't') {
          flags[t] = 1;
          flags[v] = 1;
        } else if (argv[i][j] == 'E') {
          flags[e] = 1;
        } else if (argv[i][j] == 'T') {
          flags[t] = 1;
        } else if (argv[i][j] == 'v') {
          flags[v] = 1;
        } else {
          correct = 0;
        }
        j++;
      }
    } else {
      have_file = 1;
    }
  }
  return correct;
}

int cat(int argc, char *argv[], int *flags) {
  int correct = 0;
  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] != '-') {
      FILE *f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "No such files or directories\n");
        continue;
      } else {
        correct = 1;
        output(f, flags);
      }
      fclose(f);
    }
  }
  return correct;
}

void output(FILE *f, int *flags) {
  unsigned char out;
  unsigned char before_out = '\n', before_before_out = ' ';
  int count = 1;
  while (fread(&out, sizeof(unsigned char), 1, f) == 1) {
    int skip = 0;
    int was_permutation = 0;
    unsigned char copy_before_out = before_out;
    if (flags[s]) {
      if (out == '\n' && before_out == '\n' && before_before_out == '\n') {
        before_before_out = before_out;
        before_out = out;
        was_permutation = 1;
        skip = 1;
      } else {
        before_before_out = before_out;
        before_out = out;
        was_permutation = 1;
      }
    }
    if (!skip) {
      if (flags[n] && !flags[b]) {
        if (copy_before_out == '\n') {
          printf("%6d\t", count);
          count++;
        }
      } else if ((flags[b] && flags[n]) || (flags[b] && !flags[n])) {
        if (copy_before_out == '\n' && out != '\n') {
          printf("%6d\t", count);
          count++;
        }
      }
    }

    if (flags[t]) {
      if (out == '\t') {
        printf("^I");
        skip = 1;
      }
      if (!was_permutation) {
        before_before_out = before_out;
        before_out = out;
        was_permutation = 1;
      }
    }

    if (flags[e]) {
      if (out == '\n' && !skip) {
        printf("$\n");
        skip = 1;
      }
      if (!was_permutation) {
        before_before_out = before_out;
        before_out = out;
        was_permutation = 1;
      }
    }

    if (flags[v]) {
      if (out < 32 && (out != '\n') && (out != '\t')) {
        printf("^%c", out + 64);
        skip = 1;
      } else if (out == 127) {
        printf("^?");
        skip = 1;
      }
    }

    if (!was_permutation) {
      before_before_out = before_out;
      before_out = out;
      was_permutation = 1;
    }
    if (!skip) {
      printf("%c", out);
    }
  }
}
