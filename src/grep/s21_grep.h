#define _POSIX_C_SOURCE 200809L
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct avi_flags {
  int e;
  int i;
  int n;
  int v;
  int c;
  int l;
  int h;
  int s;
  int f;
  int x;
};
void fc(int argc, char **argv, int *check, struct avi_flags *my_flags,
        char *arr, char **arr_files, int *cnt_files);
void fill_arr(char *arr, struct avi_flags *my_flags, int *check);
void flag_c(int *cnt_c, char *filename, int check, struct avi_flags *my_flags,
            int cnt_l);
void handle_reg(int comp, int *flag, regex_t regex, struct avi_flags *my_flags,
                char **line, int *cnt_n, int *cnt_c, int *cnt_l);
int get_par(struct avi_flags *my_flags, int argc, char **argv, char *arr,
            char **arr_files, int *cnt_files);
void line_from_file(FILE *f, int check, char *filename,
                    struct avi_flags *my_flags, char *arr);
int make_reg(char **line, struct avi_flags *my_flags, int *cnt_n, int *cnt_l,
             int *cnt_c, char *arr);
void parser(int argc, char **argv);
void open_files(FILE *f, struct avi_flags *my_flags, char *arr,
                char **arr_files, int *cnt_files);
void print_files(char **line, int check, char *filename,
                 struct avi_flags *my_flags, int cnt_n);
