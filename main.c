#include "sistema.h"



int main(){
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int opcao;
   
    do{
        printf("\n1. Cadastrar Produto\n2. Listar Estoque\n3. Registrar Compra\n4. Registrar Venda\n5. Sair\nEscolha: ");
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
                printf("\n----------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("Saindo...");
                printf("\n----------------------------------------------------------------------------------------------------------------------------------------\n");
                break;
            default:
                printf("\n----------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("Opção inválida!");
                printf("\n----------------------------------------------------------------------------------------------------------------------------------------\n");
        }
   }while(opcao != 5);
   
    return 0;
}
