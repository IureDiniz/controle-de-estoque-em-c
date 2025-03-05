#ifndef sistema_h
#define sistema_h

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <sys/stat.h>


typedef struct Produto TProduto, *PProduto;
typedef struct Venda TVenda, *PVenda;
typedef struct Compra TCompra, *PCompra;

void  cadastro_de_produto();
void  lista_do_estoque();

void registro_de_compra();
float entrada_no_estoque();
void lista_de_compras();

void registro_de_venda();
float saida_do_estoque();
void lista_de_vendas();


#endif