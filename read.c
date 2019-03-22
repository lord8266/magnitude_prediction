#include "header.h"



int main() {

    FILE *contents =fopen("datasets/earthquake2.csv","r");

    // ------------------------------------------------------------------------------

    long len;
    fseek(contents,0,SEEK_END);
    len =ftell(contents);
    fseek(contents,0,SEEK_SET);
    printf("file len: %ld\n",len);
    char buf[500];
    matrix *train_features = alloc_matrix(train_len,feature_len); 
    matrix *train_target = alloc_matrix(train_len,target_len);
    // ----------------------------------------------------------------------------------

    fgets(buf,500,contents);
    for(int i=0;i<train_len;i++) {
    fgets(buf,500,contents);
    csv_todata(buf,train_features,train_target,i); //read line to ith element
    
    }

    // -----------------------------------------------------------------------------------
    fclose(contents);
    matrix *m1 = alloc_matrix(1,3);
    fill_matrix(m1,1);
    print_matrix(m1);
    matrix *m2 = transpose(m1);
    print_matrix(m2);
    print_matrix(train_features);
    print_matrix(train_target);
}