#include "cat.h"

int main(int argc, char *argv[]) {
  struct Flags flag = flagParcer(argc, argv);
  output(&flag, argv, argc);
  return 0;
}

struct Flags flagParcer(int argc, char *argv[]) {
  struct Flags flag = {0};
  int opt;
  struct option long_options[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                  {"number", no_argument, NULL, 'n'},
                                  {"squeeze-blank", no_argument, NULL, 's'},
                                  {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "bEensTtv", long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'b':
        flag.b = 1;
        break;
      case 'n':
        flag.n = 1;
        break;
      case 'E':
        flag.E = 1;
        break;
      case 'e':
        flag.E = 1;
        flag.v = 1;
        break;
      case 's':
        flag.s = 1;
        break;
      case 'T':
        flag.T = 1;
        break;
      case 't':
        flag.T = 1;
        flag.v = 1;
        break;
      case 'v':
        flag.v = 1;
        break;
      case '?':
        fprintf(stderr, "Wrong option");
        exit(1);
    }
  }
  return flag;
}

void output(struct Flags *flag, char *argv[], int argc) {
  int line_count = 1;
  int empty_lines = 0;
  int prev_char = '\n';
  for (int i = optind; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    if (fp == NULL) {
      fprintf(stderr, "cat: %s: No such file or directory", argv[i]);
    } else {
      int current_char = fgetc(fp);
      while (current_char != EOF) {
        if (flag->s && prev_char == '\n' && current_char == '\n' &&
            empty_lines == 1) {
        } else {
          if (prev_char == '\n' && current_char == '\n') {
            empty_lines = 1;
          } else {
            empty_lines = 0;
          }
          if (((flag->n && !flag->b) || (flag->b && current_char != '\n')) &&
              prev_char == '\n') {
            printf("%6d\t", line_count);
            line_count++;
          }
          if (flag->E && current_char == '\n') {
            printf("$");
          }
          if (flag->T && current_char == '\t') {
            printf("^");
            current_char += 64;
          }
          if (flag->v) {
            vflag_output(current_char);
          } else {
            putchar(current_char);
          }
        }
        prev_char = current_char;
        current_char = fgetc(fp);
      }
      fclose(fp);
    }
  }
}


void vflag_output(unsigned char c) {
  if (c == '\n' || c == '\t' || (c >= 32 && c < 127)) {
    printf("%c", c);
  } else if (c < 32) {
    printf("^%c", c += 64);
  } else if (c == 127) {
    printf("^?");
  } else if (c > 127 && c < 160) {
    printf("M-^%c", c -= 64);
  } else if ((c >= 160 && c < 255)) {
    printf("M-%c", c -= 128);
  } else if (c == 255)
    printf("M-^?");
}