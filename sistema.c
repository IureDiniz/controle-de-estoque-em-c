#include "sistema.h"

struct Produto{
    char nome[50];
    int id;
    float preco_compra;
    float preco_venda;
    int qtd;
};

void linha(){
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
}


long arquivo_tamanho(const char *arq) {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    struct stat st;
    if (stat(arq, &st) != 0) {
        perror("Erro ao obter informações do arquivo");
        return -1; // Erro ao obter as informações do arquivo
    }
    return st.st_size;
}

void  cadastro_de_produto(){
    setlocale(LC_ALL, "pt_BR.UTF-8");
    FILE *arq = fopen("arquivos/produtos.bin","ab");
    long arq_tamanho = arquivo_tamanho("arquivos/produtos.bin");

    if(!arq){
        linha();
        printf("Erro ao abrir arquivo de estoque!\n");
        linha();
        return;
    }else{
        
        TProduto p;
        p.id = (arq_tamanho/sizeof(TProduto)) + 1;
        p.qtd = 0;
        printf("Nome: ");
        scanf(" %s", p.nome);
        printf("Preço de compra: ");
        scanf(" %f", &p.preco_compra);
        printf("Preço de venda: ");
        scanf(" %f", &p.preco_venda);

        fwrite(&p, sizeof(TProduto), 1, arq);
        fclose(arq);
        linha();
        printf("Produto cadastrado com sucesso!\n");
        linha();
    }
}

void  lista_do_estoque(){
    setlocale(LC_ALL, "pt_BR.UTF-8");
    FILE *arq = fopen("arquivos/produtos.bin", "rb");
    long arq_tamanho = arquivo_tamanho("arquivos/produtos.bin");

    if(!arq || arq_tamanho == 0){
        linha();
        printf("Nenhum produto no estoque!\n");
        linha();
        return;
    }
    
    TProduto p;
    linha();
    printf("Lista de Produtos em Estoque:\n");
    while(fread(&p, sizeof(TProduto),1,arq)){
        printf("ID: %-3d\t Nome: %-25s\t Quantidade: %-5d\t Preço de Venda: %-7.2f\t Preço de Compra: %-7.2f\n",p.id,p.nome,p.qtd,p.preco_venda, p.preco_compra);
    }
    linha();
    fclose(arq);
}

void registro_de_compra(){
    setlocale(LC_ALL, "pt_BR.UTF-8");
    FILE *arq = fopen("arquivos/produtos.bin", "rb+");
    long arq_tamanho = arquivo_tamanho("arquivos/produtos.bin");

    if (!arq || arq_tamanho == 0) {
        linha();
        printf("Nenhum produto em estoque!\n");
        linha();
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
            linha();
            printf("Compra registrada!\nNova quantidade no estoque: %d\n",p.qtd);
            linha();
            return;
        }
    }
    fclose(arq);
    linha();
    printf("Produto nao encontrado!\n");
    linha();
}

void registro_de_venda(){
    setlocale(LC_ALL, "pt_BR.UTF-8");
    FILE *arq;
    arq = fopen("arquivos/produtos.bin","rb+");
    long arq_tamanho = arquivo_tamanho("arquivos/produtos.bin");

    if(!arq || arq_tamanho == 0){
        linha();
        printf("\nNenhum produto no estoque!\n");
        linha();
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
                
                linha();
                printf("Venda registrada com sucesso!\nNovo estoque: %d\n",p.qtd);
                linha();
                return;
            }else{
                linha();
                printf("Estoque insuficiente!\n");
                linha();
                fclose(arq);
                return;
            }
        }
    }
    fclose(arq);
    linha();
    printf("Produto não encontrado!\n");
    linha();
        
}
