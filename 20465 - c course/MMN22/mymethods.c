#include <errno.h>
#include "mymethods.h"

/* methods to help check correct input from user */
    	   
int invalid_comma(char *cmdcpy)
{
    int i,j,end,error,open;
    char comma;
    char *splitcmd[COMMAND_ELEMENTS];
    char *token=strtok(cmdcpy," \t\n");
    comma=',';
    error=0;
    open=0;
    initialize_string(splitcmd);/* set strings as no value - "" */
    /*split strings to tokens by white spacese */
    for (i=0;i<COMMAND_ELEMENTS && token != NULL;i++) 
    { 
        splitcmd[i]=token;/* save the token as an element */
        token = strtok(NULL, " \t\n"); 
    } 
    end=i;/* end of input in the array */

    /* check for invalid commas */
    /* comma before or after command name */
    if(splitcmd[0][0]==comma || splitcmd[0][strlen(splitcmd[0])-1]==comma ||splitcmd[1][0]==comma)
    {
        printf("Illegal comma\n");  
        error=1;
    }
    /*missing or illegal commas in total command */
    else
    {
        if(splitcmd[1][strlen(splitcmd[1])-1]==comma)
        {
            open=1;
        }
        for(i=1;i<end && !error;i++)
        {
            if(i!=1)/* no comma at beginning for the first argument - was checked before */
            {
		    /* comma before argument*/
		    if(splitcmd[i][0]==comma)
		    {
		        /* comma after last argument - two commas ->illegal*/
			if(open)
			{
			    error=1;
			    printf("Multiply consecutive commas\n"); 
			}
			else
			    open=1;
		    }
		    /* no comma before the argument*/
		    else if(!open)
		    {
			error=1;
			printf("Missing comma\n");
		    }
            }
            if(!error)
            {
            /*check if the entire line correct (were not sepreate by white spaces), no illegals comma */
            for(j=0;  j<strlen(splitcmd[i])-1 && !error;j++)
            {
                /* commas one after the other before or after argument */
                if(splitcmd[i][j]==comma)
                {
                    if(splitcmd[i][j+1]==comma)
                    {
                        error=1;
                        printf("Illegal comma\n"); 
                    }
                }
            }
            }
            /* end of argument check whether there is a comma*/
            if(splitcmd[i][strlen(splitcmd[i])-1]==comma)
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
        if(!error && open)
        {
            error=1;
            printf("Illegal comma\n"); 
        } 
    }
    return error;
}  
/* split command by spaces, tabs and commas */
void split_command(char *splitcmd[], char *command)
{
	/* split by using token */
	int i;
        char *token=strtok(command," \t\n,");
	for (i=0;i<COMMAND_ELEMENTS && token != NULL;i++) 
	{ 
	    splitcmd[i]=token;/* save the token as an element */
	    token = strtok(NULL, " \t\n,"); 
	}   
} 
/* check command */
int check_cmd(char *splitcmd[])
{
      int i=0;
      char *cmd[]={"read_mat","print_mat","add_mat","sub_mat","mul_mat","mul_scalar","trans_mat","stop",NULL};
      /* first element is command function */
      /* go over the existed commands */
      for(i=0;cmd[i]!=NULL;i++)
      {
          if(strcmp(splitcmd[0],cmd[i])==0)/* if found the specific command exist will stop the loop */
              break;
      }
      if(cmd[i]==NULL)/* in case that loop finished and command didnt exist */
      {
          printf("Undefined command name\n");
          return 1;
      }
      return 0;/* command is correct */
}

int check_read_mat(char *splitcmd[],mat **mat1)
{
    int i,error;
    double numbers[MAT_LENGTH*MAT_LENGTH];
    /* initilaize array with default value, in case that will not fill up entirely */
    for(i=0;i<MAT_LENGTH*MAT_LENGTH;i++)
        numbers[i]=0;
    error=0;
	    if(strcmp(splitcmd[0],"read_mat")==0)
            {
                if(strcmp(splitcmd[2],"")==0)/* no numbers passed in */
                {
                    printf("no number had passed in\n");
                    error=1;
                }
                else
                {
		        /* pass in matrix and array of numbers of type double */
		        for(i=2;!error && !(strcmp(splitcmd[i],"")==0);i++)/* check untill the end of input */
		        /* the numbers are stored from the second argument */
		        {
		            error=real_number(splitcmd[i]);/* will check if the input is a real number */  
		            if(!error && i<MAT_LENGTH*MAT_LENGTH+2)
		            {
		                /* convert the number and save it as a real number (-double) */
		                numbers[i-2]=atof(splitcmd[i]);/* indexes 0-15 */
		            }
		            else if(error)
		            {
		                printf("Argument is not a real number\n");
		            }
		         }
		         if(!error)
		         {
		             /* send to function that will enter the values to the matrix*/
		             read_mat(mat1,numbers);
		         }
                 }
             }/* end of read_mat */
        return error;
}
/* check if a string is a real number */
int real_number(char * str)
{
    int error,first,i;
    error=0;
    first=1;
    /*skip whitespaces */
    for(i=0;isspace(str[i]);i++)
    ;
    if(str[i]=='.' && str[i+1]=='\0')/* the string that was passed in is "." and is illegal */
        error=1;
    else
    {
    for(;!error && str[i]!='\0' ;i++)
    {
        /* the sign could be shown only before the number */
        if(str[i]=='-' || str[i]=='+')
        {
            if(i!=0)
            {
                error=1;
            }
        }     
        else if(!(isdigit(str[i])))/* in case character is not digit, will check specific cases */
        {
                if(str[i]=='.')/* the point can appear once */
                {
                    if(first)
                        first=0;
                    else
                        error=1;
                }
                else
                    error=1;
        }
    }
    }
    return error;
}
/* will get 3 matrices and the splitted command, and will determind to which function to send it */
void method_3_mat(char *splitcmd[],mat **temp,mat **mat1,mat **mat2,mat **mat3)
{
    if(strcmp(splitcmd[0],"add_mat")==0)
    {
        add_mat(mat1,mat2,mat3);
    }
    else if(strcmp(splitcmd[0],"sub_mat")==0)
    {
        sub_mat(mat1,mat2,mat3);
    }
    else if(strcmp(splitcmd[0],"mul_mat")==0)
    {
        mul_mat(temp,mat1,mat2,mat3);
    }
}
/* initializ the array elements to be empty strings */
void initialize_string(char *splitcmd[])
{
    int i;
    for(i=0;i<COMMAND_ELEMENTS;i++)
    {
        splitcmd[i]="";
    }
}
/* if ended by EOF, and not an a correct way by using stop */
int illegal_end(char *command)
{
	if(command[strlen(command)-1]!='\n' || command[strlen(command)-1]==EOF)/* exit not an a valid way */
		return 1;
	return 0;
}
/* will check if matrix is correct and exist */
int matrix_exist(mats *mats2,char *string,mat **mat1)
{
    int i;
    /* go over all matrices */
    for(i=0;mats2[i].matrix!=NULL;i++)
    {
        if(strcmp(string,mats2[i].name)==0)/* if found the specific matrix will stop the loop */
            break;
    }
    /* in case that loop finished and matrix didnt exist */
    if(mats2[i].matrix==NULL)
    {
       printf("Undefined matrix name\n");
       return 1;
    }
    else/* matrix is correct */
    {
        *mat1=mats2[i].matrix;
    }
    return 0;
}
/* check if there some extra input after command */
int extra_input(char *splitcmd[],int index)
{
    /* index - the index after the last argument */
    if(strcmp(splitcmd[index],"")!=0)
    {
        printf("Extraneous text after end of command \n");
        return 1;
    }
    return 0;
}
/* stop the program */
void stop_run(char *splitcmd[],int endfile,mats *mats2,mat *temp)
{
    int i,error;
    error=0;
    if(strcmp(splitcmd[0],"stop")==0 || endfile)/* check also EOF or didnt enter stop at end of file */
    {
        /* in case of exiting not by the command stop */
        if(!(strcmp(splitcmd[0],"stop")==0) )
        {
            error=1;
        }
        else
        { 
            /* in case of text after command will print a comment */
            i=extra_input(splitcmd,1);/* return a value, will save it as gurbage, will not be in use */
        }
        /* will empty out the dinamic memory */
        for(i=0;i<NUM_MAT;i++)
        {
            free(mats2[i].matrix);
        }
        free(temp);
        stop(error);
    }
}
