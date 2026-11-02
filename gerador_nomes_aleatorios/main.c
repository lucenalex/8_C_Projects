#include <stdio.h>
#include <string.h>

/* Exemplo de leitura/escrita de texto. Grava apenas em exemplo.txt
 * no diretório de execução; executar em uma pasta de testes isolada.
 */
int main(void) {
    char linha[100];
    FILE *arquivo = fopen("exemplo.txt", "a+");
    if (!arquivo) { perror("exemplo.txt"); return 1; }
    fputs("Informe um nome: ", stdout);
    if (!fgets(linha, sizeof linha, stdin)) { fclose(arquivo); return 1; }
    linha[strcspn(linha, "\n")] = '\0';
    if (fprintf(arquivo, "%s\n", linha) < 0 || fflush(arquivo) != 0) {
        perror("Gravação"); fclose(arquivo); return 1;
    }
    rewind(arquivo);
    puts("Nomes registrados:");
    while (fgets(linha, sizeof linha, arquivo)) fputs(linha, stdout);
    if (ferror(arquivo)) { perror("Leitura"); fclose(arquivo); return 1; }
    if (fclose(arquivo) != 0) { perror("Fechamento"); return 1; }
    return 0;
}
