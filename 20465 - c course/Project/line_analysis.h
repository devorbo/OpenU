#ifndef LINE_ANALYSIS_H
#define LINE_ANALYSIS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "global.h"
#include "symbol_list.h"
#include "reserved.h"

#define COMMA ','

int is_comment_or_space(char *line,int cnt_line_as);
int is_space(char c); 	   
int invalid_comma(line_info curr_line_info);
void initialize_string(char *splitcmd[]);
int split_line(char *splitcmd[], line_info line_no_label);
void free_split_line(char **line_words);
void trim_first_word(line_info curr_line_info);
int is_integar(char *word,line_info curr_line);
int label_handling(char *word,symbol_type ***symbol_table,int *num_symbol,line_info curr_line_info);
int is_poss_label(char *word);
int valid_label(char *word,symbol_type ***symbol_table,int *num_symbol,line_info curr_line_info);
void int_to_string(char *dest, int source);

#endif
