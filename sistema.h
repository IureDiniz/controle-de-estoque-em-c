#ifndef sistema_h
#define sistema_h

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


typedef struct Produto TProduto, *PProduto;

void  cadastro_de_produto();
void  lista_do_estoque();
void registro_de_compra();
void registro_de_venda();


#endif