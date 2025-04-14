#include "file_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Структура для хранения путей к файлам
 *
 * @param filenames Массив путей к файлам
 * @param size Текущий размер массива
 * @param capacity Емкость массива (изменяется)
 * @param message_digest Хеш-сумма файлов
 */
typedef struct file_list_t {
  char **filenames;
  int size;
  int capacity;
  char **message_digest;
} file_list_t;

file_list_t *file_list_new(void) {
  file_list_t *list = (file_list_t *)malloc(sizeof(file_list_t));
  if (!list)
    return NULL;
  list->size = 0;
  list->capacity = 8;

  list->filenames = (char **)malloc(sizeof(char *) * list->capacity);
  if (!list->filenames) {
    free(list->filenames);
    free(list);
    return NULL;
  }

  list->message_digest = (char **)malloc(sizeof(char *) * list->capacity);
  if (!list->message_digest) {
    free(list->message_digest);
    free(list);
    return NULL;
  }
  return list;
}

int file_list_get_size(file_list_t *list) { return list->size; }

int file_list_get_capacity(file_list_t *list) { return list->capacity; }

void file_list_destructor(file_list_t *list) {
  for (int i = 0; i < list->size; i++) {
    free(list->filenames[i]);
    free(list->message_digest[i]);
  }
  free(list->filenames);
  free(list->message_digest);
}

int file_list_append(file_list_t *list, const char *filepath,
                     const char *message_digest) {
  if (list->size >= list->capacity) {
    int temp_capacity = list->capacity * 2;
    char **temp = realloc(list->filenames, sizeof(char *) * temp_capacity);
    char **temp_digest =
        realloc(list->message_digest, sizeof(char *) * temp_capacity);
    if (!temp || !temp_digest) {
      return 0;
    } else {
      list->capacity = temp_capacity;
      list->filenames = temp;
      list->message_digest = temp_digest;
    }
  }
  list->filenames[list->size] =
      (char *)malloc(sizeof(char) * (strlen(filepath) + 1));
  list->message_digest[list->size] =
      (char *)malloc(sizeof(char) * (strlen(message_digest) + 1));
  if (!list->filenames[list->size] || !list->message_digest[list->size])
    return 0;

  strcpy(list->filenames[list->size], filepath);
  strcpy(list->message_digest[list->size], message_digest);
  list->size++;
  return 1;
}

char **file_list_get_filenames(file_list_t *list) { return list->filenames; }

char **file_list_get_message_digest(file_list_t *list) {
  return list->message_digest;
}

void file_list_print_path(file_list_t *list) {
  for (int i = 0; i < list->size; i++) {
    printf("%s: %s\n", list->filenames[i], list->message_digest[i]);
  }
}