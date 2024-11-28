#ifndef FORNECEDOR_H
#define FORNECEDOR_H

typedef struct {
    int id;
    char cnpj[19];
    char nome[50];
    char categoria[31];
    char contato[60];
} Fornecedor;

void cadastrarFornecedor();
void consultarFornecedorPeloId();
void consultarTodosFornecedores();
void editarFornecedor();
void excluirFornecedor();
int listarFornecedores();

#endif // FORNECEDOR_H
