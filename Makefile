CFLAGS=-Wall -Werror -std=gnu11 -g -Wno-unused-variable

all:parse_file.o matrix.o header.h 
	gcc $(CFLAGS) $(m).c parse_file.o matrix.o -o $(m)

parse_file.o:parse_file.c
	gcc $(CFLAGS) -c parse_file.c -o parse_file.o

matrix.o:matrix.c matrix.h
	gcc $(CFLAGS) -c matrix.c -o matrix.o
