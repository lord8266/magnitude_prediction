#ifndef mat_
#define mat_ 1

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double *elems;
    int rows;
    int cols;
}matrix;

matrix* alloc_matrix(int rows,int cols);
matrix* multiply_matrix(matrix * m1,matrix* m2) ;
matrix* transpose(matrix*);
matrix* invert(matrix *);

void    print_matrix(matrix *m);
void    fill_matrix(matrix* m1,int val);
void    set_identity(matrix* m1);
void    free_matrix(matrix*);


#endif