CC_FLAGS = -Wall -g -std=c11

all:
	${CC} stack.c ${CC_FLAGS} -o stack
