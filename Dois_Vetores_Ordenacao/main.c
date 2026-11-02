#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Atividade original: dois vetores de oito elementos e buscas.
 * A versão anterior continha estruturas de cadastro, alheias ao enunciado.
 * Código didático: valores ordenados crescentemente antes da busca binária.
 */
#define TAM 8
static int ler_inteiro(const char *mensagem, int *valor) {
    char linha[128], *fim;
    long v;
    for (;;) {
        fputs(mensagem, stdout);
        if (!fgets(linha, sizeof linha, stdin)) return 0;
        errno = 0;
        v = strtol(linha, &fim, 10);
        while (isspace((unsigned char)*fim)) fim++;
        if (errno == 0 && fim != linha && *fim == '\0' && v >= INT_MIN && v <= INT_MAX) {
            *valor = (int)v;
            return 1;
        }
        puts("Entrada inválida: informe um número inteiro.");
    }
}

static int comparar(const void *a, const void *b) {
    int x = *(const int*)a, y = *(const int*)b;
    return (x > y) - (x < y);
}
static int preencher(int vetor[TAM], int ordenado) {
    for (int i = 0; i < TAM; ++i) {
        char pergunta[80];
        snprintf(pergunta, sizeof pergunta, "Elemento %d/%d: ", i + 1, TAM);
        if (!ler_inteiro(pergunta, &vetor[i])) return 0;
    }
    if (ordenado) qsort(vetor, TAM, sizeof vetor[0], comparar);
    return 1;
}
static int busca_sequencial(const int vetor[TAM], int alvo) {
    for (int i = 0; i < TAM; ++i) if (vetor[i] == alvo) return i;
    return -1;
}
static int busca_binaria(const int vetor[TAM], int alvo) {
    int esquerda = 0, direita = TAM - 1;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        if (vetor[meio] == alvo) return meio;
        if (vetor[meio] < alvo) esquerda = meio + 1;
        else direita = meio - 1;
    }
    return -1;
}
static void imprimir(const int vetor[TAM]) {
    putchar('{');
    for (int i = 0; i < TAM; ++i) printf("%s%d", i ? ", " : "", vetor[i]);
    puts("}");
}
int main(void) {
    int vetor1[TAM] = {0}, vetor2[TAM] = {0};
    int pronto1 = 0, pronto2 = 0, opcao, alvo, pos;
    puts("Dois vetores: busca sequencial e binária.");
    for (;;) {
        puts("1 Preencher vetor 1 | 2 Preencher vetor 2 | 3 Busca sequencial");
        puts("4 Busca binária | 5 Imprimir vetor 1 | 6 Imprimir vetor 2 | 7 Sair");
        if (!ler_inteiro("Opção: ", &opcao)) return 0;
        switch (opcao) {
            case 1: if (!preencher(vetor1, 0)) return 0; pronto1 = 1; break;
            case 2: if (!preencher(vetor2, 1)) return 0; pronto2 = 1; break;
            case 3:
            case 4:
                if ((opcao == 3 && !pronto1) || (opcao == 4 && !pronto2)) {
                    puts("Preencha primeiro o vetor correspondente.");
                    break;
                }
                if (!ler_inteiro("Valor a buscar: ", &alvo)) return 0;
                pos = (opcao == 3) ? busca_sequencial(vetor1, alvo) : busca_binaria(vetor2, alvo);
                if (pos < 0) puts("Valor não encontrado.");
                else printf("Valor %d encontrado na posição %d (índice começando em zero).\n", alvo, pos);
                break;
            case 5: if (pronto1) imprimir(vetor1); else puts("Vetor 1 vazio."); break;
            case 6: if (pronto2) imprimir(vetor2); else puts("Vetor 2 vazio."); break;
            case 7: return 0;
            default: puts("Opção inválida.");
        }
    }
}
