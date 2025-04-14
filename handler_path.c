#include "handler_path.h"
#include "file_list.h"
#include <dirent.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void get_hash(const char *filename, char *filehash) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    printf("Error fopen\n");
    return;
  }
  char buffer[4096];
  size_t count_bytes = 0;
  EVP_MD_CTX *context = EVP_MD_CTX_new();
  const EVP_MD *md = EVP_sha256();
  EVP_DigestInit_ex(context, md, NULL);

  while ((count_bytes = fread(buffer, sizeof(char), sizeof(buffer), file)) >
         0) {
    EVP_DigestUpdate(context, buffer, count_bytes);
  }

  unsigned char hash[EVP_MAX_MD_SIZE];
  unsigned int len = 0;

  EVP_DigestFinal_ex(context, hash, &len);
  for (unsigned int i = 0; i < len; i++) {
    sprintf(filehash + (i * 2), "%02X", hash[i]);
  }

  EVP_MD_CTX_free(context);
  fclose(file);
}

void recursive_find(char *dirname, char *except, file_list_t *list,
                    int offset) {
  DIR *dir = opendir(dirname);
  if (!dir) {
    printf("Данного каталога не существует: %s\n", dirname);
    return;
  }

  struct dirent *file;
  while ((file = readdir(dir)) != NULL) {
    if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0 ||
        (strlen(except) && !strcmp(file->d_name, except))) {
      continue;
    }
    char path[MAX_LEN_PATH];
    memset(path, 0, MAX_LEN_PATH);
    strcat(path, dirname);
    strcat(path, "/");
    strcat(path, file->d_name);
    struct stat file_stat;
    if (stat(path, &file_stat)) {
      continue;
    }
    if (S_ISREG(file_stat.st_mode)) {
      char hash[EVP_MAX_MD_SIZE];
      get_hash(path, hash);
      if (!file_list_append(list, path + offset, hash)) {
        printf("Error file_list_append: %s\n", path + offset);
        closedir(dir);
        file_list_destructor(list);
        return;
      }
    }
  }
  rewinddir(dir);
  while ((file = readdir(dir)) != NULL) {
    if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0 ||
        (strlen(except) && !strcmp(file->d_name, except))) {
      continue;
    }
    char path[MAX_LEN_PATH];
    memset(path, 0, MAX_LEN_PATH);
    strcat(path, dirname);
    strcat(path, "/");
    strcat(path, file->d_name);

    struct stat file_stat;
    if (stat(path, &file_stat)) {
      continue;
    }
    if (S_ISDIR(file_stat.st_mode)) {
      recursive_find(path, except, list, offset);
    }
  }

  closedir(dir);
}
