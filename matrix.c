#include "include/header.h"
#include "lapack/lapack_wrapper.h"

//matrices are ordered in column major format required by lapack
//all functions which return matrix* allocate a new matrix which must be deallocated by the user

void print_row(double *data,int stride,int len ) { 

    //for column major you need to jump row elements every iteration since you can nly print horizontally
    //hence a stride is required and len specifies length of column
     printf("[");

    if(len>10) { //if len ( ie. cols ) is greater than 10 then dont print everything

    for (int j=0;j<3;j+=1) {
        printf("%8.4f, ",data[j*stride]); //equal spacing for numbers
    }
    printf(" ... "); //numpy does the same thing

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
    //prints the matrix (calls print row every iteration of rows)

    if(m->rows>60) { //if number of cols is greatet than 60 dont print everything
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
    //return a new matrix
    //allocating a new matrix m3 since thats how lapack library has defined some optimization
    //see lapack_wrapper.c

    matrix *m3 = NULL;
    if(m1->cols==m2->rows) {

    m3 = alloc_matrix(m1->rows,m2->cols);
    matrix *temp = alloc_matrix(m3->rows,m3->cols);
    matrix_matrix_mult(m1->rows,m2->cols,m2->rows,1.0,0.0,m1->elems,m2->elems,m3->elems);//defined in lapack_wrapper library
    free_matrix(temp);
    }
    return m3;
    
}

void fill_matrix(matrix* m,int val) {
    //fill matrix with val
    //change the matrix inplace
    for (int c=0;c<m->rows;c++) {
        for (int r=0;r<m->cols;r++) {

            m->elems[r*m->cols+c]=val;
        }
    }
}

void set_identity(matrix* m) {

    //change the matrix inplace
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
    //allocate a new matrix and return 
    matrix *m2 = alloc_matrix(m1->cols,m1->rows);
    for (int c=0;c<m1->cols;c++) {
        for (int r=0;r<m1->rows;r++) {
            m2->elems[r*m2->rows+c] = m1->elems[r+c*m1->rows];
        }
    }
    return m2;
}


matrix *invert(matrix *m) {
    //allocate a new matrix and return 
    matrix *m2 = alloc_matrix(m->rows,m->cols);
    matrix_invert(m->cols,m->elems,m2->elems); //defined in laplace warapper library
    return m2;
}

void free_matrix(matrix *m) {
    //first free the elems (the double pointer then the matrix struct itself)
    free(m->elems);
    free(m);
}