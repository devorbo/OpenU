#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAT_LENGTH 4
#define FOREVER for(;;)

typedef double mat[MAT_LENGTH][MAT_LENGTH];


void read_mat(mat **m,double *numbers);
void print_mat(mat **m);
void add_mat(mat **m1,mat **m2,mat **m3);
void sub_mat(mat **m1,mat **m2,mat **m3);
void mul_mat(mat **temp,mat **m1,mat **m2,mat **m3);
void mul_scalar(mat **m1,double scalar,mat **m2);
void trans_mat(mat **temp,mat **m1,mat **m2);
void stop(int error);
void copy_mat(mat *copy, mat *move);








