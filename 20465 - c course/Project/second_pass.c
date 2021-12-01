#include "line_analysis.h"
#include "symbol_list.h"
#include "code_memory.h"
#include "data_memory.h"
#include "second_pass.h"
#include "extern_label.h"



int file_second_pass(char *file_name, machine_word *code_img,int *data_img, int *ic, symbol_type ***symbol_table,int *num_symbol,extern_ref ***extern_table,int *num_ref)
{
    /* open file then go line by line */    
    FILE *fp;
    int i=0,file_error=VALID;
    int cnt_line=0;
    char c;
    char curr_line[LINE_LENGTH];
    line_info curr_line_info;
    
    fp=fopen(file_name,"r");/* open current file */
    if(!fp)
    {
        fprintf(stdout,"Error: File %s did not open correctly\n",file_name);
        return ERROR;
    }
    /* read the file */
    while((c=getc(fp))!=EOF)
    {
        if(i<LINE_LENGTH-1 && c!='\n')
        {
            curr_line[i]=c;
            i++;
        } 
        else
        {
            curr_line[i]='\0';/* end of line - mark as end of string*/
            cnt_line++;
            /* line information, save in a struct */
            curr_line_info.line=curr_line;
            strcpy(curr_line_info.file_name,file_name);
            curr_line_info.cnt_line=cnt_line;
            if(is_comment_or_space(curr_line,cnt_line)==ERROR)/*if a comment line, will continue on and will not analyze the line */
            {
                if(line_handling_second_pass  (curr_line_info,code_img, data_img,ic, symbol_table,num_symbol,extern_table,num_ref)==ERROR)/* anaylyze this line */
                {
                    file_error=ERROR;
                }
            }
            i=0;
        }
    }
    fclose(fp);
    return file_error;
}

 
int line_handling_second_pass(line_info curr_line_info,machine_word *code_img,int *data_img, int *ic, symbol_type ***symbol_table,int *num_symbol,extern_ref ***extern_table,int *num_ref)
{
    int line_error=VALID;
    int stop=NONE;/* stop- not to build a code word for this line */
    int there_is_label;
    char *word=NULL;
    char *linecpy=malloc(LINE_LENGTH);
    char *line_words[LINE_LENGTH];
   
    strcpy(linecpy,curr_line_info.line);
    word=strtok(linecpy," \t");/* first argument */
    
    /* label */
    there_is_label=is_poss_label(word);/* if there is a label, it is a legal label */
    if(there_is_label==VALID)
    {
        /* remove lable */
         while(curr_line_info.line && is_space(*curr_line_info.line))
             curr_line_info.line++;
         while(curr_line_info.line && !is_space(*curr_line_info.line))
             curr_line_info.line++;
         while(curr_line_info.line && is_space(*curr_line_info.line))
             curr_line_info.line++; 
    }
    
    split_line(line_words,curr_line_info);/* split line elements to an array of string */
    
    /* check if this a data line */
    if(strcmp(line_words[0],".data")==0||strcmp(line_words[0],".string")==0)/* data line- skip it, dont need to deal with it */
    {
        stop=VALID;
    }
    else if(strcmp(line_words[0],".entry")==0 )
    {
        /* add to the second word- label the attribute entry, if not exist report error */
        if(add_entry_to_symbol(line_words[1],symbol_table,num_symbol)==ERROR)
        {
            fprintf(stdout,"Error in file %s line #%d: Label '%s' does not exist in this file or declared as an external label\n",curr_line_info.file_name,curr_line_info.cnt_line,word);
            line_error=ERROR;
        }
        else
            stop=VALID;
    }

    else if(strcmp(line_words[0],".extern")==0)
    {
        /* will not add to the code array, because not a type of an instruction line */
        stop=VALID;
    }
    if(stop==VALID || line_error==ERROR)/* if found error or if should not build a code word for this line */
    {
        free_split_line(line_words);
        free(linecpy);
        return line_error;
    }
     
    /* finally, add the command line as a word machine */
    if(add_machine_word(code_img,ic,symbol_table,num_symbol, extern_table,num_ref, there_is_label,line_words, curr_line_info)==ERROR)
    {
        line_error= ERROR;
    }
    
    free_split_line(line_words);
    free(linecpy);

    return line_error;
}

