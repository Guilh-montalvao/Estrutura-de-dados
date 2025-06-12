#include "grafo.h"

/**
 * @brief Cria um novo grafo com uma determinada quantidade de vértices.
 *
 * Aloca memória para a estrutura do grafo e inicializa as listas de adjacência de cada vértice como vazias.
 *
 * @param num_vertices Número de vértices do grafo a ser criado.
 * @return Ponteiro para o grafo criado.
 */
Grafo* criar_grafo(int num_vertices) {
    Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));
    grafo->num_vertices = num_vertices;
    grafo->adj = (Elemento**) malloc(num_vertices * sizeof(Elemento*));
    for (int i = 0; i < num_vertices; i++)
        grafo->adj[i] = NULL;

    return grafo;
}

/**
 * @brief Adiciona uma aresta do vértice de origem ao vértice de destino no grafo.
 *
 * Esta função cria um novo elemento na lista de adjacência do vértice de origem,
 * representando uma aresta direcionada para o vértice de destino.
 *
 * @param grafo Ponteiro para a estrutura do grafo onde a aresta será adicionada.
 * @param origem Índice do vértice de origem da aresta.
 * @param destino Índice do vértice de destino da aresta.
 * @return Não retorna valor.
 */
void adicionar_aresta(Grafo* grafo, int origem, int destino) {
    Elemento* novo = (Elemento*) malloc(sizeof(Elemento));
    novo->vertice = destino;
    novo->prox = grafo->adj[origem];
    grafo->adj[origem] = novo;
}

/**
 * @brief Imprime a representação do grafo na forma de lista de adjacência.
 *
 * Esta função percorre todos os vértices do grafo e imprime, para cada vértice,
 * a lista de vértices adjacentes a ele. Cada linha corresponde a um vértice e
 * sua respectiva lista de adjacências, terminando com "NULL".
 *
 * @param grafo Ponteiro para a estrutura do grafo a ser impresso.
 */
void imprimir_grafo(Grafo* grafo) {
    for (int v = 0; v < grafo->num_vertices; v++) {
        printf(GREEN_TEXT "%d: " RESET_TEXT, v);
        Elemento* temp = grafo->adj[v];
        while (temp) {
            printf("%d -> ", temp->vertice);
            temp = temp->prox;
        }
        printf("NULL\n");
    }
}

/**
 * @brief Cria e inicializa uma nova pilha.
 *
 * Esta função aloca dinamicamente uma estrutura do tipo Pilha,
 * inicializando o ponteiro topo como NULL para indicar que a pilha está vazia.
 *
 * @return Um ponteiro para a nova pilha criada, ou NULL em caso de falha na alocação.
 */
Pilha* criar_pilha() {
    Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
    if (pilha != NULL)
        pilha->topo = NULL;
    
    pilha->tamanho = 0; // Inicializa o tamanho da pilha como 0
    return pilha;
}

/**
 * @brief Adiciona um novo vértice ao topo da pilha.
 *
 * Esta função aloca dinamicamente um novo elemento, define o valor do vértice,
 * ajusta o ponteiro para o próximo elemento e atualiza o topo da pilha.
 * Incrementa o tamanho da pilha ao adicionar o novo elemento.
 *
 * @param pilha Ponteiro para a estrutura da pilha.
 * @param vertice Valor do vértice a ser inserido na pilha.
 * @return int Retorna 1 em caso de sucesso e 0 em caso de falha (pilha nula ou falha na alocação).
 */
int push(Pilha* pilha, int vertice) {
    // Verifica se a pilha é válida
    if(pilha == NULL) return 0;

    /* Aloca memória para o novo elemento que será inserido no topo da pilha */
    Elemento* novo = (Elemento*) malloc(sizeof(Elemento));
    // Se falhar a alocação, retorna erro
    if(novo == NULL) return 0;
    
    // Define o valor do vértice no novo elemento
    novo->vertice = vertice;
    // O próximo elemento do novo nó será o antigo topo (pode ser NULL se pilha vazia)
    novo->prox = pilha->topo;
    // Atualiza o topo da pilha para apontar para o novo elemento
    pilha->topo = novo;
    // Incrementa o contador de elementos na pilha
    pilha->tamanho++;

    return 1; // Retorna sucesso
}

/**
 * Remove e retorna o elemento do topo da pilha.
 *
 * @param pilha Ponteiro para a estrutura da pilha.
 * @return O valor do vértice removido do topo da pilha. Retorna 0 se a pilha estiver vazia ou for nula.
 */
int pop(Pilha* pilha) {
    // Verifica se a pilha é válida e não está vazia
    if (pilha == NULL || pilha->topo == NULL) return 0;

    /* Remove e retorna o elemento do topo da pilha */
    // Guarda referência ao elemento que será removido
    Elemento* remover = pilha->topo;
    // Salva o valor do vértice antes de liberar a memória
    int vertice = remover->vertice;
    
    // Atualiza o topo para apontar para o próximo elemento (desce um nível na pilha)
    pilha->topo = pilha->topo->prox;
    // Decrementa o contador de elementos
    pilha->tamanho--;
    // Libera a memória do elemento removido
    free(remover);

    // Retorna o valor do vértice que estava no topo
    return vertice;
}

/**
 * Verifica se a pilha está vazia.
 *
 * Esta função retorna verdadeiro se a pilha fornecida for nula ou se o topo da pilha for nulo,
 * indicando que não há elementos na pilha.
 *
 * @param pilha Ponteiro para a estrutura da pilha a ser verificada.
 * @return true se a pilha estiver vazia ou nula, false caso contrário.
 */
bool pilha_vazia(Pilha* pilha) {
    return (pilha == NULL || pilha->topo == NULL);
}

/**
 * @brief Libera toda a memória alocada para a pilha.
 *
 * Esta função percorre todos os elementos da pilha, liberando a memória
 * alocada para cada nó e, ao final, libera também a estrutura da pilha.
 * Caso o ponteiro para a pilha seja NULL, nada é feito.
 *
 * @param pi Ponteiro para a pilha a ser liberada.
 */
void libera_pilha(Pilha* pi){
    if(pi != NULL){
        Elemento* no;
        while(pi->topo != NULL){
            no = pi->topo;
            pi->topo = pi->topo->prox;
            free(no);
        }
        free(pi);
    }
}

/**
 * @brief Imprime os elementos da pilha na saída padrão.
 *
 * Esta função percorre a pilha a partir do topo e imprime cada elemento
 * no formato "[ valor ]", utilizando cores se definido. Caso a pilha esteja
 * vazia ou seja nula, imprime apenas "[ ]".
 *
 * @param pilha Ponteiro para a estrutura da pilha a ser impressa.
 */
void imprime_pilha(Pilha* pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        printf("[ ]");
        return;
    }

    Elemento* atual = pilha->topo;
    while (atual != NULL) {
        printf(GREEN_TEXT "[ %d ]" RESET_TEXT, atual->vertice);
        atual = atual->prox;
    }
    printf("\n");
}

/**
 * @brief Cria e inicializa uma nova fila.
 *
 * Esta função aloca dinamicamente uma estrutura do tipo Fila,
 * inicializando seus ponteiros de início e fim como NULL.
 *
 * @return Um ponteiro para a nova fila criada, ou NULL em caso de falha na alocação.
 */
Fila* criar_fila() {
    Fila* fila = (Fila*) malloc(sizeof(Fila));
    if(fila != NULL) {
        fila->inicio = NULL;
        fila->fim = NULL;
    }

    fila->tamanho = 0; // Inicializa o tamanho da fila como 0
    return fila;
}

/**
 * @brief Adiciona um vértice ao final da fila.
 *
 * Esta função insere um novo elemento contendo o vértice especificado
 * ao final da fila apontada por 'fila'. Caso a fila esteja vazia, o novo
 * elemento será o primeiro da fila. Caso contrário, ele será adicionado
 * após o último elemento atual. A função também atualiza o ponteiro para
 * o fim da fila e incrementa o tamanho.
 *
 * @param fila Ponteiro para a estrutura da fila onde o vértice será inserido.
 * @param vertice Valor do vértice a ser inserido na fila.
 * @return int Retorna 1 em caso de sucesso e 0 em caso de falha (por exemplo, fila nula ou falha de alocação).
 */
int enfileira(Fila* fila, int vertice){
    // Verifica se a fila é válida
    if(fila == NULL) return 0;

    /* Aloca memória para o novo elemento que será inserido no final da fila */
    Elemento* novo = (Elemento*) malloc(sizeof(Elemento));
    // Se falhar a alocação, retorna erro
    if(novo == NULL) return 0;
    
    // Define o valor do vértice no novo elemento
    novo->vertice = vertice;
    // Como será o último elemento, seu próximo é NULL
    novo->prox = NULL;
    
    // Verifica se a fila está vazia
    if(fila->fim == NULL) {
        // Se a fila está vazia, o novo elemento será tanto o início quanto o fim
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        // Se a fila não está vazia, adiciona o novo elemento após o atual último
        fila->fim->prox = novo;
        // Atualiza o ponteiro fim para apontar para o novo último elemento
        fila->fim = novo;
    }
    
    // Incrementa o contador de elementos na fila
    fila->tamanho++;

    return 1; // Retorna sucesso
}

/**
 * @brief Remove e retorna o elemento do início da fila.
 *
 * Esta função desenfileira (remove) o primeiro elemento da fila, libera a memória
 * associada a este elemento e retorna o valor do vértice armazenado. Caso a fila esteja
 * vazia ou seja nula, retorna 0.
 *
 * @param fila Ponteiro para a estrutura da fila.
 * @return int Valor do vértice removido do início da fila, ou 0 se a fila estiver vazia ou nula.
 */
int desenfileira(Fila* fila){
    // Verifica se a fila é válida e não está vazia
    if(fila == NULL || fila->inicio == NULL) return 0;

    /* Remove e retorna o elemento do início da fila (FIFO - primeiro a entrar, primeiro a sair) */
    // Guarda referência ao elemento que será removido (primeiro da fila)
    Elemento* remover = fila->inicio;
    // Salva o valor do vértice antes de liberar a memória
    int vertice = remover->vertice;
    
    // Atualiza o início da fila para apontar para o próximo elemento
    fila->inicio = fila->inicio->prox;
    
    // Verifica se a fila ficou vazia após a remoção
    if(fila->inicio == NULL) {
        // Se ficou vazia, o ponteiro fim também deve ser NULL
        fila->fim = NULL;
    }
    
    // Decrementa o contador de elementos
    fila->tamanho--;
    // Libera a memória do elemento removido
    free(remover);

    // Retorna o valor do vértice que estava no início da fila
    return vertice;
}

/**
 * @brief Imprime os elementos de uma fila na tela.
 *
 * Esta função percorre a fila passada como parâmetro e imprime cada elemento (vértice)
 * no formato "[ valor ]". Caso a fila esteja vazia ou seja nula, imprime "[ ]".
 *
 * @param fila Ponteiro para a estrutura Fila a ser impressa.
 */
void imprime_fila(Fila* fila) {
    if (fila == NULL || fila->inicio == NULL) {
        printf("[ ]\n");
        return;
    }

    Elemento* atual = fila->inicio;
    while (atual != NULL) {
        printf(GREEN_TEXT "[ %d ]" RESET_TEXT, atual->vertice);
        atual = atual->prox;
    }
    printf("\n");
}

/**
 * @brief Verifica se uma fila está vazia.
 *
 * Esta função retorna verdadeiro se a fila fornecida for nula ou se o ponteiro para o início da fila for nulo,
 * indicando que não há elementos na fila.
 *
 * @param fila Ponteiro para a estrutura da fila a ser verificada.
 * @return true se a fila estiver vazia ou nula, false caso contrário.
 */
bool fila_vazia(Fila* fila) {
    return (fila == NULL || fila->inicio == NULL);
}

/**
 * @brief Libera toda a memória alocada para uma fila.
 *
 * Esta função percorre todos os elementos da fila, liberando a memória
 * alocada para cada nó, e por fim libera a estrutura da fila em si.
 * Caso o ponteiro passado seja NULL, nada é feito.
 *
 * @param fila Ponteiro para a estrutura da fila a ser liberada.
 */
void libera_fila(Fila* fila){
    if(fila != NULL){
        Elemento *aux;
        while(fila->inicio != NULL){
            aux = fila->inicio;
            fila->inicio = fila->inicio->prox;
            free(aux);
        }
        free(fila);
    }
}

/**
 * @brief Realiza a busca em profundidade (DFS) em um grafo a partir de um vértice inicial.
 *
 * Esta função executa o algoritmo de busca em profundidade (Depth-First Search) utilizando uma pilha
 * para percorrer os vértices do grafo representado por lista de adjacência. Ela imprime a ordem em que
 * os vértices são visitados a partir do vértice inicial fornecido.
 *
 * @param grafo Ponteiro para a estrutura do grafo.
 * @param vertice_inicial Índice do vértice a partir do qual a busca será iniciada.
 *
 * @note A função aloca memória dinamicamente para o vetor de visitados e para a pilha, 
 * liberando-os ao final.
 */
void DFS(Grafo* grafo, int vertice_inicial) {
    bool* visitado = (bool*) malloc(grafo->num_vertices * sizeof(bool));
    for (int i = 0; i < grafo->num_vertices; i++) {
        visitado[i] = false;
    }

    Pilha* pilha = criar_pilha();

    printf(BLUE_TEXT "\nBusca em Profundidade (DFS) a partir do vértice %d:\n" RESET_TEXT, vertice_inicial);

    push(pilha, vertice_inicial);
    imprime_pilha(pilha);
    visitado[vertice_inicial] = true;

    while (!pilha_vazia(pilha)) {
        int vertice_atual = pop(pilha);
        printf("Vertice atual: %d\n", vertice_atual);
        imprime_pilha(pilha);

        Elemento* vizinho = grafo->adj[vertice_atual];
        while (vizinho) {
            if (!visitado[vizinho->vertice]) {
                visitado[vizinho->vertice] = true;
                push(pilha, vizinho->vertice);
                imprime_pilha(pilha);
            }
            vizinho = vizinho->prox;
        }
    }
    printf("\n");

    libera_pilha(pilha);
    free(visitado);
}

/**
 * @brief Realiza a busca em largura (BFS) em um grafo a partir de um vértice inicial.
 *
 * Esta função percorre todos os vértices alcançáveis a partir do vértice inicial
 * utilizando o algoritmo de busca em largura (BFS). Durante o percurso, imprime
 * a ordem em que os vértices são visitados.
 *
 * @param grafo Ponteiro para a estrutura do grafo.
 * @param vertice_inicial Índice do vértice a partir do qual a busca será iniciada.
 *
 * @note A função assume que as funções auxiliares criar_fila, enfileira, desenfileira,
 * fila_vazia, libera_fila e as estruturas Grafo, Fila e Elemento estão corretamente implementadas.
 */
void BFS(Grafo* grafo, int vertice_inicial) {
    bool* visitado = (bool*) malloc(grafo->num_vertices * sizeof(bool));
    for (int i = 0; i < grafo->num_vertices; i++) {
        visitado[i] = false;
    }

    Fila* fila = criar_fila();

    printf(BLUE_TEXT "\n\nBusca em Largura (BFS) a partir do vértice %d:\n" RESET_TEXT, vertice_inicial);

    enfileira(fila, vertice_inicial);
    imprime_fila(fila);
    visitado[vertice_inicial] = true;

    while (!fila_vazia(fila)) {
        int vertice_atual = desenfileira(fila);
        printf("Vertice atual: %d\n", vertice_atual);
        imprime_fila(fila);

        Elemento* vizinho = grafo->adj[vertice_atual];
        while (vizinho) {
            if (!visitado[vizinho->vertice]) {
                visitado[vizinho->vertice] = true;
                enfileira(fila, vizinho->vertice);
                imprime_fila(fila);
            }
            vizinho = vizinho->prox;
        }
    }
    printf("\n");

    libera_fila(fila);
    free(visitado);
}

/**
 * @brief Realiza busca em profundidade (DFS) procurando um vértice destino específico.
 *
 * Esta função executa o algoritmo DFS até encontrar o vértice destino. Quando encontra,
 * imprime o caminho percorrido e o número de vértices no caminho. Para rastrear o caminho,
 * mantém um array de predecessores que registra de qual vértice cada vértice foi descoberto.
 *
 * @param grafo Ponteiro para a estrutura do grafo onde a busca será realizada.
 * @param vertice_inicial Vértice de onde a busca começará.
 * @param vertice_destino Vértice que estamos procurando.
 */
void DFS_com_destino(Grafo* grafo, int vertice_inicial, int vertice_destino) {
    // Array para marcar vértices já visitados
    bool* visitado = (bool*) malloc(grafo->num_vertices * sizeof(bool));
    // Array para armazenar o predecessor de cada vértice (para reconstruir o caminho)
    int* predecessor = (int*) malloc(grafo->num_vertices * sizeof(int));
    
    // Inicializa todos os vértices como não visitados e sem predecessor
    for (int i = 0; i < grafo->num_vertices; i++) {
        visitado[i] = false;
        predecessor[i] = -1; // -1 indica que não tem predecessor
    }

    // Cria a pilha para o algoritmo DFS
    Pilha* pilha = criar_pilha();
    
    printf(BLUE_TEXT "\nBusca em Profundidade (DFS) do vértice %d até o vértice %d:\n" RESET_TEXT, 
           vertice_inicial, vertice_destino);

    // Marca o vértice inicial como visitado e o empilha
    push(pilha, vertice_inicial);
    visitado[vertice_inicial] = true;
    
    // Flag para indicar se encontramos o destino
    bool destino_encontrado = false;

    // Continua enquanto a pilha não estiver vazia e não tivermos encontrado o destino
    while (!pilha_vazia(pilha) && !destino_encontrado) {
        int vertice_atual = pop(pilha);
        printf("Visitando vértice: %d\n", vertice_atual);

        // Verifica se chegamos ao destino
        if (vertice_atual == vertice_destino) {
            destino_encontrado = true;
            printf(GREEN_TEXT "\nDestino encontrado!\n" RESET_TEXT);
            break;
        }

        // Explora todos os vizinhos do vértice atual
        Elemento* vizinho = grafo->adj[vertice_atual];
        while (vizinho) {
            // Se o vizinho ainda não foi visitado
            if (!visitado[vizinho->vertice]) {
                visitado[vizinho->vertice] = true;
                predecessor[vizinho->vertice] = vertice_atual; // Registra o predecessor
                push(pilha, vizinho->vertice);
            }
            vizinho = vizinho->prox;
        }
    }

    // Se encontramos o destino, reconstruímos e imprimimos o caminho
    if (destino_encontrado) {
        // Reconstrói o caminho do destino até a origem usando o array de predecessores
        int* caminho = (int*) malloc(grafo->num_vertices * sizeof(int));
        int tamanho_caminho = 0;
        
        // Percorre do destino até a origem através dos predecessores
        int v = vertice_destino;
        while (v != -1) {
            caminho[tamanho_caminho++] = v;
            v = predecessor[v];
        }

        // Imprime o caminho (está invertido, então imprimimos de trás para frente)
        printf("\nCaminho encontrado: ");
        for (int i = tamanho_caminho - 1; i >= 0; i--) {
            printf("%d", caminho[i]);
            if (i > 0) printf(" -> ");
        }
        printf("\nNúmero de vértices no caminho: %d\n", tamanho_caminho);
        
        free(caminho);
    } else {
        printf(RED_TEXT "\nNão foi possível encontrar um caminho do vértice %d até o vértice %d\n" RESET_TEXT, 
               vertice_inicial, vertice_destino);
    }

    // Libera a memória alocada
    libera_pilha(pilha);
    free(visitado);
    free(predecessor);
}

/**
 * @brief Realiza busca em largura (BFS) procurando um vértice destino específico.
 *
 * Esta função executa o algoritmo BFS até encontrar o vértice destino. A vantagem do BFS
 * é que ele sempre encontra o caminho mais curto (com menor número de arestas) entre
 * a origem e o destino. Mantém um array de predecessores para reconstruir o caminho.
 *
 * @param grafo Ponteiro para a estrutura do grafo onde a busca será realizada.
 * @param vertice_inicial Vértice de onde a busca começará.
 * @param vertice_destino Vértice que estamos procurando.
 */
void BFS_com_destino(Grafo* grafo, int vertice_inicial, int vertice_destino) {
    // Array para marcar vértices já visitados
    bool* visitado = (bool*) malloc(grafo->num_vertices * sizeof(bool));
    // Array para armazenar o predecessor de cada vértice (para reconstruir o caminho)
    int* predecessor = (int*) malloc(grafo->num_vertices * sizeof(int));
    
    // Inicializa todos os vértices como não visitados e sem predecessor
    for (int i = 0; i < grafo->num_vertices; i++) {
        visitado[i] = false;
        predecessor[i] = -1; // -1 indica que não tem predecessor
    }

    // Cria a fila para o algoritmo BFS
    Fila* fila = criar_fila();
    
    printf(BLUE_TEXT "\nBusca em Largura (BFS) do vértice %d até o vértice %d:\n" RESET_TEXT, 
           vertice_inicial, vertice_destino);

    // Marca o vértice inicial como visitado e o enfileira
    enfileira(fila, vertice_inicial);
    visitado[vertice_inicial] = true;
    
    // Flag para indicar se encontramos o destino
    bool destino_encontrado = false;

    // Continua enquanto a fila não estiver vazia e não tivermos encontrado o destino
    while (!fila_vazia(fila) && !destino_encontrado) {
        int vertice_atual = desenfileira(fila);
        printf("Visitando vértice: %d\n", vertice_atual);

        // Verifica se chegamos ao destino
        if (vertice_atual == vertice_destino) {
            destino_encontrado = true;
            printf(GREEN_TEXT "\nDestino encontrado!\n" RESET_TEXT);
            break;
        }

        // Explora todos os vizinhos do vértice atual
        Elemento* vizinho = grafo->adj[vertice_atual];
        while (vizinho) {
            // Se o vizinho ainda não foi visitado
            if (!visitado[vizinho->vertice]) {
                visitado[vizinho->vertice] = true;
                predecessor[vizinho->vertice] = vertice_atual; // Registra o predecessor
                enfileira(fila, vizinho->vertice);
            }
            vizinho = vizinho->prox;
        }
    }

    // Se encontramos o destino, reconstruímos e imprimimos o caminho
    if (destino_encontrado) {
        // Reconstrói o caminho do destino até a origem usando o array de predecessores
        int* caminho = (int*) malloc(grafo->num_vertices * sizeof(int));
        int tamanho_caminho = 0;
        
        // Percorre do destino até a origem através dos predecessores
        int v = vertice_destino;
        while (v != -1) {
            caminho[tamanho_caminho++] = v;
            v = predecessor[v];
        }

        // Imprime o caminho (está invertido, então imprimimos de trás para frente)
        printf("\nCaminho mais curto encontrado: ");
        for (int i = tamanho_caminho - 1; i >= 0; i--) {
            printf("%d", caminho[i]);
            if (i > 0) printf(" -> ");
        }
        printf("\nNúmero de vértices no caminho: %d\n", tamanho_caminho);
        
        free(caminho);
    } else {
        printf(RED_TEXT "\nNão foi possível encontrar um caminho do vértice %d até o vértice %d\n" RESET_TEXT, 
               vertice_inicial, vertice_destino);
    }

    // Libera a memória alocada
    libera_fila(fila);
    free(visitado);
    free(predecessor);
}