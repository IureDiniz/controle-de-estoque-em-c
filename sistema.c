#include "sistema.h"

struct Produto{
    char nome[50];
    int id;
    float preco;
    int qtd;
};

struct Venda{
    char cliente[50];
    int id;
    float preco;
    PProduto itens; 
};

struct Compra{
    int id;
    float preco;    
    PProduto itens;
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
        printf("Erro ao abrir arquivo de estoque!\n");
        return;
    }else{
        
        TProduto p;
        p.id = (arq_tamanho/sizeof(TProduto)) + 1;
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
    long arq_tamanho = arquivo_tamanho("arquivos/produtos.bin");

    if(!arq || arq_tamanho == 0){
        printf("Nenhum produto no estoque!\n");
        return;
    }
    
    TProduto p;
    printf("----------------------------------------------------------------------------------------------------");
    printf("\nLista de Produtos em estoque:\n");
    while(fread(&p, sizeof(TProduto),1,arq)){
        printf("ID: %-5d\t Nome: %-25s\t Quantidade: %-5d\t Preço: %-7.2f\n",p.id,p.nome,p.qtd,p.preco);
    }
    printf("----------------------------------------------------------------------------------------------------\n");
    fclose(arq);
}

void registro_de_compra(){
    FILE *arq = fopen("arquivos/compras.bin","ab");
    long arq_tamanho = arquivo_tamanho("arquivos/compras.bin");
    TCompra c;
    float total = 0;

    if(!arq){
        printf("Erro ao abrir arquivo de estoque!\n");
        return;
    }else{
        c.id = (arq_tamanho/sizeof(TCompra)) + 1;

        total = total + entrada_no_estoque(); 

        c.preco = total;

        fwrite(&c, sizeof(TCompra), 1, arq);
        fclose(arq);
        printf("Compra registrada com sucesso!\n");
        printf("-----------------------------\n");
    }
}

float entrada_no_estoque(){
      FILE *arq = fopen("arquivos/produtos.bin", "rb+");
    if (!arq) {
        printf("Nenhum produto em estoque!\n");
        return -1;
    }
    int id, num;
    printf("ID do produto: ");
    scanf("%d",&id);
    printf("Quantidade comprada: ");
    scanf("%d",&num);
    
    float total = 0;
    TProduto p;
    while(fread(&p, sizeof(TProduto),1,arq)){
        if(p.id == id){
            p.qtd = p.qtd + num;
            total = total + (p.preco * num);
            fseek(arq, -sizeof(TProduto),SEEK_CUR);
            fwrite(&p,sizeof(TProduto),1,arq);
            fclose(arq);
            printf("Compra registrada!\nNovo estoque: %d\n",p.qtd);
            return total;
        }
    }
    fclose(arq);
    printf("Produto não encontrado!\n");
}

void lista_de_compras(){
    FILE *arq = fopen("arquivos/compras.bin", "rb");
    long arq_tamanho = arquivo_tamanho("arquivos/compras.bin");

    if(!arq || arq_tamanho == 0){
        printf("Nenhuma compra realizada!\n");
        return;
    }
    
    TCompra c;
    printf("----------------------------------------------------------------------------------------------------");
    printf("\nLista de Compras:\n");
    while(fread(&c, sizeof(TCompra),1,arq)){
        printf("ID: %-5d\t Preço: %-7.2f\n",c.id, c.preco);
    }
    printf("----------------------------------------------------------------------------------------------------\n");
    fclose(arq);
}

void registro_de_venda(){
    FILE *arq = fopen("arquivos/vendas.bin","ab");
    long arq_tamanho = arquivo_tamanho("arquivos/vendas.bin");
    TVenda v;
    int itens;
    float total = 0;

    if(!arq){
        printf("Erro ao abrir arquivo de estoque!\n");
        return;
    }else{
        v.id = (arq_tamanho/sizeof(TVenda)) + 1;
        printf("Cliente: ");
        scanf(" %s", v.cliente);
        printf("Número de produtos: ");
        scanf(" %d", &itens);

        for(int i = 0; i < itens; i++){
            total = total + saida_do_estoque(); 
            if(total == -1){
                printf("Nenhum produto no estoque!\n");
                return;
            }
        }

        v.preco = total;

        fwrite(&v, sizeof(TVenda), 1, arq);
        fclose(arq);
        printf("Venda registrada com sucesso!\n");
        printf("-----------------------------\n");
    }
}

float saida_do_estoque(){
    FILE *arq;
    arq = fopen("arquivos/produtos.bin","rb+");
    if(!arq){
        printf("Nenhum produto no estoque!\n");
        return -1;
    }
    
    float total = 0;
    int id, num;
    printf("ID do produto: ");
    scanf("%d",&id);
    printf("Quantidade vendida: ");
    scanf("%d",&num);
    
    TProduto p;
    while(fread(&p, sizeof(TProduto),1,arq)){
        if(p.id == id){
            if(p.qtd >= num){
                total = total + (p.preco * num);
                p.qtd = p.qtd - num;
                fseek(arq, -sizeof(TProduto), SEEK_CUR);
                fwrite(&p,sizeof(TProduto),1,arq);
                fclose(arq);
            }else{
                printf("\nESTOQUE INSUFICIENTE!\n\n");
                fclose(arq);
            }
            return total;
        }
    }
    fclose(arq);
    printf("Produto não encontrado!\n");
    return 0;
}

void lista_de_vendas(){
    FILE *arq = fopen("arquivos/vendas.bin", "rb");
    long arq_tamanho = arquivo_tamanho("arquivos/vendas.bin");

    if(!arq || arq_tamanho == 0){
        printf("Nenhuma venda realizada!\n");
        return;
    }
    
    TVenda v;
    printf("----------------------------------------------------------------------------------------------------");
    printf("\nLista de Vendas:\n");
    while(fread(&v, sizeof(TVenda),1,arq)){
        printf("ID: %-5d\t Cliente: %-15s\t Preço: %-7.2f\n",v.id, v.cliente, v.preco);
    }
    printf("----------------------------------------------------------------------------------------------------\n");
    fclose(arq);
}