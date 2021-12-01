#ifndef EXTERN_LABEL_H
#define EXTERN_LABEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"

typedef struct extern_ref{
    char symbol[LABEL_LENGTH];
    int value;
    }extern_ref;
    
int add_extern_reference(extern_ref ***extern_table,int *num_ref,char *symbol,int value,line_info curr_line_info);
int extern_table_is_empty(extern_ref ***extern_table);
void free_extern_table(extern_ref ***extern_table,int *num_ref);
void print_extern_ref(extern_ref ***extern_table,int *num_ref);    
#endif 
