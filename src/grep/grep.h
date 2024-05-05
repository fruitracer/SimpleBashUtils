#ifndef GREP
#define GREP
#define _GNU_SOURCE
#define BUFFER_SIZE 2000
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Flags {
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
};

struct Templates {
  char pat[BUFFER_SIZE];
  int len;
};

struct Flags flagParcer(int argc, char *argv[], struct Templates *template);
void pattern_make(char *pattern, struct Templates *template);
void reg_comp(struct Flags flag, int argc, char *argv[],
              struct Templates template);
void grep(struct Flags flag, char *path, regex_t *re);
void o_flag(regex_t *re, char *line, char *path, struct Flags flag,
            int line_count);
void f_flag(struct Flags flag, char *filepath, struct Templates *template);
void output(char *line, int n);

#endif