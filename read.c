#include "header.h"

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

int main() {

    matrix *train_features = alloc_matrix(train_len,feature_len); 
    matrix *train_target = alloc_matrix(train_len,target_len);
    
    read_csv("datasets/earthquake2.csv",train_features,train_target);

    matrix *X           =   prepend_x0(train_features); //add x0 =1

    matrix *X_transpose =   transpose(X); // transpose of x

    matrix *X_mult      =   multiply_matrix(X_transpose,X); // multiply transpose*X

    matrix *inv         =   invert(X_mult);// then invert the matrix 

    matrix *inv_mul     =   multiply_matrix(inv,X_transpose); //invert*X

    matrix *params      =   multiply_matrix(inv_mul,train_target); // finally multiply with y

    matrix *pred        =   multiply_matrix(X,params); // X * params =prediction

    print_matrix(pred);

}

