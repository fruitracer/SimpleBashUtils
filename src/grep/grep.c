#include "grep.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: s_grep [OPTION]... PATTERNS [FILE]...");
  } else {
    struct Templates template = {0};
    struct Flags flag = flagParcer(argc, argv, &template);
    reg_comp(flag, argc, argv, template);
  }

  return 0;
}

struct Flags flagParcer(int argc, char *argv[], struct Templates *template) {
  int opt;
  struct Flags flag = {0};
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        flag.e = 1;
        pattern_make(optarg, template);
        break;
      case 'i':
        flag.i = 1;
        break;
      case 'v':
        flag.v = 1;
        break;
      case 'c':
        flag.c = 1;
        break;
      case 'l':
        flag.l = 1;
        break;
      case 'n':
        flag.n = 1;
        break;
      case 'h':
        flag.h = 1;
        break;
      case 's':
        flag.s = 1;
        break;
      case 'f':
        flag.f = 1;
        f_flag(flag, optarg, template);
        break;
      case 'o':
        flag.o = 1;
        break;
    }
  }

  if (flag.l) {
    flag.c = 0;
    flag.o = 0;
  }
  if (flag.c) {
    flag.o = 0;
  }

  if (template->len == 0) {
    pattern_make(argv[optind], template);
    optind++;
  }
  if (argc - optind == 1) {
    flag.h = 1;
  }

  return flag;
}

void pattern_make(char *pattern, struct Templates *template) {
  if (template->len != 0) {
    strcat(template->pat + template->len, "|");
    template->len++;
  }

  size_t pattern_len = strlen(pattern);
  strcpy(template->pat + template->len, "(");
  strcpy(template->pat + template->len + 1, pattern);
  strcpy(template->pat + template->len + 1 + pattern_len, ")");
  template->len += 2 + pattern_len;
}

void reg_comp(struct Flags flag, int argc, char *argv[],
              struct Templates template) {
  regex_t re;
  int result;
  if (flag.i) {
    result = regcomp(&re, template.pat, REG_ICASE | REG_EXTENDED);
  } else {
    result = regcomp(&re, template.pat, REG_EXTENDED);
  }

  if (result) {
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
  }

  for (int i = optind; i < argc; i++) {
    grep(flag, argv[i], &re);
  }
  regfree(&re);
}

void grep(struct Flags flag, char *path, regex_t *re) {
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    if (!flag.s)
      fprintf(stderr, "s_grep: %s No such file or directory\n", path);

  } else {
    char *line = NULL;
    size_t len = 0;

    int line_count = 1;
    int reg_count = 0;
    int read;
    while ((read = getline(&line, &len, f)) != -1) {
      int result = regexec(re, line, 0, NULL, 0);
      if (flag.v && flag.o) exit(1);
      if ((result == 0 && !flag.v) || (flag.v && result != 0)) {
        if (!flag.c && !flag.l) {
          if (!flag.h || (flag.v && result == 0)) {
            printf("%s:", path);
          }
          if (flag.n) {
            printf("%d:", line_count);
          }
          if (flag.o) {
            o_flag(re, line, path, flag, line_count);
          } else {
            output(line, read);
          }
        }
        reg_count++;
      }
      line_count++;
    }
    free(line);
    if (flag.c) {
      if (!flag.h) {
        printf("%s:", path);
      }
      printf("%d\n", reg_count);
    }

    if (flag.l && reg_count > 0) {
      printf("%s\n", path);
    }

    fclose(f);
  }
}

void f_flag(struct Flags flag, char *filepath, struct Templates *template) {
  FILE *f = fopen(filepath, "r");
  if (f == NULL) {
    if (!flag.s) {
      fprintf(stderr, "s_grep: %s No such file or directory\n", filepath);
    }
  } else {
    char *line = NULL;
    size_t len = 0;
    int read;
    while ((read = getline(&line, &len, f)) != -1) {
      if (line[read - 1] == '\n') {
        line[read - 1] = '\0';
      }
      pattern_make(line, template);
    }

    free(line);
    fclose(f);
  }
}

void output(char *line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') {
    putchar('\n');
  }
}

void o_flag(regex_t *re, char *line, char *path, struct Flags flag,
            int line_count) {
  regmatch_t match;
  int offset = 0;

  while (regexec(re, line + offset, 1, &match, 0) == 0) {
    if (offset > 0 && !flag.h) {
      printf("%s:", path);
    }
    if (offset > 0 && flag.n) {
      printf("%d:", line_count);
    }

    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[offset + i]);
    }
    putchar('\n');
    offset += match.rm_eo;
  }
}