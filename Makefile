CC=clang
CFLAGS=-g
LIBS=-lm

HEADERS=$(wildcard src/*.h)

DAY=01

solution: ${HEADERS} src/${DAY}.cpp
	${CC} src/${DAY}.cpp -o $@ ${CFLAGS} ${LIBS}

