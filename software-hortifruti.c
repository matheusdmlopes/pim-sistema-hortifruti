#include <stdio.h>
#include <string.h>

typedef struct
{
    int id;
    int quantidade;
    double preco;
    char nome[50];
} TProduto;

void cadastrarProdutos()
{
    TProduto produto, produtos[5];
    int i;

    for (i = 0; i < 5; i++)
    {
        produtos[i].id = i + 1;

        printf("Digite o nome do produto: ");
        fgets(produtos[i].nome, sizeof(produtos[i].nome), stdin);

        printf("Digite a quantidade do produto: ");
        scanf("%d", &produtos[i].quantidade);

        printf("Digite o preco do produto: ");
        scanf("%lf", &produtos[i].preco);

        getchar();

        printf("Seu produto foi cadastrado, informacoes abaixo: \n");
        printf("ID: %d\n", produtos[i].id);
        printf("Quantidade: %d\n", produtos[i].quantidade);
        printf("Preço: %.2lfR$\n", produtos[i].preco);
        printf("Nome: %s\n", produtos[i].nome);
    }
    printf("Produtos cadastrados:\n");
    for (i = 0; i < 5; i++)
    {
        printf("ID: %d\n", produtos[i].id);
        printf("Nome: %s", produtos[i].nome);
        printf("Quantidade: %d\n", produtos[i].quantidade);
        printf("Preço: %.2lfR$\n", produtos[i].preco);
    }
}

int main()
{
    cadastrarProdutos();
    return 0;
}
