#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NO_COLOR='\033[0m'

>"tests/sha256.txt"
echo ""

echo "Starting tests..."
echo "Test 1. Сравнение хешей"
echo "[-] Запуск программы..."
./test_mangen tests/test_dir/
file="tests/path.txt"

echo "[-] Генерация эталонных хешей..."
while IFS= read -r line
do
    sha256sum "$line" | awk '{print $1}' | tr 'a-z' 'A-Z' >> "tests/sha256.txt"
done < "$file"

echo "[-] Сравнение контрольных хешей..."
if diff -q tests/sha256.txt tests/my_sha256.txt; then
    printf "${GREEN} Тест успешно пройден. Хеши совпадают ${NO_COLOR}\n"
else 
    printf "${RED} Хеши не совпадают ${NO_COLOR}\n"
    printf "[-]Различия\n"
    diff -u tests/sha256.txt tests/my_sha256.txt 
fi

echo ""
echo "Test 2. Указан путь которого нет"
echo "[-] Запуск программы..."
./test_mangen qwerty12345 > tests/bad_path.txt
if grep -q "Данного каталога не существует" tests/bad_path.txt; then
    printf "${GREEN} Тест успешно пройден ${NO_COLOR}\n"
else 
    printf "${RED} Ошибка ${NO_COLOR}\n"
fi

echo ""
echo "Test 3. Вывод путей с флагом -e"
./test_mangen tests/test_dir/ -e dir1
echo "[-] Генерация путей..."
echo "[-] Сравнение путей..."
if grep -q "dir1" tests/path_with_flag_e.txt; then
    printf "${RED} Пути не совпадают ${NO_COLOR}\n"
else 
    printf "${GREEN} Тест успешно пройден ${NO_COLOR}\n"
fi

echo ""
echo "Test 4. Тест на учтечку памяти"
echo "[-] Запуск программы..."
echo "[-] Проверка valgrind..."
valgrind --leak-check=full ./test_mangen 2>&1 | tee tests/mem_leak.txt
if grep -q "All heap blocks were freed -- no leaks are possible" tests/mem_leak.txt; then
    printf "${GREEN} Тест успешно пройден. Утечек памяти нет ${NO_COLOR}\n"
else 
    printf "${RED} Есть утечки памяти ${NO_COLOR}\n"
fi

rm -rf tests/path.txt