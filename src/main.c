#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <produto.h>
#include <fornecedor.h>
#include <autenticacao.h>
#include <cores.h>
#include <interface.h>

int main()
{
    int opcaoPrincipal, opcaoProduto, opcaoFornecedor, opcaoFluxoCaixa;

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Bem-vindo ao Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);


    if(!autenticarUsuario()) {
        return 0;
    }

    do {
        char *opcoesPrincipal[] = {
            "Cadastro Geral de Produtos",
            "Cadastro Geral de Fornecedores",
            "Fluxo de Caixa",
            "Sair"
        };
        int numOpcoesPrincipal = 4;

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

        switch(opcaoPrincipal) {
        case 1:
            do {
                char *opcoesProduto[] = {
                    "Cadastrar Produto",
                    "Consultar Produto por ID",
                    "Consultar Todos os Produtos",
                    "Editar Produto",
                    "Alterar Estoque de Produto",
                    "Excluir Produto",
                    "Voltar ao Menu Principal"
                };
                int numOpcoesProduto = 7;

                limparTela();

                desenharLinha(80, '=', ANSI_TEXT_GREEN);
                exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
                desenharLinha(80, '=', ANSI_TEXT_GREEN);

                exibirTitulo("Cadastro Geral de Produtos", 80, ANSI_TEXT_CYAN);
                desenharLinha(80, '-', ANSI_TEXT_GREEN);

                exibirMenu(opcoesProduto, numOpcoesProduto, ANSI_RESET);
                printf("Escolha uma opcao: ");
                scanf("%d", &opcaoProduto);
                getchar();

                switch(opcaoProduto) {
                case 1:
                    cadastrarProduto();
                    break;
                case 2:
                    consultarProdutoPeloId();
                    break;
                case 3:
                    consultarTodosProdutos();
                    break;
                case 4:
                    editarProduto();
                    break;
                case 5:
                    alterarEstoqueProduto();
                    break;
                case 6:
                    excluirProduto();
                    break;
                case 7:
                    limparTela();
                    break;
                default:
                    printf("Opcao invalida! Tente novamente.\n");
                }
            } while(opcaoProduto != 7);
            break;

        case 2:
            do {
                char *opcoesFornecedor[] = {
                    "Cadastrar Fornecedor",
                    "Consultar Fornecedor por ID",
                    "Consultar Todos os Fornecedores",
                    "Editar Fornecedor",
                    "Excluir Fornecedor",
                    "Voltar ao Menu Principal"
                };
                int numOpcoesFornecedor = 6;

                limparTela();

                desenharLinha(80, '=', ANSI_TEXT_GREEN);
                exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
                desenharLinha(80, '=', ANSI_TEXT_GREEN);

                exibirTitulo("Cadastro Geral de Fornecedores", 80, ANSI_TEXT_CYAN);
                desenharLinha(80, '-', ANSI_TEXT_GREEN);

                exibirMenu(opcoesFornecedor, numOpcoesFornecedor, ANSI_RESET);
                printf("Escolha uma opcao: ");
                scanf("%d", &opcaoFornecedor);
                getchar();

                switch(opcaoFornecedor) {
                case 1:
                    cadastrarFornecedor();
                    break;
                case 2:
                    consultarFornecedorPeloId();
                    break;
                case 3:
                    consultarTodosFornecedores();
                    break;
                case 4:
                    editarFornecedor();
                    break;
                case 5:
                    excluirFornecedor();
                    break;
                case 6:
                    limparTela();
                    break;
                default:
                    printf("Opcao invalida! Tente novamente.\n");
                }
            } while(opcaoFornecedor != 6);
            break;
        case 3:
            do {
                char *opcoesFluxoCaixa[] = {
                    "Registrar Entrada",
                    "Registrar Saída",
                    "Venda de Produto",
                    "Remover Transação",
                    "Exibir Relatório do Caixa",
                    "Voltar ao Menu Principal"
                };
                int numOpcoesFluxoCaixa = 6;

                limparTela();

                desenharLinha(80, '=', ANSI_TEXT_GREEN);
                exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
                desenharLinha(80, '=', ANSI_TEXT_GREEN);

                exibirTitulo("Fluxo de Caixa", 80, ANSI_TEXT_CYAN);
                desenharLinha(80, '-', ANSI_TEXT_GREEN);

                exibirMenu(opcoesFluxoCaixa, numOpcoesFluxoCaixa, ANSI_RESET);
                printf("Escolha uma opcao: ");
                scanf("%d", &opcaoFluxoCaixa);
                getchar();

                switch(opcaoFluxoCaixa) {
                case 1:
                    registrarTransacaoMenu("Entrada");
                    break;
                case 2:
                    registrarTransacaoMenu("Saida");
                    break;
                case 3:
                    simularVendaProduto();
                    break;
                case 4:
                    removerTransacao();
                    break;
                case 5:
                    exibirFluxoCaixa();
                    break;
                case 6:
                    limparTela();
                    break;
                default:
                    printf("Opcao invalida! Tente novamente.\n");
                }

            } while(opcaoFluxoCaixa != 6);
            break;

        case 4:
            printf("Encerrando o sistema... Até mais!\n");
            break;

        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcaoPrincipal != 4);

    return 0;
}
