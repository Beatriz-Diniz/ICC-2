all: spotify.o
	gcc main.c spotify.o -lm -o main

spotify.o: spotify.c spotify.h
	gcc -c spotify.c

run: 
	./main