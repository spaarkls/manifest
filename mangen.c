#include "file_list.h"
#include "handler_path.h"
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_hash(file_list_t *list, const char *dirname);
void test_e_flag(file_list_t *list);

int main(int argc, char *argv[]) {

  flags_t flags = {0};
  char *dirname = parse_args(argc, argv, &flags);
  if (flags.h || flags.v || flags.bad) {
    put_info(&flags);
    free(dirname);
    return 0;
  }
  file_list_t *list = file_list_new();
  recursive_find(dirname, flags.except, list, strlen(dirname) + 1);

#ifdef TEST
  test_hash(list, dirname);
  test_e_flag(list);
#else
  file_list_print_path(list);
#endif
  file_list_destructor(list);
  free(dirname);
  free(list);
  return 0;
}

void test_hash(file_list_t *list, const char *dirname) {
  char **md = file_list_get_message_digest(list);
  char **path = file_list_get_filenames(list);
  int size = file_list_get_size(list);

  FILE *file = fopen("tests/path.txt", "w");
  for (int i = 0; i < size; i++) {
    fprintf(file, "%s/%s\n", dirname, path[i]);
  }
  fclose(file);

  file = fopen("tests/my_sha256.txt", "w");
  for (int i = 0; i < size; i++) {
    fprintf(file, "%s\n", md[i]);
  }
  fclose(file);
}

void test_e_flag(file_list_t *list) {
  char **path = file_list_get_filenames(list);
  int size = file_list_get_size(list);
  FILE *file = fopen("tests/path_with_flag_e.txt", "w");
  for (int i = 0; i < size; i++) {
    fprintf(file, "%s\n", path[i]);
  }
  fclose(file);
}