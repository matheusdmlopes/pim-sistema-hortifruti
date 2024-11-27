#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <caixa.h>
#include <interface.h>
#include <cores.h>
#include <produto.h>

void registrarTransacaoMenu(const char* tipo)
{
    double valor;
    char descricao[100];

    limparTela();

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    exibirTitulo("Registrar Transação", 80, ANSI_TEXT_CYAN);
    desenharLinha(80, '-', ANSI_TEXT_GREEN);

    printf("Digite o valor da %s: ", tipo);
    scanf("%lf", &valor);
    getchar();
    printf("Digite a descrição da %s: ", tipo);
    fgets(descricao, sizeof(descricao), stdin);
    descricao[strcspn(descricao, "\n")] = '\0';

    if (strcmp(tipo, "Entrada") == 0) {
        registrarEntrada(valor, descricao);
    } else {
        registrarSaida(valor, descricao);
    }

    printf("\n");
    exibirTitulo("Transacao registrada com sucesso!", 80, ANSI_TEXT_GREEN);
    printf("\nPressione Enter para continuar.");
    getchar();
}

void registrarEntrada(double valor, const char *descricao)
{
    registrarTransacao("Entrada", valor, 0, descricao);
}

void registrarSaida(double valor, const char *descricao)
{
    registrarTransacao("Saída", valor, 0, descricao);
}

void registrarTransacao(const char *tipo, double valor, int quantidade, const char *descricao)
{
    FILE *arquivo;
    Transacao transacao;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    arquivo = fopen("data/caixa.bin", "ab");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de fluxo de caixa");
        exit(1);
    }

    fseek(arquivo, 0, SEEK_END);
    long fileSize = ftell(arquivo);
    int novoId = fileSize / sizeof(Transacao) + 1;

    transacao.id = novoId;
    strcpy(transacao.tipo, tipo);
    transacao.valor = valor;
    transacao.quantidade = quantidade;
    strcpy(transacao.descricao, descricao);
    snprintf(transacao.data, sizeof(transacao.data), "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    fwrite(&transacao, sizeof(Transacao), 1, arquivo);

    fclose(arquivo);
}


void exibirFluxoCaixa()
{
    FILE *arquivo;
    Transacao transacao;
    double saldo = 0.0;
    int encontrou = 0;

    arquivo = fopen("data/caixa.bin", "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de fluxo de caixa");
        exit(1);
    }

    limparTela();

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    exibirTitulo("Relatório do Caixa", 80, ANSI_TEXT_CYAN);
    desenharLinha(80, '-', ANSI_TEXT_GREEN);

    while (fread(&transacao, sizeof(Transacao), 1, arquivo)) {

        printf("ID: %d\n", transacao.id);
        printf("Data: %s\n", transacao.data);
        printf("Tipo: %s\n", transacao.tipo);
        printf("Descrição: %s\n", transacao.descricao);

        if (transacao.quantidade > 0) {
            double valorUnitario = transacao.valor / transacao.quantidade;
            printf("Valor Unitário: %.2lf\n", valorUnitario);
            printf("Quantidade: %d\n", transacao.quantidade);
        } else {
            printf("Valor: %.2lf\n", transacao.valor);
        }

        desenharLinha(80, '-', ANSI_TEXT_GREEN);

        if (strcmp(transacao.tipo, "Entrada") == 0) {
            saldo += transacao.valor;
        } else if (strcmp(transacao.tipo, "Saída") == 0) {
            saldo -= transacao.valor;
        }
        encontrou = 1;
    }
    fclose(arquivo);

    if (encontrou == 0) {
        exibirTitulo("Nenhuma transação registrada no momento.", 80, ANSI_TEXT_RED);
    }

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    printf("Saldo Atual: R$%.2lf\n", saldo);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    printf("\nPressione Enter para voltar ao menu.");
    getchar();
}

void simularVendaProduto()
{
    FILE *arquivo;
    Produto produto;
    int id, quantidadeVendida, encontrou = 0;

    arquivo = fopen("data/produtos.bin", "rb+");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de produtos");
        exit(1);
    }

    limparTela();

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Venda de Produto", 80, ANSI_TEXT_CYAN);

    if (!exibirCatalogoProdutos()) {
        printf("\nPressione Enter para voltar ao menu.");
        getchar();
        return;
    }

    printf("Digite o ID do produto a ser vendido: ");
    scanf("%d", &id);
    getchar();
    printf("Digite a quantidade a ser vendida: ");
    scanf("%d", &quantidadeVendida);
    getchar();

    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        if (produto.id == id) {
            encontrou = 1;
            if (produto.quantidade < quantidadeVendida) {
                desenharLinha(80, '=', ANSI_TEXT_RED);
                printf("Quantidade insuficiente em estoque para a venda.\n");
                desenharLinha(80, '=', ANSI_TEXT_RED);
                fclose(arquivo);
                printf("\nPressione Enter para voltar ao menu.");
                getchar();
                return;
            }

            produto.quantidade -= quantidadeVendida;

            fseek(arquivo, -(long)sizeof(Produto), SEEK_CUR);
            fwrite(&produto, sizeof(Produto), 1, arquivo);

            double valorTotal = produto.preco * quantidadeVendida;
            char descricao[100];
            snprintf(descricao, sizeof(descricao), "Venda do produto '%s' (ID: %d)", produto.nome, produto.id);
            registrarTransacao("Entrada", valorTotal, quantidadeVendida, descricao);

            desenharLinha(80, '=', ANSI_TEXT_GREEN);
            exibirTitulo("Venda realizada com sucesso!", 80, ANSI_TEXT_GREEN);
            desenharLinha(80, '=', ANSI_TEXT_GREEN);
            break;
        }
    }

    if (encontrou == 0) {
        desenharLinha(80, '=', ANSI_TEXT_RED);
        exibirTitulo("Produto não encontrado", 80, ANSI_TEXT_RED);
        desenharLinha(80, '=', ANSI_TEXT_RED);
    }

    fclose(arquivo);
    printf("\nPressione Enter para voltar ao menu.");
    getchar();
}

void removerTransacao()
{
    FILE *arquivo, *tempArquivo;
    Transacao transacao;
    int id, encontrou = 0;

    arquivo = fopen("data/caixa.bin", "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de fluxo de caixa");
        exit(1);
    }

    tempArquivo = fopen("data/temp_caixa.bin", "wb");
    if (tempArquivo == NULL) {
        perror("Erro ao criar arquivo temporário");
        fclose(arquivo);
        exit(1);
    }

    limparTela();

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    exibirTitulo("Remover Transação do Fluxo de Caixa", 80, ANSI_TEXT_CYAN);
    desenharLinha(80, '-', ANSI_TEXT_GREEN);

    printf("Digite o ID da transação que deseja remover: ");
    scanf("%d", &id);
    getchar();

    while (fread(&transacao, sizeof(Transacao), 1, arquivo)) {
        if (transacao.id == id) {
            encontrou = 1;
        } else {
            fwrite(&transacao, sizeof(Transacao), 1, tempArquivo);
        }
    }

    fclose(arquivo);
    fclose(tempArquivo);

    if (encontrou) {
        if (remove("data/caixa.bin") != 0) {
            perror("Erro ao remover o arquivo original");
            exit(1);
        }

        if (rename("data/temp_caixa.bin", "data/caixa.bin") != 0) {
            perror("Erro ao renomear o arquivo temporário");
            exit(1);
        }

        desenharLinha(80, '=', ANSI_TEXT_GREEN);
        exibirTitulo("Transação removida com sucesso!", 80, ANSI_TEXT_GREEN);
        desenharLinha(80, '=', ANSI_TEXT_GREEN);
    } else {
        remove("data/temp_caixa.bin");
        desenharLinha(80, '=', ANSI_TEXT_RED);
        exibirTitulo("Transação não encontrada!", 80, ANSI_TEXT_RED);
        desenharLinha(80, '=', ANSI_TEXT_RED);
    }

    printf("\nPressione Enter para voltar ao menu.");
    getchar();
}
