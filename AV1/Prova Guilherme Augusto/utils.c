#include "utils.h"

/* 
    ATENÇÃO: Essa função deve ser implementada
*/ 

// Função para ajustar a nota entre 0 e 10
float ajustar_nota(float nota) {
    if (nota < 0.0) return 0.0;
    if (nota > 10.0) return 10.0;
    return nota;
}

void calcular_notas(Aluno *aluno) {
    //verifica se o aluno tem avaliações
    if (aluno->num_avaliacoes < 2) {
        return; //nao tem avaliaoces suficientes para calcular a nota final
    }

    //ajusta as notas para o intervalo de 0 a 10, < 0 = 0, > 10 = 10
    for (int i = 0; i < aluno->num_avaliacoes; i++) {
        aluno->avaliacoes[i].ap1 = ajustar_nota(aluno->avaliacoes[i].ap1);
        aluno->avaliacoes[i].ap2 = ajustar_nota(aluno->avaliacoes[i].ap2);
        aluno->avaliacoes[i].ap3 = ajustar_nota(aluno->avaliacoes[i].ap3);
        aluno->avaliacoes[i].np  = ajustar_nota(aluno->avaliacoes[i].np);
    }

    //calcula a media das notas de AV1 (primeira avaliacao)
    float av1 = (aluno->avaliacoes[0].ap1 + aluno->avaliacoes[0].ap2 + aluno->avaliacoes[0].ap3 + aluno->avaliacoes[0].np) / 4.0;
    //calcula a media das notas de AV2 (segunda avaliacao)
    float av2 = (aluno->avaliacoes[1].ap1 + aluno->avaliacoes[1].ap2 + aluno->avaliacoes[1].ap3 + aluno->avaliacoes[1].np) / 4.0;
    //calcula a nota final (media das duas avaliacoes)
    aluno->nf = (av1 + av2) / 2.0;

    //define o status do aluno (aprovado ou reprovado), o aluno é aprovado se a nota final for maior ou igual a 6.0 
    aluno->status = (aluno->nf >= 6.0) ? 1 : 0;
}

/* Função para calcular as notas finais do aluno
void calcular_notas(Aluno *aluno) {
    //verifica se o aluno tem avaliacoes
    if (aluno->num_avaliacoes < 2) {
        return; //nao tem avaliaoces suficientes para calcular a nota final
    }
    
    //calcula a media das notas de AV1 (primeira avaliacao)
    float av1 = (aluno->avaliacoes[0].ap1 + aluno->avaliacoes[0].ap2 + aluno->avaliacoes[0].ap3 + aluno->avaliacoes[0].np) / 4.0;
    //calcula a media das notas de AV2 (segunda avaliacao)
    float av2 = (aluno->avaliacoes[1].ap1 + aluno->avaliacoes[1].ap2 + aluno->avaliacoes[1].ap3 + aluno->avaliacoes[1].np) / 4.0;
    //calcula a nota final (media das duas avaliacoes)
    aluno->nf = (av1 + av2) / 2.0;
    
    //define o status do aluno (aprovado ou reprovado)
    //aprovado se a nota final for maior ou igual a 6.0
    aluno->status = (aluno->nf >= 6.0) ? 1 : 0;
}*/ 

/* 
    ATENÇÃO: Essa função deve ser implementada
*/ 
// Função para alocar ou realocar memória para o array de alunos
Aluno* realocar_memoria_aluno(Aluno *alunos, int novo_tamanho) {
    //realoca memoria para o array de alunos
    //realoca memória usando realloc e retorna o novo ponteiro
    return (Aluno*) realloc(alunos, novo_tamanho * sizeof(Aluno));
}

/* 
    ATENÇÃO: Essa função deve ser implementada
*/ 
// Função para alocar ou realocar memória para o array de avaliacoes
Avaliacao* realocar_memoria_avaliacao(Avaliacao *avaliacoes, int novo_tamanho) {
    //realoca memoria para o array de avaliacoes
    //realoca memoria usando realloc e retorna o novo ponteiro
    return (Avaliacao*) realloc(avaliacoes, novo_tamanho * sizeof(Avaliacao));
}

/* 
    ATENÇÃO: Essa função deve ser implementada
*/ 
// Função para liberar a memória alocada para os alunos
void liberar_memoria(Aluno *alunos, int num_alunos) {
    //verifica se o ponteiro para alunos é valido
    if (!alunos) {
        return;
    }
    
    //libera a memoria alocada para as avaliacoes de cada aluno
    for (int i = 0; i < num_alunos; i++) {
        if (alunos[i].avaliacoes) {
            free(alunos[i].avaliacoes);
            alunos[i].avaliacoes = NULL;
        }
    }
    
    //libera a memoria alocada para o array de alunos
    free(alunos);
}

/* 
    ATENÇÃO: Essa função deve ser implementada
*/ 
// Função para adicionar uma nova avaliação ao histórico de avaliações do aluno
void adicionar_avaliacoes(Aluno *aluno, Avaliacao avaliacao) {
    //realoca memoria para mais uma avaliacao
    Avaliacao *temp = realocar_memoria_avaliacao(aluno->avaliacoes, aluno->num_avaliacoes + 1);
    
    //verifica se a realocacao foi feito com sucesso
    if (!temp) {
        perror("Erro ao alocar memória para avaliações");
        return;
    }
    
    //atualiza o ponteiro para o array de avaliacoes
    aluno->avaliacoes = temp;
    //adiciona a nova avaliacao ao array
    aluno->avaliacoes[aluno->num_avaliacoes] = avaliacao; 
    //incrementa o nmero de avaliacoes
    aluno->num_avaliacoes++;
}

// Carrega os alunos do arquivo CSV e retorna um array de alunos
// O número de alunos é retornado através do ponteiro num_alunos
Aluno *carregar_alunos(const char *nome_arquivo, int *num_alunos) {
    // Abre o arquivo para leitura
    FILE *arquivo = fopen(nome_arquivo, "r"); 
    // Verifica se o arquivo foi aberto corretamente
    // Se não, imprime uma mensagem de erro e retorna NULL    
    if (!arquivo) { 
        perror("Erro ao abrir arquivo de alunos");
        return NULL;
    }

    Aluno *alunos   = NULL;                 // Inicializa o ponteiro para alunos
    char linha[256];                        // Buffer para ler cada linha do arquivo
    fgets(linha, sizeof(linha), arquivo);   // Ler e descartar o cabeçalho

    while (fgets(linha, sizeof(linha), arquivo)) { // Lê cada linha do arquivo
        Aluno novo_aluno;       // Inicializa um novo aluno
        Avaliacao avaliacao1;   // Inicializa a avaliação 1
        Avaliacao avaliacao2;   // Inicializa a avaliação 2
        // Lê os dados do aluno da linha e armazena em novo_aluno
        // O sscanf retorna o número de itens lidos com sucesso
        float av1ap1, av1ap2, av1ap3, np1, av2ap1, av2ap2, av2ap3, np2;
        if (sscanf(linha, "%d,%[^,],%f,%f,%f,%f,%f,%f,%f,%f", &novo_aluno.matricula, novo_aluno.nome, &avaliacao1.ap1,&avaliacao1.ap2, &avaliacao1.ap3, &avaliacao1.np, &avaliacao2.ap1, &avaliacao2.ap2,&avaliacao2.ap3, &avaliacao2.np) == 10) {

            /* 
                ATENÇÃO: Essa função deve ser implementada
            */             
            // Realoca memória para mais um aluno
            alunos = realocar_memoria_aluno(alunos, (*num_alunos + 1));

            // Verifica se a realocação foi bem-sucedida
            if (!alunos) {
                perror("Erro ao alocar memória para alunos");
                fclose(arquivo);
                return NULL;
            }

            // Adiciona o novo aluno ao array
            novo_aluno.avaliacoes = NULL; // Inicializa o histórico de avaliações
            novo_aluno.num_avaliacoes = 0; // Inicializa o número de avaliacoes

            /* 
                ATENÇÃO: Essa função deve ser implementada
            */             
            adicionar_avaliacoes(&novo_aluno, avaliacao1); // Adiciona a primeira avaliação
            adicionar_avaliacoes(&novo_aluno, avaliacao2); // Adiciona a segunda avaliação

            /* 
                ATENÇÃO: Essa função deve ser implementada
            */ 
            calcular_notas(&novo_aluno); // Calcula as notas do aluno

            // Adiciona o novo aluno ao array de alunos
            // O ponteiro alunos é atualizado para apontar para o novo array
            alunos[*num_alunos] = novo_aluno;
            (*num_alunos)++; // Incrementa o número de alunos

        } else { // Se a leitura falhar, imprime uma mensagem de erro
            fprintf(stderr, "Erro ao ler linha do arquivo de alunos: %s", linha);
        }
    }

    fclose(arquivo);
    return alunos;
}

// Função para ordenar os alunos por nota final (NF)
void ordenar_alunos(Aluno *alunos, int num_alunos) {
    for (int i = 0; i < num_alunos - 1; i++) {
        for (int j = 0; j < num_alunos - i - 1; j++) {
            if (alunos[j].nf < alunos[j + 1].nf) {
                Aluno temp = alunos[j];
                alunos[j] = alunos[j + 1];
                alunos[j + 1] = temp;
            }
        }
    }
}

void listar_alunos(const Aluno *alunos, int num_alunos) {
    if (num_alunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("\n");
    printf("%-10s| %-30s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-10s\n",
           " Matricula ", "Nome", "AV1:AP1", "AV1:AP2", "AV1:AP3", "NP1", "AV2:AP1", "AV2:AP2", "AV2:AP3", "NP2", "NF", "Status"); //correcao de nomes com caracteres especiais
    printf("-----------|--------------------------------|----------|----------|----------|----------|----------|----------|----------|----------|----------|------------\n");

    for (int i = 0; i < num_alunos; i++) {
        if (alunos[i].status == 0) { // Reprovado
            printf(RED_TEXT);
        }
        printf("%-10d | %-30s | %-8.2f | %-8.2f | %-8.2f | %-8.2f | %-8.2f | %-8.2f | %-8.2f | %-8.2f | %-8.2f | %-10s",
                alunos[i].matricula,
                alunos[i].nome,
                alunos[i].avaliacoes[0].ap1,
                alunos[i].avaliacoes[0].ap2,
                alunos[i].avaliacoes[0].ap3,
                alunos[i].avaliacoes[0].np,
                alunos[i].avaliacoes[1].ap1,
                alunos[i].avaliacoes[1].ap2,
                alunos[i].avaliacoes[1].ap3,
                alunos[i].avaliacoes[1].np,
                alunos[i].nf,
                alunos[i].status == 1 ? "Aprovado" : "Reprovado");
        if (alunos[i].status == 0) {
            printf(RESET_TEXT);
        }
        printf("\n");
    }
    printf("\n");
}

//validção das notas
//Se uma nota for menor que 0, ela devera ser ajustada para 0
//Se uma nota for maior que 10, ela deverá ser ajustada para 10.