#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
struct avi_flags {
  int b;
  int e;
  int n;
  int t;
  int s;
  int v;
};
void check_symb(int *c, struct avi_flags *my_flags, int *flag);
void flag_n(int *first_str, int *cnt_n, int *prev, int fl_s);
void flag_b(int *first_str, int *cnt_n, int *prev, int *c, int *cnt_b);
int flag_s(int *prev_2, int *prev, int *c, int *flag);
void flag_e(int *c, int *flag, int fl_s, struct avi_flags *my_flags);
void flag_t(int *flag);
void parser(int argc, char **argv);
int get_par(int argc, char **argv, struct avi_flags *my_flags);
void open_files(char **argv, int argc, struct avi_flags *my_flags);
void print_char(int *c, struct avi_flags *my_flags, int *prev, int *cnt_b,
                int *cnt_n, int *prev_2, int *first_str);
void by_char(FILE *f, struct avi_flags *my_flags, int check_flag);