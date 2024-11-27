#ifndef CAIXA_H
#define CAIXA_H

typedef struct {
    int id;
    char tipo[10];
    double valor;
    int quantidade;
    char descricao[100];
    char data[20];
} Transacao;

void registrarTransacaoMenu(const char* tipo);
void registrarTransacao(const char *tipo, double valor, int quantidade, const char *descricao);
void registrarEntrada(double valor, const char *descricao);
void registrarSaida(double valor, const char *descricao);
void exibirFluxoCaixa();
void simularVendaProduto();
void removerTransacao();

#endif // CAIXA_H
