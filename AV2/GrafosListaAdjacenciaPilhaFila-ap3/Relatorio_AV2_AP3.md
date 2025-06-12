# Relatório - AV2: AP3

## Desafio de Programação: Implementação de Pilha e Fila nos algoritmos DFS e BFS

**Aluno:** [Guilherme Augusto Montalvão]  
**Data:** [02 junho de 2025]

---

### 1.b) Prints das Saídas dos Algoritmos

#### Saída do Algoritmo DFS (Busca em Profundidade):

```
Busca em Profundidade (DFS) a partir do vértice 0:
[ 0 ]
Vertice atual: 0
[ ]
[ 5 ]
[ 5 ][ 4 ]
[ 5 ][ 4 ][ 3 ]
[ 5 ][ 4 ][ 3 ][ 2 ]
[ 5 ][ 4 ][ 3 ][ 2 ][ 1 ]
Vertice atual: 1
[ 5 ][ 4 ][ 3 ][ 2 ]
[ 9 ][ 5 ][ 4 ][ 3 ][ 2 ]
[ 7 ][ 9 ][ 5 ][ 4 ][ 3 ][ 2 ]
[ 6 ][ 7 ][ 9 ][ 5 ][ 4 ][ 3 ][ 2 ]
Vertice atual: 6
[ 7 ][ 9 ][ 5 ][ 4 ][ 3 ][ 2 ]
[ 8 ][ 7 ][ 9 ][ 5 ][ 4 ][ 3 ][ 2 ]
Vertice atual: 8
[ 7 ][ 9 ][ 5 ][ 4 ][ 3 ][ 2 ]
Vertice atual: 7
[ 9 ][ 5 ][ 4 ][ 3 ][ 2 ]
Vertice atual: 9
[ 5 ][ 4 ][ 3 ][ 2 ]
Vertice atual: 2
[ 5 ][ 4 ][ 3 ]
Vertice atual: 3
[ 5 ][ 4 ]
Vertice atual: 4
[ 5 ]
Vertice atual: 5
[ ]
```

**Ordem de visitação DFS:** 0 → 1 → 6 → 8 → 7 → 9 → 2 → 3 → 4 → 5

#### Saída do Algoritmo BFS (Busca em Largura):

```
Busca em Largura (BFS) a partir do vértice 0:
[ 0 ]
Vertice atual: 0
[ ]
[ 5 ]
[ 5 ][ 4 ]
[ 5 ][ 4 ][ 3 ]
[ 5 ][ 4 ][ 3 ][ 2 ]
[ 5 ][ 4 ][ 3 ][ 2 ][ 1 ]
Vertice atual: 5
[ 4 ][ 3 ][ 2 ][ 1 ]
Vertice atual: 4
[ 3 ][ 2 ][ 1 ]
[ 3 ][ 2 ][ 1 ][ 7 ]
[ 3 ][ 2 ][ 1 ][ 7 ][ 6 ]
Vertice atual: 3
[ 2 ][ 1 ][ 7 ][ 6 ]
[ 2 ][ 1 ][ 7 ][ 6 ][ 8 ]
Vertice atual: 2
[ 1 ][ 7 ][ 6 ][ 8 ]
[ 1 ][ 7 ][ 6 ][ 8 ][ 9 ]
Vertice atual: 1
[ 7 ][ 6 ][ 8 ][ 9 ]
Vertice atual: 7
[ 6 ][ 8 ][ 9 ]
Vertice atual: 6
[ 8 ][ 9 ]
Vertice atual: 8
[ 9 ]
Vertice atual: 9
[ ]
```

**Ordem de visitação BFS:** 0 → 5 → 4 → 3 → 2 → 1 → 7 → 6 → 8 → 9

---

### 1.c) Análise e Comparação entre DFS e BFS

#### Diferenças entre as Saídas:

A principal diferença entre as saídas dos algoritmos DFS e BFS está na **ordem de visitação dos vértices**:

1. **DFS (Depth-First Search - Busca em Profundidade):**

   - Visitou os vértices na ordem: 0 → 1 → 6 → 8 → 7 → 9 → 2 → 3 → 4 → 5
   - O algoritmo "mergulhou" profundamente no grafo, seguindo um caminho até o fim antes de voltar
   - Começou em 0, foi para 1, depois explorou completamente o caminho 1→6→8 antes de voltar

2. **BFS (Breadth-First Search - Busca em Largura):**
   - Visitou os vértices na ordem: 0 → 5 → 4 → 3 → 2 → 1 → 7 → 6 → 8 → 9
   - O algoritmo visitou primeiro todos os vizinhos diretos de 0 (5, 4, 3, 2, 1)
   - Depois visitou os vizinhos dos vizinhos (7, 6, 8, 9)

#### Influência das Estruturas de Dados:

**Pilha (Stack) no DFS:**

- A pilha segue o princípio **LIFO** (Last In, First Out - Último a Entrar, Primeiro a Sair)
- Quando um vértice é descoberto, seus vizinhos são empilhados
- O próximo vértice a ser explorado é sempre o último adicionado (topo da pilha)
- Isso faz com que o algoritmo explore **profundamente** um caminho antes de voltar e explorar outros
- É como explorar um labirinto sempre virando para a primeira passagem disponível e só voltando quando encontra um beco sem saída

**Fila (Queue) no BFS:**

- A fila segue o princípio **FIFO** (First In, First Out - Primeiro a Entrar, Primeiro a Sair)
- Quando um vértice é descoberto, seus vizinhos são enfileirados no final
- O próximo vértice a ser explorado é sempre o primeiro da fila
- Isso garante que todos os vértices a uma distância k sejam visitados antes dos vértices a distância k+1
- É como uma onda que se propaga uniformemente a partir do vértice inicial, explorando todos os vértices por "camadas" ou "níveis"

#### Conclusão:

A escolha entre pilha e fila determina fundamentalmente o comportamento do algoritmo de busca. O DFS com pilha é ideal para problemas que requerem exploração completa de caminhos (como encontrar ciclos ou caminhos específicos), enquanto o BFS com fila é perfeito para encontrar o caminho mais curto em grafos não ponderados ou explorar sistematicamente por níveis de distância.

---

### Implementações Realizadas:

As seguintes funções foram implementadas no arquivo `grafo.c`:

1. **push()** - Adiciona elemento no topo da pilha
2. **pop()** - Remove e retorna elemento do topo da pilha
3. **enfileira()** - Adiciona elemento no final da fila
4. **desenfileira()** - Remove e retorna elemento do início da fila

Todas as implementações seguem as especificações das estruturas de dados e garantem o funcionamento correto dos algoritmos DFS e BFS.
