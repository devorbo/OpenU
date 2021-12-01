
#include "reserved.h"
#include "global.h"

struct func_element{
	char *func_name;
	opcode op;
	func fu;
};

/* function table */
static struct func_element func_table[] = {
		{"mov", MOV_OP, NONE_FU},
		{"cmp",CMP_OP, NONE_FU},
		{"add",ADD_OP, ADD_FU},
		{"sub",SUB_OP, SUB_FU},
		{"lea",LEA_OP, NONE_FU},
		{"clr",CLR_OP, CLR_FU},
		{"not",NOT_OP, NONE_FU},
		{"inc",INC_OP, INC_FU},
		{"dec",DEC_OP, DEC_FU},
		{"jmp",JMP_OP, JMP_FU},
		{"bne",BNE_OP, BNE_FU},
		{"jsr",JSR_OP, JSR_FU},
		{"red",RED_OP, NONE_FU},
		{"prn",PRN_OP, NONE_FU},
		{"rts",RTS_OP, NONE_FU},
		{"stop",STOP_OP, NONE_FU},
		{0, NOT_VALID_OP, NONE_FU}
};

/* check if a word is a reverse word in this assembly */
int is_reserved_word(char *word)
{
    if(is_command(word)==VALID || is_register(word)==VALID|| is_word_use_in_as(word)==VALID)
        return VALID;
    return ERROR;
}
/* word is register */
int is_register(char *word)
{
    if(word[0]=='r' && word[1]>='0' && word[1]<='7' && word[2]=='\0')/* word is a name of a register. register in this assembly are r0,r1...r7 */
    {
        return VALID;
    }
    return ERROR;
}

/* word is command */
int is_command(char *word) 
{
    int i;
    for(i=0;func_table[i].func_name!=0;i++)
    {
        if(strcmp(word,func_table[i].func_name)==0)/* word is a command */
        {
            break;
        }
    }
    if(func_table[i].func_name!=0)
    {
        return VALID;
    }
    return ERROR;/* word is not a command */
}
/* word is a saved word in the language */
int is_word_use_in_as(char *word)
{
    /* one of the saved words */
    if(strcmp(word,"data")==0 || strcmp(word,"string")==0 || strcmp(word,"extern")==0 || strcmp(word,"entry")==0 )
    {
        return VALID;
    }
    return ERROR;
}

/* return value opcode of command */
int find_command_opcode(char *word)
{
    int i;
    for(i=0;func_table[i].func_name!=0;i++)
    {
        if(strcmp(word,func_table[i].func_name)==0)/* found command name */
        {
            return func_table[i].op;/* return the value of opcode */
        }
    }
    return NOT_VALID_OP;/* command not exist */
}
/* return value func of command */
int find_command_func(char *word)
{
    int i;
    for(i=0;func_table[i].func_name!=0;i++)
    {
        if(strcmp(word,func_table[i].func_name)==0)/* found command name */
        {
            return func_table[i].fu;/* return the value of func */
        }
    }
    return NONE_FU;/* command not exist */
}

