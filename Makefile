CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
FLAGS_COV = -lcheck -lgcov -fprofile-arcs --coverage
LDFLAGS = -lgtest -lgtest_main -lgmock -lgmock_main -pthread -lncurses
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
OS_NAME=$(shell uname)

INCLUDES=-I/Users/sanchez02/.brew/opt/qt/include \
         -I/Users/sanchez02/.brew/opt/qt/include/QtWidgets \
         -I/Users/sanchez02/.brew/opt/qt/include/QtCore \
         -I/Users/sanchez02/.brew/opt/qt/include/QtGui

ifeq (${OS_NAME}, Linux)
FLAGS_L = -lcheck -lm -lpthread -lrt -lsubunit
else 
FLAGS_L = -lcheck
endif


all: install 

snake_model.a:
	gcc -Wall -Werror -Wextra -std=c17 $(INCLUDES) -c brick_game/snake/snakegame_back.c
	ar rcs snakegame_back.a snakegame_back.o
	ranlib snakegame_back.a
	rm -rf snakegame_back.o


tetris_model.a:
	gcc -Wall -Werror -Wextra -std=c17 $(INCLUDES) -c brick_game/tetris/tetris_back_desktop.c 
	ar rcs tetris_back_desktop.a tetris_back_desktop.o
	ranlib tetris_back_desktop.a
	rm -rf tetris_back_desktop.o


clean:
	rm -rf build
	rm -rf *.a
	rm -rf *.o
	rm -rf *.h.gch
	rm -rf gui/cli/*.h.gch
	rm -rf tetris.out
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.out
	rm -rf snake_test
	rm -rf test

build_console_version: tetris_back.a tetris_front.a
	gcc -Wall -Werror -Wextra -std=c17 -c brick_game/tetris/tetris_main.c -o tetris_main.o

	gcc -Wall -Werror -Wextra -std=c17 -c brick_game/snake/snakegame_back.c -o snakegame_back.o

	g++ -Wall -Werror -Wextra -std=c++17 tetris_main.o snakegame_back.o tetris_back.a tetris_front.a -lncurses -o tetris.out

build_desktop_version: clean
	
	mkdir build
	cd build && cmake ..
	make -C build
	
install: build_console_version build_desktop_version

tetris_back.a:
	gcc -Wall -Werror -Wextra -std=c17 -c brick_game/tetris/tetris_back.c 
	ar rcs tetris_back.a tetris_back.o
	ranlib tetris_back.a
	rm -rf tetris_back.o
	rm -rf tetris_back.h.gch

tetris_front.a:
	gcc -Wall -Werror -Wextra -std=c17 -c gui/cli/tetris_front.c gui/cli/tetris_front.h 
	ar rcs tetris_front.a tetris_front.o
	ranlib tetris_front.a
	rm -rf tetris_front.o
	rm -rf ../../gui/cli/tetris_front.h.gch

uninstall: clean
	rm -rf brick_game/db/high_score_tetris.txt
	rm -rf brick_game/db/high_score_snake.txt

run_desktop_version: clean build_desktop_version
	sh run.sh

run_console_version: clean build_console_version
	./tetris.out


test_tetris_back: clean tetris_back.a
	gcc brick_game/tetris/tetris_tests.c tetris_back.a $(FLAGS_L) -lncurses -rpath '/usr/local/lib' -o test
	./test

	
snake_tests: clean snake_model.a
	g++ -Wall -Werror -Wextra -std=c++17 -arch arm64 brick_game/snake/snake_tests.cpp  snakegame_back.a -o snake_test -lgtest -lgtest_main -lgmock -lgmock_main -pthread -lncurses 
	clear
	./snake_test
	rm -rf snake_model.a
	rm -rf snake_test

dist:
	tar -cvzf archive.tar ./
	clear

dvi:
	open ./documentation.md