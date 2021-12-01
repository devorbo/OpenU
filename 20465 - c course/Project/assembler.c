
#include <math.h>
#include "first_pass.h"
#include "second_pass.h"
#include "symbol_list.h"
#include "extern_label.h"
#include "line_analysis.h"

int file_handling(char *file_name);
int write_to_ob_file(char *file_name,machine_word *code_img,int *data_img, int *icf, int *dcf,symbol_type ***symbol_table,int *num_symbol);
int add_entry_file(char *file_name,symbol_type ***symbol_table,int *num_symbol);
int add_extern_file(char *file_name,symbol_type ***symbol_table,int *num_symbol,extern_ref ***extern_table,int *num_ref);


int main(int argc,char *argv[])
{
    int i;
    fprintf(stdout,"\nAssembler program in action\n\n");
    if(argc<2)
    {
        fprintf(stdout,"Error: No input was passes in\n");
        return 0;
    }
    for(i=1;i<argc;i++)
    {
        file_handling(argv[i]);/* pass each argument as a file name */
    }
    fprintf(stdout,"This assembler program has ended \n");

    return 0;
}

int file_handling(char *file_name)
{   
    int ic=IC_INITIAL,dc=0,icf,dcf;
    machine_word code_img[ARR_CODE_MECHINE_LENGTH];
    char *cpy_name=malloc(LABEL_LENGTH);
    int data_img[ARR_CODE_MECHINE_LENGTH];
    symbol_type **symbol_table=NULL;/* table that will hold the label information */
    int num_symbol=0;/* num of symbols */
    extern_ref **extern_table=NULL;/* the table will hold the info of extern labels and there references in the given code, implementaion as the symbol_table */
    int num_ref=0;/* num of exten refernces */
    strcpy(cpy_name,file_name);/* will not destroy the original, each time will use a copy of the string */
    
    /* check memory allocation */
    if(!cpy_name )
    {
        fprintf(stdout,"Error in file %s.as: Memory allocation failed\n",file_name);
        return ERROR;
    }
    
    /* go through the file for the first time, will save all the label information, including refernce of externs label but not including entry. labels. Also will count code instruction and will save the data lines to the data memory .If an error was found in this stage, will report and will stop here */
    if(file_first_pass(cpy_name,data_img,&ic,&dc,&symbol_table,&num_symbol)==ERROR)
    {
        printf("File %s: Errors were found in this file, could not build an object file\n\n",cpy_name);
        return ERROR;
    }
    /* update the address of the symbols of type data */
    update_data_value_of_symbol(&ic,&symbol_table,&num_symbol);
    
    icf=ic;/* num of instruction memory */
    dcf=dc;/* will use it as num of data in memory */
    ic=IC_INITIAL;
    /*dc=0;*//*the dc value at the second pass is not useful. from here and on will use the dcf value */
   
    
    /* go through the file for the second time, build code memory. If an error was found in this stage, will stop running the code for this file*/
    if(file_second_pass(cpy_name,code_img,data_img,&ic,&symbol_table,&num_symbol,&extern_table,&num_ref)==ERROR)
    {
        printf("File %s: Errors were found in this file, could not build an object file\n\n",cpy_name);
        return ERROR;
    }
    
    /* will write the info of the code memory to a new file */
    strcpy(cpy_name,file_name);
    write_to_ob_file(cpy_name,code_img,data_img,&icf,&dcf,&symbol_table,&num_symbol);
    /* will write the entry labels and there address to a new file */
    strcpy(cpy_name,file_name);
    add_entry_file(cpy_name,&symbol_table,&num_symbol);
    /* will write all the refernces to extern labels to a new file */
    strcpy(cpy_name,file_name);
    add_extern_file(cpy_name,&symbol_table,&num_symbol,&extern_table,&num_ref);

    /* free the dynamic memory */
    free(cpy_name);
    free_symbol_table(&symbol_table,&num_symbol);
    free_extern_table(&extern_table,&num_ref);
    return 0;
}

/* write code memory to a file */
int write_to_ob_file(char *file_name,machine_word *code_img,int *data_img,int *icf,int *dcf,symbol_type ***symbol_table,int *num_symbol)
{
    
    FILE *fp;
    unsigned int *ptr;
    unsigned int num,shift_l;
    int i;
    char *str_lead=malloc(7);/* 4 digits for ic value, space and then max of two zeros before code,4+1+2=7 */
    char *str=malloc(LINE_LENGTH);/* str will hold the entire line to write to the file */
    char str_num[4];/* max code line is 4096- 4 digits. address value as char* */
    if(!str_lead || !str)
    {
        fprintf(stdout,"Error in file %s.as: Memory allocation failed\n",file_name);
        return ERROR;
    }
    strcat(file_name,".ob");/* add .ob to the file name */
    fp=fopen(file_name,"w");/* open a new file */
    if(!fp)
    {
        fprintf(stdout,"Error: File %s did not open correctly\n",file_name);
        return ERROR;
    }

    sprintf(str,"\t%d %d\n",*icf-IC_INITIAL,*dcf);/* number of lines of code and of data */
    fputs(str,fp);/* write the line to the file, at the top of the file */
    /* code memory */
    for(i=IC_INITIAL;i<*icf;i++)
    {
        str[0]='\0';
        ptr=(unsigned int *)(&(code_img[i].word));/* pointer to the word - as 12 bit */
        num=*ptr;
        shift_l=(unsigned int)(pow(2,12));
        num=num%shift_l;/* num will contain only 12 first bits of the word */
        strcpy(str_lead,"");
        if(i<1000)
            strcat(str_lead,"0"); /* add a zero to print before the value, to be 4 digits long */
        int_to_string(str_num,i); /* convert the value to a string */
        strcat(str_lead,str_num); /* will add the address number to be print */
        strcat(str_lead," ");
        if(num<pow(2,4))/* word is less or equal to 4 digits */
        {
            strcat(str_lead,"00");
        }
        else if(num<pow(2,8)) /*word is less or equal to 8 digits */
        {
            strcat(str_lead,"0");
        }
        sprintf(str,"%s%X %c\n",str_lead,num,code_img[i].ARE);/* save the currecnt line code as a string */     
        fputs(str,fp);/* write the line to the file */
    }
    /* write the data code to the file */
    for(i=0;i<*dcf;i++)
    {
        str[0]='\0';
        strcpy(str_lead,"");
        num=data_img[i];
        shift_l=(unsigned int)(pow(2,12));
        num=num%shift_l;
        if((i+*icf)<1000)
            strcat(str_lead,"0");
        int_to_string(str_num,i+*icf);/* address value starts at the end of the code memory, (and add i for current data)*/ 
        strcat(str_lead,str_num);
        strcat(str_lead," ");
        if(num<pow(2,4))
        {
            strcat(str_lead,"00");
        }
        else if(num<pow(2,8))
        {
            strcat(str_lead,"0");
        }
        sprintf(str,"%s%X A\n",str_lead,num);/* save the currecnt line code as a string */   
        fputs(str,fp);/* write the line to the file */
    }
    fclose(fp);
    
    free(str);
    free(str_lead);
    return VALID;
}
/* write entry info to a file */
int add_entry_file(char *file_name,symbol_type ***symbol_table,int *num_symbol)
{
    FILE *fp;
    char *str_lead=malloc(1);/* one lead zero before ic value */
    char *str=malloc(LINE_LENGTH);/* str will hold the entire line to write to the file */
    int i;
    /* check memory allocation */
    if(!str_lead || !str)
    {
        fprintf(stdout,"Error in file %s.as: Memory allocation failed\n",file_name);
        return ERROR;
    }
    /* check if there is entry labels, if true then create a file for this labels */
    if(entry_exist(symbol_table,num_symbol)==VALID)
    {
        strcat(file_name,".ent");/* add .ent to the file name */
        fp=fopen(file_name,"w");/* open a new file */
        if(!fp)
        {
            fprintf(stdout,"Error: File %s did not open correctly\n",file_name);
            return ERROR;
        }
        for(i=0;i<*num_symbol;i++)/* go over the symbol table */
        {
            if(strstr((*(*symbol_table+i))->attribute,"entry")!=NULL)/* check if current label in the table is an entry label*/
            {
                str[0]='\0';
                strcpy(str_lead,"");
                if((*(*symbol_table+i))->value<1000)
                    strcat(str_lead,"0"); 
                sprintf(str,"%s %s%d\n",(*(*symbol_table+i))->symbol,str_lead,(*(*symbol_table+i))->value);/* symbol and address of entry label */     
                fputs(str,fp);/* write the line to the file */
            }
        }
        fclose(fp);
    }
    free(str);
    free(str_lead);
    return VALID;
}

/* write extern refernce to a file */
int add_extern_file(char *file_name,symbol_type ***symbol_table,int *num_symbol,extern_ref ***extern_table,int *num_ref)
{
    FILE *fp;
    char *str_lead=malloc(1);/* one lead zero before ic value */
    char *str=malloc(LINE_LENGTH);
    int i;
    /* check memory allocation */
    if(!str_lead || !str)
    {
        fprintf(stdout,"Error in file %s.as: Memory allocation failed\n",file_name);
        return ERROR;
    }
    if(extern_exist(symbol_table,num_symbol)==VALID)
    {
        strcat(file_name,".ext");/* add .ext to the file name */
        fp=fopen(file_name,"w");/* open a new file */
        if(!fp)
        {
            fprintf(stdout,"Error: File %s did not open correctly\n",file_name);
            return ERROR;
        }
        for(i=0;i<*num_ref;i++)/* go over the extern reference table */
        {
            str[0]='\0';
            strcpy(str_lead,"");
            if((*(*extern_table+i))->value<1000)
                strcat(str_lead,"0"); 
            sprintf(str,"%s %s%d\n",(*(*extern_table+i))->symbol,str_lead,(*(*extern_table+i))->value);
            fputs(str,fp);/* write the line to the file */
        }
        fclose(fp);
    }
    
    free(str);
    free(str_lead);
    return VALID;
}

