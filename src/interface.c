#include <stdio.h>
#include <string.h>
#include <interface.h>
#include <cores.h>


void desenharLinha(int largura, char caractere, const char *cor) {
    setTextColor(cor);
    for (int i = 0; i < largura; i++) {
        printf("%c", caractere);
    }
    resetColors();
    printf("\n");
}


void exibirTitulo(const char *titulo, int larguraTela, const char *cor) {
    int espacos = (larguraTela - strlen(titulo)) / 2;
    setTextColor(cor);
    setTextStyle(ANSI_BOLD);
    for (int i = 0; i < espacos; i++) {
        printf(" ");
    }
    printf("%s\n", titulo);
    resetColors();
}


void exibirMenu(const char *opcoes[], int numOpcoes, const char *cor) {
    setTextColor(cor);
    for (int i = 0; i < numOpcoes; i++) {
        printf("%d. %s\n", i + 1, opcoes[i]);
    }
    resetColors();
}

void limparTela() {
    printf("\033[H\033[J");
}
