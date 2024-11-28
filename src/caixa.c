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
    registrarTransacao("Entrada", valor, 0, descricao, "");
}

void registrarSaida(double valor, const char *descricao)
{
    registrarTransacao("Saída", valor, 0, descricao, "");
}

void registrarTransacao(const char *tipo, double valor, int quantidade, const char *descricao, const char *formaPagamento)
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
    strcpy(transacao.formaPagamento, formaPagamento);
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
    int idMaisVendido, quantidadeMaisVendida;
    char nomeMaisVendido[100];

    obterProdutoMaisVendido(&idMaisVendido, nomeMaisVendido, &quantidadeMaisVendida);

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

    if (quantidadeMaisVendida > 0) {
        printf("Produto mais vendido: %s (ID: %d), Quantidade Vendida: %d\n", nomeMaisVendido, idMaisVendido, quantidadeMaisVendida);
        desenharLinha(80, '-', ANSI_TEXT_GREEN);
    }

    while (fread(&transacao, sizeof(Transacao), 1, arquivo)) {

        printf("ID: %d\n", transacao.id);
        printf("Data: %s\n", transacao.data);
        printf("Tipo: %s\n", transacao.tipo);
        printf("Descrição: %s\n", transacao.descricao);

        if (transacao.quantidade > 0) {
            double valorUnitario = transacao.valor / transacao.quantidade;
            printf("Valor Unitário: R$%.2lf\n", valorUnitario);
            printf("Quantidade: %d\n", transacao.quantidade);
            printf("Valor total: R$%.2lf\n", transacao.valor);
            if (strlen(transacao.formaPagamento) > 0) {
                printf("Forma de Pagamento: %s\n", transacao.formaPagamento);
            }
        } else {
            printf("Valor: R$%.2lf\n", transacao.valor);
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

    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        if (produto.id == id) {
            encontrou = 1;

            desenharLinha(80, '=', ANSI_TEXT_GREEN);
            exibirTitulo("Produto Selecionado", 80, ANSI_TEXT_GREEN);
            desenharLinha(80, '=', ANSI_TEXT_GREEN);

            printf("ID: %d\n", produto.id);
            printf("Nome: %s\n", produto.nome);
            printf("Quantidade: %d kg\n", produto.quantidade);
            printf("Preco: R$%.2lf\n", produto.preco);
            desenharLinha(80, '-', ANSI_TEXT_GREEN);

            printf("Digite a quantidade a ser vendida: ");
            scanf("%d", &quantidadeVendida);
            getchar();
            if (produto.quantidade < quantidadeVendida) {
                desenharLinha(80, '=', ANSI_TEXT_RED);
                printf("Quantidade insuficiente em estoque para a venda.\n");
                desenharLinha(80, '=', ANSI_TEXT_RED);
                fclose(arquivo);
                printf("\nPressione Enter para voltar ao menu.");
                getchar();
                return;
            }

            int opcaoPagamento;
            char formaPagamento[20];

            do {
                printf("\nEscolha a forma de pagamento:\n");
                printf("1. Dinheiro\n");
                printf("2. Cartão de Crédito\n");
                printf("3. Cartão de Débito\n");
                printf("4. PIX\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcaoPagamento);
                getchar();

                switch (opcaoPagamento) {
                case 1:
                    strcpy(formaPagamento, "Dinheiro");
                    break;
                case 2:
                    strcpy(formaPagamento, "Cartão de Crédito");
                    break;
                case 3:
                    strcpy(formaPagamento, "Cartão de Débito");
                    break;
                case 4:
                    strcpy(formaPagamento, "PIX");
                    break;
                default:
                    printf("Opção inválida! Tente novamente.\n");
                }
            } while (opcaoPagamento < 1 || opcaoPagamento > 4);


            produto.quantidade -= quantidadeVendida;

            fseek(arquivo, -(long)sizeof(Produto), SEEK_CUR);
            fwrite(&produto, sizeof(Produto), 1, arquivo);

            double valorTotal = produto.preco * quantidadeVendida;
            char descricao[100];
            snprintf(descricao, sizeof(descricao), "Venda do produto '%s' (ID: %d)", produto.nome, produto.id);
            registrarTransacao("Entrada", valorTotal, quantidadeVendida, descricao, formaPagamento);

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

    limparTela();

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    exibirTitulo("Remover Transação do Fluxo de Caixa", 80, ANSI_TEXT_CYAN);
    desenharLinha(80, '-', ANSI_TEXT_GREEN);

    int encontrouTransacao = 0;
    while (fread(&transacao, sizeof(Transacao), 1, arquivo)) {
        encontrouTransacao = 1;
        printf("ID: %d\n", transacao.id);
        printf("Data: %s\n", transacao.data);
        printf("Tipo: %s\n", transacao.tipo);
        printf("Descrição: %s\n", transacao.descricao);

        if (transacao.quantidade > 0) {
            double valorUnitario = transacao.valor / transacao.quantidade;
            printf("Valor Unitário: R$%.2lf\n", valorUnitario);
            printf("Quantidade: %d\n", transacao.quantidade);
            printf("Valor total: R$%.2lf\n", transacao.valor);
            if (strlen(transacao.formaPagamento) > 0) {
                printf("Forma de Pagamento: %s\n", transacao.formaPagamento);
            }
        } else {
            printf("Valor: R$%.2lf\n", transacao.valor);
        }

        desenharLinha(80, '-', ANSI_TEXT_GREEN);
    }
    fclose(arquivo);

    if (!encontrouTransacao) {
        exibirTitulo("Nenhuma transação registrada no momento.", 80, ANSI_TEXT_RED);
        printf("\nPressione Enter para voltar ao menu.");
        getchar();
        return;
    }

    printf("Digite o ID da transação que deseja remover: ");
    scanf("%d", &id);
    getchar();

    arquivo = fopen("data/caixa.bin", "rb");
    tempArquivo = fopen("data/temp_caixa.bin", "wb");
    if (arquivo == NULL || tempArquivo == NULL) {
        perror("Erro ao manipular arquivos");
        exit(1);
    }

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

void obterProdutoMaisVendido(int *idMaisVendido, char *nomeMaisVendido, int *quantidadeMaisVendida)
{
    FILE *arquivo;
    Transacao transacao;
    int quantidades[1000] = {0};
    char nomes[1000][100] = {""};

    arquivo = fopen("data/caixa.bin", "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de fluxo de caixa");
        exit(1);
    }

    while (fread(&transacao, sizeof(Transacao), 1, arquivo)) {
        if (strcmp(transacao.tipo, "Entrada") == 0 && strstr(transacao.descricao, "Venda do produto") != NULL) {
            int idProduto;
            char nomeProduto[100];

            sscanf(transacao.descricao, "Venda do produto '%99[^']' (ID: %d)", nomeProduto, &idProduto);

            quantidades[idProduto] += transacao.quantidade;

            strcpy(nomes[idProduto], nomeProduto);
        }
    }

    fclose(arquivo);

    *quantidadeMaisVendida = 0;
    for (int i = 0; i < 1000; i++) {
        if (quantidades[i] > *quantidadeMaisVendida) {
            *quantidadeMaisVendida = quantidades[i];
            *idMaisVendido = i;
            strcpy(nomeMaisVendido, nomes[i]);
        }
    }
}
