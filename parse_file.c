#include "header.h"

void csv_todata(char *buf,matrix* features,matrix *targets,int pos) {
    char *curr = strtok(buf,",");
    for (int i=0;i<features->cols;i++) {
        sscanf(curr,"%g",&features->elems[pos*features->cols+i]);
        curr =strtok(NULL,",");
    }
    for (int i=0;i<targets->cols;i++) {
        sscanf(curr,"%g",&targets->elems[pos*targets->cols+i]);
        curr =strtok(NULL,",");
    }
   
}




