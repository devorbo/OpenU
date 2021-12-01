#include "mymethods.h"

        	   
int main()
{
    char command[COMMAND_LENGTH];/* command from user */
    char cmdcpy[COMMAND_LENGTH];/* command to be worked on and destroy */
    char *splitcmd[COMMAND_ELEMENTS];/* the command splited, each argument as a element */
    int i,error,endfile,count;
    double scalar=1;
    mat *MAT_A=NULL,*MAT_B=NULL,*MAT_C=NULL,*MAT_D=NULL,*MAT_E=NULL,*MAT_F=NULL;
    mat *mat1=NULL,*mat2=NULL,*mat3=NULL;
    mat *temp=NULL;/* use it as a temporary matrix for passing temporary data */
    mats mats2[NUM_MAT+1];/* hold matrixs and matrices names */
    
    error=0;
    endfile=0;
    count=0;
    
    /* insert the values of matrices */
    mats2[0].name="MAT_A";
    mats2[0].matrix=MAT_A;
    mats2[1].name="MAT_B";
    mats2[1].matrix=MAT_B;
    mats2[2].name="MAT_C";
    mats2[2].matrix=MAT_C;
    mats2[3].name="MAT_D";
    mats2[3].matrix=MAT_D;
    mats2[4].name="MAT_E";
    mats2[4].matrix=MAT_E;
    mats2[5].name="MAT_F";
    mats2[5].matrix=MAT_F;
    mats2[6].name="not_valid";
    mats2[6].matrix=NULL;

    /* initialize and build dinamic memory for the matrices */
    /* dinamic memory and 2D array? */
    for(i=0;i<NUM_MAT;i++)
    {
        mats2[i].matrix=(mat *)calloc(MAT_LENGTH*MAT_LENGTH,sizeof(mat));
        if(!mats2[i].matrix)/* if calloc didnt work correctly */
        {
            printf("Memory allocation failed\n");
            exit(0);
        }
    }	
    temp=(mat *)calloc(MAT_LENGTH*MAT_LENGTH,sizeof(mat));
    if(temp==NULL)/* if calloc didnt work correctly */
    {
        printf("Memory allocation failed\n");
        exit(0);
    }


  FOREVER
  {
    /* initialize the variable in each round */
    count=0;
    error=0;
    endfile=0;
    /*getstring*/
    printf("\ninsert a command\n");
    fgets(command,COMMAND_LENGTH,stdin);/* fgets - will stop when reach end of file , \n or COMMAND_LENGTH-1 */
    printf("the command is: %s\n",command);

    
    strcpy(cmdcpy,command);/* copy string */
    error=invalid_comma(cmdcpy);/* check for invalid commas  */
    initialize_string(splitcmd);/* set strings as no value - "" */
    if(!error)/* no error of commas*/
    {
        /*command: */
	strcpy(cmdcpy,command);
	split_command(splitcmd,cmdcpy);/* split command by spaces, tabs and commas */
      if(!(strcmp(splitcmd[0],"")==0) )/* not an empty line */         
      {
        
	error=check_cmd(splitcmd);/* does command exist? return 1 incase of error*/	
        if(!error)/* no error from command*/
        {
            count++;/* command is the first element*/
            stop_run(splitcmd,endfile,mats2,temp);/* will exit the program in case of stop. in other case will continue*/
        
              /* all methods except stop are using at least one matrix, as the first argument */
              if(strcmp(splitcmd[1],"")==0)              
              {
                  printf("Missing Argument\n");
                  error=1;
              }
              else
              {
                  error=matrix_exist(mats2,splitcmd[1],&mat1);/* check whether matrix name is correct */
              }
              if(!error)/* no error in first argument - matrix */
              { 
                  count++;/* first matrix */
         	    if(strcmp(splitcmd[0],"read_mat")==0)
     	 	    {
		        error= check_read_mat(splitcmd,&mat1);/* send to method the check if the arguments are real numers, and if the entire command is correct, will enter the values to the matrix */
		    }
		    else if(strcmp(splitcmd[0],"print_mat")==0)
		    {
		        error=extra_input(splitcmd,count);/* check whether there extra input after command */
		        if(!error)
		        {
		            print_mat(&mat1);/* send a the address of matrix */ 
		        }
		    }
		    /* multiply by scalar */
		    else if(strcmp(splitcmd[0],"mul_scalar")==0)
		    { 
		         if(strcmp(splitcmd[2],"")==0||strcmp(splitcmd[3],"")==0) 
              		 {
                	      printf("Missing Argument\n");
              		      error=1;
            	         }
            	         else
            	         {
            	             /* second argument is a real number */
		             error = real_number(splitcmd[2]);
		             if(error)
		             {
		                 printf("Argument is not a scalar\n");
		             }
		             else
		             {
		                 count++;/* scalar */      
		                 error=matrix_exist(mats2,splitcmd[3],&mat2);/* third argument is matrix */ 
		                 count++;/* second matrix */
				     if(!error)/* no error at matrix */
				     { 
					 /* send arguments to multiply by scalar */
					 error=extra_input(splitcmd,count);
					 if(!error)
					 {
					     scalar=atof(splitcmd[2]);/* convert the string to double */
					     mul_scalar(&mat1,scalar,&mat2);
					 }
				     }
		              }

		         }
		    }
		    else
		    {
		        /* rest of functions are using at least two matrices (-matrix as second argument) */
		        if(strcmp(splitcmd[2],"")==0) 
              	        {
                	      printf("Missing Argument\n");
              		      error=1;
            	        } 
            	        else
            	        {
		            error=matrix_exist(mats2,splitcmd[2],&mat2);/* second argument is matrix */
		            count++;/* second matrix */
		        }
		        if(!error)/* no error at the second matrix */
		        {
		            if(strcmp(splitcmd[0],"trans_mat")==0)
		            {
		                error=extra_input(splitcmd,count);
		                if(!error)
		                    trans_mat(&temp,&mat1,&mat2);
		            }
		            else 
		            {
		            /* rest of functions are using three matrices(-matrix as first,second and third arguments)*/
		                if(strcmp(splitcmd[3],"")==0) 
              		        {
                                    printf("Missing Argument\n");
                                    error=1;
            	                }
            	                else
            	                {
		                    error=matrix_exist(mats2,splitcmd[3],&mat3);/* third argument is matrix */
		                    count++;/* thired matrix */
		                }
		            }
		        }/* end error after second matrix */
		        if(!error)/* if no error until here inclding at third matrix */
		        {
		            error=extra_input(splitcmd,count);
		            if(!error)
		            {
		                method_3_mat(splitcmd,&temp,&mat1,&mat2,&mat3);/* send the three matrices, the method will send to the currect functions */ 
		            }
		        }

                    }
                
            }  /* end for no errors for first matrix */
          }/* end of not an empty line */
        } /* end for command name */  
    }/* end of no errors for commas */   
  }/* end of FOREVER loop*/  
    return 0;
}
  

