#include "include/header.h"

int main() {

    //first allocate matrices for reading data
    matrix *features = alloc_matrix(data_len,feature_len); 
    matrix *target = alloc_matrix(data_len,target_len);

    read_csv("datasets/earthquake2.csv",features,target); 

    //---------------------------------------------------------------

    //Next define matrices for train set and test set
    matrix *X_train=NULL,*y_train=NULL;
    matrix *X_test=NULL,*y_test=NULL;

    split_matrix_row(features,&X_train,&X_test,0.7); //split features into X_train and X_test
    split_matrix_row(target,&y_train,&y_test,0.7); //split features into y_train and y_test
    
    //Data is now split in 70:30 ratio

    matrix *params = fit(X_train,y_train);
    matrix *prediction = predict(X_test,params);

    print_matrix(prediction);
    print_matrix(y_test);

    matrix *err = rmse(prediction,y_test);
    print_matrix(err);

    free_matrix(features);
    free_matrix(target);
    free_matrix(X_train);
    free_matrix(X_test);
    free_matrix(y_train);
    free_matrix(y_test);
    free_matrix(params);
    free_matrix(prediction);
    free_matrix(err);
}
