CFLAGS=-Wall -Werror -std=gnu11 -g -Wno-unused-variable

LAPACK_LIBS = `pkg-config --libs blas-atlas lapack-atlas`
LAPACK_CFLAGS = `pkg-config --cflags blas-atlas lapack-atlas`

all:csv_utility.o matrix.o header.h lapack_wrapper.o
	gcc $(CFLAGS) $(m).c csv_utility.o matrix.o lapack_wrapper.o -o $(m) -lm $(LAPACK_LIBS)

csv_utilty.o:csv_utility.c csv_utility.h header.h
	gcc $(CFLAGS) -c csv_utility.c -o csv_utility.o

matrix.o:matrix.c matrix.h header.h
	gcc $(CFLAGS) -c matrix.c -o matrix.o

lapack_wrapper.o:lapack/lapack_wrapper.c lapack/lapack_wrapper.h
	gcc $(CFLAGS) $(LAPACK_CFLAGS) -c lapack/lapack_wrapper.c -o lapack_wrapper.o -lm $(LAPACK_LIBS)

lapack_example:lapack_wrapper.o
	gcc $(CFLAGS) $(LAPACK_CFLAGS) lapack/lapack_example.c lapack_wrapper.o -o lapack_example -lm $(LAPACK_LIBS)
