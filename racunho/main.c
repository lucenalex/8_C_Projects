/* Rascunho didatico: 20 ponteiros compartilham uma mesma string.
 * A vida util do bloco referenciado deve durar ate a liberação do vetor.
 * Nao alocar/ liberar um bloco diferente para cada alias.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
    const size_t n = 20, capacidade = 15;
    char *nome = calloc(capacidade, sizeof *nome);
    char **pos = calloc(n, sizeof *pos);
    if (!nome || !pos) {
        perror("calloc");
        free(nome);
        free(pos);
        return 1;
    }
    snprintf(nome, capacidade, "%s", "Exemplo");
    for (size_t i=0; i<n; ++i) pos[i] = nome;
    for (size_t i=0; i<n; ++i) {
        if (pos[i] != nome || strcmp(pos[i], "Exemplo") != 0) {
            free(pos); free(nome);
            return 1;
        }
    }
    printf("%zu ponteiros compartilham o mesmo texto: %s\n", n, pos[0]);
    free(pos);
    free(nome);
    return 0;
}
