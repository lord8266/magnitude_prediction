#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix.h"

#define feature_len 3
#define target_len 2
#define train_len 23412

typedef struct  {
float data[5];
}data;

void csv_todata(char *buf,matrix*,matrix*,int );
void print_data(data *);
void refine_csv(char*,data*);