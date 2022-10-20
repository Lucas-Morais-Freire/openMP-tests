CC = gcc
CFLAGS = -Wall -Wextra -fopenmp -O3
MAIN = linked.c
SRCS = 
BIN = ${MAIN:.c=.exe}

compile: ${BIN}

${BIN}: ${MAIN}
	${CC} ${CFLAGS} ${SRCS} ${MAIN} -o ${BIN}

run: ${BIN}
	@./${BIN}