#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Exercício de alocação dinâmica e escrita de registros binários de 15 bytes.
 * Os nomes são dados fictícios; o programa não usa arquivos pessoais reais.
 */
#define LIMITE 20
#define TAM_NOME 15

/* 1: linha lida; 0: EOF; -1: excede a capacidade do destino. */
static int ler_linha(char *destino, size_t capacidade) {
    char linha[256];
    if (!fgets(linha, sizeof linha, stdin)) return 0;
    size_t n = strcspn(linha, "\n");
    if (linha[n] != '\n' && !feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        return -1;
    }
    if (n && linha[n - 1] == '\r') --n;
    if (n >= capacidade) return -1;
    memcpy(destino, linha, n);
    destino[n] = '\0';
    return 1;
}

int main(void) {
    char (*nomes)[TAM_NOME] = calloc(LIMITE, sizeof *nomes);
    if (!nomes) {
        perror("calloc");
        return 1;
    }
    size_t quantidade = 0;
    char escolha[16];
    puts("NOMES MASCULINOS — registro binário de nomes fictícios.");
    while (quantidade < LIMITE) {
        printf("Digite um nome (%zu de %d, até %d bytes): ",
               quantidade + 1, LIMITE, TAM_NOME - 1);
        fflush(stdout);
        int lido = ler_linha(nomes[quantidade], sizeof nomes[quantidade]);
        if (lido == 0) break;
        if (lido < 0) {
            puts("Nome muito longo; tente novamente.");
            continue;
        }
        if (!nomes[quantidade][0]) {
            puts("Nome vazio; tente novamente.");
            continue;
        }
        ++quantidade;
        if (quantidade == LIMITE) break;
        printf("Cadastrar outro nome? 1=sim, outro=não: ");
        fflush(stdout);
        lido = ler_linha(escolha, sizeof escolha);
        if (lido == 0) break;
        if (lido < 0 || strcmp(escolha, "1") != 0) break;
    }
    if (!quantidade) {
        puts("Nenhum nome cadastrado; nenhum arquivo foi criado.");
        free(nomes);
        return 0;
    }
    FILE *arquivo = fopen("nomes_masculinos.bin", "wb");
    if (!arquivo) {
        perror("nomes_masculinos.bin");
        free(nomes);
        return 1;
    }
    size_t gravados = fwrite(nomes, sizeof nomes[0], quantidade, arquivo);
    int falhou = gravados != quantidade;
    if (fclose(arquivo) != 0) falhou = 1;
    if (falhou) {
        fputs("Falha ao gravar o arquivo binário.\n", stderr);
        free(nomes);
        return 1;
    }
    for (size_t i = 0; i < quantidade; ++i)
        printf("nome[%zu]: %s\n", i, nomes[i]);
    printf("%zu nomes gravados em registros de %d bytes.\n",
           quantidade, TAM_NOME);
    free(nomes);
    return 0;
}
