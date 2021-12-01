#include "mat.h"

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

/* count_bits: count how many bits are turned on, 
by counting each one and turning it off, and then going to the next one */
int count_bits(long int num)
{
    int count=0;
    while(num) /* num value is not 0 yet */
    {
        num=num&(num-1); /* will turn off the rightest bit that is on */
        count++;         /* will loop as many as bits that are on */
    } 
    return count;
}
