

#ifndef SYMBOL_LIST_H
#define SYMBOL_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"

typedef struct symbol_type{
    char symbol[LABEL_LENGTH];
    int value;
    char attribute[WORD_LENGTH];
    }symbol_type;

  
    
int add_symbol_to_table(symbol_type ***symbol_table,int *num_symbol,char *symbol,int value,char *att,line_info curr_line_info);
void update_data_value_of_symbol(int *ic,symbol_type ***symbol_table,int *num_symbol);
int symbol_table_is_empty(symbol_type ***symbol_table);
int symbol_exist(char *label,symbol_type ***symbol_table,int *num_symbol);
int symbol_address(char *label,int *symbol_address,symbol_type ***symbol_table,int *num_symbol);
int symbol_is_extern(char *label,symbol_type ***symbol_table,int *num_symbol);
int symbol_is_local(char *label,symbol_type ***symbol_table,int *num_symbol);
int symbol_is_data(char *label,symbol_type ***symbol_table,int *num_symbol);
int add_entry_to_symbol(char *label,symbol_type ***symbol_table,int *num_symbol);
int entry_exist(symbol_type ***symbol_table,int *num_symbol);
int extern_exist(symbol_type ***symbol_table,int *num_symbol);
void free_symbol_table(symbol_type ***symbol_table,int *num_symbol);
void print_symbol_list(symbol_type ***symbol_table,int *num_symbol);

#endif
