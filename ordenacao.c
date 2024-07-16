#include "ordenacao.h" // Inclui o arquivo de cabeçalho ordenacao.h, que contém as declarações das funções de ordenação
#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída
#include <stddef.h> // Inclui definições de tipos e macros para trabalhar com ponteiros e tamanho de objetos
#include <stdlib.h> // Inclui funções para alocação de memória, controle de processos e outras operações de sistema
#include <time.h> // Inclui funções e tipos relacionados ao tempo
#include <sys/resource.h> // Inclui definições relacionadas a recursos do sistema, como uso de CPU e memória

void getNome(char nome[]) {
    snprintf(nome, MAX_CHAR_NOME, "Marcello Eduardo Pereira Jorge"); // Preenche a string 'nome' com o nome completo
}

uint32_t getGRR() {
    return 20244350; // Retorna o número de GRR do estudante
}

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp; // Troca os valores das variáveis apontadas por 'a' e 'b'
}

// Funções de busca

ssize_t buscaSequencialRec(int vetor[], size_t tam, int valor,
                           uint64_t* numComparacoes) {
    if (tam == 0) {
        return -1; // Se o tamanho do vetor for 0, retorna -1 indicando que o valor não foi encontrado
    }
    *numComparacoes += 1; // Incrementa o contador de comparações
    if (vetor[0] == valor) {
        return 0; // Se o primeiro elemento do vetor for igual ao valor, retorna o índice 0
    }
    ssize_t pos = buscaSequencialRec(vetor + 1, tam - 1, valor, numComparacoes); // Chama recursivamente a função para o restante do vetor
    if (pos == -1) {
        return -1; // Se o valor não foi encontrado no restante do vetor, retorna -1
    }
    *numComparacoes += 1; // Incrementa o contador de comparações
    return pos + 1; // Retorna a posição encontrada mais 1 (devido à recursão)
}

ssize_t buscaSequencial(int vetor[], size_t tam, int valor,
                        uint64_t* numComparacoes) {
    *numComparacoes = 0; // Inicializa o contador de comparações
    for (size_t i = 0; i < tam; i++) { // Percorre o vetor
        *numComparacoes += 1; // Incrementa o contador de comparações
        if (vetor[i] == valor) {
            return i; // Se o valor for encontrado, retorna o índice
        }
    }
    return -1; // Se o valor não for encontrado, retorna -1
}

ssize_t buscaBinariaRec(int vetor[], size_t tam, int valor,
                        uint64_t* numComparacoes) {
    if (tam == 0) {
        return -1; // Se o tamanho do vetor for 0, retorna -1 indicando que o valor não foi encontrado
    }
    *numComparacoes += 1; // Incrementa o contador de comparações
    size_t meio = tam / 2; // Calcula o índice do elemento do meio do vetor
    if (vetor[meio] == valor) {
        return meio; // Se o valor for igual ao elemento do meio, retorna o índice do meio
    }
    if (vetor[meio] < valor) { // Se o valor for maior que o elemento do meio
        ssize_t pos = buscaBinariaRec(vetor + meio + 1, tam - meio - 1, valor, numComparacoes); // Chama recursivamente a função para o subvetor à direita
        if (pos == -1) {
            return -1; // Se o valor não foi encontrado no subvetor à direita, retorna -1
        }
        *numComparacoes += pos + 1; // Incrementa o contador de comparações
        return pos + meio + 1; // Retorna a posição encontrada mais o índice do meio
    }
    ssize_t pos = buscaBinariaRec(vetor, meio, valor, numComparacoes); // Se o valor for menor que o elemento do meio, chama recursivamente a função para o subvetor à esquerda
    if (pos == -1) {
        return -1; // Se o valor não foi encontrado no subvetor à esquerda, retorna -1
    }
    *numComparacoes += tam - meio; // Incrementa o contador de comparações
    return pos; // Retorna a posição encontrada
}

ssize_t buscaBinaria(int vetor[], size_t tam, int valor,
                     uint64_t* numComparacoes) {
    *numComparacoes = 0; // Inicializa o contador de comparações
    size_t inicio = 0; // Define o índice de início como 0
    size_t fim = tam - 1; // Define o índice de fim como o último elemento do vetor
    while (inicio <= fim) { // Enquanto houver elementos no vetor para pesquisar
        *numComparacoes += 1; // Incrementa o contador de comparações
        size_t meio = (inicio + fim) / 2; // Calcula o índice do elemento do meio do vetor
        if (vetor[meio] == valor) {
            return meio; // Se o valor for igual ao elemento do meio, retorna o índice do meio
        }
        if (vetor[meio] < valor) {
            inicio = meio + 1; // Se o valor for maior que o elemento do meio, redefine o índice de início para o próximo elemento à direita
        } else {
            fim = meio - 1; // Se o valor for menor que o elemento do meio, redefine o índice de fim para o próximo elemento à esquerda
        }
    }
    return -1; // Se o valor não for encontrado, retorna -1
}

// Funções de ordenação

uint64_t insertionSortRec(int vetor[], size_t tam) {
    if (tam <= 1)
        return 0; // Caso base: vetor com tamanho 1 ou vazio

    int chave = vetor[tam - 1]; // Seleciona o último elemento do vetor como chave
    size_t j = tam - 2; // Inicializa o índice j como o penúltimo elemento do vetor
    uint64_t comparacoes = 0; // Inicializa o contador de comparações

    while (j >= 0 && vetor[j] > chave) { // Enquanto j não for negativo e o elemento atual for maior que a chave
        comparacoes++; // Incrementa o contador de comparações
        vetor[j + 1] = vetor[j]; // Move o elemento atual para a direita
        j--; // Decrementa o índice j
    }
    vetor[j + 1] = chave; // Insere a chave na posição correta

    return comparacoes + insertionSortRec(vetor, tam - 1); // Chama recursivamente a função para o restante do vetor
}

uint64_t insertionSort(int vetor[], size_t tam) {
    int *temp = malloc(tam * sizeof(int)); // Aloca memória para um vetor temporário
    if (temp == NULL) {
        return 0; // Retorna 0 se a alocação de memória falhar
    }

    for (size_t i = 0; i < tam; i++) {
        temp[i] = vetor[i]; // Copia os elementos do vetor original para o vetor temporário
    }

    uint64_t comparacoes = 0; // Inicializa o contador de comparações
    for (size_t i = 1; i < tam; i++) { // Percorre o vetor a partir do segundo elemento
        int chave = temp[i]; // Seleciona o elemento atual como chave
        ssize_t j = i - 1; // Inicializa o índice j como o elemento anterior ao atual
        while (j >= 0 && temp[j] > chave) { // Enquanto j não for negativo e o elemento atual for maior que a chave
            comparacoes++; // Incrementa o contador de comparações
            temp[j + 1] = temp[j]; // Move o elemento atual para a direita
            j--; // Decrementa o índice j
        }
        temp[j + 1] = chave; // Insere a chave na posição correta
    }

    free(temp); // Libera a memória alocada para o vetor temporário
    return comparacoes; // Retorna o número total de comparações realizadas
}

uint64_t selectionSortRec(int vetor[], size_t tam) {
    if (tam <= 1)
        return 0; // Caso base: vetor com tamanho 1 ou vazio

    size_t idx_max = 0; // Inicializa o índice do elemento máximo como 0
    for (size_t i = 1; i < tam; i++) { // Percorre o vetor a partir do segundo elemento
        if (vetor[i] > vetor[idx_max])
            idx_max = i; // Atualiza o índice do elemento máximo se o elemento atual for maior
    }
    if (idx_max != tam - 1) {
        trocar(&vetor[idx_max], &vetor[tam - 1]); // Troca o elemento máximo com o último elemento do vetor
    }

    return tam - 1 + selectionSortRec(vetor, tam - 1); // Chama recursivamente a função para o restante do vetor
}

uint64_t selectionSort(int vetor[], size_t tam) {
    int *temp = malloc(tam * sizeof(int)); // Aloca memória para um vetor temporário
    if (temp == NULL) {
        return 0; // Retorna 0 se a alocação de memória falhar
    }

    for (size_t i = 0; i < tam; i++) {
        temp[i] = vetor[i]; // Copia os elementos do vetor original para o vetor temporário
    }

    uint64_t comparacoes = 0; // Inicializa o contador de comparações
    for (size_t i = 0; i < tam - 1; i++) { // Percorre o vetor até o penúltimo elemento
        size_t idx_min = i; // Inicializa o índice do elemento mínimo como o índice atual
        for (size_t j = i + 1; j < tam; j++) { // Percorre o restante do vetor
            comparacoes++; // Incrementa o contador de comparações
            if (temp[j] < temp[idx_min])
                idx_min = j; // Atualiza o índice do elemento mínimo se o elemento atual for menor
        }
        if (idx_min != i)
            trocar(&temp[i], &temp[idx_min]); // Troca o elemento mínimo com o elemento atual, se necessário
    }

    free(temp); // Libera a memória alocada para o vetor temporário
    return comparacoes; // Retorna o número total de comparações realizadas
}

// Função auxiliar para mesclar dois subvetores ordenados
static void merge(int vetor[], int inicio, int meio, int fim, uint64_t *comparacoes) {
    int tam_esq = meio - inicio + 1; // Calcula o tamanho do subvetor esquerdo
    int tam_dir = fim - meio; // Calcula o tamanho do subvetor direito

    // Aloca memória para os subvetores esquerdo e direito
    int *esq = malloc(tam_esq * sizeof(int));
    int *dir = malloc(tam_dir * sizeof(int));

    // Verifica se a alocação de memória foi bem-sucedida
    if (esq == NULL || dir == NULL) {
        if (esq != NULL)
            free(esq);
        if (dir != NULL)
            free(dir);
        return;
    }

    // Copia os elementos para os subvetores esquerdo e direito
    for (int i = 0; i < tam_esq; i++)
        esq[i] = vetor[inicio + i];
    for (int j = 0; j < tam_dir; j++)
        dir[j] = vetor[meio + 1 + j];

    int i = 0;
    int j = 0;
    int k = inicio;

    // Mescla os subvetores ordenados
    while (i < tam_esq && j < tam_dir) {
        (*comparacoes)++;
        if (esq[i] <= dir[j]) {
            vetor[k] = esq[i];
            i++;
        } else {
            vetor[k] = dir[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes do subvetor esquerdo, se houver
    while (i < tam_esq) {
        vetor[k] = esq[i];
        i++;
        k++;
    }

    // Copia os elementos restantes do subvetor direito, se houver
    while (j < tam_dir) {
        vetor[k] = dir[j];
        j++;
        k++;
    }

    // Libera a memória alocada para os subvetores esquerdo e direito
    free(esq);
    free(dir);
}

uint64_t mergeSortRec(int vetor[], size_t tam) {
    if (tam <= 1) {
        return 0; // Caso base: vetor com tamanho 1 ou vazio
    }

    uint64_t comparacoes = 0; // Inicializa o contador de comparações

    // Calcula o índice do elemento do meio
    size_t meio = tam / 2;

    // Chamadas recursivas para ordenar os subvetores esquerdo e direito
    comparacoes += mergeSortRec(vetor, meio);
    comparacoes += mergeSortRec(vetor + meio, tam - meio);

    // Mescla os subvetores ordenados
    merge(vetor, 0, meio - 1, tam - 1, &comparacoes);

    return comparacoes; // Retorna o número total de comparações realizadas
}

// Função para medir o tempo de execução e o uso de memória de uma função de ordenação
uint64_t medirTempo(uint64_t (funcaoOrdenacao)(int[], size_t), int vetor[], size_t tam, long *memoria) {
    clock_t start, end;
    double total;
    uint64_t comparacoes = 0;

    struct rusage usage_start, usage_end;

    getrusage(RUSAGE_SELF, &usage_start); // Obtém o uso de recursos no início da execução da função

    start = clock(); // Marca o tempo de início

    comparacoes = funcaoOrdenacao(vetor, tam); // Chama a função de ordenação e obtém o número de comparações

    end = clock(); // Marca o tempo de término

    getrusage(RUSAGE_SELF, &usage_end); // Obtém o uso de recursos no final da execução da função

    *memoria = usage_end.ru_maxrss - usage_start.ru_maxrss; // Calcula o uso de memória em bytes

    total = ((double)(end - start)) / CLOCKS_PER_SEC; // Calcula o tempo total de execução em segundos

    printf("Tempo total da função: %f segundos\n", total); // Imprime o tempo total de execução
    printf("Uso de memória da função: %ld bytes\n", *memoria); // Imprime o uso de memória em bytes
    printf("Número de comparações: %lu\n", comparacoes); // Imprime o número de comparações realizadas

    return comparacoes; // Retorna o número total de comparações realizadas
}
