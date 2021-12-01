
#ifndef CODE_MEMORY_H
#define CODE_MEMORY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "global.h"
#include "symbol_list.h"
#include "extern_label.h"


int count_machine_word_to_add(int *ic,char **line_words,line_info curr_line_info);
int argument_is_num(char *word,line_info curr_line_info);
int add_machine_word(machine_word *code_img,int *ic,symbol_type ***symbol_table,int *num_symbol,extern_ref ***extern_table,int *num_ref,int there_is_label,char **line_words,line_info curr_line_info);
int set_current_word(char *word, machine_word *code_img,int *ic,int *num_add_word,char *target,int there_is_label,int op,symbol_type ***symbol_table,int *num_symbol,extern_ref ***extern_table,int *num_ref,line_info curr_line_info);
int check_type_valid_for_command(int op,int address_type,char *target);
void set_ARE(machine_word *code_img,char *word,int *ic,int *num_add_word,int address_type,symbol_type ***symbol_table,int *num_symbol);
int addressing_method(char *word,int *address_type,int there_is_label,int op,symbol_type ***symbol_table,int *num_symbol,line_info curr_line_info);

#endif
