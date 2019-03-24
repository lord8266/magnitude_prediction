#include "include/header.h"

void read_line(char *buf,matrix* features,matrix* target,int pos) {
    //reads data into features and target 
    char *curr = strtok(buf,",");

    for (unsigned long i=0;i<features->cols;i++) {
        sscanf(curr,"%lg",&features->elems[pos+features->rows*i]);
        curr =strtok(NULL,",");
    }

    for (unsigned long i=0;i<target->cols;i++) {
        sscanf(curr,"%lg",&target->elems[pos+target->rows*i]);
        curr =strtok(NULL,",");
    }   
    
}

void read_csv(char *file,matrix *features,matrix* target) {
    FILE *contents =fopen(file,"r");


    long len;
    fseek(contents,0,SEEK_END);
    len =ftell(contents);
    fseek(contents,0,SEEK_SET);
    printf("file len: %ld\n",len);
    char buf[500];


    fgets(buf,500,contents);
    //ignore the first line (they are data labels)

    for(int i=0;i<features->rows;i++) {
        fgets(buf,500,contents);
        read_line(buf,features,target,i);
    }


    fclose(contents);

}