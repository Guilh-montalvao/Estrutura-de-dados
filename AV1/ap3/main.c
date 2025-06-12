// main.c
#include "utils.c"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <clientes.csv> <emprestimos.csv>\n", argv[0]);
        return 1;
    }

    const char *nome_arquivo_clientes = argv[1];
    const char *nome_arquivo_emprestimos = argv[2];

    int num_clientes = 0;
    Cliente *clientes = carregar_clientes(nome_arquivo_clientes, &num_clientes);
    if (!clientes) {
        return 1;
    }

    // Os empréstimos são carregados e adicionados ao histórico dos clientes
    carregar_emprestimos(nome_arquivo_emprestimos, clientes, num_clientes);

    int opcao;
    Cliente *temp_clientes = NULL; // Declaração movida para fora do switch
    do {
        printf("\n----------------Entrada------------------------------\n");
        printf("1 - Cadastrar Novo Cliente\n");
        printf("2 - Solicitar Novo Emprestimo\n");
        printf("3 - Listar Clientes e seus Emprestimos\n");
        printf("4 - Listar todos os Emprestimos Carregados\n");
        printf("0 - Sair\n");
        printf("-------------------------------------------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao) {
            case 1:
                temp_clientes = cadastrar_novo_cliente(clientes, &num_clientes);
                if (temp_clientes) {
                    clientes = temp_clientes;
                } else {
                    fprintf(stderr, "Erro ao cadastrar novo cliente.\n");
                }
                break;
            case 2:
                solicitar_novo_emprestimo(clientes, num_clientes);
                break;
            case 3:
                listar_clientes(clientes, num_clientes);
                break;
            case 4:
                listar_emprestimos(clientes, num_clientes);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberar_memoria(clientes, num_clientes);

    return 0;
}