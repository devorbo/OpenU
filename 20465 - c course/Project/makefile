assembler:assembler.o second_pass.o first_pass.o data_memory.o code_memory.o extern_label.o symbol_list.o reserved.o line_analysis.o 
	gcc -g -Wall -ansi -pedantic  assembler.o second_pass.o first_pass.o data_memory.o code_memory.o extern_label.o symbol_list.o  reserved.o line_analysis.o -o assembler -lm
	
line_analysis.o: line_analysis.c line_analysis.h
	gcc -c -Wall -ansi -pedantic line_analysis.c -o line_analysis.o
	
reserved.o: reserved.c reserved.h 
	gcc -c -Wall -ansi -pedantic reserved.c -o reserved.o

	
symbol_list.o: symbol_list.c symbol_list.h  global.h
	gcc -c -Wall -ansi -pedantic symbol_list.c -o symbol_list.o

extern_label.o: extern_label.c extern_label.h  
	gcc -c -Wall -ansi -pedantic extern_label.c -o extern_label.o
	
	
data_memory.o: data_memory.c data_memory.h
	gcc -c -Wall -ansi -pedantic data_memory.c -o data_memory.o		

code_memory.o: code_memory.c code_memory.h
	gcc -c -Wall -ansi -pedantic  code_memory.c -o code_memory.o -lm
	
first_pass.o: first_pass.c first_pass.h data_memory.h
	gcc -c -Wall -ansi -pedantic first_pass.c -o first_pass.o

second_pass.o: second_pass.c second_pass.h 
	gcc -c -Wall -ansi -pedantic second_pass.c -o second_pass.o
	
assembler.o: assembler.c    
	gcc -c -Wall -ansi -pedantic assembler.c  -o assembler.o -lm

clean:
	rm -rf *.o
