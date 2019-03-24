#ifndef lr_ 
#define lr_  1

#include "matrix.h"

void split_matrix_row(matrix* start,matrix **m1,matrix **m2,double ratio);
matrix* prepend_x0(matrix *m); 

matrix* fit(matrix *X_,matrix *y) ;
matrix* predict(matrix *X_,matrix* params);

matrix* rmse(matrix *,matrix*); 



#endif