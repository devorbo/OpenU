#include "mat.h"
#include <mat.h>
int count_bits(long int num);

/* for a given number will return the amount of bits that are on, in the binary represention */
int main()
{
    int num;
    printf("Insert a decimal - long integar number\n");
    scanf("%d",&num);
    printf("For the number %d there are %d bits on.\n",num,count_bits(num));
    
    return 0;
}

