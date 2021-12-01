#include "file_comments.c"

/* the first file will get the info from the second file passed in, in each #include command will actually copy the info from the file specified */
void add_include(FILE *fp3, FILE *fp2)
{
    char command[]={'#','i','n','c','l','u','d','e'};
    char file_name[LINE_LENGTH];
    char line[LINE_LENGTH];
    char ch;
    int i,j,k,error=0;
    FILE *tfp;/* temporary file */
    i=0;
    file_name[0]='\0';
/* going throgh the .c1 file, and copying it to the .c2 file
    wherever theres #include, will replace it with the data from the include file 
    insted of the include command*/
    while((ch=getc(fp2))!=EOF)
    {
        /* save each line */
        if(ch!='\n')
        {
            line[i]=ch;
            i++;
        }
        else/* when reach the end of the line, will check that specific line */
        {
            /* entire line */
            /* i -> num of char in line */
            line[i+1]='\0';
            line[i]='\n';
            
            i=0;
            error=0;
            /* skip white spaces */
            for(j=0;j<LINE_LENGTH && (line[j]==' ' || line[j]=='\t') ;j++)
            ;
            for(k=0;line[j]==command[k];j++,k++)/* check if the line contain #include at the beggining of line*/
            ;
            if(k==(COMMAND_LENGTH))/* #include is at beginning as a command */
            {
                /* insert insted of #include the actual info at that file */
                /* skip white spaces */
                for(;j<LINE_LENGTH && (line[j]==' ' || line[j]=='\t') ;j++)
                ;
                /* next character is " ->"name.c" */
                if(line[j]!='\"')
                {
                /*included file is not in "", will ignore this command */
                    error=1;
                }
                if(!error)
                {
                
                    j++;
                    for(k=0;j<LINE_LENGTH && line[j]!='\"' ;j++,k++)
                    {
                        file_name[k]=line[j];
                    }
                    file_name[k]='\0';
                    /*file_name contain the file to add content */
                    tfp=fopen(file_name,"r");
                    open_file(tfp);
                    /* copy the info from the file that is includ */
                    while((ch=getc(tfp))!=EOF)
    		    {
        	        putc(ch,fp3);
    		    }
    		    fclose(tfp);
    		    close_file(tfp);
    		}
                
            }
            else
            {
                /* the line does not begin with a include command */
                for(j=0;j<LINE_LENGTH && line[j]!='\0';j++)
                {
                     putc(line[j],fp3);
                }
               
            }
        }
    }
    /* close the open files (were passed in) */
    fclose(fp2);
    close_file(fp2);
    fclose(fp3);
    close_file(fp3);
    
}
