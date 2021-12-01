		
mymat: mat.o mymat.o mymethods.o
	gcc -g -Wall -ansi -pedantic mymat.o mat.o mymethods.o -o mymat	
mat.o: mat.c mat.h
	gcc -c -Wall -ansi -pedantic mat.c -o mat.o
		
mymethods.o: mymethods.c mymethods.h
	gcc -c -Wall -ansi -pedantic mymethods.c -o mymethods.o
		
mymat.o: mymat.c
	gcc -c -Wall -ansi -pedantic mymat.c -o mymat.o
