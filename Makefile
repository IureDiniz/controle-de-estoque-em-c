compile:
	gcc -c sistema.c main.c 
	gcc -o a.out sistema.o main.o -lm

clean:
	rm arquivos/compras.bin

execute: compile
		 ./a.out
