

#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "symbol_list.h"
#include "extern_label.h"

int file_second_pass(char *file_name, machine_word *code_img,int *data_img, int *ic, symbol_type ***symbol_table,int *num_symbol,extern_ref ***extern_table,int *num_ref);
int line_handling_second_pass(line_info curr_line_info,machine_word *code_img,int *data_img, int *ic, symbol_type ***symbol_table,int *num_symbol,extern_ref ***extern_table,int *num_ref);

#endif
