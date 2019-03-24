#include "include/header.h"

matrix * prepend_x0(matrix *m) {

    matrix *ret = alloc_matrix(m->rows,m->cols+1);

    for (int r=0;r<m->rows;r++) {
        ret->elems[r] = 1;
    }
    
    for (int c=1;c<ret->cols;c++) {
        for (int r=0;r<m->rows;r++) {
            ret->elems[c*m->rows+r] = m->elems[(c-1)*m->rows+r];
        }
    }

    return ret;
}

matrix *fit(matrix *X_,matrix *y) {

    matrix *X = prepend_x0(X_);

    matrix *X_transpose =   transpose(X); // transpose of x
    matrix *X_mult      =   multiply_matrix(X_transpose,X); // multiply transpose*X
    matrix *inv         =   invert(X_mult);// then invert the matrix 
    matrix *inv_mul     =   multiply_matrix(inv,X_transpose); //invert*X
    matrix *params      =   multiply_matrix(inv_mul,y); // finally multiply with y
    
    free_matrix(X_transpose);
    free_matrix(X_mult);
    free_matrix(inv);
    free_matrix(inv_mul);
    free_matrix(X);
    return params;
}

matrix *predict(matrix *X_,matrix* params) {
    matrix *X = prepend_x0(X_);
    matrix *prediction = multiply_matrix(X,params);
    free_matrix(X);
    return prediction;
}



matrix *rmse(matrix* pred,matrix *target) {

    int rows = pred->rows,cols = pred->cols;
    matrix *ret = alloc_matrix(1,cols);

    for (int c=0;c<cols;c++) {
        double error = 0;
        for (int r=0;r<rows;r++) {
            double temp = target->elems[c*rows+r] - pred->elems[c*rows+r]; 
            temp*=temp;
            error+=temp;
        }
        error = sqrt(error);
        error/=rows;
        ret->elems[c] = error;
    }
    return ret;
}

void split_matrix_row(matrix* start,matrix **m1,matrix **m2,double ratio) {
    int sep = ratio*start->rows;
    *m1 =alloc_matrix(sep,start->cols);
    *m2 = alloc_matrix(start->rows-sep,start->cols);

    for (int c=0;c<start->cols;c++) {
        for (int r=0;r<sep;r++) {
            (*m1)->elems[c*(*m1)->rows+r] = start->elems[c*start->rows+r];
        }
    }

    for (int c=0;c<start->cols;c++) {
        for (int r=sep;r<start->rows;r++) {
            (*m2)->elems[c*(*m2)->rows+r-sep] = start->elems[c*start->rows+r];
        }
    }
}
