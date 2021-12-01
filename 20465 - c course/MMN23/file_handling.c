#include "preprocessor.h"

/* after openning a file will check if the file had opened correctly */
void open_file(FILE *fp)
{
    if(!fp)
    {
        printf("Error in opening file\n");
        exit(0);
    }
}
/* after calling the method fclose to close a file will check that the file has closed properly */
void close_file(FILE *fp)
{
    if(!fp)
    {
        printf("Error in closing file\n");
        exit(0);
    }
}
/* copy the string src and adding a char at the end. placing it at dest */
void copy_name(char *dest, char *src,char c)
{
    strcpy(dest,src);
    dest[strlen(src)+1]='\0';
    dest[strlen(dest)]=c;/* the last char that is not the null terminate */
}
