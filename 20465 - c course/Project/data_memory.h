#ifndef DATA_MEMORY_H
#define DATA_MEMORY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "global.h"

#define DATA_MEMORY_LENGTH 500


int add_data_memory(int *data_img,int *ic,int *dc,char *line_words[],char *word,line_info curr_line_info);
int add_data(int *data_img,int *ic,int *dc,char *numbers[],line_info curr_line);
int add_string(int *data_img,int *ic,int *dc,line_info curr_line);
void print_data_memory(int *data_img,int *dc);

#endif
