
#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "symbol_list.h"

int file_first_pass(char *file_name, int *data_img, int *ic, int *dc, symbol_type ***symbol_table,int *num_symbol);
int line_handling(line_info curr_line_info,int *data_img, int *ic, int *dc, symbol_type ***symbol_table,int *num_symbol);
int label_at_beginning(int *ic , int *dc, symbol_type ***symbol_table,int *num_symbol,line_info curr_line_info);
int add_label(char *label,char *instr,int *ic , int *dc, symbol_type ***symbol_table,int *num_symbol,line_info curr_line_info);

#endif
