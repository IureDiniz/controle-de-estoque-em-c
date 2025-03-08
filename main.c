#include "sistema.h"



int main(){
   int opcao;
   
   do{
        printf("\n1. Cadastrar Produto\n2. Listar Estoque\n3. Registrar Compra\n4. Listar Compras\n5. Registrar Venda\n6. Listar Vendas\n7. Sair\nEscolha: ");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                cadastro_de_produto();
                break;
            case 2:
                lista_do_estoque();
                break;
            case 3:
                registro_de_compra();
                break;
            case 4:
                lista_de_compras();
                break;
            case 5:
                registro_de_venda();
                break;
            case 6:
                lista_de_vendas();
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
   }while(opcao != 7);
   
    return 0;
}
