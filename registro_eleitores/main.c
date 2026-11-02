#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Exercício didático de lista encadeada.
 * Usar apenas registros fictícios; nenhum dado real de eleitor é necessário.
 */
typedef struct Registro {
    int codigo;
    char nome[50];
    char instituicao[5];
    struct Registro *proximo;
} Registro;

static int ler_codigo(const char *mensagem, int *saida) {
    char texto[64], *fim;
    long v;
    fputs(mensagem, stdout);
    if (!fgets(texto, sizeof texto, stdin)) return 0;
    size_t tamanho = strcspn(texto, "\n");
    if (texto[tamanho] != '\n' && !feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        return -1;
    }
    errno = 0;
    v = strtol(texto, &fim, 10);
    if (errno || fim == texto || (*fim != '\n' && *fim != '\0') || v < 1 || v > INT_MAX)
        return -1;
    *saida = (int)v;
    return 1;
}
static int ler_texto(const char *mensagem, char *saida, size_t capacidade) {
    char linha[128];
    fputs(mensagem, stdout);
    if (!fgets(linha, sizeof linha, stdin)) return 0;
    size_t n = strcspn(linha, "\n");
    if (linha[n] != '\n' && !feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        puts("Texto vazio ou maior que o limite."); return -1;
    }
    if (n == 0 || n >= capacidade) {
        puts("Texto vazio ou maior que o limite."); return -1;
    }
    memcpy(saida, linha, n); saida[n] = '\0';
    return 1;
}
static Registro *buscar(Registro *inicio, int codigo) {
    for (Registro *p = inicio; p; p = p->proximo)
        if (p->codigo == codigo) return p;
    return NULL;
}
static Registro *excluir(Registro *inicio, int codigo) {
    Registro **cursor = &inicio;
    while (*cursor && (*cursor)->codigo != codigo) cursor = &(*cursor)->proximo;
    if (*cursor) { Registro *alvo = *cursor; *cursor = alvo->proximo; free(alvo); }
    else puts("Código não encontrado.");
    return inicio;
}
int main(void) {
    Registro *inicio = NULL;
    int opcao, codigo, resposta;
    puts("Registro demonstrativo — dados fictícios.");
    for (;;) {
        resposta = ler_codigo("1 Inserir | 2 Excluir | 3 Listar | 4 Sair: ", &opcao);
        if (!resposta) break;
        if (resposta < 0) { puts("Opção inválida."); continue; }
        if (opcao == 4) break;
        if (opcao == 1) {
            resposta = ler_codigo("Código: ", &codigo);
            if (!resposta) break;
            if (resposta < 0 || buscar(inicio, codigo)) {
                puts("Código inválido ou já cadastrado."); continue;
            }
            Registro *novo = calloc(1, sizeof *novo);
            if (!novo) { perror("calloc"); break; }
            novo->codigo = codigo;
            resposta = ler_texto("Nome fictício: ", novo->nome, sizeof novo->nome);
            if (!resposta) { free(novo); break; }
            if (resposta < 0) { free(novo); continue; }
            resposta = ler_texto("Sigla (até 4 caracteres): ", novo->instituicao, sizeof novo->instituicao);
            if (!resposta) { free(novo); break; }
            if (resposta < 0) { free(novo); continue; }
            novo->proximo = inicio; inicio = novo; puts("Registro incluído.");
        } else if (opcao == 2) {
            resposta = ler_codigo("Código a excluir: ", &codigo);
            if (!resposta) break;
            if (resposta < 0) { puts("Código inválido."); continue; }
            inicio = excluir(inicio, codigo);
        } else if (opcao == 3) {
            for (Registro *p = inicio; p; p = p->proximo)
                printf("%d | %s | %s\n", p->codigo, p->nome, p->instituicao);
        } else puts("Opção inválida.");
    }
    while (inicio) { Registro *proximo = inicio->proximo; free(inicio); inicio = proximo; }
    return 0;
}
