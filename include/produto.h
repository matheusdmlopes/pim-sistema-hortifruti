#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct {
    int id;
    int quantidade;
    double preco;
    char nome[50];
} Produto;

void cadastrarProdutos();
void consultarProdutoPeloId();
void consultarTodosProdutos();
void editarProduto();
void excluirProduto();

#endif // PRODUTO_H
