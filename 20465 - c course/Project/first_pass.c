#include "line_analysis.h"
#include "symbol_list.h"
#include "code_memory.h"
#include "data_memory.h"
#include "first_pass.h"

/* deal with current file, first pass */
int file_first_pass(char *file_name, int *data_img, int *ic, int *dc, symbol_type ***symbol_table,int *num_symbol)
{
    FILE *fp;
    int i=0,file_error=VALID;
    int cnt_line=0;
    char c;
    char curr_line[LINE_LENGTH];
    line_info curr_line_info;
    

    strcat(file_name,".as");/* add .as to file name */
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
        else if(c!='\n') /*more than 80 character*/
        {
            curr_line[i]='\0';/* end of line - mark as end of string*/
            cnt_line++;
            fprintf(stdout,"Error in file %s line %d: Line length is longer than allowed \n",file_name,cnt_line);
            while((c=getc(fp))!='\n');/*then skip until the end of line */
            file_error=ERROR;
            i=0;
        }
        else
        {   
            curr_line[i]='\0';/* end of line - mark as end of string*/
            cnt_line++;
            /* line information, save as a struct */
            curr_line_info.line=curr_line;
            strcpy(curr_line_info.file_name,file_name);
            curr_line_info.cnt_line=cnt_line;
            if(is_comment_or_space(curr_line,cnt_line)==ERROR)/*if a comment line, will continue on and will not analyze the line */
            {
                if(line_handling(curr_line_info,data_img,ic,dc,symbol_table,num_symbol)==ERROR)/* anaylyze this line */
                {
                    file_error=ERROR;
                }
            }
            i=0;
            /*printf("\n\n");*/
        }
        
    } 
    fclose(fp);
    return file_error;
    
}
/* will check the current line from errors. will save each label infomation and also will count code words- ic. if the line is a data type, will save in the data memory*/
int line_handling(line_info curr_line_info,int *data_img, int *ic, int *dc, symbol_type ***symbol_table,int *num_symbol)
{
    int is_data=0,line_error=VALID;
    int there_is_label;
    char *word=NULL;
    char *linecpy=malloc(LINE_LENGTH);
    char *line_words[LINE_LENGTH];
   
    strcpy(linecpy,curr_line_info.line);
    word=strtok(linecpy," \t");/* first word of line */
    
    /* label */
    there_is_label=label_handling(word,symbol_table,num_symbol,curr_line_info);/* check if the first argument is a label*/
    if(there_is_label==ERROR)/* invalid label */
    {
        free(linecpy);
        return ERROR;
    }
    else if(there_is_label==VALID)
    {
        label_at_beginning(ic,dc,symbol_table,num_symbol,curr_line_info);/* add label to symbol table */
        
        /* there is a label, trim it, and then continue on regular */
         while(curr_line_info.line && is_space(*curr_line_info.line))
             curr_line_info.line++;
         while(curr_line_info.line && !is_space(*curr_line_info.line))
             curr_line_info.line++;
         while(curr_line_info.line && is_space(*curr_line_info.line))
             curr_line_info.line++;
    }
    /* continue analysis the line here */
    
    split_line(line_words,curr_line_info);/* split line elements to an array of string */
    
    is_data=add_data_memory(data_img,ic,dc,line_words,line_words[0],curr_line_info);/* if it is a line of data will add to the data memory */
   
    if(is_data==ERROR)
    {
        line_error=ERROR;
    }
    /* not data, will check other option */
    else if(strcmp(line_words[0],".entry")==0)/* will save entry label at the second pass */
    {
        if(strcmp(line_words[1],"")==0)/* missing argument */
        {
            fprintf(stdout,"Error in file %s line %d: Missing argument\n",curr_line_info.file_name,curr_line_info.cnt_line);
            line_error=ERROR;
        } 
        else if(strcmp(line_words[2],"")!=0)/* extra text at end of line */
        {
            fprintf(stdout,"Error in file %s line %d: Extra text after command\n",curr_line_info.file_name,curr_line_info.cnt_line);
            line_error=ERROR;
        }
    }
    else if(strcmp(line_words[0],".extern")==0)
    {
        /* label is second argument and not first */
        if(strcmp(line_words[1],"")==0)/* missing argument */
        {
            fprintf(stdout,"Error in file %s line %d: Missing argument\n",curr_line_info.file_name,curr_line_info.cnt_line);
            line_error=ERROR;
        }  
        else if(add_label(line_words[1],".extern",ic,dc,symbol_table,num_symbol,curr_line_info)==ERROR)/* add label as extern */
        {
            line_error=ERROR;
        }
        else if(strcmp(line_words[2],"")!=0)/* extra text at end of line */
        {
            fprintf(stdout,"Error in file %s line %d: Extra text after command\n",curr_line_info.file_name,curr_line_info.cnt_line);
            line_error=ERROR;
        }
    }
    /* if reached this condition and the first argumen is not a command and not a data line ao the there is an error */   
    else if(is_command(line_words[0])==ERROR && is_data!=VALID)
    {
        fprintf(stdout,"Error in file %s line %d: Error in first argument\n",curr_line_info.file_name,curr_line_info.cnt_line);
            line_error=ERROR;
    }
    
    /* checking if the commas are all valid, not including the label that was checked at the label method */
    else if(strcmp(line_words[0],".string")!=0 && invalid_comma(curr_line_info)==ERROR)/* a string instruction will contain at the second argument a string, could be with whitespaces */
    {
        free_split_line(line_words);
        free(linecpy);
        return ERROR;
    }
    /* a command- count machine word needed for this command */
    else if(line_error!=ERROR && is_data==NONE)
    {
        if(count_machine_word_to_add(ic,line_words,curr_line_info)==ERROR)
            line_error=ERROR;
    }

    /*free out elements that were used */
    free_split_line(line_words);
    free(linecpy);

    return line_error;/* return the value of line_error*/
}

/* deal with label at beggning of line */
int label_at_beginning(int *ic , int *dc, symbol_type ***symbol_table,int *num_symbol,line_info curr_line_info)
{
    /* if there is a label before extern or entry dont add to symbol table */
    char *word;
    char *linecpy=malloc(LINE_LENGTH);
    char *label=malloc(LABEL_LENGTH);/* label max length is 31*/
    
    strcpy(linecpy,curr_line_info.line);
    word=strtok(linecpy," \t");
    strcpy(label,word);/* label contain the first argument */
    word=strtok(NULL," \t");/* word contain the second argument */
    if(strcmp(word,".entry")==0 || strcmp(word,".extern")==0)
    {
        fprintf(stdout,"Warning in file %s line %d: Lable before extern or entern\n",curr_line_info.file_name,curr_line_info.cnt_line);
        return NONE;
    }
    /* check the label type, and add it to the symbol table */
    
    /* dealing with comma */
    if(label[0]==COMMA || label[strlen(label)-1]==COMMA || word[0]==COMMA) /* check comma. Before the first argument and between the first and the second argument - not suppose to be a comma */
    {
        fprintf(stdout,"Error in file %s line %d: Invalid comma\n",curr_line_info.file_name,curr_line_info.cnt_line);
        return ERROR;
    }
    label=strtok(label,":");/* label is valid, and will trim the last char and stay with label name*/
    if(add_label(label,word,ic,dc,symbol_table,num_symbol,curr_line_info)==ERROR)/* add label */
    {
        return ERROR;
    }
    
    free(label);
    free(linecpy);
    
    return VALID;
}

/* add label to the symbol table */
int add_label(char *label,char *instr,int *ic , int *dc, symbol_type ***symbol_table,int *num_symbol,line_info curr_line_info)
{
    int value;
    char *att=malloc(10);
    
    /*printf("line %d: *address=%d label=%s \n",curr_line_info.cnt_line,*ic+*dc,label);*/
        if(strcmp(instr,".data")==0 || strcmp(instr,".string")==0)
        {
            strcpy(att,"data");
            value=*dc;
        }
        else if(strcmp(instr,".extern")==0 || strcmp(instr,".entry")==0)
        {
            if(strcmp(instr,".extern")==0)
            {
                strcpy(att,"external");
                value=0;
            }
            else
            {
                /* will deal with entry at the second pass */
                free(att);
                return VALID;
            }   
        }
        else /* check command */
        {
            if(is_command(instr)==VALID)
            {
                strcpy(att,"code");
                value=*ic;
            }
            
           else
            {
                fprintf(stdout,"Error in file %s line %d: Invalid Command\n",curr_line_info.file_name,curr_line_info.cnt_line);
                free(att);
                return ERROR;
            }
        }
            add_symbol_to_table(symbol_table,num_symbol,label,value,att,curr_line_info);/* add the label to the symbol table, with the info of the symbol */

    free(att);
    return VALID;
}

