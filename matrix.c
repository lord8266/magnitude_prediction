#include "header.h"


void print_row(float *data,int len) {
     printf("[");
    if(len>10) {
    for (int j=0;j<3;j++) {
        printf("%8.4f, ",data[j]);
    }
    printf(" ... ");
        for (int j=len-3;j<len;j++) {
        printf("%8.4f",data[j]);
        if(j!=(len-1))
            printf(", ");
        else
            printf(" ");
    }
    
    }
    else {
        for (int j=0;j<len;j++) {
            printf("%8.4f",data[j]);
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
              print_row(m->elems+m->cols*i,m->cols);
        }
        printf("\n\t.\n\t.\n\t.\n\n");
        for (int i=m->rows-3;i<m->rows;i++) {
            print_row(m->elems+m->cols*i,m->cols);
        }
    }
    else {
        for (int i=0;i<m->rows;i++) {
            print_row(m->elems+m->cols*i,m->cols);
        }
    }
    
    printf("Shape: (%d, %d)\n",m->rows,m->cols);
}


matrix* alloc_matrix(int rows,int cols) {
    matrix *m = malloc(sizeof(matrix));
    m->rows =rows;
    m->cols = cols;
    m->elems = malloc(rows*cols*4);
    return m;
}

matrix* multiply_matrix(matrix * m1,matrix* m2) {
    matrix *m3 = alloc_matrix(m1->rows,m2->cols);
    for (int i=0;i<m3->rows;i++) {
        for (int j=0;j<m3->cols;j++) {
            m3->elems[i*m3->cols+j] =0;
            for (int k=0;k<m1->cols;k++) { 
                m3->elems[i*m3->cols+j]+= m1->elems[i*m1->cols+k]*m2->elems[k*m2->cols+j];
               
            }
            
        }
    }
    return m3;
}

void fill_matrix(matrix* m,int val) {
    for (int r=0;r<m->rows;r++) {
        for (int c=0;c<m->cols;c++) {

            m->elems[r*m->cols+c]=val;
        }
    }
}

void set_identity(matrix* m) {
    for (int r=0;r<m->rows;r++) {
        for (int c=0;c<m->cols;c++) {
            if(r==c)
                m->elems[r*m->cols+c]=1;
            else
                m->elems[r*m->cols+c]=0;
        }
    }
}

matrix* transpose(matrix *m1) {
    matrix *m2 = alloc_matrix(m1->cols,m1->rows);
    for (int r=0;r<m1->rows;r++) {
        for (int c=0;c<m1->cols;c++) {
            m2->elems[c*m2->cols+r] = m1->elems[r*m1->cols+c];
        }
    }
    return m2;
}
