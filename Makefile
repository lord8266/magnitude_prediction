CFLAGS=-Wall -Werror -std=gnu11 -g -Wno-unused-variable

LAPACK_LIBS = `pkg-config --libs blas-atlas lapack-atlas`
LAPACK_CFLAGS = `pkg-config --cflags blas-atlas lapack-atlas`

OBJECTS=csv_utility.o matrix.o lapack_wrapper.o linear_regression.o

all:$(OBJECTS) predict.c include/header.h datasets/earthquake2.csv
	gcc $(CFLAGS) predict.c $(OBJECTS) -o $(m) -lm $(LAPACK_LIBS)

csv_utilty.o:csv_utility.c include/csv_utility.h include/header.h
	gcc $(CFLAGS) -c csv_utility.c -o csv_utility.o

matrix.o:matrix.c include/matrix.h include/header.h
	gcc $(CFLAGS) -c matrix.c -o matrix.o

lapack_wrapper.o:lapack/lapack_wrapper.c lapack/lapack_wrapper.h
	gcc $(CFLAGS) $(LAPACK_CFLAGS) -c lapack/lapack_wrapper.c -o lapack_wrapper.o

linear_regression.o:linear_regression.c include/linear_regression.h include/header.h
	gcc $(CFLAGS) -c linear_regression.c -o linear_regression.o