CC=clang
CFLAGS=-std=c++11 -g -Wall -Wno-unused-function
LIBS=-lm

HEADERS=$(wildcard src/*.h)

DAY=17b

.PHONY: solution

solution: ${HEADERS} src/${DAY}.cpp
	${CC} src/${DAY}.cpp -o $@ ${CFLAGS} ${LIBS}

