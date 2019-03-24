#include "include/header.h"
#include "lapack/lapack_wrapper.h"

void print_row(double *data,int stride,int len ) {
     printf("[");
    if(len>10) {
    for (int j=0;j<3;j+=1) {
        printf("%8.4f, ",data[j*stride]);
    }
    printf(" ... ");
        for (int j=len-3;j<len;j+=1) {
        printf("%8.4f",data[j*stride]);
        if(j!=(len-1))
            printf(", ");
        else
            printf(" ");
    }
    
    }
    else {
        for (int j=0;j<len;j+=1) {
            printf("%8.4f",data[j*stride]);
            if(j!=(len-1))
                printf(", ");
            else
                printf(" ");
        }
    }
    printf("]");
    putchar('\n'); 
}

void print_matrix(matrix *m) {

    if(m->rows>60) {
         for (int i=0;i<3;i++) {
              print_row(m->elems+i,m->rows,m->cols);
        }
        printf("\n\t.\n\t.\n\t.\n\n");
        for (int i=m->rows-3;i<m->rows;i++) {
            print_row(m->elems+i,m->rows,m->cols);
        }
    }
    else {
        for (int i=0;i<m->rows;i++) {
            print_row(m->elems+i,m->rows,m->cols);
        }
    }
    
    printf("Shape: (%d, %d)\n",m->rows,m->cols);
}


matrix* alloc_matrix(int rows,int cols) {
    unsigned long long i1 = rows;
    unsigned long long i2 =cols;

    matrix *m = malloc(sizeof(matrix));
    m->rows =rows;
    m->cols = cols;
    m->elems = malloc(i1*i2*8);
    return m;
}

matrix* multiply_matrix(matrix * m1,matrix* m2) {
    matrix *m3 = NULL;
    if(m1->cols==m2->rows) {

    m3 = alloc_matrix(m1->rows,m2->cols);
    matrix *temp = alloc_matrix(m3->rows,m3->cols);
    matrix_matrix_mult(m1->rows,m2->cols,m2->rows,1.0,0.0,m1->elems,m2->elems,m3->elems);
    free_matrix(temp);
    }
    return m3;
    
}

void fill_matrix(matrix* m,int val) {
    for (int c=0;c<m->rows;c++) {
        for (int r=0;r<m->cols;r++) {

            m->elems[r*m->cols+c]=val;
        }
    }
}

void set_identity(matrix* m) {
    for (int c=0;c<m->rows;c++) {
        for (int r=0;r<m->cols;r++) {
            if(r==c)
                m->elems[r+c*m->rows]=1;
            else
                m->elems[r+c*m->rows]=0;
        }
    }
}

matrix* transpose(matrix *m1) {
    matrix *m2 = alloc_matrix(m1->cols,m1->rows);
    for (int c=0;c<m1->cols;c++) {
        for (int r=0;r<m1->rows;r++) {
            m2->elems[r*m2->rows+c] = m1->elems[r+c*m1->rows];
        }
    }
    return m2;
}


matrix *invert(matrix *m) {
    matrix *m2 = alloc_matrix(m->rows,m->cols);
    matrix_invert(m->cols,m->elems,m2->elems);
    return m2;
}

void free_matrix(matrix *m) {
    free(m->elems);
    free(m);
}