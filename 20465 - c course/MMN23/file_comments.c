#include "file_handling.c"

void remove_comment(FILE *fp2, FILE *fp)
{
    int c;
    int state=OUT;
    /* writing to the .c1 file the conntext of the .c file, not including the comments of the c language */
    while((c=getc(fp))!=EOF)
    {
        switch(state)
        {
            case OUT:
                if(c=='/')
                    state=LEFT_SLASH;
                else
                {
                    putc(c,fp2);
                    if(c=='\"')
                        state=IN_STRING;
                }
                break;
            case LEFT_SLASH:
                if(c=='*')
                    state= IN_COMMENT;
                else
                {
                    putc((int)'\'',fp2);/* write the slash now, was ignored before untill that the char after was checked */
                    putc(c,fp2);
                    state=OUT;
                }
                break;
            case IN_COMMENT:
                if(c=='*')
                    state=RIGHT_STAR;
                break;
            case RIGHT_STAR:
                if(c=='/')
                    state=OUT;
                else if(c!='*')
                    state=IN_COMMENT;
                break;
            case IN_STRING:
                if(c=='\"')
                    state=OUT;
                putc(c,fp2);
                break;
        }     
    }
    fclose(fp);
    fclose(fp2);
}


