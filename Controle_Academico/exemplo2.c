#include <stdio.h>
#include <stdlib.h>

#define MAX 3
typedef struct {
    char nome[21];
    float salario;
} Funcionario;

int main(void) {
    Funcionario *pessoas = calloc(MAX, sizeof *pessoas);
    if (!pessoas) { fputs("Erro de memória.\n", stderr); return 1; }
    for (int i = 0; i < MAX; ++i) {
        printf("Nome: ");
        if (scanf("%20s", pessoas[i].nome) != 1) { free(pessoas); return 1; }
        printf("Salário: ");
        if (scanf("%f", &pessoas[i].salario) != 1) { free(pessoas); return 1; }
    }
    for (int i = 0; i < MAX; ++i)
        printf("Nome: %s | Salário: %.2f\n", pessoas[i].nome, pessoas[i].salario);
    free(pessoas);
    return 0;
}
