# Estrutura de Dados

Este repositório contém exercícios e implementações práticas da disciplina de Estrutura de Dados.

## Estrutura do Projeto

```
├── AV1
│   ├── AP1
│   ├── Prova
│   ├── Prova Guilherme Augusto
│   └── ap3
├── AV2
│   └── Ap1
└── Monitoria
    └── A1
        └── Ex1
```

## Conteúdo

O projeto está organizado em avaliações (AV1 e AV2) e inclui exercícios de monitoria. Cada pasta contém implementações específicas focadas em diferentes conceitos de Estrutura de Dados.

### AV1 - Primeira Avaliação

- **AP1**: Primeira atividade prática
- **Prova**: Arquivos da prova regular
- **Prova Guilherme Augusto**: Implementação específica da prova
  - Manipulação de arquivos CSV (notas.csv)
  - Estruturas e funções utilitárias
- **ap3**: Terceira atividade prática
  - Sistema de gestão com arquivos CSV (clientes.csv, emprestimos.csv)
  - Implementação de estruturas de dados para gerenciamento

### AV2 - Segunda Avaliação

- **Ap1**: Lista Dinâmica Encadeada Dupla
  - Implementação completa de lista duplamente encadeada
  - Operações de inserção, remoção e manipulação

### Monitoria

Exercícios práticos desenvolvidos durante as sessões de monitoria:

- **A1/Ex1**: Exercícios básicos com ponteiros e funções

### Exemplos de Implementações

#### Cálculo de Média (Monitoria/A1/Ex1/Q5.c)

```c
void media(float n1, float n2, float *resultado) {
    *resultado = (n1 + n2) / 2;
}
```

Este exemplo demonstra o uso de ponteiros para calcular a média de dois números.

## Como Compilar e Executar

1. Certifique-se de ter um compilador C instalado (por exemplo, GCC)
2. Navegue até o diretório do exercício desejado
3. Compile o arquivo usando o comando:
   ```bash
   gcc nome_do_arquivo.c -o programa
   ```
4. Execute o programa:
   ```bash
   ./programa
   ```

## Tecnologias Utilizadas

- Linguagem C
- Conceitos de Estrutura de Dados
- Ponteiros e Alocação de Memória

## Contribuição

Sinta-se à vontade para contribuir com melhorias nos códigos ou adicionar novos exercícios. Abra uma issue ou envie um pull request com suas sugestões.
