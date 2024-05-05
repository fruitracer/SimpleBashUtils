#ifndef CAT
#define CAT
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

struct Flags {
  int b;
  int E;
  int n;
  int s;
  int T;
  int v;
};

struct Flags flagParcer(int argc, char *argv[]);
void output(struct Flags *flag, char *argv[], int argc);
void vflag_output(unsigned char c);

#endif