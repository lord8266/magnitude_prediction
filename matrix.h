#ifndef mat_
#define mat_ 1

#include <stdio.h>
#include <stdlib.h>
typedef struct {
    double *elems;
    unsigned long rows;
    unsigned long cols;
}matrix;



void print_matrix(matrix *m);
matrix* alloc_matrix(int rows,int cols);
matrix* multiply_matrix(matrix * m1,matrix* m2) ;
matrix *transpose(matrix*);
void fill_matrix(matrix* m1,int val);
void set_identity(matrix* m1);
matrix *invert(matrix *); 
#endif