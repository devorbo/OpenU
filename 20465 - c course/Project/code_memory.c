#include "code_memory.h"
#include "global.h"
#include "reserved.h"
#include "line_analysis.h"
#include "extern_label.h"


/* for first pass: add to the counter the num that will need for the current command */
int count_machine_word_to_add(int *ic,char **line_words,line_info curr_line_info)
{
     /* line given with label trim (if was one) */
     /* first element is the command name */
     int num_add;
     int op;
     op=find_command_opcode(line_words[0]);
     
     if(op==NOT_VALID_OP)/* argument is not a command */
     {
         fprintf(stdout,"Error in file %s line %d: Invalid Command\n",curr_line_info.file_name,curr_line_info.cnt_line);
         return ERROR;
     }
     
     num_add=1;/* opcode 14-15 no arguments given, one machine word only*/
     /* opcode less that 14, uses more that one machine word */ 
     if(op<RTS_OP)
     {
          if(strcmp(line_words[1],"")==0)
          {
              fprintf(stdout,"Error in file %s line %d: Expected an argument for this command \n",curr_line_info.file_name,curr_line_info.cnt_line);
              return ERROR;
          }
          /* at least one argument, add another mechine word*/
          if(argument_is_num(line_words[1],curr_line_info)==ERROR)/* if there is a number expected, check that is given in a valid way */
              return ERROR;
          num_add++;/* there is another machine word */
          /* there is 2 arguments for this opcode */
          if(op>=MOV_OP && op<=LEA_OP)
          {
              if(strcmp(line_words[2],"")==0)
              {
                  fprintf(stdout,"Error in file %s line %d: Expected two arguments for this command \n",curr_line_info.file_name,curr_line_info.cnt_line);
                  return ERROR;
              }
              if(argument_is_num(line_words[2],curr_line_info)==ERROR)
                  return ERROR;
              num_add++;/* there is another mechine word */
          }
     }  
     *ic=*ic+num_add;/* add to the counter the num for this command */
     
     /* check extra text after command */
     if(strcmp(line_words[num_add],"")!=0)/* after num arguments (as be define before) there is more text */
     {
         fprintf(stdout,"Error in file %s line %d: Extra text after command \n",curr_line_info.file_name,curr_line_info.cnt_line);
          return ERROR;
     } 
     return VALID;
}

/* check whether argument is a number in assembly */
int argument_is_num(char *word,line_info curr_line_info)
{
    if(word[0]=='#')/* immediate, expect an integar after this char */
      {
          if(is_integar((word+1),curr_line_info)==ERROR)/* check that after the # the value is valid - is an integar */
          {
              fprintf(stdout,"Error in file %s line %d: Error value is not an integar \n",curr_line_info.file_name,curr_line_info.cnt_line);
              return ERROR;
          }
      }
      return VALID;
}

/* for second pass: add the command as machine words to the code memory */
int add_machine_word(machine_word *code_img,int *ic,symbol_type ***symbol_table,int *num_symbol,extern_ref ***extern_table,int *num_ref,int there_is_label,char **line_words,line_info curr_line_info)
{
     /* first element is the command name */
     int num_add=1;
     int op=find_command_opcode(line_words[0]);
     int func=find_command_func(line_words[0]);
     
     code_img[*ic].word.opcode=op;
     code_img[*ic].word.func=func;
     code_img[*ic].ARE='A';
     /* opcode 14-15 no arguments given*/
     if(op==RTS_OP || op==STOP_OP)
     { 
         /* dest and source will be zero */
         code_img[*ic].word.dest=0;
         code_img[*ic].word.source=0;
     }
     else 
     {
          /* at least one argument */
          if(strcmp(line_words[1],"")==0)
          {
              fprintf(stdout,"Error in file %s line %d: Expected more arguments\n", curr_line_info.file_name, curr_line_info.cnt_line);
              return ERROR;
          }
          if(op>=CLR_OP && op<=PRN_OP)/* one argument only */
          {
              /*structure looks like: opcode target-operand */
              if(set_current_word(line_words[1],code_img,ic,&num_add,"dest", there_is_label,op,symbol_table,num_symbol,extern_table,num_ref, curr_line_info)==ERROR)
                  return ERROR;
              code_img[*ic].word.source=0;/* no source operand value will be zero */
          }
          
          /* there are 2 arguments for this opcode */
          /* structure looks like: opcode source-operand , target-operand */
          else if(op>=MOV_OP && op<=LEA_OP)
          {
              if(set_current_word(line_words[1],code_img,ic,&num_add,"source", there_is_label,op,symbol_table,num_symbol,extern_table,num_ref, curr_line_info)==ERROR)/* set source operand */
              return ERROR;
              if(strcmp(line_words[2],"")==0)
              {
                  fprintf(stdout,"Error in file %s line %d: Expected more arguments\n", curr_line_info.file_name, curr_line_info.cnt_line);
                  return ERROR;
              }
              if(set_current_word(line_words[2],code_img,ic,&num_add,"dest",there_is_label,op,symbol_table, num_symbol,extern_table,num_ref,curr_line_info)==ERROR)/* set target operan */
                  return ERROR;      
          }
     }
      
     *ic=*ic+num_add;/* add to code memory counter the num of current command words */

     return VALID;
}

/* set and save the new word machine according to the type */
int set_current_word(char *word, machine_word *code_img,int *ic,int *num_add_word,char *target,int there_is_label,int op,symbol_type ***symbol_table,int *num_symbol,extern_ref ***extern_table,int *num_ref,line_info curr_line_info)
{
    int type=0,label_address,val;
    unsigned int *ptr;
    ptr=(unsigned int *)(&(code_img[*ic+*num_add_word].word));/*point to the current machine word*/
    /* send the word to the addressing_method and will save into type the addressing type */ 
    if(addressing_method(word,&type,there_is_label,op,symbol_table,num_symbol,curr_line_info)==ERROR)
    {
        return ERROR;
    }
    
    (*num_add_word)++;/* there is another machine word */
    
    /* set the first word dest or source to be type */
    if(strcmp(target,"dest")==0)
    {
        code_img[*ic].word.dest=type;
    }
    else
    {
        code_img[*ic].word.source=type;
    }
    
    /* the current word (ptr is pointing to there) will get a value according to its type */
    switch(type)
    {
        case IMMEDIATE:
            *ptr=atoi(word+1); /* the constant number */
            break;
        case REGISTER:
            val=atoi(word+1);
            *ptr=pow(2,val);/* the register number */
            break;
        case DIRECT:
            /* chekc if this a extern label, if yes save a reference to this line */
            if(symbol_is_extern(word,symbol_table,num_symbol)==VALID)
            {
                if(add_extern_reference(extern_table,num_ref,word,*ic+*num_add_word-1,curr_line_info)==ERROR)/* save a referenc */
                    return ERROR;
            }
            symbol_address(word,&label_address,symbol_table,num_symbol);/* will insert into val the address of this symbol */   *ptr=label_address;/* label address */
            break;
        case RELATIVE: 
            symbol_address(word,&label_address,symbol_table,num_symbol);/* will insert into val the address of this symbol */   
            *ptr=label_address-(*ic+*num_add_word-1);/* label distance from specific word mechine*/

            break;
    }
    if(check_type_valid_for_command(op,type,target)==ERROR)/* check that the type is valid and allowed for the command */
    {
        fprintf(stdout,"Error in file %s line %d: Addressing type did not match the command \n", curr_line_info.file_name, curr_line_info.cnt_line);
        return ERROR;
    }
    set_ARE(code_img,word,ic,num_add_word,type,symbol_table,num_symbol);/* set ARE for curren machine word */
    return VALID;
            
}
/* check that the addressing type is valid for this command, as listed at page 31 in the course booklet */
int check_type_valid_for_command(int op,int address_type,char *target)
{
    if( (op>=MOV_OP && op<=SUB_OP && strcmp(target,"source")==0) || ( strcmp(target,"dest")==0 && (op==CMP_OP || op==PRN_OP)) )
    {
        if(address_type==RELATIVE)
            return ERROR;
        return VALID;
    }
    if(op==LEA_OP && strcmp(target,"source")==0)
    {
        if(address_type==DIRECT)
            return VALID;
        return ERROR;
    }
    if(strcmp(target,"dest")==0 && ( op==MOV_OP || (op>=ADD_OP && op<=DEC_OP) || op==RED_OP) )
    {
        if(address_type==DIRECT || address_type==REGISTER)
            return VALID;
        return ERROR;
    }
    if(strcmp(target,"dest")==0 &&op==JMP_OP)
    {
        if(address_type==DIRECT || address_type==RELATIVE)
            return VALID;
        return ERROR;
    }

    return VALID;
}

/* set the ARE feild of the current machine word */
void set_ARE(machine_word *code_img,char *word,int *ic,int *num_add_word,int address_type,symbol_type ***symbol_table,int *num_symbol)
{
    if(symbol_exist(word,symbol_table,num_symbol)==VALID)
    {
        if(address_type==RELATIVE)/* if RELATIVE type set to be 'A' */
        {
            code_img[*ic+*num_add_word-1].ARE='A';
        }
        else if(symbol_is_local(word,symbol_table,num_symbol)==VALID)/* local label */
        {
            code_img[*ic+*num_add_word-1].ARE='R';
        }
        else/* extern label */
        {
            code_img[*ic+*num_add_word-1].ARE='E';
        }
    }
    else/* if there is no symbol */
    {
        code_img[*ic+*num_add_word-1].ARE='A';
    }
}

/* set type to the addressing type of word */
int addressing_method(char *word,int *address_type,int there_is_label,int op,symbol_type ***symbol_table,int *num_symbol,line_info curr_line_info)
{

    if(word[0]=='#')/* immediate */
      {
          if(is_integar((word+1),curr_line_info)==ERROR)/* check that after the # the value is valid - is an integar */
          {
              fprintf(stdout,"Error in file %s line %d: Error value is not an integar \n",curr_line_info.file_name,curr_line_info.cnt_line);
              return ERROR;
          }
          *address_type=IMMEDIATE;
      }
      else if(symbol_exist(word,symbol_table,num_symbol)==VALID)/* label */
      {
          *address_type=DIRECT;
      }
      else if(word[0]=='%')/* relative */
      {
          if(op==9)
          {
              if(symbol_is_data(word+1,symbol_table,num_symbol)!=ERROR ||symbol_is_extern(word+1,symbol_table,num_symbol)!=ERROR )/* label should be of command type only, could not be a data type or extern label or for sure if label not exist */
              {
                  fprintf(stdout,"Error in file %s line %d: Label of relative type could not be sign to this label \n", curr_line_info.file_name, curr_line_info.cnt_line);
                  return ERROR;
              }   
              *address_type=RELATIVE;
          }
          else
          {
               fprintf(stdout,"Error in file %s line %d: Invalid argument for this opcode \n",curr_line_info.file_name,curr_line_info.cnt_line);
               return ERROR;
          }
      }
      else if(is_register(word)==VALID)/* register direct */
      {
          *address_type=REGISTER;
      }
      else /* argument is not valid */
      {       
          fprintf(stdout,"Error in file %s line %d: Invalid argument \n",curr_line_info.file_name,curr_line_info.cnt_line);
          *address_type=NOT_VALID;
          return ERROR;
      }
      return VALID;
}

