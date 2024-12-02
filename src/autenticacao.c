#include <stdio.h>
#include <string.h>
#include <autenticacao.h>

#define USUARIO "user"
#define SENHA "password"

int autenticarUsuario() {
    char senhaDigitada[20], usuarioDigitado[20];


    printf("Por favor, insira o usuário e senha para acessar o sistema.\n");
    printf("Você pode digitar 'sair' para encerrar o programa.\n");

    do {
        printf("Digite o usuario: ");
        fgets(usuarioDigitado, sizeof(usuarioDigitado), stdin);

        usuarioDigitado[strcspn(usuarioDigitado, "\n")] = '\0';

        printf("Digite a senha: ");
        fgets(senhaDigitada, sizeof(senhaDigitada), stdin);

        if (strchr(senhaDigitada, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        senhaDigitada[strcspn(senhaDigitada, "\n")] = '\0';

        if (strcmp(usuarioDigitado, "sair") == 0 || strcmp(usuarioDigitado, "SAIR") == 0) {
            printf("\nEncerrando o sistema... Até mais!\n");
            return 0;
        }

        if (strcmp(senhaDigitada, "sair") == 0 || strcmp(senhaDigitada, "SAIR") == 0) {
            printf("\nEncerrando o sistema... Até mais!\n");
            return 0;
        }

        if (strcmp(USUARIO, usuarioDigitado) != 0 || strcmp(SENHA, senhaDigitada) != 0) {
            printf("\nAcesso negado. Tente novamente ou digite 'sair' para encerrar.\n");
        } else {
            printf("\nAcesso autorizado.\n");
            break;
        }

    } while (1);
}
