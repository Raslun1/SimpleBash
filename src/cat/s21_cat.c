#include "./s21_cat.h"

int main(int argc, char **argv) {
  parser(argc, argv);
  return 0;
}
void parser(int argc, char **argv) {
  struct avi_flags my_flags = {0, 0, 0, 0, 0, 0};
  if (get_par(argc, argv, &my_flags)) {
    open_files(argv, argc, &my_flags);
  }
}

int get_par(int argc, char **argv, struct avi_flags *my_flags) {
  int check = 1;
  struct option long_options[] = {{"squeeze-blank", no_argument, NULL, 's'},
                                  {"number-nonblank", no_argument, NULL, 'b'},
                                  {"number", no_argument, NULL, 'n'},
                                  {"E", no_argument, NULL, 'e'},
                                  {"T", no_argument, NULL, 't'},
                                  {NULL, 0, NULL, 0}};
  int opt;

  while ((opt = getopt_long(argc, argv, "beEntTsv", long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'b':
        my_flags->b = 1;
        break;
      case 'e':
        my_flags->e = 1;
        my_flags->v = 1;
        break;
      case 'n':
        my_flags->n = 1;
        break;
      case 't':
        my_flags->t = 1;
        my_flags->v = 1;
        break;
      case 's':
        my_flags->s = 1;
        break;
      case 'v':
        my_flags->v = 1;
        break;
      case 'E':
        my_flags->e = 1;
        break;
      case 'T':
        my_flags->t = 1;
        break;
      default:
        check = 0;
        break;
    }
  }
  return check;
}

void open_files(char **argv, int argc, struct avi_flags *my_flags) {
  FILE *f = NULL;
  int check_flag = 0;
  for (int i = 1; i < argc; i++) {
    f = fopen(argv[i], "r");
    if (f == NULL) {
    } else {
      if (my_flags->e || my_flags->t || my_flags->v || my_flags->s ||
          my_flags->b || my_flags->n) {
        check_flag = 1;
        by_char(f, my_flags, check_flag);
      } else {
        by_char(f, my_flags, check_flag);
      }
      fclose(f);
    }
  }
}

void by_char(FILE *f, struct avi_flags *my_flags, int check_flag) {
  int c;
  int first_str = 0;
  int prev_2 = 0;
  int prev = 0;
  int cnt_b = 1;
  int cnt_n = 1;
  while ((c = fgetc(f)) != EOF) {
    if (check_flag)
      print_char(&c, my_flags, &prev, &cnt_b, &cnt_n, &prev_2, &first_str);
    else if (!check_flag)
      printf("%c", c);
  }
}

void flag_n(int *first_str, int *cnt_n, int *prev, int fl_s) {
  if (!*first_str) {
    printf("%6d\t", *cnt_n);
    (*first_str)++;
    (*cnt_n)++;
  } else if (*prev == '\n' && *first_str && !fl_s) {
    printf("%6d\t", *cnt_n);
    (*cnt_n)++;
  }
}

void flag_b(int *first_str, int *cnt_n, int *prev, int *c, int *cnt_b) {
  if (!*first_str && *c != '\n') {
    printf("%6d\t", *cnt_n);
    (*first_str)++;
    (*cnt_n)++;
    (*cnt_b)++;
  } else if (*prev == '\n' && *c != '\n') {
    printf("%6d\t", *cnt_b);
    (*cnt_b)++;
  }
}

int flag_s(int *prev_2, int *prev, int *c, int *flag) {
  int fl_s = 0;
  if (*prev_2 == '\n' && *prev == '\n' && *c == '\n') {
    *flag = 1;
    fl_s = 1;
  }
  return fl_s;
}

void flag_e(int *c, int *flag, int fl_s, struct avi_flags *my_flags) {
  if (*c == '\n' && !fl_s) {
    printf("$\n");
    *flag = 1;
  } else if (*c == '\t' && !my_flags->t) {
    printf("\t");
    *flag = 1;
  }
}

void flag_t(int *flag) {
  printf("^I");
  *flag = 1;
}

void check_symb(int *c, struct avi_flags *my_flags, int *flag) {
  if (*c < 32 && my_flags->v && *c != 10 && *c != 9) {
    printf("^%c", *c + 64);
    *flag = 1;
  } else if (*c == 127 && my_flags->v) {
    printf("^?");
    *flag = 1;
  } else if (*c > 127) {
    printf("M-^%c", *c - 128);
    *flag = 1;
  }
}

void print_char(int *c, struct avi_flags *my_flags, int *prev, int *cnt_b,
                int *cnt_n, int *prev_2, int *first_str) {
  int flag = 0;
  int fl_s = 0;
  if (my_flags->s) fl_s = flag_s(prev_2, prev, c, &flag);
  if (my_flags->b) flag_b(first_str, cnt_n, prev, c, cnt_b);
  if (my_flags->n && !my_flags->b) flag_n(first_str, cnt_n, prev, fl_s);
  if (*c == '\t' && my_flags->t) flag_t(&flag);
  if (my_flags->e) flag_e(c, &flag, fl_s, my_flags);

  check_symb(c, my_flags, &flag);
  *prev_2 = *prev;
  *prev = *c;

  if (!flag) {
    putchar(*c);
  }
}
