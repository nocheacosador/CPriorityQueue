SRC_DIR = src
BIN_DIR = bin
CC = gcc
CFLAGS = -Wall -std=c11 -ggdb -pedantic

all:
	mkdir -p ${BIN_DIR}
	${CC} ${CFLAGS} -o ${BIN_DIR}/priority_queue ${SRC_DIR}/Main.c ${SRC_DIR}/PriorityQueue.c ${SRC_DIR}/MemoryAllocation.c

clean:
	rm -r ${BIN_DIR}