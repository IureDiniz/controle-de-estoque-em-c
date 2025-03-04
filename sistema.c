#include "sistema.h"

struct Produto{
    char nome[50];
    int id;
    float preco;
    int qtd;
};

void  cadastro_de_produto(){
    FILE *arq = fopen("arquivos/produtos.bin","ab");
    
    if(!arq){
        printf("Erro ao abrir arquivo de estoque!\n");
        return;
    }else{
        TProduto p;
        printf("ID: ");
        scanf(" %d", &p.id);
        printf("Nome: ");
        scanf(" %s", p.nome);
        printf("Quantidade: ");
        scanf(" %d", &p.qtd);
        printf("Preço: ");
        scanf(" %f", &p.preco);

        fwrite(&p, sizeof(TProduto), 1, arq);
        fclose(arq);
        printf("Produto cadastrado com sucesso!\n");
    }
}

void  lista_do_estoque(){
    FILE *arq = fopen("arquivos/produtos.bin", "rb");
    if(!arq){
        printf("Nenhum produto no estoque!\n");
        return;
    }
    
    TProduto p;
    printf("\nLista de Produtos em estoque:\n");
    while(fread(&p, sizeof(TProduto),1,arq)){
        printf("ID: %-5d\t Nome: %-25s\t Quantidade: %-5d\t Preço: %-7.2f\n",p.id,p.nome,p.qtd,p.preco);
    }
    fclose(arq);
}

void registro_de_compra(){
      FILE *arq = fopen("arquivos/produtos.bin", "rb+");
    if (!arq) {
        printf("Nenhum produto em estoque!\n");
        return;
    }
     int id, num;
    printf("ID do produto: ");
    scanf("%d",&id);
    printf("Quantidade comprada: ");
    scanf("%d",&num);
    
    TProduto p;
    while(fread(&p, sizeof(TProduto),1,arq)){
        if(p.id == id){
            p.qtd = p.qtd + num;
            fseek(arq, -sizeof(TProduto),SEEK_CUR);
            fwrite(&p,sizeof(TProduto),1,arq);
            fclose(arq);
            printf("Compra registrada!\nNovo estoque: %d\n",p.qtd);
            return;
        }
    }
    fclose(arq);
    printf("Produto não encontrado!\n");
}

void registro_de_venda(){
    FILE *arq;
    arq = fopen("arquivos/produtos.bin","rb+");
    if(!arq){
        printf("Nenhum produto no estoque!\n");
        return;
    }
    
    int id, num;
    printf("ID do produto: ");
    scanf("%d",&id);
    printf("Quantidade vendida: ");
    scanf("%d",&num);
    
    TProduto p;
    while(fread(&p, sizeof(TProduto),1,arq)){
        if(p.id == id){
            if(p.qtd >= num){
                p.qtd = p.qtd - num;
                fseek(arq, -sizeof(TProduto), SEEK_CUR);
                fwrite(&p,sizeof(TProduto),1,arq);
                fclose(arq);
                printf("Venda registrada com sucesso!\nNovo estoque: %d\n",p.qtd);
            }else{
                printf("Estoque innsuficiente!\n");
                fclose(arq);
            }
            return;
        }
    }
    fclose(arq);
    printf("Produto não encontrado!\n");
        
}
