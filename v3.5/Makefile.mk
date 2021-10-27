all: fun.o main.o
	g++ main.o fun.o -o all

libra: all.h Matrix.h MyException.h

fun.o: libra fun.cpp
	g++ -c fun.cpp

main.o: libra main.cpp
	g++ -c main.cpp
	
