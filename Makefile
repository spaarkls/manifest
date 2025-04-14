CC = gcc
CFLAGS= -std=c11 -Wall -Werror -Wextra
TARGET = mangen
TEST_FILE = test_mangen

all: mangen clean_obj

mangen: mangen.o handler_path.o parse.o file_list.o
	$(CC) $(CFLAGS) $^ -lssl -lcrypto -o $(TARGET)

mangen.o: mangen.c handler_path.h parse.h file_list.h
	$(CC) $(CFLAGS) -c mangen.c -o mangen.o

handler_path.o: handler_path.c handler_path.h file_list.h
	$(CC) $(CFLAGS) -c handler_path.c -o handler_path.o

parse.o: parse.c parse.h
	$(CC) $(CFLAGS) -c parse.c -o parse.o

file_list.o: file_list.c file_list.h
	$(CC) $(CFLAGS) -c file_list.c -o file_list.o


test: mangen_test clean_obj

mangen_test: mangen_test.o handler_path.o parse.o file_list.o
	$(CC) $(CFLAGS) $^ -lcrypto -lssl -o $(TEST_FILE)
	bash ./check.sh

mangen_test.o: mangen.c handler_path.h parse.h file_list.h
	$(CC) $(CFLAGS) -c mangen.c -DTEST -o mangen_test.o

clean:
	rm -rf *.o $(TARGET) $(TEST_FILE)

clean_obj:
	rm -rf *.o