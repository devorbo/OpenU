#include "line_analysis.h"

/* line is a comment or a spce line */
int is_comment_or_space(char *line,int cnt_line_as)
{
    int i;
    for(i=0;line[i]!='\0' && is_space(line[i]);i++)/* skip all the spaces */
     ;
    if(line[i]=='\0'||line[i]==';')/* line begin with ';' that is a comment line or have reached the end of line the and contained only whitespaces */
        return VALID;/* true, this is a comment or an empty line */
    return ERROR;    
}

/* char is a white space */
int is_space(char c)
{
    if(c==' '||c=='\t')/* char is space or tab */
        return 1;
    return 0;
}

/* check that the commas are correct in the given line */  	   
int invalid_comma(line_info curr_line_info)
{
    /* split the line by spaces only and not by the commas */
    int i,j,end,error,open;
    char *splitcmd[LINE_LENGTH];
    char *linecpy=malloc(LINE_LENGTH);
    char *token;
    
    strcpy(linecpy,curr_line_info.line);
    token=strtok(linecpy," \t\n"); 
    error=0;
    open=0;
    initialize_string(splitcmd);/* set strings as no value - "" */
    /*split strings to tokens by white spacese */
    for (i=0;i<LINE_LENGTH && token != NULL;i++) 
    { 
        splitcmd[i]=token;/* point to that token  */
        token = strtok(NULL, " \t\n"); 
    } 
    end=i;/* end of input in the array */

    /* check for invalid commas */
    /* comma before or after command name */
    if(splitcmd[0][0]==COMMA || splitcmd[0][strlen(splitcmd[0])-1]==COMMA ||splitcmd[1][0]==COMMA)
    {
        fprintf(stdout,"Error in file %s line %d: Illegal comma\n",curr_line_info.file_name,curr_line_info.cnt_line);
        return ERROR;
    }
    /*missing or illegal commas in total command */
    else
    {
        if(splitcmd[1][strlen(splitcmd[1])-1]==COMMA)
        {
            open=1;
        }
        for(i=1;i<end && !error;i++)
        {
            if(i!=1)/* no comma at beginning for the first argument - was checked before */
            {
		    /* comma before argument*/
		    if(splitcmd[i][0]==COMMA)
		    {
		        /* comma after last argument - two commas ->illegal*/
			if(open)
			{
			    fprintf(stdout,"Error in file %s line %d: Multiply consecutive commas\n",curr_line_info.file_name,curr_line_info.cnt_line);
                            return ERROR; 
			}
			else
			    open=1;
		    }
		    /* no comma before the argument*/
		    else if(!open)
		    {
			fprintf(stdout,"Error in file %s line %d: Missing comma\n",curr_line_info.file_name,curr_line_info.cnt_line);
                            return ERROR;
		    }
            }

            /*check if the entire line correct (were not sepreate by white spaces), no illegals comma */
            for(j=0;  j<strlen(splitcmd[i])-1 && !error;j++)
            {
                /* commas one after the other before or after argument */
                if(splitcmd[i][j]==COMMA)
                {
                    if(splitcmd[i][j+1]==COMMA)
                    {

                        fprintf(stdout,"Error in file %s line %d: Illegal comma\n",curr_line_info.file_name,curr_line_info.cnt_line);
                            return ERROR;
                    }
                }
            }
            
            /* end of argument check whether there is a comma*/
            if(splitcmd[i][strlen(splitcmd[i])-1]==COMMA)
            {
                open=1;
            }
            else 
            {
                if(splitcmd[i][strlen(splitcmd[i])-1]!='\n')
                    open=0;
            }
        }/* end of loop of strings */
        /* comma at end of command is illeag l*/
        if(open)
        {
            fprintf(stdout,"Error in file %s line %d: Illegal comma\n",curr_line_info.file_name,curr_line_info.cnt_line);
            return ERROR; 
        } 
    }
    free(linecpy);
    return VALID;
}  
/* initializ the array elements to be empty strings */
void initialize_string(char *splitcmd[])
{
    int i;
    for(i=0;i<LINE_LENGTH;i++)
    {
        splitcmd[i]="";
    }
}
/* split command by spaces, tabs and commas */
int split_line(char *splitcmd[], line_info curr_line)
{
	int i;
	char lncpy[LINE_LENGTH];
	char *token;
	
	strcpy(lncpy,curr_line.line);/* work with a copy of the line */
	
        token=strtok(lncpy," \t\n,");
	for (i=0;i<LINE_LENGTH && token != NULL;i++) 
	{    
	    splitcmd[i]=malloc(strlen(token)+1);/* allocate memory for each token from the current line */
	    if(!splitcmd[i])
	    {
	        fprintf(stdout,"Error in file %s line %d: Memory allocation failled\n",curr_line.file_name,curr_line.cnt_line);
                return ERROR;
            }
	    strcpy(splitcmd[i],token);/* save the token as an element */
	    token = strtok(NULL, " \t\n,"); 
	    
	}
        /* initialize next element*/
        splitcmd[i]=malloc(1);/* allocate memory for the last element in the current line */
	if(!splitcmd[i])
	{
	    fprintf(stdout,"Error in file %s line %d: Memory allocation failled\n",curr_line.file_name,curr_line.cnt_line);
            return ERROR;
        }
        strcpy(splitcmd[i],"");/* save last element as an empty string*/
	return VALID;
} 
void free_split_line(char **line_words)
{
    int i;
    /*free out elements that were used */
    for(i=0;i<LINE_LENGTH&&strcmp(line_words[i],"")!=0;i++)
    {
        free(*(line_words+i));
    }
    free(*(line_words+i));/* free last element */  
}
/* return if string is a valid integar */        
int is_integar(char *word,line_info curr_line)
{
    int j=0;
    /* the number sign */
    if(word[0]=='-' || word[0]=='+')
        j=1;/* check digit from the second char */
    for(;j<strlen(word);j++)
    {
        if(!isdigit(word[j]))/* check that each character is a digit */
        {
            return ERROR;
        }  
    }
    return VALID;
}        
    
 /* return if there is possible label or not and if it is valid */
int label_handling(char *word,symbol_type ***symbol_table,int *num_symbol,line_info curr_line_info)
{
    if(is_poss_label(word)==VALID)
    {
        return valid_label(word,symbol_table,num_symbol,curr_line_info);/* return if the label is valid */
    }
    else 
        return NONE;
}
/* word is possibly a label */
int is_poss_label(char *word)
{
    if(word[strlen(word)-1]==':')/* last character of string (before \0) */
    {
        return VALID;
    }
    else
        return ERROR;
}
int valid_label(char *word,symbol_type ***symbol_table,int *num_symbol,line_info curr_line_info)
{
    int i;
    if(strlen(word)>LABEL_LENGTH)/* length is illegal */
    {
        fprintf(stdout,"Error in file %s line %d: Label length is longer than allowed\n",curr_line_info.file_name,curr_line_info.cnt_line);
        return ERROR;
    }
    /*check whether the label name is legal  */
    if(!isalpha(word[0]))
    {
        fprintf(stdout,"Error in file %s line %d: Label is not legal\n",curr_line_info.file_name,curr_line_info.cnt_line);
        return ERROR;
    }
    for(i=1;i<strlen(word)-1;i++)/* not including the ':' sign */
        if(!isalnum(word[i]))
        {
            fprintf(stdout,"Error in file %s line %d: Label is not legal\n",curr_line_info.file_name,curr_line_info.cnt_line);
            return ERROR;
        }
    
    word=strtok(word,":");/* trim label sign : */

    /* check if label is a reserved word */
    if(is_reserved_word(word)==VALID)
    {
        fprintf(stdout,"Error in file %s line %d: Label is a resevred word\n",curr_line_info.file_name,curr_line_info.cnt_line);
        return ERROR;     
    }
    /* check symbol table if exist*/
    if(symbol_exist(word,symbol_table,num_symbol)==VALID)
    {
        fprintf(stdout,"Error in file %s line %d: Label exist\n",curr_line_info.file_name,curr_line_info.cnt_line);
        return ERROR;
    }
    
    return VALID;/*valid*/
}
/* note: dest should be large enough to hold the num of digits of the number */
void int_to_string(char *dest, int source)
{
    int num=source;
    int digits=0;

    /* count num of digits in the given number */
    while(num>=1)
    {
        digits++;
        num=num/10;
    }
    num=source;
    dest[digits]='\0';/* end of number */
    digits--;
    /* save each digit in the string, from right to left */
    while(num>=1)
    {
        dest[digits]=(num%10)+'0';/* the ascii value:the ascii value of zero plus the specefic digit */
        num=num/10;
        digits--;
    }
}   
