#include "s21_grep.h"

int main(int argc, char **argv) {
  parser(argc, argv);
  return 0;
}

void parser(int argc, char **argv) {
  struct avi_flags my_flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  FILE *f = NULL;
  char arr[8000] = {0};
  char *arr_files[argc];
  int cnt_files = 0;
  if (get_par(&my_flags, argc, argv, arr, arr_files, &cnt_files)) {
    open_files(f, &my_flags, arr, arr_files, &cnt_files);
  }
}

void fill_arr(char *arr, struct avi_flags *my_flags, int *check) {
  if (optarg != NULL) {
    if (my_flags->e) strcat(arr, "|");
    strcat(arr, optarg);
  } else {
    *check = 0;
    fprintf(stderr, "INVALID INPUT, ENTER -flag \"pattern\" filename\n");
  }
}

int get_par(struct avi_flags *my_flags, int argc, char **argv, char *arr,
            char **arr_files, int *cnt_files) {
  int check = 1;
  int option, option_index = 0;
  static struct option long_option[] = {{0, 0, 0, 0}};
  while ((option = getopt_long(argc, argv, "e:ivclnhsf:o", long_option,
                               &option_index)) != -1) {
    switch (option) {
      case 'e':
        fill_arr(arr, my_flags, &check);
        my_flags->e = 1;
        break;
      case 'f':
        my_flags->f = 1;
        break;
      case 'i':
        my_flags->i = 1;
        break;
      case 'v':
        my_flags->v = 1;
        break;
      case 'c':
        my_flags->c = 1;
        break;
      case 'l':
        my_flags->l = 1;
        break;
      case 'n':
        my_flags->n = 1;
        break;
      case 'h':
        my_flags->h = 1;
        break;
      case 's':
        my_flags->s = 1;
        break;
      case 'o':
        break;
      default:
        check = 0;
        break;
    }
  }
  fc(argc, argv, &check, my_flags, arr, arr_files, cnt_files);
  return check;
}

void fc(int argc, char **argv, int *check, struct avi_flags *my_flags,
        char *arr, char **arr_files, int *cnt_files) {
  if (optind == argc || argc == 1) {
    *check = 0;
    fprintf(stderr, "INVALID INPUT, ENTER -flag \"pattern\" filename\n");
  }
  if (*check) {
    if (!my_flags->e && !my_flags->f) {
      if (!arr[0])
        strcat(arr, argv[optind]);
      else {
        strcat(arr, "|");
        strcat(arr, argv[optind]);
      }
      optind++;
    }
    while (optind < argc) {
      arr_files[*cnt_files] = argv[optind];
      (*cnt_files)++;
      optind++;
    }
  }
}

void open_files(FILE *f, struct avi_flags *my_flags, char *arr,
                char **arr_files, int *cnt_files) {
  int check = 0;
  if (*cnt_files > 1) check = 1;
  for (int i = 0; i < *cnt_files; i++) {
    f = fopen(arr_files[i], "r");
    if (f == NULL && my_flags->s) {
    } else if (f == NULL && !my_flags->s) {
      fprintf(stderr, "no such file or directory\n");
    } else {
      line_from_file(f, check, arr_files[i], my_flags, arr);
      fclose(f);
    }
  }
}
void line_from_file(FILE *f, int check, char *filename,
                    struct avi_flags *my_flags, char *arr) {
  int cnt_n = 0;
  int cnt_l = 0;
  int cnt_c = 0;
  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, f) != -1) {
    if (line != NULL) {
      if (make_reg(&line, my_flags, &cnt_n, &cnt_l, &cnt_c, arr) &&
          !my_flags->c && !my_flags->l) {
        print_files(&line, check, filename, my_flags, cnt_n);
      }
    }
  }
  free(line);
  if (my_flags->c) flag_c(&cnt_c, filename, check, my_flags, cnt_l);
  if (my_flags->l && cnt_l) printf("%s\n", filename);
}

void flag_c(int *cnt_c, char *filename, int check, struct avi_flags *my_flags,
            int cnt_l) {
  if (cnt_l && my_flags->l) *cnt_c = 1;
  if (!check || my_flags->h)
    printf("%d\n", *cnt_c);
  else
    printf("%s:%d\n", filename, *cnt_c);
}

int make_reg(char **line, struct avi_flags *my_flags, int *cnt_n, int *cnt_l,
             int *cnt_c, char *arr) {
  regex_t regex;
  int flag = 0;
  int comp;
  if (my_flags->i)
    comp = regcomp(&regex, arr, REG_EXTENDED | REG_ICASE);
  else
    comp = regcomp(&regex, arr, REG_EXTENDED);

  if (comp) {
    fprintf(stderr, "expression wasn't compiled");
  } else {
    int res = regexec(&regex, *line, 0, NULL, 0);
    if (!res && !my_flags->v) {
      flag = 1;
      if (my_flags->n) (*cnt_n)++;
      if (my_flags->c) (*cnt_c)++;
      if (my_flags->l) *cnt_l = 1;
    } else if (res && my_flags->v) {
      flag = 1;
      if (my_flags->n) (*cnt_n)++;
      if (my_flags->c) (*cnt_c)++;
      if (my_flags->l) *cnt_l = 1;
    } else {
      if (my_flags->n) (*cnt_n)++;
    }
  }
  regfree(&regex);
  return flag;
}

void print_files(char **line, int check, char *filename,
                 struct avi_flags *my_flags, int cnt_n) {
  if (check && !my_flags->h) printf("%s:", filename);
  if (my_flags->n)
    printf("%d:%s", cnt_n, *line);
  else
    printf("%s", *line);
}
