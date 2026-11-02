#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Controle acadêmico didático: cadastro, disciplinas e médias.
 * Preserva a finalidade declarada no projeto de 2022, corrigindo índices
 * incorretos, uso de gets, acesso a aluno[indice] e falta de desalocação.
 */
#define MAX_ALUNOS 30
#define NUM_DISCIPLINAS 3

typedef struct { const char *nome; float media; int matriculado; } Disciplina;
typedef struct { char nome[76]; int matricula; Disciplina disc[NUM_DISCIPLINAS]; } Aluno;
static const char *nomes[NUM_DISCIPLINAS] = {"POO", "AOC", "MATDISC"};
static int ler_inteiro(const char *mensagem, int *valor) {
    char linha[128], *fim;
    long v;
    for (;;) {
        fputs(mensagem, stdout);
        if (!fgets(linha, sizeof linha, stdin)) return 0;
        size_t comprimento = strcspn(linha, "\n");
        if (linha[comprimento] != '\n' && !feof(stdin)) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            puts("Entrada muito longa; tente novamente.");
            continue;
        }
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

static int ler_nome(char *destino, size_t capacidade) {
    char linha[256];
    fputs("Nome do aluno: ", stdout);
    if (!fgets(linha, sizeof linha, stdin)) return 0;
    size_t tam = strcspn(linha, "\n");
    if (linha[tam] != '\n' && !feof(stdin)) {
        int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
    }
    if (tam == 0 || tam >= capacidade) {
        puts("Nome vazio ou longo demais."); return -1;
    }
    memcpy(destino, linha, tam);
    destino[tam] = '\0';
    return 1;
}
static int ler_nota(float *valor) {
    char linha[128], *fim;
    float v;
    for (;;) {
        fputs("Média (0 a 10): ", stdout);
        if (!fgets(linha, sizeof linha, stdin)) return 0;
        size_t comprimento = strcspn(linha, "\n");
        if (linha[comprimento] != '\n' && !feof(stdin)) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            puts("Entrada muito longa; tente novamente.");
            continue;
        }
        errno = 0; v = strtof(linha, &fim);
        while (isspace((unsigned char)*fim)) fim++;
        if (errno == 0 && fim != linha && *fim == '\0' && v >= 0.f && v <= 10.f) {
            *valor = v; return 1;
        }
        puts("Média inválida.");
    }
}
static Aluno *localizar(Aluno *alunos, int n, int matricula) {
    for (int i = 0; i < n; ++i) if (alunos[i].matricula == matricula) return &alunos[i];
    return NULL;
}
int main(void) {
    Aluno *alunos = calloc(MAX_ALUNOS, sizeof *alunos);
    int total = 0, opcao;
    if (!alunos) { fputs("Sem memória.\n", stderr); return 1; }
    puts("Controle acadêmico — POO, AOC e MATDISC.");
    for (;;) {
        puts("1 Cadastrar aluno | 2 Matricular em disciplina | 3 Informar média | 4 Boletim | 5 Sair");
        if (!ler_inteiro("Opção: ", &opcao)) break;
        if (opcao == 5) break;
        if (opcao == 1) {
            if (total == MAX_ALUNOS) { puts("Limite de 30 alunos atingido."); continue; }
            int ok = ler_nome(alunos[total].nome, sizeof alunos[total].nome);
            if (ok == 0) break;
            if (ok < 0) continue;
            alunos[total].matricula = total + 1;
            for (int j = 0; j < NUM_DISCIPLINAS; ++j)
                alunos[total].disc[j] = (Disciplina){nomes[j], 0.f, 0};
            printf("Matrícula: %d\n", ++total);
            continue;
        }
        if (opcao >= 2 && opcao <= 4) {
            if (total == 0) { puts("Cadastre um aluno primeiro."); continue; }
            int matricula;
            if (!ler_inteiro("Matrícula: ", &matricula)) break;
            Aluno *aluno = localizar(alunos, total, matricula);
            if (!aluno) { puts("Matrícula inexistente."); continue; }
            if (opcao == 4) {
                float soma = 0.f; int n = 0;
                printf("Boletim de %s (matrícula %d):\n", aluno->nome, matricula);
                for (int j = 0; j < NUM_DISCIPLINAS; ++j) {
                    if (aluno->disc[j].matriculado) {
                        printf("%s: %.2f\n", nomes[j], aluno->disc[j].media);
                        soma += aluno->disc[j].media; ++n;
                    }
                }
                if (n) printf("Média geral: %.2f\n", soma / n);
                else puts("Sem disciplinas matriculadas.");
                continue;
            }
            int indice;
            if (!ler_inteiro("Disciplina (1 POO, 2 AOC, 3 MATDISC): ", &indice)) break;
            if (indice < 1 || indice > NUM_DISCIPLINAS) { puts("Disciplina inválida."); continue; }
            Disciplina *d = &aluno->disc[indice - 1];
            if (opcao == 2) { d->matriculado = 1; puts("Matrícula realizada."); }
            else if (!d->matriculado) puts("Aluno não matriculado nesta disciplina.");
            else if (!ler_nota(&d->media)) break;
            else puts("Média registrada.");
        } else puts("Opção inválida.");
    }
    free(alunos);
    return 0;
}
