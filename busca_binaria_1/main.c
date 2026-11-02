/* Exercicio didatico de busca binaria em vetor ordenado.
 * Usa os mesmos nove valores do codigo historico, com alvo opcional.
 */
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int pertence(int x, const int *lista, size_t n) {
    size_t inicio=0, fim=n;
    while(inicio<fim) {
        size_t meio=inicio+(fim-inicio)/2;
        if(lista[meio]<x) inicio=meio+1;
        else fim=meio;
    }
    return inicio<n && lista[inicio]==x;
}
int main(int argc, char **argv) {
    static const int lista[]={14,27,39,46,55,63,71,80,92};
    int alvo=63;
    if(argc>2) {
        fputs("Uso: busca_binaria_1 [alvo_inteiro]\n",stderr);
        return 2;
    }
    if(argc==2) {
        char *fim;
        errno=0;
        long valor=strtol(argv[1],&fim,10);
        if(errno || fim==argv[1] || *fim || valor<INT_MIN || valor>INT_MAX) {
            fputs("Alvo nao e inteiro valido.\n",stderr);
            return 2;
        }
        alvo=(int)valor;
    }
    printf("Busca binaria de %d em {14,27,39,46,55,63,71,80,92}.\n",alvo);
    puts(pertence(alvo,lista,sizeof lista/sizeof lista[0])
         ?"Dado encontrado! Pertence a lista."
         :"Dado nao encontrado! Nao pertence a lista.");
    return 0;
}
