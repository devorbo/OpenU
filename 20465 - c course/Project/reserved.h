
#ifndef RESERVED_H
#define RESERVED_H

#include <string.h>
/* function opcodes */
typedef enum opcode{
    /* first command group - 2 operands */
    MOV_OP=0,
    CMP_OP=1,
    ADD_OP=2,
    SUB_OP=2,
    LEA_OP=4,
    /* second command group - 1 operand */
    CLR_OP=5,
    NOT_OP=5,
    INC_OP=5,
    DEC_OP=5,
    JMP_OP=9,
    BNE_OP=9,
    JSR_OP=9,
    RED_OP=12,
    PRN_OP=13,
    /* third command group - no operands */
    RTS_OP=14,
    STOP_OP=15,
    /* Error */
    NOT_VALID_OP=-1
    } opcode;
    
/* function func value */
typedef enum func{
    /* func for opcode 2  */
    ADD_FU=10,
    SUB_FU=11,
    /* func for opcode 5  */
    CLR_FU=10,
    NOT_FU=11,
    INC_FU=12,
    DEC_FU=13,
    /* func for opcode 9  */
    JMP_FU=10,
    BNE_FU=11,
    JSR_FU=12,
    /* NO value */
    NONE_FU=0
    }func;  
/* addressing type of command*/
typedef enum addressing{
    IMMEDIATE=0,
    DIRECT=1,
    RELATIVE=2,
    REGISTER=3,
    NOT_VALID=-1
    }addressing;

int is_reserved_word(char *word);
int is_command(char *word);
int is_register(char *word);
int is_word_use_in_as(char *word);
int find_command_opcode(char *word);
int find_command_func(char *word);


#endif

