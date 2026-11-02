/* Estudo historico de min/max em vetor dinamico (2022).
 * Entrada validada; nenhum dado persistido. Fonte anterior preservado no Git.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX_DIM 100000

/* 0=sucesso; -1=vetor vazio ou ponteiro invalido. */
int miniMax(const int *vetor, size_t n, int *menor, int *maior) {
    if (!vetor || !n || !menor || !maior) return -1;
    int min = vetor[0], max = vetor[0];
    for (size_t i=1; i<n; ++i) {
        if (vetor[i] < min) min = vetor[i];
        if (vetor[i] > max) max = vetor[i];
    }
    *menor = min;
    *maior = max;
    return 0;
}

int main(void) {
    int dim;
    printf("PROGRAMA miniMax\nDIM (1..%d): ", MAX_DIM);
    fflush(stdout);
    if (scanf("%d", &dim) != 1 || dim < 1 || dim > MAX_DIM) {
        fputs("Dimensao invalida. Informe inteiro positivo no limite.\n", stderr);
        return 1;
    }
    int *vetor = malloc((size_t)dim * sizeof *vetor);
    if (!vetor) { perror("malloc"); return 1; }
    printf("Informe %d valores inteiros:\n", dim);
    for (int i=0; i<dim; ++i) {
        if (scanf("%d", &vetor[i]) != 1) {
            fputs("Entrada de componente invalida.\n", stderr);
            free(vetor);
            return 1;
        }
    }
    int menor, maior;
    if (miniMax(vetor, (size_t)dim, &menor, &maior) != 0) {
        free(vetor);
        return 1;
    }
    printf("O menor valor entre as componentes e: %d.\n", menor);
    printf("O maior valor entre as componentes e: %d.\n", maior);
    free(vetor);
    return 0;
}
