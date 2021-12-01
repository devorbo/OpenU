
#ifndef GLOBAL_H
#define GLOBAL_H


#define ARR_CODE_MECHINE_LENGTH 1200
#define IC_INITIAL 100
#define LINE_LENGTH 81
#define LABEL_LENGTH 31
#define WORD_LENGTH 10

enum status{VALID,ERROR,NONE};

typedef struct
    {
        unsigned int dest:2;
        unsigned int source : 2;
        unsigned int func :4;
        unsigned int opcode:4;
}m_word;
    
typedef struct
{
    char ARE;
    m_word word;
   
}machine_word;

 
typedef struct line_info{
    char *line;
    char file_name[LABEL_LENGTH];
    int cnt_line;
}line_info;

#endif
