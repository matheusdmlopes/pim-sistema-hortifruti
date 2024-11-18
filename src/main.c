#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "produto.h"

int main()
{
    int opcao;

    do {
        printf("\n--- Sistema Hortifruti ---\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Consultar Produto por ID\n");
        printf("3. Consultar Todos os Produtos\n");
        printf("4. Editar Produto\n");
        printf("5. Excluir Produto\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                cadastrarProdutos();
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
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 6);

    return 0;
}

