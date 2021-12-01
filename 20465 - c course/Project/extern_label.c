#include "extern_label.h"


int add_extern_reference(extern_ref ***extern_table,int *num_ref,char *symbol,int value,line_info curr_line_info)
{
    
    if(extern_table_is_empty(extern_table))/* no label yet */
    {
        (*extern_table)=(extern_ref **)malloc(sizeof(extern_ref*));/* allocate memory for the array*/
        if(!(*extern_table))
        {
            fprintf(stdout,"Error in file %s line %d: Memory allocation failed\n",curr_line_info.file_name,curr_line_info.cnt_line);
            return ERROR;
        }
        (*(*extern_table+*num_ref))=(extern_ref *)malloc(sizeof(extern_ref));/* allocate the empty element(symbol)*/
        if(!(*(*extern_table+*num_ref)))
        {
            fprintf(stdout,"Error in file %s line %d: Memory allocation failed\n",curr_line_info.file_name,curr_line_info.cnt_line);
            return ERROR;
        }
    }
    /* insert the information in the spesefic element*/
    strcpy((*(*extern_table+*num_ref))->symbol,symbol);
    (*(*extern_table+*num_ref))->value=value;

    /* get the array ready for the next symbol */ 
    (*num_ref)++;
    /* re allocate memory */
    (*extern_table)=/*(extern_table **)*/realloc(*extern_table,sizeof(extern_ref*)*(*num_ref+1));/* add memory to the array, will include an empty element for the next symbol*/ 
    if(!(*extern_table))
    {
        fprintf(stdout,"Error in file %s line %d: Memory allocation failled\n",curr_line_info.file_name,curr_line_info.cnt_line);
        return ERROR;
    } 
    (*(*extern_table+*num_ref))=/*(extern_table *)*/malloc(sizeof(extern_ref));/* allocate the empty element(symbol)*/
    if(!(*(*extern_table+*num_ref)))
    {
        fprintf(stdout,"Error in file %s line %d: Memory allocation failled\n",curr_line_info.file_name,curr_line_info.cnt_line);
        return ERROR;
    }
    /* insert NULL data in the last element */
    strcpy((*(*extern_table+*num_ref))->symbol,"");
    (*(*extern_table+*num_ref))->value=0;
    
    return VALID;  
}
/* return if the symbol table is empty */
int extern_table_is_empty(extern_ref ***extern_table)
{
    if(*extern_table==NULL)
        return 1;
    return 0;
}

/* free the extern_ref table */
void free_extern_table(extern_ref ***extern_table,int *num_ref)
{
    int i;
    for(i=0;i<(*num_ref);i++)
    {
        free(*(*extern_table+i));
    }
    free(*extern_table);
} 

void print_extern_ref(extern_ref ***extern_table,int *num_ref)
{
    int i;
    printf("print extern_ref list\n");
    for(i=0;i<(*num_ref);i++)
    {
        fprintf(stdout,"ref #%d: ",i+1);
        fprintf(stdout,"Symbol: %s Value: %d \n",(*(*extern_table+i))->symbol,(*(*extern_table+i))->value);
    }
}
