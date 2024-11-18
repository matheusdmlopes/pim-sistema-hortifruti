#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <produto.h>

void cadastrarProdutos()
{
    FILE *arquivo;
    Produto produto;
    int i;

    arquivo = fopen("dados.bin", "ab");
    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    printf("\n--- Cadastro de Novo Produto ---\n");

    printf("Digite o ID: ");
    scanf("%d", &produto.id);
    getchar();

    printf("Digite o nome do produto: ");
    fgets(produto.nome, sizeof(produto.nome), stdin);
    produto.nome[strcspn(produto.nome, "\n")] = '\0';

    printf("Digite a quantidade do produto: ");
    scanf("%d", &produto.quantidade);

    printf("Digite o preco do produto: ");
    scanf("%lf", &produto.preco);

    getchar();

    fwrite(&produto, sizeof(Produto), 1, arquivo);

    fclose(arquivo);

    printf("\n--- Registro incluído com sucesso ---\n");
    printf("ID: %d\n", produto.id);
    printf("Nome: %s\n", produto.nome);
    printf("Quantidade: %d\n", produto.quantidade);
    printf("Preco: %.2lf\n", produto.preco);
    printf("-----------------------------------\n");
}

void consultarProdutoPeloId()
{
    FILE *arquivo;
    Produto produto;
    int id_busca, encontrou = 0;

    arquivo = fopen("dados.bin", "rb");
    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    printf("\nDigite o ID para pesquisa: ");
    scanf("%d", &id_busca);

    while(fread(&produto, sizeof(Produto), 1, arquivo)) {
        if(produto.id == id_busca) {
            encontrou = 1;
            printf("\n--- Registro encontrado ---\n");
            printf("ID: %d\n", produto.id);
            printf("Nome: %s\n", produto.nome);
            printf("Quantidade: %d\n", produto.quantidade);
            printf("Preco: %.2lf\n", produto.preco);
            printf("---------------------------\n");
            break;
        }
    }

    fclose(arquivo);

    if(encontrou == 0) {
        printf("\nNao ha registro com o valor pesquisado.\n");
    }
}

void consultarTodosProdutos ()
{
    FILE *arquivo;
    Produto produto;

    arquivo = fopen("dados.bin", "rb");

    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    printf("\n--- Lista de Produtos Cadastrados ---\n");
    while(fread(&produto, sizeof(Produto), 1, arquivo)) {
        printf("ID: %d\n", produto.id);
        printf("Nome: %s\n", produto.nome);
        printf("Quantidade: %d\n", produto.quantidade);
        printf("Preco: %.2lf\n", produto.preco);
        printf("-----------------------------------\n");
    }
    fclose(arquivo);
}

void editarProduto()
{
    FILE *arquivo;
    Produto produto;
    int id_busca, encontrou = 0;

    arquivo = fopen("dados.bin", "rb+");
    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    printf("\nDigite o ID para pesquisa: ");
    scanf("%d", &id_busca);
    getchar();
    while(fread(&produto, sizeof(Produto), 1, arquivo)) {
        if(produto.id == id_busca) {
            encontrou = 1;

            printf("\n--- Registro Encontrado ---\n");
            printf("ID: %d\n", produto.id);
            printf("Nome: %s\n", produto.nome);
            printf("Quantidade: %d\n", produto.quantidade);
            printf("Preco: %.2lf\n", produto.preco);
            printf("---------------------------\n");

            printf("\nDigite o novo nome: ");
            fgets(produto.nome, sizeof(produto.nome), stdin);
            produto.nome[strcspn(produto.nome, "\n")] = '\0';

            printf("Digite a nova quantidade: ");
            scanf("%d", &produto.quantidade);

            printf("Digite o novo preco: ");
            scanf("%lf", &produto.preco);

            fseek(arquivo, -(long)sizeof(Produto), SEEK_CUR);
            fwrite(&produto, sizeof(Produto), 1, arquivo);

            printf("\n--- Registro alterado com sucesso ---\n");
            printf("ID: %d\n", produto.id);
            printf("Nome: %s\n", produto.nome);
            printf("Quantidade: %d\n", produto.quantidade);
            printf("Preco: %.2lf\n", produto.preco);
            printf("-------------------------------------\n");
            break;
        }
    }
    fclose(arquivo);

    if(encontrou == 0) {
        printf("Nao ha registro com o valor pesquisado.\n");
    }

}

void excluirProduto()
{
    FILE *arquivo, *novoArquivo;
    Produto produto;
    int id_busca, op, encontrou = 0, exclui = 0;

    arquivo = fopen("dados.bin", "rb");
    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    novoArquivo = fopen("temp.bin", "wb");
    if(novoArquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        fclose(arquivo);
        exit(1);
    }

    printf("\nDigite o ID do registro para exclusao: ");
    scanf("%d", &id_busca);
    getchar();

    while(fread(&produto, sizeof(Produto), 1, arquivo)) {
        if(produto.id == id_busca) {
            encontrou = 1;
            printf("\n--- Registro Encontrado ---\n");
            printf("ID: %d\n", produto.id);
            printf("Nome: %s\n", produto.nome);
            printf("Quantidade: %d\n", produto.quantidade);
            printf("Preco: %.2lf\n", produto.preco);
            printf("---------------------------\n");

            printf("Deseja realmente excluir este registro? (1- Sim | 2- Nao): ");
            scanf("%d", &op);
            getchar();

            if(op != 1) {
                fwrite(&produto, sizeof(Produto), 1, novoArquivo);
            }
        } else {
            fwrite(&produto, sizeof(Produto), 1, novoArquivo);
        }
    }

    fclose(arquivo);
    fclose(novoArquivo);

    if(encontrou == 0) {
        printf("\nNao ha registro com o valor pesquisado.\n");
        remove("temp.bin");
    } else if(op == 1 && encontrou == 1) {
        if(remove("dados.bin") != 0) {
            perror("Erro ao remover o arquivo original");
            exit(1);
        }

        if(rename("temp.bin", "dados.bin") != 0) {
            perror("Erro ao renomear o arquivo");
            exit(1);
        }

        printf("\n--- Registro excluido com sucesso ---\n");
    } else {
        remove("temp.bin");
    }
}
