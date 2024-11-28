#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct {
    int id;
    int quantidade;
    double preco;
    char nome[50];
    int fornecedorId;
} Produto;

void cadastrarProduto();
void consultarProdutoPeloId();
void consultarTodosProdutos();
void editarProduto();
void alterarEstoqueProduto();
void excluirProduto();
int exibirCatalogoProdutos();

#endif // PRODUTO_H
