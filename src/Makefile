#all, install, uninstall, clean, dvi, dist, tests
CC = g++
CC_FLAGS = -Wall -Wextra -Werror -std=c++17 #-pedantic-errors
TEST_FLAGS = -lgtest -lgtest_main -pthread
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
SANITIZER_FLAGS = -fsanitize=address
PROJECT_NAME = A1_Maze-1
REPORT_DIR = report

all: install

install:
	cmake -S . -B build -G "Unix Makefiles"
	make -C build
	cd ./build && rm -rf CMakeFiles Maze cmake_install.cmake CMakeCache.txt Makefile
	open build

uninstall:
	rm -rf build

clean:
	@rm -rf *.o *.a test.out *.dSYM Maze.tar.gz CMakeLists.txt.user

dvi:
	open documentation.html

dist:
	tar -czf Maze.tar.gz main.cc Makefile model view_controller documentation.html CMakeLists.txt
	open .

tests: 
	clear
	@$(CC) $(CC_FLAGS) ./tests/tests_explore.cc ./tests/tests_eller.cc ./tests/tests_download.cc ./model/eller_algo.cc ./model/explore.cc ./model/download.cc -o test.out $(TEST_FLAGS)
	./test.out

%.o:%.cc
	$(CC) -c $(FLAGS) $< -o $@ -I .

style:
	clang-format -i --style=Google **/*.cc **/*.h 
	clang-format -n --style=Google **/*.cc **/*.h

.PHONY: all clean tests install uninstall dvi dist style

