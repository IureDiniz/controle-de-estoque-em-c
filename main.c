#include "sistema.h"



int main(){
   setlocale(LC_ALL,"Portuguese");
   int opcao;
   
   do{
        printf("\n1. Cadastrar Produto\n2. Listar Estoque\n3. Registrar Compra\n4. Registrar Venda\n5. Lista de vendas\n6. Sair\nEscolha: ");
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
                registro_de_venda();
                break;
            case 5:
                lista_de_vendas();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
   }while(opcao != 6);
   
    return 0;
}
