#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fornecedor.h>
#include <cores.h>
#include <interface.h>


void cadastrarFornecedor()
{
    FILE *arquivo;
    Fornecedor fornecedor;
    int ultimoId = 0;

    arquivo = fopen("data/fornecedores.bin", "rb");
    if (arquivo != NULL) {
        while (fread(&fornecedor, sizeof(Fornecedor), 1, arquivo)) {
            ultimoId = fornecedor.id;
        }
        fclose(arquivo);
    }

    arquivo = fopen("data/fornecedores.bin", "ab");
    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    limparTela();

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    exibirTitulo("Cadastro de Novo Fornecedor", 80, ANSI_TEXT_CYAN);

    fornecedor.id = ultimoId + 1;

    printf("ID gerado automaticamente: %d\n", fornecedor.id);

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

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Registro incluído com sucesso!", 80, ANSI_TEXT_GREEN);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    printf("ID: %d\n", fornecedor.id);
    printf("CNPJ: %s\n", fornecedor.cnpj);
    printf("Nome: %s\n", fornecedor.nome);
    printf("Contato: %s\n", fornecedor.contato);

    desenharLinha(80, '-', ANSI_TEXT_GREEN);

    printf("\nPressione Enter para voltar ao menu.");
    getchar();
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

    limparTela();

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    exibirTitulo("Consulta de Fornecedor por ID", 80, ANSI_TEXT_CYAN);

    printf("\nDigite o ID para pesquisa: ");
    scanf("%d", &id_busca);
    getchar();

    while(fread(&fornecedor, sizeof(Fornecedor), 1, arquivo)) {
        if(fornecedor.id == id_busca) {
            encontrou = 1;

            desenharLinha(80, '=', ANSI_TEXT_GREEN);
            exibirTitulo("Registro Encontrado", 80, ANSI_TEXT_GREEN);
            desenharLinha(80, '=', ANSI_TEXT_GREEN);

            printf("ID: %d\n", fornecedor.id);
            printf("CNPJ: %s\n", fornecedor.cnpj);
            printf("Nome: %s\n", fornecedor.nome);
            printf("Contato: %s\n", fornecedor.contato);
            desenharLinha(80, '-', ANSI_TEXT_GREEN);
            break;
        }
    }

    fclose(arquivo);

    if(encontrou == 0) {
        desenharLinha(80, '=', ANSI_TEXT_RED);
        exibirTitulo("Nao ha registro com o valor pesquisado.", 80, ANSI_TEXT_RED);
        desenharLinha(80, '=', ANSI_TEXT_RED);
    }

    printf("\nPressione Enter para voltar ao menu.");
    getchar();
}

void consultarTodosFornecedores()
{
    FILE *arquivo;
    Fornecedor fornecedor;
    int encontrou = 0;

    arquivo = fopen("data/fornecedores.bin", "rb");

    if(arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    limparTela();

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    exibirTitulo("Lista de Fornecedores Cadastrados", 80, ANSI_TEXT_CYAN);
    desenharLinha(80, '-', ANSI_TEXT_GREEN);

    while(fread(&fornecedor, sizeof(Fornecedor), 1, arquivo)) {
        printf("ID: %d\n", fornecedor.id);
        printf("CNPJ: %s\n", fornecedor.cnpj);
        printf("Nome: %s\n", fornecedor.nome);
        printf("Contato: %s\n", fornecedor.contato);
        desenharLinha(80, '-', ANSI_TEXT_GREEN);
        encontrou = 1;
    }
    fclose(arquivo);

    if (encontrou == 0) {
        exibirTitulo("Nenhum fornecedor cadastrado no momento.", 80, ANSI_TEXT_RED);
    }

    printf("\nPressione Enter para voltar ao menu.");
    getchar();
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

    limparTela();

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    exibirTitulo("Editar Fornecedor", 80, ANSI_TEXT_CYAN);

    printf("\nDigite o ID para pesquisa: ");
    scanf("%d", &id_busca);
    getchar();
    while(fread(&fornecedor, sizeof(Fornecedor), 1, arquivo)) {
        if(fornecedor.id == id_busca) {
            encontrou = 1;

            desenharLinha(80, '=', ANSI_TEXT_GREEN);
            exibirTitulo("Registro Encontrado", 80, ANSI_TEXT_GREEN);
            desenharLinha(80, '=', ANSI_TEXT_GREEN);

            printf("ID: %d\n", fornecedor.id);
            printf("CNPJ: %s\n", fornecedor.cnpj);
            printf("Nome: %s\n", fornecedor.nome);
            printf("Contato: %s\n", fornecedor.contato);
            desenharLinha(80, '-', ANSI_TEXT_GREEN);

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

            desenharLinha(80, '=', ANSI_TEXT_GREEN);
            exibirTitulo("Registro alterado com sucesso!", 80, ANSI_TEXT_GREEN);
            desenharLinha(80, '=', ANSI_TEXT_GREEN);
            printf("ID: %d\n", fornecedor.id);
            printf("CNPJ: %s\n", fornecedor.cnpj);
            printf("Nome: %s\n", fornecedor.nome);
            printf("Contato: %s\n", fornecedor.contato);
            desenharLinha(80, '-', ANSI_TEXT_GREEN);
            break;
        }
    }
    fclose(arquivo);

    if(encontrou == 0) {
        desenharLinha(80, '=', ANSI_TEXT_RED);
        exibirTitulo("Nao ha registro com o valor pesquisado.", 80, ANSI_TEXT_RED);
        desenharLinha(80, '=', ANSI_TEXT_RED);
    }
    printf("\nPressione Enter para voltar ao menu.");
    getchar();
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

    limparTela();

    desenharLinha(80, '=', ANSI_TEXT_GREEN);
    exibirTitulo("Sistema Hortifruti", 80, ANSI_TEXT_YELLOW);
    desenharLinha(80, '=', ANSI_TEXT_GREEN);

    exibirTitulo("Excluir Fornecedor", 80, ANSI_TEXT_CYAN);

    printf("\nDigite o ID do registro para exclusao: ");
    scanf("%d", &id_busca);
    getchar();

    while(fread(&fornecedor, sizeof(Fornecedor), 1, arquivo)) {
        if(fornecedor.id == id_busca) {
            encontrou = 1;

            desenharLinha(80, '=', ANSI_TEXT_GREEN);
            exibirTitulo("Registro Encontrado", 80, ANSI_TEXT_GREEN);
            desenharLinha(80, '=', ANSI_TEXT_GREEN);

            printf("ID: %d\n", fornecedor.id);
            printf("CNPJ: %s\n", fornecedor.cnpj);
            printf("Nome: %s\n", fornecedor.nome);
            printf("Contato: %s\n", fornecedor.contato);

            desenharLinha(80, '-', ANSI_TEXT_GREEN);

            printf("Deseja realmente excluir este registro? (1- Sim | 2- Nao): ");
            scanf("%d", &op);
            printf("\n");
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
        desenharLinha(80, '=', ANSI_TEXT_RED);
        exibirTitulo("Nao ha registro com o valor pesquisado.", 80, ANSI_TEXT_RED);
        desenharLinha(80, '=', ANSI_TEXT_RED);
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

        exibirTitulo("Registro excluido com sucesso!", 80, ANSI_TEXT_GREEN);
    } else {
        remove("data/temp.bin");
    }
    printf("\nPressione Enter para voltar ao menu.");
    getchar();
}
