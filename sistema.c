#include "sistema.h"


struct Produto{
    char nome[50];
    int id;
    float preco;
    int qtd;
};

long arquivo_tamanho(const char *arq) {
    struct stat st;
    if (stat(arq, &st) != 0) {
        perror("Erro ao obter informações do arquivo");
        return -1; // Erro ao obter as informações do arquivo
    }
    return st.st_size;
}

void  cadastro_de_produto(){
    FILE *arq = fopen("arquivos/produtos.bin","ab");
    long arq_tamanho = arquivo_tamanho("arquivos/produtos.bin");

    if(!arq){
        printf("----------------------------------------------------------------------------------------------------\n");
        printf("Erro ao abrir arquivo de estoque!\n");
        printf("----------------------------------------------------------------------------------------------------\n");
        return;
    }else{
        
        TProduto p;
        p.id = (arq_tamanho/sizeof(TProduto)) + 1;
        printf("Nome: ");
        scanf(" %s", p.nome);
        printf("Quantidade: ");
        scanf(" %d", &p.qtd);
        printf("Preco: ");
        scanf(" %f", &p.preco);

        fwrite(&p, sizeof(TProduto), 1, arq);
        fclose(arq);
        printf("----------------------------------------------------------------------------------------------------\n");
        printf("Produto cadastrado com sucesso!\n");
        printf("----------------------------------------------------------------------------------------------------\n");
    }
}

void  lista_do_estoque(){
    FILE *arq = fopen("arquivos/produtos.bin", "rb");
    long arq_tamanho = arquivo_tamanho("arquivos/produtos.bin");

    if(!arq || arq_tamanho == 0){
        printf("----------------------------------------------------------------------------------------------------\n");
        printf("Nenhum produto no estoque!\n");
        printf("----------------------------------------------------------------------------------------------------\n");
        return;
    }
    
    TProduto p;
    printf("----------------------------------------------------------------------------------------------------");
    printf("\nLista de Produtos em Estoque:\n");
    while(fread(&p, sizeof(TProduto),1,arq)){
        printf("ID: %-5d\t Nome: %-25s\t Quantidade: %-5d\t Preco: %-7.2f\n",p.id,p.nome,p.qtd,p.preco);
    }
    printf("----------------------------------------------------------------------------------------------------\n");
    fclose(arq);
}

void registro_de_compra(){
      FILE *arq = fopen("arquivos/produtos.bin", "rb+");
      long arq_tamanho = arquivo_tamanho("arquivos/produtos.bin");

    if (!arq || arq_tamanho == 0) {
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
            printf("----------------------------------------------------------------------------------------------------");
            printf("\nCompra registrada!\nNova quantidade no estoque: %d\n",p.qtd);
            printf("----------------------------------------------------------------------------------------------------");
            return;
        }
    }
    fclose(arq);
    printf("----------------------------------------------------------------------------------------------------");
    printf("\nProduto nao encontrado!\n");
    printf("----------------------------------------------------------------------------------------------------");
}

void registro_de_venda(){
    FILE *arq;
    arq = fopen("arquivos/produtos.bin","rb+");
    long arq_tamanho = arquivo_tamanho("arquivos/produtos.bin");

    if(!arq || arq_tamanho == 0){
        printf("\nNenhum produto no estoque!\n");
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
                printf("----------------------------------------------------------------------------------------------------");
                printf("\nVenda registrada com sucesso!\nNovo estoque: %d\n",p.qtd);
                printf("----------------------------------------------------------------------------------------------------");
            }else{
                printf("----------------------------------------------------------------------------------------------------");
                printf("\nEstoque insuficiente!\n");
                printf("----------------------------------------------------------------------------------------------------");
                fclose(arq);
            }
            return;
        }
    }
    fclose(arq);
    printf("----------------------------------------------------------------------------------------------------");
    printf("\nProduto nao encontrado!\n");
    printf("----------------------------------------------------------------------------------------------------");
        
}
