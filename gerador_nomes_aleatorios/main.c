#include <stdio.h>
#include <string.h>

/* Exemplo didático de append e leitura de nomes fictícios.
 * Executar em diretório de testes isolado; grava em exemplo.txt no CWD.
 */
int main(void) {
    char linha[100];
    fputs("Informe um nome: ", stdout);
    fflush(stdout);
    if (!fgets(linha, sizeof linha, stdin)) {
        puts("Entrada encerrada; nenhum arquivo alterado.");
        return 0;
    }
    size_t tamanho = strcspn(linha, "\n");
    if (linha[tamanho] != '\n' && !feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        fputs("Nome muito longo; nenhum arquivo alterado.\n", stderr);
        return 1;
    }
    if (tamanho && linha[tamanho - 1] == '\r') --tamanho;
    linha[tamanho] = '\0';
    if (!tamanho) {
        fputs("Nome vazio; nenhum arquivo alterado.\n", stderr);
        return 1;
    }
    FILE *arquivo = fopen("exemplo.txt", "a+");
    if (!arquivo) { perror("exemplo.txt"); return 1; }
    if (fprintf(arquivo, "%s\n", linha) < 0 || fflush(arquivo) != 0) {
        perror("Gravação");
        (void)fclose(arquivo);
        return 1;
    }
    rewind(arquivo);
    puts("Nomes registrados:");
    while (fgets(linha, sizeof linha, arquivo)) fputs(linha, stdout);
    if (ferror(arquivo)) {
        perror("Leitura");
        (void)fclose(arquivo);
        return 1;
    }
    if (fclose(arquivo) != 0) { perror("Fechamento"); return 1; }
    return 0;
}
