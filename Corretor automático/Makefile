all: skiplist.o
	gcc main.c skiplist.o -lm -o main

pilha.o: skiplist.c skiplist.h
	gcc -c skiplist.c

run: 
	./main