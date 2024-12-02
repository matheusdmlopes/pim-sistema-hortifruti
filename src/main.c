#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <produto.h>
#include <fornecedor.h>
#include <autenticacao.h>
#include <cores.h>
#include <interface.h>

void resetarDadosSistema() {
    FILE *arquivo;

    const char* arquivos[] = {"data/fornecedores.bin", "data/produtos.bin", "data/caixa.bin"};
    for (int i = 0; i < 3; i++) {
        arquivo = fopen(arquivos[i], "wb");
        if (arquivo == NULL) {
            perror("Erro ao limpar o arquivo");
        } else {
            fclose(arquivo);
        }
    }

    printf("\n");
    exibirTitulo("Todos os dados foram resetados com sucesso!", 80, ANSI_TEXT_GREEN);
    printf("\nPressione Enter para voltar ao menu.");
    getchar();
}

int main() {
    int opcaoPrincipal;

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Bem-vindo ao Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    if (!autenticarUsuario()) {
        return 0;
    }

    do {
        char *opcoesPrincipal[] = {
            "Cadastro Geral de Produtos",
            "Cadastro Geral de Fornecedores",
            "Fluxo de Caixa",
            "Resetar Dados do Sistema",
            "Sair"
        };
        int numOpcoesPrincipal = 5;

        limparTela();
        desenharLinha(80, '=', ANSI_TEXT_GREEN);
        exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
        desenharLinha(80, '=', ANSI_TEXT_GREEN);
        exibirTitulo("Menu Principal", 80, ANSI_TEXT_CYAN);
        desenharLinha(80, '-', ANSI_TEXT_GREEN);
        exibirMenu(opcoesPrincipal, numOpcoesPrincipal, ANSI_RESET);

        printf("Escolha uma opcao: ");
        scanf("%d", &opcaoPrincipal);
        getchar();

        switch (opcaoPrincipal) {
            case 1: menuProdutos(); break;
            case 2: menuFornecedores(); break;
            case 3: menuFluxoCaixa(); break;
            case 4: resetarDadosSistema(); break;
            case 5: exibirTitulo("Encerrando o sistema... Até mais!", 80, ANSI_TEXT_YELLOW); break;
            default: printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcaoPrincipal != 5);

    return 0;
}
