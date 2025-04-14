#ifndef __PARSE_H__
#define __PARSE_H__


#define MAX_LEN_CMD 100

/**
 * @brief Структура для хранения ключей
 * 
 * @param bad Переменная сигнализирует о неверном ключе
 * @param bad_cmd Запоминает последний неправильный ключ
 * @param h Ключ вывода информации для правильного использования
 * @param v Ключ вывода информации о версии приложения, авторе.
 * @param e Ключ для исключения из поиска файла/директории который содержит данное названия
 * @param except Слово которое не ищем. 
 */
typedef struct {
    int bad;
    char bad_cmd[MAX_LEN_CMD];
    int h;
    int v;
    int e;
    char except[MAX_LEN_CMD];
} flags_t;


/**
 * @brief Функция парсинга аргументов из командной строки
 * 
 * @param argc Количество аргументов
 * @param argv Массив аргументов
 * @param flags Структура для обозначения ключей
 * @return Возвращает путь в виде строки, где нужно производить поиск 
 */
char *parse_args(int argc, char *argv[], flags_t *flags);


/**
 * @brief Функция парсинга ключа из строки string 
 * 
 * @param string Строка, которая содержит ключ
 * @param flags Структура для обобзначения ключей
 */
void parse_flags(const char *string, flags_t *flags);


/**
 * @brief Функция вывода информации в зависимости от пойманного ключа
 * 
 * @param flags Структура ключей
 */
void put_info(flags_t *flags);

#endif