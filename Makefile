CC=clang
CFLAGS=-g -Wall -Wno-unused-function
LIBS=-lm

HEADERS=$(wildcard src/*.h)

DAY=10b

.PHONY: solution

solution: ${HEADERS} src/${DAY}.cpp
	${CC} src/${DAY}.cpp -o $@ ${CFLAGS} ${LIBS}

