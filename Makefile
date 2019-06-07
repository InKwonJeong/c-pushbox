all:main

main:main.cpp board.o
	g++ -o main main.cpp board.o -lncurses

board.o:board.cpp
	g++ -c board.o board.cpp -lncurses
