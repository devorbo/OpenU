mypreprocessor: preprocessor.o 
	gcc -g -Wall -ansi -pedantic preprocessor.o -o mypreprocessor
file_handling.o: file_handling.c
	gcc -c -Wall -ansi -pedantic file_handling.c -o file_handling.o	
file_comments.o: file_comments.c file_handling.o
	gcc -c -Wall -ansi -pedantic file_comments.c -o file_comments.o
file_include.o: file_include.c file_comments.o 
	gcc -c -Wall -ansi -pedantic file_include.c -o file_include.o
preprocessor.o: preprocessor.c preprocessor.h file_include.o 
	gcc -c -Wall -ansi -pedantic preprocessor.c -o preprocessor.o
	

	
