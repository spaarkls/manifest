#ifndef __HANDLER_PATH_H__
#define __HANDLER_PATH_H__

typedef struct file_list_t file_list_t;

/**
 * @brief Функция для составления пути к файлам
 * 
 * @param dirname Путь где будет поиск
 * @param except Название, которое пропускаем
 * @param list Структура для сохранения путей
 * @param offset Смещение для игнорирования корня папки
 */
void recursive_find(char *dirname, char *except, file_list_t *list, int offset);


/**
 * @brief Функция генерации хеш-суммы sha-2256
 * 
 * @param filename Путь к файлу
 * @param filehash Куда записываем хеш-сумму
 */
void get_hash(const char *filename, char *filehash);

#endif
