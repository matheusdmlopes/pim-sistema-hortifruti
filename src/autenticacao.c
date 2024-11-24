#include <stdio.h>
#include <string.h>
#include <autenticacao.h>

#define SENHA "UNIP"

int autenticarUsuario() {
    char senha[5], senhaDigitada[20];

    strcpy(senha, "UNIP");

    printf("Por favor, insira a senha para acessar o sistema.\n");
    printf("Você pode digitar 'sair' para encerrar o programa.\n");

    do {
        printf("Digite a senha: ");
        fgets(senhaDigitada, sizeof(senhaDigitada), stdin);

        if (strchr(senhaDigitada, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        senhaDigitada[strcspn(senhaDigitada, "\n")] = '\0';

        if (strcmp(senhaDigitada, "sair") == 0 || strcmp(senhaDigitada, "SAIR") == 0) {
            printf("\nEncerrando o sistema... Até mais!\n");
            return 0;
        }

        if (strlen(senhaDigitada) != strlen(senha) || strcmp(senha, senhaDigitada) != 0) {
            printf("\nAcesso negado. Tente novamente ou digite 'sair' para encerrar.\n");
        } else {
            printf("\nAcesso autorizado.\n");
            break;
        }

    } while (1);
}
