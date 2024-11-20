#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fornecedor.h>


void cadastrarFornecedor()
{
    FILE *arquivo;
    Fornecedor fornecedor;

    arquivo = fopen("data/fornecedores.bin", "ab");
    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    printf("\n--- Cadastro de Novo Fornecedor ---\n");

    printf("Digite o ID: ");
    scanf("%d", &fornecedor.id);
    getchar();

    printf("Digite o CNPJ: ");
    fgets(fornecedor.cnpj, sizeof(fornecedor.cnpj), stdin);
    fornecedor.cnpj[strcspn(fornecedor.cnpj, "\n")] = '\0';

    if (strchr(fornecedor.cnpj, '\n') == NULL) {
        while (getchar() != '\n');
    }

    printf("Digite o nome: ");
    fgets(fornecedor.nome, sizeof(fornecedor.nome), stdin);
    fornecedor.nome[strcspn(fornecedor.nome, "\n")] = '\0';

    printf("Digite o contato (email ou telefone): ");
    fgets(fornecedor.contato, sizeof(fornecedor.contato), stdin);
    fornecedor.contato[strcspn(fornecedor.contato, "\n")] = '\0';

    fwrite(&fornecedor, sizeof(Fornecedor), 1, arquivo);

    fclose(arquivo);

    printf("\n--- Registro incluído com sucesso ---\n");
    printf("ID: %d\n", fornecedor.id);
    printf("CNPJ: %s\n", fornecedor.cnpj);
    printf("Nome: %s\n", fornecedor.nome);
    printf("Contato: %s\n", fornecedor.contato);
    printf("-----------------------------------\n");
}

void consultarFornecedorPeloId()
{
    FILE *arquivo;
    Fornecedor fornecedor;
    int id_busca, encontrou = 0;

    arquivo = fopen("data/fornecedores.bin", "rb");
    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    printf("\nDigite o ID para pesquisa: ");
    scanf("%d", &id_busca);

    while(fread(&fornecedor, sizeof(Fornecedor), 1, arquivo)) {
        if(fornecedor.id == id_busca) {
            encontrou = 1;
            printf("\n--- Registro encontrado ---\n");
            printf("ID: %d\n", fornecedor.id);
            printf("CNPJ: %s\n", fornecedor.cnpj);
            printf("Nome: %s\n", fornecedor.nome);
            printf("Contato: %s\n", fornecedor.contato);
            printf("---------------------------\n");
            break;
        }
    }

    fclose(arquivo);

    if(encontrou == 0) {
        printf("\nNao ha registro com o valor pesquisado.\n");
    }
}

void consultarTodosFornecedores()
{
    FILE *arquivo;
    Fornecedor fornecedor;

    arquivo = fopen("data/fornecedores.bin", "rb");

    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    printf("\n--- Lista de Fornecedores Cadastrados ---\n");
    while(fread(&fornecedor, sizeof(Fornecedor), 1, arquivo)) {
        printf("ID: %d\n", fornecedor.id);
        printf("CNPJ: %s\n", fornecedor.cnpj);
        printf("Nome: %s\n", fornecedor.nome);
        printf("Contato: %s\n", fornecedor.contato);
        printf("-----------------------------------\n");
    }
    fclose(arquivo);
}

void editarFornecedor()
{
    FILE *arquivo;
    Fornecedor fornecedor;
    int id_busca, encontrou = 0;

    arquivo = fopen("data/fornecedores.bin", "rb+");
    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    printf("\nDigite o ID para pesquisa: ");
    scanf("%d", &id_busca);
    getchar();
    while(fread(&fornecedor, sizeof(Fornecedor), 1, arquivo)) {
        if(fornecedor.id == id_busca) {
            encontrou = 1;

            printf("\n--- Registro Encontrado ---\n");
            printf("ID: %d\n", fornecedor.id);
            printf("CNPJ: %s\n", fornecedor.cnpj);
            printf("Nome: %s\n", fornecedor.nome);
            printf("Contato: %s\n", fornecedor.contato);
            printf("-----------------------------------\n");

            printf("\nDigite o novo CNPJ: ");
            fgets(fornecedor.cnpj, sizeof(fornecedor.cnpj), stdin);
            fornecedor.cnpj[strcspn(fornecedor.cnpj, "\n")] = '\0';

            if (strchr(fornecedor.cnpj, '\n') == NULL) {
                while (getchar() != '\n');
            }

            printf("Digite o novo nome: ");
            fgets(fornecedor.nome, sizeof(fornecedor.nome), stdin);
            fornecedor.nome[strcspn(fornecedor.nome, "\n")] = '\0';

            printf("Digite o novo contato: ");
            fgets(fornecedor.contato, sizeof(fornecedor.contato), stdin);
            fornecedor.contato[strcspn(fornecedor.contato, "\n")] = '\0';

            fseek(arquivo, -(long)sizeof(Fornecedor), SEEK_CUR);
            fwrite(&fornecedor, sizeof(Fornecedor), 1, arquivo);

            printf("\n--- Registro alterado com sucesso ---\n");
            printf("ID: %d\n", fornecedor.id);
            printf("CNPJ: %s\n", fornecedor.cnpj);
            printf("Nome: %s\n", fornecedor.nome);
            printf("Contato: %s\n", fornecedor.contato);
            printf("-------------------------------------\n");
            break;
        }
    }
    fclose(arquivo);

    if(encontrou == 0) {
        printf("Nao ha registro com o valor pesquisado.\n");
    }

}

void excluirFornecedor()
{
    FILE *arquivo, *novoArquivo;
    Fornecedor fornecedor;
    int id_busca, op, encontrou = 0;

    arquivo = fopen("data/fornecedores.bin", "rb");
    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    novoArquivo = fopen("data/temp.bin", "wb");
    if(novoArquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        fclose(arquivo);
        exit(1);
    }

    printf("\nDigite o ID do registro para exclusao: ");
    scanf("%d", &id_busca);
    getchar();

    while(fread(&fornecedor, sizeof(Fornecedor), 1, arquivo)) {
        if(fornecedor.id == id_busca) {
            encontrou = 1;
            printf("\n--- Registro Encontrado ---\n");
            printf("ID: %d\n", fornecedor.id);
            printf("CNPJ: %s\n", fornecedor.cnpj);
            printf("Nome: %s\n", fornecedor.nome);
            printf("Contato: %s\n", fornecedor.contato);
            printf("---------------------------\n");

            printf("Deseja realmente excluir este registro? (1- Sim | 2- Nao): ");
            scanf("%d", &op);
            getchar();

            if(op != 1) {
                fwrite(&fornecedor, sizeof(Fornecedor), 1, novoArquivo);
            }
        } else {
            fwrite(&fornecedor, sizeof(Fornecedor), 1, novoArquivo);
        }
    }

    fclose(arquivo);
    fclose(novoArquivo);

    if(encontrou == 0) {
        printf("\nNao ha registro com o valor pesquisado.\n");
        remove("data/temp.bin");
    } else if(op == 1 && encontrou == 1) {
        if(remove("data/fornecedores.bin") != 0) {
            perror("Erro ao remover o arquivo original");
            exit(1);
        }

        if(rename("data/temp.bin", "data/fornecedores.bin") != 0) {
            perror("Erro ao renomear o arquivo");
            exit(1);
        }

        printf("\n--- Registro excluido com sucesso ---\n");
    } else {
        remove("data/temp.bin");
    }
}
