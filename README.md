# Sistema Hortifruti - Projeto PIM

Este é um projeto desenvolvido como parte do **Projeto Integrado Multidisciplinar (PIM)** para o curso de Análise e Desenvolvimento de Sistemas. O **Sistema Hortifruti** é uma aplicação em C que permite gerenciar produtos, fornecedores e fluxo de caixa de um mercado de hortifruti.

## Funcionalidades

- **Cadastro de Produtos**:
  - Cadastrar novos produtos.
  - Consultar produto por ID.
  - Consultar todos os produtos cadastrados.
  - Editar dados dos produtos.
  - Alterar estoque dos produtos.
  - Excluir produtos.

- **Cadastro de Fornecedores**:
  - Cadastrar novos fornecedores.
  - Consultar fornecedor por ID.
  - Consultar todos os fornecedores cadastrados.
  - Editar dados dos fornecedores.
  - Excluir fornecedores.

- **Fluxo de Caixa**:
  - Registrar entradas de valor.
  - Registrar saídas de valor.
  - Simular vendas de produtos.
  - Remover transações do fluxo de caixa.
  - Exibir relatório completo do fluxo de caixa.

- **Resetar Dados**:
  - Limpar todos os registros do sistema (produtos, fornecedores e fluxo de caixa) para iniciar o cadastro do zero.

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

- **src/**: Contém os arquivos de código fonte (`.c`).
- **include/**: Contém os cabeçalhos (`.h`).
- **data/**: Diretório utilizado para armazenar arquivos binários dos registros (`.bin`).
- **.gitignore**: Arquivo para ignorar arquivos e diretórios desnecessários no repositório.
- **README.md**: Descrição do projeto e funcionalidades.

## Tecnologias Utilizadas

- **Linguagem**: C
- **IDE**: Code::Blocks