#include "grafo.c"
#include <string.h>

int main() {

    // Define o nome do arquivo de arestas
    char *arquivoArestas = "arestas.txt"; // Valor padrão para o arquivo de arestas
    // Abre o arquivo de arestas para leitura
    FILE *fArestas = fopen(arquivoArestas, "r");
    if (!fArestas) {
        perror("Erro ao abrir arquivo de arestas");
        return 1;
    }

    // Lê o arquivo para determinar o número de vértices
    // O número de vértices é determinado pelo maior índice encontrado nas arestas
    int maxVertice = -1;
    int origem, destino;
    while (fscanf(fArestas, "%d %d", &origem, &destino) == 2) {
        if (origem > maxVertice) {
            maxVertice = origem;
        }
        if (destino > maxVertice) {
            maxVertice = destino;
        }
    }
    fclose(fArestas);

    // O número de vértices é o maior índice encontrado + 1
    int numVertices = maxVertice + 1;
    if (numVertices <= 0) {
        fprintf(stderr, "Nenhuma aresta encontrada no arquivo ou arquivo vazio.\n");
        return 1;
    }

    // Cria o grafo com o número de vértices determinado
    // A função criarGrafo aloca memória para o grafo e inicializa suas listas de adjacência
    Grafo* grafo = criar_grafo(numVertices);

    // Reabrir o arquivo para adicionar as arestas ao grafo
    fArestas = fopen(arquivoArestas, "r");
    if (!fArestas) {
        perror("Erro ao reabrir arquivo de arestas");
        free(grafo->adj);
        free(grafo);
        return 1;
    }

    // Lê as arestas do arquivo e adiciona ao grafo
    // Cada linha do arquivo deve conter dois inteiros representando uma aresta direcionada
    while (fscanf(fArestas, "%d %d", &origem, &destino) == 2) {
        if (origem >= 0 && origem < numVertices && destino >= 0 && destino < numVertices) {
            adicionar_aresta(grafo, origem, destino);
        } else {
            fprintf(stderr, "Aresta inválida encontrada no arquivo.\n");
        }
    }
    fclose(fArestas);

    // Imprime o grafo e executa as buscas DFS e BFS
    printf("Grafo criado com %d vértices:\n", numVertices);
    imprimir_grafo(grafo);

    int verticeInicialDFS = 0;
    // Verifica se o grafo não está vazio e se o vértice inicial é válido para DFS
    // Se o grafo estiver vazio ou o vértice inicial for inválido, exibe uma mensagem de erro
    if (numVertices > 0 && verticeInicialDFS < numVertices) {
        DFS(grafo, verticeInicialDFS);
    } else {
        printf("Não é possível realizar DFS: grafo vazio ou vértice inicial inválido.\n");
    }

    int verticeInicialBFS = 0;
    // Verifica se o grafo não está vazio e se o vértice inicial é válido para BFS
    // Se o grafo estiver vazio ou o vértice inicial for inválido, exibe uma mensagem de erro
    if (numVertices > 0 && verticeInicialBFS < numVertices) {
        BFS(grafo, verticeInicialBFS);
    } else {
        printf("Não é possível realizar BFS: grafo vazio ou vértice inicial inválido.\n");
    }

    // PARTE OPCIONAL: Teste das funções de busca com destino
    printf("\n========== PARTE OPCIONAL: BUSCA COM DESTINO ==========\n");
    
    // Define os vértices de origem e destino para os testes
    int origem_teste = 0;
    int destino_teste = 8;
    
    // Testa DFS com destino - pode não encontrar o caminho mais curto
    if (numVertices > 0 && origem_teste < numVertices && destino_teste < numVertices) {
        DFS_com_destino(grafo, origem_teste, destino_teste);
    }
    
    // Testa BFS com destino - sempre encontra o caminho mais curto
    if (numVertices > 0 && origem_teste < numVertices && destino_teste < numVertices) {
        BFS_com_destino(grafo, origem_teste, destino_teste);
    }
    
    // Teste adicional com origem e destino diferentes
    printf("\n--- Teste adicional: origem=1, destino=9 ---\n");
    origem_teste = 1;
    destino_teste = 9;
    
    if (numVertices > 0 && origem_teste < numVertices && destino_teste < numVertices) {
        DFS_com_destino(grafo, origem_teste, destino_teste);
        BFS_com_destino(grafo, origem_teste, destino_teste);
    }

    // Liberar a memória alocada para o grafo
    for (int i = 0; i < grafo->num_vertices; i++) {
        Elemento* atual = grafo->adj[i];
        while (atual) {
            Elemento* proximo = atual->prox;
            free(atual);
            atual = proximo;
        }
    }
    free(grafo->adj);
    free(grafo);

    return 0;
}