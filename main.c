#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprimirVetor(int vetor[], size_t tam) {
    printf("Vetor: ");
    for (size_t i = 0; i < tam; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL)); // Inicializa a semente para números aleatórios com o tempo atual

    char nome[MAX_CHAR_NOME];
    uint32_t grr;
    getNome(nome);
    grr = getGRR();
    printf("Nome: %s\nGRR: %u\n\n", nome, grr);
    
    // Solicita ao usuário o tamanho do vetor
    size_t tam;
    printf("Digite o tamanho do vetor a ser ordenado: ");
    scanf("%lu", &tam);

    // Aloca memória para o vetor
    int *vetor = (int *)malloc(tam * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memória para o vetor.\n");
        return 1;
    }

    // Preenche o vetor com números aleatórios entre 0 e 99
    for (size_t i = 0; i < tam; i++) {
        vetor[i] = rand() % 100; // Números aleatórios entre 0 e 99
    }

    // Pergunta ao usuário se ele deseja ver o vetor original
    int verVetor;
    printf("Deseja ver o vetor original? (1 para sim, 0 para não): ");
    scanf("%d", &verVetor);

    // Se o usuário quiser ver o vetor e o tamanho do vetor for no máximo 10, imprime o vetor original
    if (verVetor)
        imprimirVetor(vetor, tam);

    // Declara variáveis para armazenar o uso de memória, tempo de execução e número de comparações
    long memoria;
    uint64_t comparacoes;

    // Mede o tempo de execução, uso de memória e número de comparações para cada método de ordenação
    printf("\n=== Resultados da Ordenação ===\n");

    printf("\nInsertion Sort Recursivo: ");
    comparacoes = medirTempo(insertionSortRec, vetor, tam, &memoria);

    printf("\nInsertion Sort Iterativo: ");
    comparacoes = medirTempo(insertionSort, vetor, tam, &memoria);

    printf("\nSelection Sort Recursivo: ");
    comparacoes = medirTempo(selectionSortRec, vetor, tam, &memoria);

    printf("\nSelection Sort Iterativo: ");
    comparacoes = medirTempo(selectionSort, vetor, tam, &memoria);

    printf("\nMerge Sort Recursivo: ");
    comparacoes = medirTempo(mergeSortRec, vetor, tam, &memoria);

    mergeSortRec(vetor, tam); // Ordena o vetor

    // Pergunta ao usuário se ele deseja ver o vetor ordenado
    int verVetorOrdenado;
    printf("Deseja ver o vetor ordenado? (1 para sim, 0 para não): ");
    scanf("%d", &verVetorOrdenado);

    // Se o usuário quiser ver o vetor ordenado e o tamanho do vetor for no máximo 10, imprime o vetor ordenado
    if (verVetorOrdenado)
        imprimirVetor(vetor, tam);

    // Realiza a pesquisa usando os quatro métodos de busca
    printf("\n=== Resultados da Pesquisa ===\n");
    // Solicitar ao usuário um valor para buscar no vetor
    printf("Digite um número para pesquisar no vetor: ");
    int valor;
    scanf("%d", &valor);

    // Variável para armazenar o número de comparações feitas pelas funções de busca
    uint64_t numComparacoes;

    // Busca Sequencial Recursiva
    numComparacoes = 0;  // Importante inicializar antes de cada chamada
    ssize_t posicao = buscaSequencialRec(vetor, tam, valor, &numComparacoes);
    printf("Busca Sequencial Recursiva: Valor %d encontrado na posição %ld. Comparacoes: %lu\n", valor, posicao, numComparacoes);

    // Busca Sequencial Iterativa
    numComparacoes = 0;  // Reinicializar antes da chamada
    posicao = buscaSequencial(vetor, tam, valor, &numComparacoes);
    printf("Busca Sequencial Iterativa: Valor %d encontrado na posição %ld. Comparacoes: %lu\n", valor, posicao, numComparacoes);

    // Busca Binária Recursiva
    // Nota: O vetor deve estar ordenado para usar busca binária
    numComparacoes = 0;  // Reinicializar antes da chamada
    posicao = buscaBinariaRec(vetor, tam, valor, &numComparacoes);
    printf("Busca Binária Recursiva: Valor %d encontrado na posição %ld. Comparacoes: %lu\n", valor, posicao, numComparacoes);

    // Busca Binária Iterativa
    numComparacoes = 0;  // Reinicializar antes da chamada
    posicao = buscaBinaria(vetor, tam, valor, &numComparacoes);
    printf("Busca Binária Iterativa: Valor %d encontrado na posição %ld. Comparacoes: %lu\n", valor, posicao, numComparacoes);
    
    // Libera a memória alocada para o vetor
    free(vetor);

    return 0;
}
