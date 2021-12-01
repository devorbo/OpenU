#include "mat.h" /* for using mat it is important */


#define COMMAND_LENGTH 256
#define COMMAND_ELEMENTS 128
#define NUM_MAT 6

/* matrix name and pointer */
typedef struct mats{
    char *name;
    mat *matrix;
    } mats;
	   
    	   
int invalid_comma(char *cmdcpy);
void split_command(char *splitcmd[], char *command);
int check_cmd(char * splitcmd[]);
int check_read_mat(char *splitcmd[],mat **mat1);
int real_number(char * str);
void method_3_mat(char *splitcmd[],mat **temp,mat **mat1,mat **mat2,mat **mat3);
void initialize_string(char *splitcmd[]);
int illegal_end(char *command);
int matrix_exist(mats *mats2,char *string,mat **mat1);
int extra_input(char *splitcmd[],int index);
void stop_run(char *splitcmd[],int endfile,mats *mats2,mat *temp);

