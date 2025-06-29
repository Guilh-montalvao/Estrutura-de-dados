#include "utils.h"

#define TAXA_JUROS 0.05
#define LIMITE_PARCELA 0.20


// Definição de macros para limpar a tela
void limpar_buffer(){
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

void msg_erro(char *msg){
    limpar_buffer();
    system(LIMPAR_TELA);
    printf("\n----------------Erro------------------------------\n");
    printf("%s", msg);
    printf("----------------------------------------------------\n");
    printf("\nAperte <ENTER> para voltar ao menu principal.");
    getchar();
}

/* 
    ATENÇÃO: A função "realocar_memoria_cliente" deve ser implementada pelo aluno 
*/

// Função para alocar ou realocar memória para o array de clientes
Cliente* realocar_memoria_cliente(Cliente *clientes, int novo_tamanho) {
        // Realoca memória para o array de clientes
        // Realoca memória usando realloc e retorna o novo ponteiro
        return (Cliente*) realloc(clientes, novo_tamanho * sizeof(Cliente));
    }


/* 
    ATENÇÃO: A função "realocar_memoria_emprestimo" deve ser implementada pelo aluno 
*/

// Função para alocar ou realocar memória para o array de emprestimos
Emprestimo* realocar_memoria_emprestimo(Emprestimo *emprestimos, int novo_tamanho) {
        // Realoca memória para o array de empréstimos
        // Realoca memória usando realloc e retorna o novo ponteiro
        return (Emprestimo*) realloc(emprestimos, novo_tamanho * sizeof(Emprestimo));
    }



/* 
    ATENÇÃO: A função "cadastrar_novo_cliente" deve ser implementada pelo aluno 
*/

// Cadastra um novo cliente e adiciona ao array de clientes
Cliente *cadastrar_novo_cliente(Cliente *clientes, int *num_clientes) {
    Cliente novo_cliente;
    
    // Gera um ID único para o novo cliente (maior ID atual + 1)
    int maior_id = 0;
    for (int i = 0; i < *num_clientes; i++) {
        if (clientes[i].id > maior_id) {
            maior_id = clientes[i].id;
        }
    }
    novo_cliente.id = maior_id + 1;
    
    // Solicita informações do cliente
    printf("\n--- Cadastro de Novo Cliente ---\n");
    printf("Nome: ");
    fgets(novo_cliente.nome, MAX_NOME, stdin);
    // Remove o caractere de nova linha do final do nome
    novo_cliente.nome[strcspn(novo_cliente.nome, "\n")] = '\0';
    
    printf("Salario: ");
    if (scanf("%f", &novo_cliente.salario) != 1) {
        msg_erro("Erro: Salario invalido.\n");
        limpar_buffer();
        return clientes;
    }
    limpar_buffer(); // Limpa o buffer após a leitura do salário
    
    // Inicializa o histórico de empréstimos
    novo_cliente.historico_emprestimos = NULL;
    novo_cliente.num_emprestimos = 0;
    
    // Realoca memória para adicionar o novo cliente
    Cliente *temp = realocar_memoria_cliente(clientes, (*num_clientes + 1));
    if (!temp) {
        msg_erro("Erro: Falha ao alocar memória para o novo cliente.\n");
        return clientes;
    }
    
    // Adiciona o novo cliente ao array
    temp[*num_clientes] = novo_cliente;
    (*num_clientes)++;
    
    printf("\nCliente cadastrado com sucesso! ID: %d\n", novo_cliente.id);
    return temp;
}

/*
    ATENÇÃO: A função "solicitar_novo_emprestimo" deve ser implementada pelo aluno 
*/

// Solicita um novo empréstimo para um cliente
void solicitar_novo_emprestimo(Cliente *clientes, int num_clientes) {
    int cliente_id;
    Emprestimo novo_emprestimo;
    
    printf("\n--- Solicitacao de Novo Emprestimo ---\n");
    printf("ID do Cliente: ");
    if (scanf("%d", &cliente_id) != 1) {
        msg_erro("Erro: ID invalido.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();
    
    // Busca o cliente pelo ID
    Cliente *cliente = buscar_cliente_por_id(clientes, num_clientes, cliente_id);
    if (!cliente) {
        msg_erro("Erro: Cliente nao encontrado.\n");
        return;
    }
    
    // Preenche os dados do empréstimo
    novo_emprestimo.cliente_id = cliente_id;
    
    printf("Valor do Emprestimo: ");
    if (scanf("%f", &novo_emprestimo.valor_emprestimo) != 1 || novo_emprestimo.valor_emprestimo <= 0) {
        msg_erro("Erro: Valor de emprestimo invalido.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();
    
    printf("Numero de Parcelas: ");
    if (scanf("%d", &novo_emprestimo.num_parcelas) != 1 || novo_emprestimo.num_parcelas <= 0) {
        msg_erro("Erro: Numero de parcelas invalido.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();
    
    // Define o empréstimo como ativo
    novo_emprestimo.ativo = 1;
    
    // Calcula o valor da parcela
    calcular_valor_parcela(&novo_emprestimo);
    
    // Verifica se o empréstimo pode ser aprovado
    aprovar_reprovar_emprestimo(cliente, &novo_emprestimo);
    
    // Adiciona o empréstimo ao histórico do cliente
    adicionar_emprestimo_historico(cliente, novo_emprestimo);
    
    // Exibe o resultado da solicitação
    printf("\nEmprestimo processado:\n");
    printf("Valor: R$ %.2f\n", novo_emprestimo.valor_emprestimo);
    printf("Parcelas: %d\n", novo_emprestimo.num_parcelas);
    printf("Valor da Parcela: R$ %.2f\n", novo_emprestimo.valor_parcela);
    printf("Status: %s\n", novo_emprestimo.aprovacao ? "Aprovado" : "Reprovado");
    
    printf("\nPressione ENTER para continuar...");
    getchar();
}

/*
    ATENÇÃO: A função "solicitar_novo_emprestimo" deve ser implementada pelo aluno 
*/

// Calcula o valor da parcela do empréstimo
void calcular_valor_parcela(Emprestimo *emprestimo) {
    // Aplicando a taxa de juros simples de 5% (TAXA_JUROS = 0.05)
    // Fórmula: valor_parcela = (valor_emprestimo + (valor_emprestimo * TAXA_JUROS)) / num_parcelas
    float valor_total = emprestimo->valor_emprestimo + (emprestimo->valor_emprestimo * TAXA_JUROS);
    emprestimo->valor_parcela = valor_total / emprestimo->num_parcelas;
}

/*
    ATENÇÃO: A função "solicitar_novo_emprestimo" deve ser implementada pelo aluno 
*/

// Aprova ou reprova o empréstimo com base no salário do cliente
void aprovar_reprovar_emprestimo(Cliente *cliente, Emprestimo *novo_emprestimo) {
    // Calcula o valor total das parcelas de empréstimos ativos
    float total_parcelas_ativas = 0.0;
    
    // Verifica se o cliente tem empréstimos ativos e soma suas parcelas
    for (int i = 0; i < cliente->num_emprestimos; i++) {
        if (cliente->historico_emprestimos[i].ativo && cliente->historico_emprestimos[i].aprovacao) {
            total_parcelas_ativas += cliente->historico_emprestimos[i].valor_parcela;
        }
    }
    
    // Adiciona a parcela do novo empréstimo
    float total_comprometido = total_parcelas_ativas + novo_emprestimo->valor_parcela;
    
    // Calcula a porcentagem do salário comprometida com as parcelas
    float porcentagem_comprometida = total_comprometido / cliente->salario;
    
    // Se a parcela for maior que 20% do salário (LIMITE_PARCELA = 0.20), reprova o empréstimo
    if (porcentagem_comprometida > LIMITE_PARCELA) {
        novo_emprestimo->aprovacao = 0; // Reprovado
    } else {
        novo_emprestimo->aprovacao = 1; // Aprovado
    }
}




// Carrega os clientes do arquivo CSV e retorna um array de clientes
// O número de clientes é retornado através do ponteiro num_clientes
// O arquivo deve ter o formato: id,nome,salario
// Exemplo: 1,João,3000.00
Cliente *carregar_clientes(const char *nome_arquivo, int *num_clientes) {
    FILE *arquivo = fopen(nome_arquivo, "r"); // Abre o arquivo para leitura
    if (!arquivo) { // Verifica se o arquivo foi aberto corretamente
        // Se não, imprime uma mensagem de erro e retorna NULL
        perror("Erro ao abrir arquivo de clientes");
        return NULL;
    }

    Cliente *clientes = NULL;   // Inicializa o ponteiro para clientes
    *num_clientes = 0;          // Inicializa o número de clientes   
    char linha[256];            // Buffer para ler cada linha do arquivo
    fgets(linha, sizeof(linha), arquivo); // Ler e descartar o cabeçalho

    while (fgets(linha, sizeof(linha), arquivo)) { // Lê cada linha do arquivo
        Cliente novo_cliente; // Inicializa um novo cliente
        // Lê os dados do cliente da linha e armazena em novo_cliente
        // O formato esperado é: id,nome,salario
        // Exemplo: 1,João,3000.00
        // O sscanf retorna o número de itens lidos com sucesso
        if (sscanf(linha, "%d,%[^,],%f", &novo_cliente.id, novo_cliente.nome, &novo_cliente.salario) == 3) {

            /* 
                ATENÇÃO: A função "realocar_memoria_cliente" deve ser implementada pelo aluno 
            */

            // Realoca memória para mais um cliente
            clientes = realocar_memoria_cliente(clientes, (*num_clientes + 1));

            // Verifica se a realocação foi bem-sucedida
            if (!clientes) {
                perror("Erro ao alocar memória para clientes");
                fclose(arquivo);
                return NULL;
            }
            // Adiciona o novo cliente ao array
            novo_cliente.historico_emprestimos = NULL; // Inicializa o histórico de empréstimos
            novo_cliente.num_emprestimos = 0; // Inicializa o número de empréstimos
            // Adiciona o novo cliente ao array de clientes
            // O ponteiro clientes é atualizado para apontar para o novo array
            clientes[*num_clientes] = novo_cliente;
            (*num_clientes)++; // Incrementa o número de clientes
        } else { // Se a leitura falhar, imprime uma mensagem de erro
            fprintf(stderr, "Erro ao ler linha do arquivo de clientes: %s", linha);
        }
    }

    fclose(arquivo);
    return clientes;
}


// Carrega os empréstimos do arquivo e associa aos clientes
// O número de empréstimos é retornado através do ponteiro num_emprestimos
// O arquivo deve ter o formato: cliente_id,valor_emprestimo,num_parcelas
// Exemplo: 1,1000.00,12
Emprestimo *carregar_emprestimos(const char *nome_arquivo, Cliente *clientes, int num_clientes) {
    FILE *arquivo = fopen(nome_arquivo, "r"); // Abre o arquivo para leitura
    if (!arquivo) { // Verifica se o arquivo foi aberto corretamente
        perror("Erro ao abrir arquivo de emprestimos");
        return NULL;
    }

    Emprestimo *todos_emprestimos = NULL;   // Inicializa o ponteiro para todos os empréstimos
    int num_emprestimos_total = 0;          // Inicializa o número total de empréstimos
    char linha[256];                        // Buffer para ler cada linha do arquivo
    fgets(linha, sizeof(linha), arquivo);   // Ler e descartar o cabeçalho

    while (fgets(linha, sizeof(linha), arquivo)) { // Lê cada linha do arquivo
        Emprestimo novo_emprestimo; // Inicializa um novo empréstimo
        // Lê os dados do empréstimo da linha e armazena em novo_emprestimo
        // O formato esperado é: cliente_id,valor_emprestimo,num_parcelas
        // Exemplo: 1,1000.00,12
        // O sscanf retorna o número de itens lidos com sucesso
        if (sscanf(linha, "%d,%f,%d", &novo_emprestimo.cliente_id, &novo_emprestimo.valor_emprestimo, &novo_emprestimo.num_parcelas) == 3) {

            /* 
                ATENÇÃO: A função "calcular_valor_parcela" deve ser implementada pelo aluno 
            */

            // Calcula o valor da parcela do empréstimo
            calcular_valor_parcela(&novo_emprestimo);   // Calcula o valor da parcela
            novo_emprestimo.ativo = 1;                  // Assume como ativo ao carregar

            // Busca o cliente correspondente ao ID do empréstimo
            // O cliente é buscado no array de clientes
            // Se o cliente for encontrado, aprova ou reprova o empréstimo
            // e adiciona ao histórico do cliente
            // Se o cliente não for encontrado, imprime uma mensagem de aviso
            // e não adiciona o empréstimo ao histórico
            Cliente *cliente = buscar_cliente_por_id(clientes, num_clientes, novo_emprestimo.cliente_id); // Busca o cliente
            // Se o cliente for encontrado, aprova ou reprova o empréstimo
            if (cliente) {

                /* 
                    ATENÇÃO: A função "aprovar_reprovar_emprestimo" deve ser implementada pelo aluno 
                */
                aprovar_reprovar_emprestimo(cliente, &novo_emprestimo);     // Aprova ou reprova o empréstimo
                adicionar_emprestimo_historico(cliente, novo_emprestimo);   // Adiciona o empréstimo ao histórico do cliente

                /* 
                    ATENÇÃO: A função "realocar_memoria_emprestimo" deve ser implementada pelo aluno 
                */
                todos_emprestimos = realocar_memoria_emprestimo(todos_emprestimos, (num_emprestimos_total + 1));

                if (!todos_emprestimos) {
                    perror("Erro ao alocar memória para todos os emprestimos");
                    fclose(arquivo);
                    return NULL;
                }
                todos_emprestimos[num_emprestimos_total] = novo_emprestimo;
                num_emprestimos_total++;
            } else {
                fprintf(stderr, "Aviso: Cliente com ID %d não encontrado para o empréstimo.\n", novo_emprestimo.cliente_id);
            }
        } else {
            fprintf(stderr, "Erro ao ler linha do arquivo de emprestimos: %s", linha);
        }
    }

    fclose(arquivo);
    return todos_emprestimos;
}


// Adiciona um novo empréstimo ao histórico do cliente
void adicionar_emprestimo_historico(Cliente *cliente, Emprestimo emprestimo) {

    /* 
        ATENÇÃO: A função "realocar_memoria_emprestimo" deve ser implementada pelo aluno
    */
    cliente->historico_emprestimos = realocar_memoria_emprestimo(cliente->historico_emprestimos, cliente->num_emprestimos + 1);

    // Verifica se a realocação foi bem-sucedida
    if (!cliente->historico_emprestimos) { // Se a realocação falhar, imprime uma mensagem de erro
        perror("Erro ao alocar memória para histórico de empréstimos");
        if (!cliente->historico_emprestimos) { // Se o histórico de empréstimos for NULL
            // Tenta alocar memória para o primeiro empréstimo
            perror("Erro ao alocar memória para histórico de empréstimos");
            if (cliente->num_emprestimos == 0) { // Se não houver empréstimos
                // Aloca memória para o primeiro empréstimo
                cliente->historico_emprestimos = malloc(sizeof(Emprestimo));
                if (!cliente->historico_emprestimos) {
                    perror("Erro crítico ao alocar memória para o primeiro empréstimo");
                    return;
                }
            } else {
                return; // Já existe memória alocada, erro ao realocar
            } 
        }       
    }
    // Adiciona o novo empréstimo ao histórico
    cliente->historico_emprestimos[cliente->num_emprestimos] = emprestimo;
    cliente->num_emprestimos++;
}

// Lista todos os clientes e seus empréstimos
void listar_clientes(const Cliente *clientes, int num_clientes) {
    system(LIMPAR_TELA);
    printf("\n--- Lista de Clientes ---\n");
    for (int i = 0; i < num_clientes; i++) { 

        printf("ID: %d, Nome: %s, Salario: %.2f, Emprestimos: %d\n",
               clientes[i].id, clientes[i].nome, clientes[i].salario, clientes[i].num_emprestimos);
        if (clientes[i].historico_emprestimos && clientes[i].num_emprestimos > 0) {
            printf("  Historico de Emprestimos:\n");
            for (int j = 0; j < clientes[i].num_emprestimos; j++) {
                printf("    ID Cliente: %d, Valor: %.2f, Parcelas: %d, Parcela: %.2f, Status: ",
                       clientes[i].historico_emprestimos[j].cliente_id,
                       clientes[i].historico_emprestimos[j].valor_emprestimo,
                       clientes[i].historico_emprestimos[j].num_parcelas,
                       clientes[i].historico_emprestimos[j].valor_parcela);
                    
                    if (clientes[i].historico_emprestimos[j].aprovacao) {
                        printf("Aprovado");
                    } else {
                        printf(COR_VERMELHO "Reprovado" COR_RESET);
                    }

                    printf(", Ativo: %s\n", clientes[i].historico_emprestimos[j].ativo ? "Sim" : "Não");
            }
        } else {
            printf("  Sem historico de emprestimos.\n");
        }
    }
    printf("-------------------------\n");
}

// Lista todos os empréstimos carregados
void listar_emprestimos(const Cliente *clientes, int num_clientes) {
    system(LIMPAR_TELA);
    printf("\n--- Lista de Emprestimos Carregados ---\n");
    int total_emprestimos = 0;
    for (int i = 0; i < num_clientes; i++) {
        total_emprestimos += clientes[i].num_emprestimos;
        if (clientes[i].historico_emprestimos) {
            for (int j = 0; j < clientes[i].num_emprestimos; j++) {
                printf("Cliente ID: %d, Valor: %.2f, Parcelas: %d, Parcela: %.2f, Status: ",
                       clientes[i].historico_emprestimos[j].cliente_id,
                       clientes[i].historico_emprestimos[j].valor_emprestimo,
                       clientes[i].historico_emprestimos[j].num_parcelas,
                       clientes[i].historico_emprestimos[j].valor_parcela);
                
                        if (clientes[i].historico_emprestimos[j].aprovacao) {
                            printf("Aprovado");
                        } else {
                            printf(COR_VERMELHO "Reprovado" COR_RESET);
                        }
                        printf(", Ativo: %s\n", clientes[i].historico_emprestimos[j].ativo ? "Sim" : "Não");
            }
        }
    }
    printf("Total de emprestimos carregados: %d\n", total_emprestimos);
    printf("---------------------------------------\n");
}

// Busca um cliente pelo ID
Cliente *buscar_cliente_por_id(Cliente *clientes, int num_clientes, int id) {
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].id == id) {
            return &clientes[i];
        }
    }
    return NULL;
}

// Libera a memória alocada para os clientes e seus históricos de empréstimos
void liberar_memoria(Cliente *clientes, int num_clientes) {
    if (clientes) {
        for (int i = 0; i < num_clientes; i++) {
            free(clientes[i].historico_emprestimos);
        }
        free(clientes);
    }
}
