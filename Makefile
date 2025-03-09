compile:
	gcc -c sistema.c main.c 
	gcc -o a.out sistema.o main.o -lm

execute:
		./a.out

compile-execute: compile
		 ./a.out
