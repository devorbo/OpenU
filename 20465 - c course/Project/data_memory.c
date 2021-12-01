#include "data_memory.h"
#include "line_analysis.h"

/* add data memory in first pass */

/* if a data line, will add to the data memory */
int add_data_memory(int *data_img,int *ic,int *dc,char *line_words[],char *word,line_info curr_line_info)
{
    if(strcmp(word,".data")==0||strcmp(word,".string")==0)/* dealing with a data line */
    {     
        if(strcmp(line_words[1],"")==0)
        {
            fprintf(stdout,"Error in file %s line %d: Missing argument\n", curr_line_info.file_name ,curr_line_info.cnt_line);
            return ERROR;
        }
        if(strcmp(word,".data")==0)
        {
            return add_data(data_img,ic,dc,line_words,curr_line_info);/* analyse data type and add it to the data memory*/
        }
        else if(strcmp(word,".string")==0)
        {
            return add_string(data_img,ic,dc,curr_line_info);/* analyse string type and add it to the data memory*/
        }
    }
    return NONE;
}
/* data type, will check that valid and will insert to the data array */
int add_data(int *data_img, int *ic,int *dc,char *numbers[],line_info curr_line)
{
    int i;
    for(i=1;i< LINE_LENGTH && strcmp(numbers[i],"")!=0 ;i++)/* data values will be from the second argument and on */
    {
        if(is_integar(numbers[i],curr_line)==ERROR)/* check that value is a valid integar */
        {
            fprintf(stdout,"Error in file %s line %d: Data value is not an integar\n",curr_line.file_name,curr_line.cnt_line);
            return ERROR;
        }
        *(data_img+*dc)=atoi(numbers[i]);/* add the integar to the memory */
        (*dc)++;/* data was added to memory */
    }
    return VALID;
}
/* string type, will add the string to the data memory array, each char as is ASCII value */
int add_string(int *data_img,int *ic,int *dc,line_info curr_line)
{
    int i,k;
    /*start with the second argument */
    char *str;
    str=malloc(LINE_LENGTH);/* allocate memory for a copy of line */
    if(!str)
    {
        fprintf(stdout,"Error in file %s line %d: Memory allocation failled\n",curr_line.file_name,curr_line.cnt_line);
        return ERROR;
    }
    strcpy(str,curr_line.line);/* not to destroy the original line */
    /* point to the beggining of the data type */
    for(k=0;k<LINE_LENGTH && is_space(*(str+k));k++)
    ;
    if(str[k]==',')/* comma before first argument */
    {
        fprintf(stdout,"Error in file %s line %d: Illegal comma\n",curr_line.file_name,curr_line.cnt_line);
        free(str);
        return ERROR;
    }
    for(;k<LINE_LENGTH && !is_space(*(str+k));k++)/* skip first argument .string */
    ;
    for(;k<LINE_LENGTH && is_space(*(str+k));k++)
    ;
    if(str[k]==',')/* comma before second argument */
    {
        fprintf(stdout,"Error in file %s line %d: Illegal comma\n",curr_line.file_name,curr_line.cnt_line);
        free(str);
        return ERROR;
    }
    
    /* trim the white spaces at the end of the line */
    while(is_space(str[strlen(str)-1]))
    {
        str[strlen(str)-1]='\0';
    }
    /*check that this value is a string */
    if(str[k]!='\"'||str[strlen(str)-1]!='\"')
    {
        fprintf(stdout,"Error in file %s line %d: Input is not a string or extra text \n",curr_line.file_name,curr_line.cnt_line);
        free(str);
        return ERROR;
    }
    /* go through the string and save each char as an ascii value */
    for(i=k+1;i<strlen(str)-1;i++)
    {
        if(!isprint((int)(str[i])))
        {
            fprintf(stdout,"Error in file %s line %d: Input is not printable\n",curr_line.file_name,curr_line.cnt_line);
            free(str);
            return ERROR;
        } 
         *(data_img+*dc)=(int)(str[i]);/* add to data memory in first pass? */
        (*dc)++;/* data was added to memory */
    }
     *(data_img+*dc)=0;/*ascii code as end of the string - \0*/
    (*dc)++;/* add to data memory in first pass */
    free(str);
    return VALID;
}

void print_data_memory(int *data_img,int *dc)
{
    int i;
    fprintf(stdout,"Data Memory\n");
    for(i=0;i<*dc;i++)
    {
        fprintf(stdout,"#%d: %d\n",i, *(data_img+i));
    }
}
 
