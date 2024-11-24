#ifndef INTERFACE_H
#define INTERFACE_H

void desenharLinha(int largura, char caractere, const char *cor);
void exibirTitulo(const char *titulo, int larguraTela, const char *cor);
void exibirMenu(const char *opcoes[], int numOpcoes, const char *cor);
void limparTela();

#endif
