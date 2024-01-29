CC=gcc
CFLAGS=-c -Wall  -Werror -Wextra -g -std=c11
CCTEST=gcc -fprofile-arcs -ftest-coverage

all: s21_math.a

s21_math.a: s21_math.o
	ar rc s21_math.a s21_math.o

s21_math.o: s21_math.c 
	$(CC) $(CFLAGS) s21_math.c


test.o: test.c 
	$(CC) $(CFLAGS) test.c

all_tests: tests/*.c
	$(CC) $(CFLAGS) tests/*.c

test: clean test.o all_tests s21_math.a
ifeq ($(shell uname),Linux)   
	$(CC) test.o test_s21_*.o s21_math.a -o unit_tests -lcheck -lm -lsubunit   
else   
	$(CC) test.o test_s21_*.o s21_math.a -o unit_tests -lcheck   
endif 


html_s21_math.a: html_s21_math.o 
	ar rc html_s21_math.a s21_math.o 

html_s21_math.o: s21_math.c 
	$(CCTEST) $(CFLAGS) s21_math.c

html_test: test.o all_tests html_s21_math.a
ifeq ($(shell uname),Linux)   
	$(CCTEST)  test.o test_s21_*.o html_s21_math.a -o unit_tests -lcheck -lm -lsubunit   
else   
	$(CCTEST)  test.o test_s21_*.o html_s21_math.a -o unit_tests -lcheck    
endif

gcov_report:clean html_test
	./unit_tests
	lcov -t "unit_tests" -o fizzbuzz.info -c -d .
	genhtml -o report fizzbuzz.info

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info *.gcov unit_tests 
