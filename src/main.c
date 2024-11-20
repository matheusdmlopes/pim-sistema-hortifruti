#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <produto.h>
#include <fornecedor.h>

int main()
{
    int opcaoPrincipal, opcaoProduto, opcaoFornecedor;

    do {
        printf("\n--- Sistema Hortifruti ---\n");
        printf("Escolha uma opcao:\n");
        printf("1. Cadastro Geral de Produtos\n");
        printf("2. Cadastro Geral de Fornecedores\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcaoPrincipal);
        getchar();

        switch(opcaoPrincipal) {
            case 1:
                do {
                    printf("\n--- Cadastro de Produtos ---\n");
                    printf("1. Cadastrar Produto\n");
                    printf("2. Consultar Produto por ID\n");
                    printf("3. Consultar Todos os Produtos\n");
                    printf("4. Editar Produto\n");
                    printf("5. Excluir Produto\n");
                    printf("6. Voltar ao Menu Principal\n");
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
                            excluirProduto();
                            break;
                        case 6:
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao invalida! Tente novamente.\n");
                    }
                } while(opcaoProduto != 6);
                break;

            case 2:
                do {
                    printf("\n--- Cadastro de Fornecedores ---\n");
                    printf("1. Cadastrar Fornecedor\n");
                    printf("2. Consultar Fornecedor por ID\n");
                    printf("3. Consultar Todos os Fornecedores\n");
                    printf("4. Editar Fornecedor\n");
                    printf("5. Excluir Fornecedor\n");
                    printf("6. Voltar ao Menu Principal\n");
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
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao invalida! Tente novamente.\n");
                    }
                } while(opcaoFornecedor != 6);
                break;

            case 3:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcaoPrincipal != 3);

    return 0;
}
