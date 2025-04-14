#ifndef __FILE_LIST_H__
#define __FILE_LIST_H__

#undef MAX_LEN_PATH
#define MAX_LEN_PATH 1024

// Структура file_list_t Для хранения массива названия файлов и их хешей
typedef struct file_list_t file_list_t;


// ------------------------------------------- //
// Поведенческие функции структуры file_list_t //
// ------------------------------------------- //
/**
 * @brief Функция для получения текущего размера массива из структуры
 * 
 * @param list Структура где хранится информация о массиве с файлами 
 * @return Возвращает длину массива
 */
int file_list_get_size(file_list_t *list);


/**
 * @brief Функция для получения ёмкости массива с файлами
 * 
 * @param list Структура где хранится информация о массиве с файлами
 * @return Возвращает ёмкость массива в структуре лист
 */
int file_list_get_capacity(file_list_t *list);


/**
 * @brief Создаёт и инициализирует новую структуру file_list_t
 * @return Указатель на новую структуру, либо NULL в случае ошибки
 */
file_list_t *file_list_new(void);


/**
 * @brief Функция память, занятую структурой file_list_t и её содержимым
 * 
 * @param list Структура где хранится информация о массиве с файлами
 */
void file_list_destructor(file_list_t *list);


/**
 * @brief Функция добавления нового пути к файлу в структуру
 * 
 * @param list Структура где хранится информация о массиве с файлами
 * @param string Путь который нужно добавить в структуру
 * @param message_digest Хеш сумма файла строки string
 * @return Возвращает 1 если добавление прошло успешно, 0 если нет
 */
int file_list_append(file_list_t *list, const char *string, const char *message_digest);


/**
 * @brief Функция устанавливет базоввую директорию
 * 
 * @param list Структура где хранится информация о массиве с файлами
 * @param base_path Базовая директория относительно которой начинается поиск
 */
void file_list_set_base_dir(file_list_t *list, const char *base_path);




/**
 * @brief Функция для получения базовой директории относительно которой был поиск
 * 
 * @param list Структура где хранится информация о массиве с файлами
 * @return Возвращает строку, которая содержит базовую директорию (char *)
 */
char *file_list_get_base_dir(file_list_t *list);


/**
 * @brief Функция для получения массива строк с путями к файлам
 * 
 * @param list Структура где хранится информация о массиве с файлами
 * @return Указатель на массив строк (char **) с путями к файлам
 */
char **file_list_get_filenames(file_list_t *list);


/**
 * @brief Функция для получения массива хеш-суммы
 * 
 * @param list Структура где хранится информация о массиве с файлами
 * @return Указатель на массив хеш-сумм (char **)  
 */
char **file_list_get_message_digest(file_list_t *list);


/**
 * @brief Функция вывода всех путей из структуры file_list_t 
 * 
 * @param list Структура где хранится информация о массиве с файлами
 */
void file_list_print_path(file_list_t *list);

#endif
