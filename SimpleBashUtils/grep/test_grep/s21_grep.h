#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

typedef struct opt {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} flags;

int check_flag(int argc, char *argv[], flags *options, char **patterns,
               int *count_pattern, char **files, int *count_files);
int check_if_no_one_pattern_and_file(int *count_pattern, char *argv[],
                                     char **patterns, flags *options, int argc,
                                     int *count_files, char **files);
void grep(flags *options, char **patterns, int count_pattern, char **files,
          int count_files, char *str);
void search(flags *options, char **patterns, int count_pattern, int count_files,
            char *str, FILE *f, char **files, int i);
void clear_memory(char **patterns, char **files, int count_pattern,
                  int count_files);

int main(int argc, char *argv[]) {
  flags options = {0};
  char *patterns[BUFFER_SIZE];
  char *files[BUFFER_SIZE];
  char str[BUFFER_SIZE];
  int count_pattern = 0;
  int count_files = 0;
  if (check_flag(argc, argv, &options, patterns, &count_pattern, files,
                 &count_files)) {
    grep(&options, patterns, count_pattern, files, count_files, str);
  }
  clear_memory(patterns, files, count_pattern, count_files);
  return 0;
}

int check_flag(int argc, char *argv[], flags *options, char **patterns,
               int *count_pattern, char **files, int *count_files) {
  int rv = 1;
  if (argc < 3) {
    printf("bad input");
    rv = 0;
  }
  for (int i = 0; i < BUFFER_SIZE; ++i) {
    patterns[i] = NULL;
  }
  for (int i = 0; i < BUFFER_SIZE; ++i) {
    files[i] = NULL;
  }
  int rez = 0;
  while ((rez = getopt_long(argc, argv, "f:e:ivclnhso", NULL, NULL)) != -1) {
    switch (rez) {
    case 'e':
      options->e = 1;
      patterns[*count_pattern] = (char *)malloc(BUFFER_SIZE);
      if (patterns[*count_pattern] == NULL) {
        printf("memory error");
        rv = 0;
        break;
      }
      strcpy(patterns[*count_pattern], optarg);
      *count_pattern += 1;
      continue;
    case 'i':
      options->i = 1;
      continue;
    case 'v':
      options->v = 1;
      continue;
    case 'c':
      options->c = 1;
      continue;
    case 'l':
      options->l = 1;
      continue;
    case 'n':
      options->n = 1;
      continue;
    case 'h':
      options->h = 1;
      continue;
    case 's':
      options->s = 1;
      continue;
    case 'f':
      options->f = 1;
      options->e = 1;
      FILE *f = fopen(optarg, "r");
      if (f == NULL) {
        printf("File not opened");
        rv = 0;
        break;
      }
      int count_string = 0;
      patterns[*count_pattern] = (char *)malloc(BUFFER_SIZE);
      if (patterns[*count_pattern] == NULL) {
        printf("memory error");
        rv = 0;
        fclose(f);
        break;
      }
      while (fgets(patterns[*count_pattern], BUFFER_SIZE, f) != NULL) {
        count_string++;
      }
      free(patterns[*count_pattern]);
      fseek(f, 0, SEEK_SET);
      for (int i = 0; i < count_string; ++i) {
        patterns[*count_pattern] = (char *)malloc(BUFFER_SIZE);
        if (patterns[*count_pattern] == NULL) {
          printf("memory error");
          rv = 0;
          fclose(f);
          break;
        }
        fgets(patterns[*count_pattern], BUFFER_SIZE, f);
        int length = (int)strlen(patterns[*count_pattern]);
        if (patterns[*count_pattern][length - 1] == '\n') {
          patterns[*count_pattern][length - 1] = '\0';
        }
        *count_pattern += 1;
      }
      fclose(f);
      if (!rv) {
        break;
      }
      continue;
    case 'o':
      options->o = 1;
      continue;
    }
  }
  if (rv) {
    rv = check_if_no_one_pattern_and_file(count_pattern, argv, patterns,
                                          options, argc, count_files, files);
  }
  if (rv && (*count_files == 0 || *count_pattern == 0)) {
    printf("bad input");
    rv = 0;
  }
  return rv;
}

int check_if_no_one_pattern_and_file(int *count_pattern, char *argv[],
                                     char **patterns, flags *options, int argc,
                                     int *count_files, char **files) {
  int rv = 1;
  if (options->e == 0) {
    patterns[*count_pattern] = (char *)malloc(BUFFER_SIZE);
    if (patterns[*count_pattern] == NULL) {
      printf("memory error");
      rv = 0;
    } else {
      strcpy(patterns[*count_pattern], argv[optind]);
      *count_pattern += 1;
      optind += 1;
    }
  }
  while (optind < argc && rv) {
    if (strcmp(argv[optind], "-e\0") == 0) {
      optind += 2;
      break;
    } else if (strcmp(argv[optind], "-f\0") == 0) {
      optind += 2;
      break;
    } else if (argv[optind][0] == '-') {
      int j = 1;
      while (argv[optind][j] != '\0') {
        if ((argv[optind][j] == 'e' || argv[optind][j] == 'f') &&
            argv[optind][j + 1] != '\0') {
          optind += 1;
          break;
        } else {
          optind += 2;
          break;
        }
        j++;
      }
    } else {
      files[*count_files] = (char *)malloc(BUFFER_SIZE);
      if (files[*count_files] == NULL) {
        printf("memory error");
        rv = 0;
        break;
      }
      strcpy(files[*count_files], argv[optind]);
      *count_files += 1;
      optind += 1;
    }
  }
  return rv;
}

void grep(flags *options, char **patterns, int count_pattern, char **files,
          int count_files, char *str) {
  for (int i = 0; i < count_files; ++i) {
    FILE *f = fopen(files[i], "r");
    if (f == NULL) {
      if (!(options->s)) {
        printf("grep: %s: No such file or directory\n", files[i]);
      }
      continue;
    } else {
      search(options, patterns, count_pattern, count_files, str, f, files, i);
      fclose(f);
    }
  }
}

void search(flags *options, char **patterns, int count_pattern, int count_files,
            char *str, FILE *f, char **files, int i) {
  int have_pattern = 0;
  int cflags1 = REG_NEWLINE;
  int new_line = 1;
  if (options->i) {
    cflags1 = REG_ICASE;
  }
  static int correct = 1;
  if (options->o && !(options->c) && !(options->l) && (options->v)) {
    int count = 1;
    while (fgets(str, BUFFER_SIZE, f) != NULL) {
      for (int j = 0; j < count_pattern; ++j) {
        if (correct) {
          int status;
          regex_t preg;
          regmatch_t pmatch[2];
          if (regcomp(&preg, patterns[j], cflags1) != 0) {
            printf("error");
            correct = 0;
            break;
          }
          status = regexec(&preg, str, 2, pmatch, 0);
          if (status == 0) {
            have_pattern = 1;
          }
          regfree(&preg);
        }
      }
      if (!have_pattern) {
        if (count_files > 1 && !(options->h)) {
          printf("%s:", files[i]);
        }
        if (options->n) {
          printf("%d:", count);
        }
        printf("%s", str);
      }
      have_pattern = 0;
      count++;
    }

    if (str[strlen(str) - 1] != '\n') {
      printf("\n");
    }
    fseek(f, 0, SEEK_SET);
  } else if (options->o && !(options->c) && !(options->l) && !(options->v)) {
    int count = 1;
    while (fgets(str, BUFFER_SIZE, f) != NULL) {
      new_line = 1;
      for (int j = 0; j < count_pattern; ++j) {
        if (correct) {
          while (1) {
            int status;
            regex_t preg;
            regmatch_t pmatch[2];
            if (regcomp(&preg, patterns[j], cflags1) != 0) {
              printf("error");
              correct = 0;
              break;
            }
            status = regexec(&preg, str, 2, pmatch, 0);
            if (status == 0 && !(options->v)) {
              if (new_line) {
                if (count_files > 1 && !(options->h)) {
                  printf("%s:", files[i]);
                }
                if (options->n) {
                  printf("%d:", count);
                }
              }
              for (int i = pmatch->rm_so; i < pmatch->rm_eo; ++i) {
                printf("%c", str[i]);
              }
              printf("\n");
              for (int i = 0; i < (int)pmatch->rm_eo; ++i) {
                str[i] = ' ';
              }
              new_line = 0;
            } else {
              regfree(&preg);
              break;
            }
            regfree(&preg);
          }
        }
      }
      count++;
    }
  } else if (options->c && options->l) {
    while (fgets(str, BUFFER_SIZE, f) != NULL) {
      for (int j = 0; j < count_pattern; ++j) {
        if (correct) {
          int status;
          regex_t preg;
          if (regcomp(&preg, patterns[j], cflags1) != 0) {
            printf("error");
            correct = 0;
            break;
          }
          status = regexec(&preg, str, 0, NULL, 0);
          if ((status == 0 && !(options->v)) || (status != 0 && options->v)) {
            have_pattern = 1;
            regfree(&preg);
            break;
          }
          regfree(&preg);
        }
      }
    }
    fseek(f, 0, SEEK_SET);
    if (correct) {
      if (count_files > 1 && !(options->h)) {
        printf("%s:", files[i]);
      }
        printf("%d\n", have_pattern);
      if (have_pattern != 0) {
         printf("%s\n", files[i]);
      }
      have_pattern = 0;
    }
  } else if (options->c && !(options->l) && !(options -> v)) {
    int count = 0;
    while (fgets(str, BUFFER_SIZE, f) != NULL) {
      for (int j = 0; j < count_pattern; ++j) {
        if (correct) {
          int status;
          regex_t preg;
          if (regcomp(&preg, patterns[j], cflags1) != 0) {
            printf("error");
            correct = 0;
            break;
          }
          status = regexec(&preg, str, 0, NULL, 0);
          if (status == 0) {
            have_pattern = 1;
            regfree(&preg);
            break;
          }
          regfree(&preg);
        }
      }
      count += have_pattern;
      have_pattern = 0;
    }
    fseek(f, 0, SEEK_SET);
    if (correct) {
      if (count_files > 1 && !(options->h)) {
        printf("%s:", files[i]);
      }
      printf("%d\n", count);
    }
    count = 0;
  } else if (options->c && !(options->l) && (options -> v)) {
    int count = 0;
    while (fgets(str, BUFFER_SIZE, f) != NULL) {
      for (int j = 0; j < count_pattern; ++j) {
        if (correct) {
          int status;
          regex_t preg;
          if (regcomp(&preg, patterns[j], cflags1) != 0) {
            printf("error");
            correct = 0;
            break;
          }
          status = regexec(&preg, str, 0, NULL, 0);
          if (status == 0) {
            have_pattern = 1;
          }
          regfree(&preg);
        }
      }
      if (have_pattern == 0) {
        count += 1;
      }
      have_pattern = 0;
    }
    fseek(f, 0, SEEK_SET);
    if (correct) {
      if (count_files > 1 && !(options->h)) {
        printf("%s:", files[i]);
      }
      printf("%d\n", count);
    }
    count = 0;
  } else if (!(options->c) && options->l) {
    while (fgets(str, BUFFER_SIZE, f) != NULL) {
      for (int j = 0; j < count_pattern; ++j) {
        if (correct) {
          int status;
          regex_t preg;
          if (regcomp(&preg, patterns[j], cflags1) != 0) {
            printf("error");
            correct = 0;
            break;
          }
          status = regexec(&preg, str, 0, NULL, 0);
          if ((status == 0 && !(options->v)) || (status != 0 && options->v)) {
            have_pattern = 1;
            regfree(&preg);
            break;
          }
          regfree(&preg);
        }
      }
    }
    fseek(f, 0, SEEK_SET);
    if (have_pattern && correct) {
      printf("%s\n", files[i]);
      have_pattern = 0;
    }
  } else if (!(options->v)) {
    if (correct) {
      int count = 1;
      int searched = 0;
      while (fgets(str, BUFFER_SIZE, f) != NULL) {
        for (int j = 0; j < count_pattern; ++j) {
          int status;
          regex_t preg;
          if (regcomp(&preg, patterns[j], cflags1) != 0) {
            printf("error");
            correct = 0;
            break;
          }
          status = regexec(&preg, str, 0, NULL, 0);
          if (status == 0) {
            if (count_files > 1 && !(options->h)) {
              printf("%s:", files[i]);
            }
            if (options->n) {
              printf("%d:", count);
            }
            printf("%s", str);
            count++;
            searched = 1;
            regfree(&preg);
            break;
          }
          regfree(&preg);
        }
        if (!searched) {
          count++;
        }
        searched = 0;
      }
      fseek(f, 0, SEEK_SET);
    }
  } else if (options->v) {
    if (correct) {
      int count = 1;
      while (fgets(str, BUFFER_SIZE, f) != NULL) {
        for (int j = 0; j < count_pattern; ++j) {
          int status;
          regex_t preg;
          if (regcomp(&preg, patterns[j], cflags1) != 0) {
            printf("error");
            correct = 0;
            break;
          }
          status = regexec(&preg, str, 0, NULL, 0);
          if (status == 0) {
            have_pattern = 1;
          }
          regfree(&preg);
        }
        if (!have_pattern) {
          if (count_files > 1 && !(options->h)) {
            printf("%s:", files[i]);
          }
          if (options->n) {
            printf("%d:", count);
          }
          printf("%s", str);
        }
        have_pattern = 0;
        count++;
      }
      if (str[strlen(str) - 1] != '\n') {
        printf("\n");
      }
    }
  }

  if (correct) {
    if (options->c && options->l) {
      // if (count_files > 1 && !(options->h)) {
      //   printf("%s:", files[i]);
      // }
      // printf("%d\n", count_main);
      // if (count_main != 0) {
      //   printf("%s\n", files[i]);
      // }
    } else if (options->c) {
      // if (count_files > 1 && !(options->h)) {
      //   printf("%s:", files[i]);
      // }
      // printf("%d\n", count_for_c);
    } else if (options->l) {
      // if (have_pattern) {
      //   printf("%s\n", files[i]);
      // }
    }
  }
}

void clear_memory(char **patterns, char **files, int count_pattern,
                  int count_files) {
  for (int i = 0; i < count_pattern; ++i) {
    if (patterns[i] != NULL) {
      free(patterns[i]);
    }
  }
  for (int i = 0; i < count_files; ++i) {
    if (files[i] != NULL) {
      free(files[i]);
    }
  }
}
