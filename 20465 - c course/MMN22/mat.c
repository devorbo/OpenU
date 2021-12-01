#include "mat.h"
/*File: mat.c 
  contain calculation functions on matrixs */

/* read information and store it at matrix */
void read_mat(mat **m1,double *numbers)
{
    int i,j;
    for(i=0;i<MAT_LENGTH;i++)
        for(j=0;j<MAT_LENGTH;j++)
        {        
            (*(*m1)[i][j])=numbers[i*MAT_LENGTH+j];
            /* i - row, i*MAT_LENGTH, the specific row, going elements one by one. j- column */
        }
}
/* print the matrix in a specific format */
void print_mat(mat **m)
{
   int i,j;
    for(i=0;i<MAT_LENGTH;i++)
    {
        for(j=0;j<MAT_LENGTH;j++)
        {
            printf("%7.2f\t",*((*m)[i][j]));
        } 
        printf("\n");
    }
}
/* add matrix m1 to m2 and stores it at m3 */
void add_mat(mat **m1,mat **m2,mat **m3)
{
    int i,j;
    for(i=0;i<MAT_LENGTH;i++)
        for(j=0;j<MAT_LENGTH;j++)
        {        
            *((*m3)[i][j])=*((*m2)[i][j])+*((*m1)[i][j]);
        }
}
/* substract m1 from m2 and stores it at m3 */
void sub_mat(mat **m1,mat **m2,mat **m3)
{
    int i,j;
    for(i=0;i<MAT_LENGTH;i++)
        for(j=0;j<MAT_LENGTH;j++)
        {        
            *((*m3)[i][j])=*((*m2)[i][j])-*((*m1)[i][j]);
        }
}
/* multiply m1 by m2 , row of m1 by coulmn of m2, stores it at m3 */
void mul_mat(mat **temp,mat **m1,mat **m2,mat **m3)/*need to write this function*/
{
    int i,j,k;
    double sum=0;
    for(i=0;i<MAT_LENGTH;i++)
    {
        for(j=0;j<MAT_LENGTH;j++)
        {        
            /* row of m1 by coulmn of m2, sum up element one by one, end store it at element(i,j) at m3 */
            for(k=0;k<MAT_LENGTH;k++)
            {
                sum+=(*((*m1)[i][k])) * (*((*m2)[k][j]));
            }
            (*((*temp)[i][j]))=sum;
            sum=0;
        }
    }
    copy_mat(*m3,*temp);
}
/* multiply matrix m1 by the scalar, store it at m3 */
void mul_scalar(mat **m1,double scalar,mat **m2)
{
    int i,j;
    for(i=0;i<MAT_LENGTH;i++)
        for(j=0;j<MAT_LENGTH;j++)
        {        
            *((*m2)[i][j])= (*((*m1)[i][j])) * scalar;/* multiply*/
        }
}

/* transfor matrix m1, store it at m2 */
void trans_mat(mat **temp,mat **m1,mat **m2)
{
   /* temp - a matrix that will save the values, in case of overwriting */
    int i,j;
    copy_mat(*temp,*m1);
    for(i=0;i<MAT_LENGTH;i++)
        for(j=0;j<MAT_LENGTH;j++)
        {        
            *((*temp)[i][j])= *((*m1)[j][i]);/* symmetrical */
        }
    copy_mat(*m2,*temp);
}

/* will stop the program. in case of exiting not an a correct way, will print out a message */
void stop(int error)
{
    if(error)
    {
        printf("Exit not an a valid way \n");
    }
    exit(0);
}

void copy_mat(mat *copy, mat *move)/* copy will get mat move values */
{
    int i,j;
    for(i=0;i<MAT_LENGTH;i++)
        for(j=0;j<MAT_LENGTH;j++)
        {        
            *(copy[i][j])=*(move[i][j]);
        }
}    
    

