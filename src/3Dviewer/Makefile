# .PHONY: all install uninstall clean dvi dist tests gcov_report lint leaks

CC = gcc
# CFLAGS=-fsanitize=address -Wall -Werror -Wextra -std=c11
GCOV=-fprofile-arcs -ftest-coverage
OS=$(shell uname)
DIR=../build/
NAME=3D_Viewer_E2
ifeq ($(OS), Linux)
	LIBS=-lcheck -lpthread -lrt -lm -lsubunit
else
	LIBS=-lcheck
endif

all: clean build

build: clean
	mkdir $(DIR); cp -rf *.* $(DIR); cd $(DIR); qmake 3DViewer.pro; make; rm -rf *.c *.h *.cpp *.ui *.o

install: build
	mkdir $(HOME)/Desktop/$(NAME)/
	cp -rf $(DIR)3DViewer.app $(HOME)/Desktop/$(NAME)/
	make clean

uninstall:
	rm -rf $(HOME)/Desktop/$(NAME)/

dvi:
	open -a "Google Chrome" ./html/description.html

dist:
	rm -rf archive_v1
	mkdir archive_v1
	cp Makefile *.c *.h archive_v1/
	cp -a QT archive_v1
	cp -a html archive_v1
	tar -cvzf $(HOME)/Desktop/archive_v1.tgz archive_v1/
	rm -rf archive_v1/

tests: 
	$(CC) $(CFLAGS) test.c s21_3d.c $(LIBS) -o test.out
	./test.out

gcov_report:
	$(CC) $(GCOV) test.c s21_3d.c $(LIBS) -o GCOV_test.out
	./GCOV_test.out
	lcov -t "GCOV_test" -o GCOV_test.info -c -d . 
	genhtml -o ./report GCOV_test.info
	open -a "Google Chrome" report/index.html

leaks:
	CK_FORK=no leaks --atExit -- ./test.out
	
check:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	cppcheck --enable=all --suppress=missingIncludeSystem s21_3d.c s21_3d.h test.c
	python3 ../materials/linters/cpplint.py --extensions=c s21_3d.c s21_3d.h test.c
	@rm -f *.cfg

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out
	rm -rf ./report
	rm -rf ../build
	rm -rf ./Documentation
	rm -rf $(HOME)/Desktop/$(NAME)_archive.tgz

clang:
	clang-format -i ./*.c ./*.h ./*.cpp ./*.h
	clang-format -n ./*.c ./*.h ./*.cpp ./*.h
