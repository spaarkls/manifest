#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *parse_args(int argc, char *argv[], flags_t *flags) {
  char *dirname = NULL;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == 'e' && argv[i][2] == '\0') {
        flags->e = 1;
        if (i + 1 < argc) {
          strncpy(flags->except, argv[i + 1], MAX_LEN_CMD);
        }
        i++;
        continue;
      }
      parse_flags(argv[i], flags);
    } else {
      dirname = (char *)malloc(sizeof(char) * (strlen(argv[i]) + 1));
      strcpy(dirname, argv[i]);
    }
  }
  if (!dirname) {
    dirname = (char *)malloc(sizeof(char) * 2);
    strcpy(dirname, ".");
  }
  char *ptr = dirname + strlen(dirname) - 1;
  while ((*ptr) == '/') {
    ptr--;
  }
  *(++ptr) = '\0';
  return dirname;
}

void parse_flags(const char *string, flags_t *flags) {
  if (strlen(string) > 2) {
    strncpy(flags->bad_cmd, string, MAX_LEN_CMD);
    flags->bad = 1;
    return;
  }

  switch (string[1]) {
  case 'h':
    flags->h = 1;
    break;
  case 'v':
    flags->v = 1;
    break;
  case 'e':
    flags->e = 1;
    break;
  default:
    flags->bad = 1;
    strcpy(flags->bad_cmd, string);
    break;
  }
}

void put_info(flags_t *flags) {
  if (flags->h) {
    printf("Использование: ./mangen [DIRPATH] [OPTIONS]\n");
    printf("где DIRPATH = путь к файлу или к директории\n");
    printf("OPTIONS = ключи"
    printf("Допустимые флаги:\n./mangen -e <except_file_name> исключает файл из обработки\n");
    printf(" ./mangen -v вывод информации о версии и авторе\n");
  }
  if (flags->v) {
    printf("mangen version 1.0\n");
    printf("Author: Баранов Дмитрий\nEmail: ds.baranof@yandex.ru\n");
  }
  if (flags->bad) {
    printf("mangen: неверный ключ %s\n", flags->bad_cmd);
    printf(
        "По команде ./mangen -h можно получить информацию по использованию\n");
  }
}
