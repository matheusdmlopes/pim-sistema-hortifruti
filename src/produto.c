#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <produto.h>
#include <interface.h>
#include <cores.h>

void cadastrarProduto()
{
    FILE *arquivo;
    Produto produto;
    int ultimoId = 0;

    arquivo = fopen("data/produtos.bin", "rb");
    if (arquivo != NULL) {
        while (fread(&produto, sizeof(Produto), 1, arquivo)) {
            ultimoId = produto.id;
        }
        fclose(arquivo);
    }

    arquivo = fopen("data/produtos.bin", "ab");
    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    limparTela();

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    exibirTitulo("Cadastro de Novo Produto", 80, ANSI_TEXT_CYAN);

    produto.id = ultimoId + 1;

    printf("ID gerado automaticamente: %d\n", produto.id);

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

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Registro incluído com sucesso!", 80, ANSI_TEXT_GREEN);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    printf("ID: %d\n", produto.id);
    printf("Nome: %s\n", produto.nome);
    printf("Quantidade: %d\n", produto.quantidade);
    printf("Preco: %.2lf\n", produto.preco);

    desenharLinha(80, '-', ANSI_TEXT_GREEN);

    printf("\nPressione Enter para voltar ao menu.");
    getchar();
}

void consultarProdutoPeloId()
{
    FILE *arquivo;
    Produto produto;
    int id_busca, encontrou = 0;

    arquivo = fopen("data/produtos.bin", "rb");
    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    limparTela();

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    exibirTitulo("Consulta de Produto por ID", 80, ANSI_TEXT_CYAN);

    printf("\nDigite o ID para pesquisa: ");
    scanf("%d", &id_busca);
    getchar();

    while(fread(&produto, sizeof(Produto), 1, arquivo)) {
        if(produto.id == id_busca) {
            encontrou = 1;

            desenharLinha(80, '=', ANSI_TEXT_GREEN);
            exibirTitulo("Registro Encontrado", 80, ANSI_TEXT_GREEN);
            desenharLinha(80, '=', ANSI_TEXT_GREEN);

            printf("ID: %d\n", produto.id);
            printf("Nome: %s\n", produto.nome);
            printf("Quantidade: %d\n", produto.quantidade);
            printf("Preco: %.2lf\n", produto.preco);
            desenharLinha(80, '-', ANSI_TEXT_GREEN);
            break;
        }
    }

    fclose(arquivo);

    if(encontrou == 0) {
        desenharLinha(80, '=', ANSI_TEXT_RED);
        exibirTitulo("Nao ha registro com o valor pesquisado.", 80, ANSI_TEXT_RED);
        desenharLinha(80, '=', ANSI_TEXT_RED);
    }

    printf("\nPressione Enter para voltar ao menu.");
    getchar();
}

void consultarTodosProdutos ()
{
    FILE *arquivo;
    Produto produto;
    int encontrou = 0;

    arquivo = fopen("data/produtos.bin", "rb");

    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    limparTela();

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    exibirTitulo("Lista de Produtos Cadastrados", 80, ANSI_TEXT_CYAN);
    desenharLinha(80, '-', ANSI_TEXT_GREEN);

    while(fread(&produto, sizeof(Produto), 1, arquivo)) {
        printf("ID: %d\n", produto.id);
        printf("Nome: %s\n", produto.nome);
        printf("Quantidade: %d\n", produto.quantidade);
        printf("Preco: %.2lf\n", produto.preco);
        desenharLinha(80, '-', ANSI_TEXT_GREEN);
        encontrou = 1;
    }
    fclose(arquivo);

    if (encontrou == 0) {
        exibirTitulo("Nenhum produto cadastrado no momento.", 80, ANSI_TEXT_RED);
    }

    printf("\nPressione Enter para voltar ao menu.");
    getchar();
}

void editarProduto()
{
    FILE *arquivo;
    Produto produto;
    int id_busca, encontrou = 0;

    arquivo = fopen("data/produtos.bin", "rb+");
    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    limparTela();

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    exibirTitulo("Editar Produto", 80, ANSI_TEXT_CYAN);

    printf("\nDigite o ID para pesquisa: ");
    scanf("%d", &id_busca);
    getchar();
    while(fread(&produto, sizeof(Produto), 1, arquivo)) {
        if(produto.id == id_busca) {
            encontrou = 1;

            desenharLinha(80, '=', ANSI_TEXT_GREEN);
            exibirTitulo("Registro Encontrado", 80, ANSI_TEXT_GREEN);
            desenharLinha(80, '=', ANSI_TEXT_GREEN);

            printf("ID: %d\n", produto.id);
            printf("Nome: %s\n", produto.nome);
            printf("Quantidade: %d\n", produto.quantidade);
            printf("Preco: %.2lf\n", produto.preco);
            desenharLinha(80, '-', ANSI_TEXT_GREEN);

            printf("\nDigite o novo nome: ");
            fgets(produto.nome, sizeof(produto.nome), stdin);
            produto.nome[strcspn(produto.nome, "\n")] = '\0';

            printf("Digite a nova quantidade: ");
            scanf("%d", &produto.quantidade);

            printf("Digite o novo preco: ");
            scanf("%lf", &produto.preco);
            getchar();

            fseek(arquivo, -(long)sizeof(Produto), SEEK_CUR);
            fwrite(&produto, sizeof(Produto), 1, arquivo);

            desenharLinha(80, '=', ANSI_TEXT_GREEN);
            exibirTitulo("Registro alterado com sucesso!", 80, ANSI_TEXT_GREEN);
            desenharLinha(80, '=', ANSI_TEXT_GREEN);

            printf("ID: %d\n", produto.id);
            printf("Nome: %s\n", produto.nome);
            printf("Quantidade: %d\n", produto.quantidade);
            printf("Preco: %.2lf\n", produto.preco);
            desenharLinha(80, '-', ANSI_TEXT_GREEN);
            break;
        }
    }
    fclose(arquivo);

    if(encontrou == 0) {
        desenharLinha(80, '=', ANSI_TEXT_RED);
        exibirTitulo("Nao ha registro com o valor pesquisado.", 80, ANSI_TEXT_RED);
        desenharLinha(80, '=', ANSI_TEXT_RED);
    }

    printf("\nPressione Enter para voltar ao menu.");
    getchar();
}

void alterarEstoqueProduto()
{
    FILE *arquivo;
    Produto produto;
    int id_busca, encontrou = 0;

    arquivo = fopen("data/produtos.bin", "rb+");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    limparTela();

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    exibirTitulo("Alterar Estoque de Produto", 80, ANSI_TEXT_CYAN);

    printf("\nDigite o ID do produto para alterar o estoque: ");
    scanf("%d", &id_busca);
    getchar();

    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        if (produto.id == id_busca) {
            encontrou = 1;

            desenharLinha(80, '=', ANSI_TEXT_GREEN);
            exibirTitulo("Registro Encontrado", 80, ANSI_TEXT_GREEN);
            desenharLinha(80, '=', ANSI_TEXT_GREEN);

            printf("ID: %d\n", produto.id);
            printf("Nome: %s\n", produto.nome);
            printf("Quantidade Atual: %d\n", produto.quantidade);
            printf("Preco: %.2lf\n", produto.preco);

            desenharLinha(80, '-', ANSI_TEXT_GREEN);

            printf("\nDigite a nova quantidade em estoque: ");
            scanf("%d", &produto.quantidade);
            getchar();

            fseek(arquivo, -(long)sizeof(Produto), SEEK_CUR);
            fwrite(&produto, sizeof(Produto), 1, arquivo);

            desenharLinha(80, '=', ANSI_TEXT_GREEN);
            exibirTitulo("Estoque alterado com sucesso!", 80, ANSI_TEXT_GREEN);
            desenharLinha(80, '=', ANSI_TEXT_GREEN);

            printf("ID: %d\n", produto.id);
            printf("Nome: %s\n", produto.nome);
            printf("Nova Quantidade: %d\n", produto.quantidade);
            desenharLinha(80, '-', ANSI_TEXT_GREEN);

            break;
        }
    }
    fclose(arquivo);

    if (encontrou == 0) {
        desenharLinha(80, '=', ANSI_TEXT_RED);
        exibirTitulo("Nao ha registro com o valor pesquisado.", 80, ANSI_TEXT_RED);
        desenharLinha(80, '=', ANSI_TEXT_RED);
    }

    printf("\nPressione Enter para voltar ao menu.");
    getchar();
}


void excluirProduto()
{
    FILE *arquivo, *novoArquivo;
    Produto produto;
    int id_busca, op, encontrou = 0;

    arquivo = fopen("data/produtos.bin", "rb");
    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    novoArquivo = fopen("data/temp.bin", "wb");
    if(novoArquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        fclose(arquivo);
        exit(1);
    }

    limparTela();

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    exibirTitulo("Excluir Produto", 80, ANSI_TEXT_CYAN);

    printf("\nDigite o ID do registro para exclusao: ");
    scanf("%d", &id_busca);
    getchar();

    while(fread(&produto, sizeof(Produto), 1, arquivo)) {
        if(produto.id == id_busca) {
            encontrou = 1;

            desenharLinha(80, '=', ANSI_TEXT_GREEN);
            exibirTitulo("Registro Encontrado", 80, ANSI_TEXT_GREEN);
            desenharLinha(80, '=', ANSI_TEXT_GREEN);

            printf("ID: %d\n", produto.id);
            printf("Nome: %s\n", produto.nome);
            printf("Quantidade: %d\n", produto.quantidade);
            printf("Preco: %.2lf\n", produto.preco);

            desenharLinha(80, '-', ANSI_TEXT_GREEN);

            printf("Deseja realmente excluir este registro? (1- Sim | 2- Nao): ");
            scanf("%d", &op);
            printf("\n");
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
        desenharLinha(80, '=', ANSI_TEXT_RED);
        exibirTitulo("Nao ha registro com o valor pesquisado.", 80, ANSI_TEXT_RED);
        desenharLinha(80, '=', ANSI_TEXT_RED);
        remove("data/temp.bin");
    } else if(op == 1 && encontrou == 1) {
        if(remove("data/produtos.bin") != 0) {
            perror("Erro ao remover o arquivo original");
            exit(1);
        }

        if(rename("data/temp.bin", "data/produtos.bin") != 0) {
            perror("Erro ao renomear o arquivo");
            exit(1);
        }

        exibirTitulo("Registro excluido com sucesso!", 80, ANSI_TEXT_GREEN);

    } else {
        remove("data/temp.bin");
    }

    printf("\nPressione Enter para voltar ao menu.");
    getchar();
}

int exibirCatalogoProdutos() {
    FILE *arquivo;
    Produto produto;

    arquivo = fopen("data/produtos.bin", "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de produtos");
        exit(1);
    }

    desenharLinha(80, '-', ANSI_TEXT_GREEN);
    exibirTitulo("Catálogo", 80, ANSI_TEXT_CYAN);
    desenharLinha(80, '-', ANSI_TEXT_GREEN);

    int encontrouProdutos = 0;

    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        encontrouProdutos = 1;
        printf("ID: %d\n", produto.id);
        printf("Nome: %s\n", produto.nome);
        printf("Quantidade em Estoque: %d\n", produto.quantidade);
        printf("Preço Unitário: %.2lf\n", produto.preco);
        desenharLinha(80, '-', ANSI_TEXT_GREEN);
    }

    fclose(arquivo);

    if (!encontrouProdutos) {
        exibirTitulo("Nenhum produto disponível no momento.", 80, ANSI_TEXT_RED);
    }

    return encontrouProdutos;
}
