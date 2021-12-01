#include "file_include.c"

int main(int argc, char *argv[])
{
    FILE *fp,*fp2,*fp3;/* fp2= The file will contain the original without comments, fp3 = The file after dealing with comments and #include  */  
    char str[LINE_LENGTH];/* will contain - file_name.c1 */
    char str2[LINE_LENGTH];/* will contain - file_name.c2 */

    printf("START\n");
    if(argc<=1)/* file name does not exist */
    {
        printf("Missing file name\n");
        exit(0);
    }
    else if(argc>2)
    {
        printf("Extra Arguments\n");
    }
    /* check that the file name is the correct type, ends with .c */
    if(argv[1][strlen(argv[1])-2]!='.' ||  argv[1][strlen(argv[1])-1]!='c')
    {
        printf("File type is not as expected. \nExpexted a .c file\n");
        exit(0);
    }
    fp=fopen(argv[1],"r");
    open_file(fp);/* check if file opened correctly, without errors */
        
    /* copying the file name and adding a char at the end e.g. name.c and naming it as name.c1 */   
    copy_name(str,argv[1],'1');
    fp2=fopen(str,"w");/* open that file to write in the information */
    open_file(fp2);
    
    remove_comment(fp2,fp);/* file_name.c1 contain the c code of file_name.c without the comments */

    copy_name(str2,argv[1],'2');/* copying the file name*/
    /* opening both files*/
    fp3=fopen(str2,"w");/* write into the .c2 file  */
    open_file(fp3);
    fp2=fopen(str,"r");/* read from the .c1 file */
    open_file(fp2);
    
    add_include(fp3,fp2);/* .c2 file will contain #including contect in addition to the .c1 file */ 
    
    printf("DONE\n");
    
    return 0;
}

