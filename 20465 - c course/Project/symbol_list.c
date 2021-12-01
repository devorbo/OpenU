#include <stdlib.h>
#include "symbol_list.h"

/* add the symbol with the other info to the symbol_table */
int add_symbol_to_table(symbol_type ***symbol_table,int *num_symbol,char *symbol,int value,char *att,line_info curr_line_info)
{
    if(symbol_table_is_empty(symbol_table))/* no label yet */
    {
        (*symbol_table)=(symbol_type **)malloc(sizeof(symbol_type*));/* allocate memory for the array*/
        if(!(*symbol_table))
        {
            fprintf(stdout,"Error in file %s line %d: Memory allocation failed\n",curr_line_info.file_name,curr_line_info.cnt_line);
            return ERROR;
        }
        (*(*symbol_table+*num_symbol))=(symbol_type *)malloc(sizeof(symbol_type));/* allocate the empty element(symbol)*/
        if(!(*(*symbol_table+*num_symbol)))
        {
            fprintf(stdout,"Error in file %s line %d: Memory allocation failed\n",curr_line_info.file_name,curr_line_info.cnt_line);
            return ERROR;
        }
    }
    /* insert the information in the spesefic element*/
    strcpy((*(*symbol_table+*num_symbol))->symbol,symbol);
    (*(*symbol_table+*num_symbol))->value=value;
    strcpy((*(*symbol_table+*num_symbol))->attribute,att);
    
    /* get the array ready for the next symbol */ 
    (*num_symbol)++;
    /* re allocate memory */
    (*symbol_table)=(symbol_type **)realloc(*symbol_table,sizeof(symbol_type*)*(*num_symbol+1));/* add memory to the array, will include an empty element for the next symbol*/ 
    if(!(*symbol_table))
    {
        fprintf(stdout,"Error in file %s line %d: Memory allocation failled\n",curr_line_info.file_name,curr_line_info.cnt_line);
        return ERROR;
    }
    (*(*symbol_table+*num_symbol))=(symbol_type *)malloc(sizeof(symbol_type));/* allocate the empty element(symbol)*/
    if(!(*(*symbol_table+*num_symbol)))
    {
        fprintf(stdout,"Error in file %s line %d: Memory allocation failled\n",curr_line_info.file_name,curr_line_info.cnt_line);
        return ERROR;
    }
    /* insert NULL data in the last element */
    strcpy((*(*symbol_table+*num_symbol))->symbol,"");
    (*(*symbol_table+*num_symbol))->value=0;
    strcpy((*(*symbol_table+*num_symbol))->attribute,"");
    
    return VALID;  
}

/* update the symbol_table the address of the data labels. The data code will be after the code memory */
void update_data_value_of_symbol(int *ic,symbol_type ***symbol_table,int *num_symbol)
{
    int i;
    for(i=0;i<(*num_symbol);i++)
    {
        if(strstr((*(*symbol_table+i))->attribute,"data")!=NULL)/* symbol attribute is of type 'data' */
        {
            (*(*symbol_table+i))->value=(*(*symbol_table+i))->value+*ic;/* add the ic counter, to be after the code memory */
        }
    }
}

/* return if the symbol table is empty */
int symbol_table_is_empty(symbol_type ***symbol_table)
{
    if(*symbol_table==NULL)
        return 1;
    return 0;
}

/* check if given label exist in symbol table */
int symbol_exist(char *label,symbol_type ***symbol_table,int *num_symbol)
{ 
    int i;
    for(i=0;i<*num_symbol;i++)/* go over the symbol table */
    {
        if(strcmp(label,(*(*symbol_table+i))->symbol)==0)/* check if label equal to current symbol in table */
        {
            break;/* if found then stop */
        }
    }
    if(i<*num_symbol)/* label exist*/
    {
        return VALID;
    }
    return ERROR;
}
/* set symbol_address to be the address of the label */
int symbol_address(char *label,int *symbol_address,symbol_type ***symbol_table,int *num_symbol)
{
    int i;
    for(i=0;i<*num_symbol;i++)/* go over the symbol table */
    {
        if(strcmp(label,(*(*symbol_table+i))->symbol)==0)/* check if label equal to current symbol in table */
        {
            break;/* if found than stop */
        }
    }
    if(i<*num_symbol)/* label exist*/
    {
        *symbol_address=(*(*symbol_table+i))->value;
        return VALID;
    }
    return ERROR;/* label not exist */
}
/* a given string is an extern label */
int symbol_is_extern(char *label,symbol_type ***symbol_table,int *num_symbol)
{
    int i;
    for(i=0;i<*num_symbol;i++)/* go over the symbol table */
    {
        if(strcmp(label,(*(*symbol_table+i))->symbol)==0)/* check if label equal to current symbol in table */
        {
            break;/* if found than stop */
        }
    }
    if(i<*num_symbol)/* label exist*/
    {
        if(strstr((*(*symbol_table+i))->attribute,"external")!=NULL)
            return VALID;
    }
    if(i==*num_symbol)
        return NONE;
    return ERROR;
}
/* label is local*/
int symbol_is_local(char *label,symbol_type ***symbol_table,int *num_symbol)
{
    return !(symbol_is_extern(label,symbol_table,num_symbol));
}
/* label is of data line*/
int symbol_is_data(char *label,symbol_type ***symbol_table,int *num_symbol)
{
    int i;
    for(i=0;i<*num_symbol;i++)/* go over the symbol table */
    {
        if(strcmp(label,(*(*symbol_table+i))->symbol)==0)/* check if label equal to current symbol in table */
        {
            break;/* if found than stop */
        }
    }
    if(i<*num_symbol)/* label exist*/
    {
        if(strstr((*(*symbol_table+i))->attribute,"data")!=NULL)
            return VALID;
    }
    if(i==*num_symbol)
        return NONE;
    return ERROR;
}

/* at second pass: add to the attribute of the given label 'entry' */
int add_entry_to_symbol(char *label,symbol_type ***symbol_table,int *num_symbol)
{ 
    int i;
    for(i=0;i<*num_symbol;i++)/* go over the symbol table */
    {
        if(strcmp(label,(*(*symbol_table+i))->symbol)==0)
        {
            break;/* if found than stop */
        }
    }
    if(i<*num_symbol)/* label exist*/
    {
        if(strstr((*(*symbol_table+i))->attribute,"external")!=NULL)/* if label attribute contains 'entry' */
        {
            return ERROR;
        }
        strcat((*(*symbol_table+i))->attribute," , entry");/* add 'entry to attribute */
        return VALID;
    }
    return ERROR;
}

int entry_exist(symbol_type ***symbol_table,int *num_symbol)
{
    int i;
    for(i=0;i<*num_symbol;i++)/* go over the symbol table */
    {
        if(strstr((*(*symbol_table+i))->attribute,"entry")!=NULL)/* if label attribute contains 'entry' */
        {
            return VALID;
        }
    }
    return ERROR;
}
int extern_exist(symbol_type ***symbol_table,int *num_symbol)
{
    int i;
    for(i=0;i<*num_symbol;i++)/* go over the symbol table */
    {
        if(strstr((*(*symbol_table+i))->attribute,"external")!=NULL)/* if label attribute contains 'external' */
        {
            return VALID;
        }
    }
    return ERROR;
}

/* free the symbol_table that was allocate */
void free_symbol_table(symbol_type ***symbol_table,int *num_symbol)
{
    int i;
    for(i=0;i<(*num_symbol);i++)
    {
        free(*(*symbol_table+i));
    }
    free(*symbol_table);
}
 
void print_symbol_list(symbol_type ***symbol_table,int *num_symbol)
{
    int i;
    for(i=0;i<(*num_symbol);i++)
    {
        fprintf(stdout,"Symbol #%d: ",i+1);
        fprintf(stdout,"Symbol: %s Value: %d Attribute: %s\n",(*(*symbol_table+i))->symbol,(*(*symbol_table+i))->value,(*(*symbol_table+i))->attribute);
    }
}

