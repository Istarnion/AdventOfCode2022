CC=clang
CFLAGS=-g -Wall
LIBS=-lm

HEADERS=$(wildcard src/*.h)

DAY=06b

.PHONY: solution

solution: ${HEADERS} src/${DAY}.cpp
	${CC} src/${DAY}.cpp -o $@ ${CFLAGS} ${LIBS}

