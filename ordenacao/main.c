/* Ordenacao - Desafio 1: tres vetores (ate 150000 inteiros).
 * Bubble, selection e insertion: O(n^2) no pior caso. O usuario decide
 * explicitamente antes de executar ordenacao grande; nao substitui algoritmos.
 * Reprodutibilidade: semente fixa para teste de resultados.
 */
#include "algoritmos.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENTOS 150000U
#define LIMIAR_LENTO 10000U
static int ler_inteiro(const char *mensagem, int *out) {
    char linha[128],*fim;
    while (1) {
        fputs(mensagem,stdout); fflush(stdout);
        if (!fgets(linha,sizeof linha,stdin)) return 0;
        size_t n=strcspn(linha,"\n");
        if (linha[n]!='\n'&&!feof(stdin)) {
            int c;while((c=getchar())!='\n'&&c!=EOF){}
            puts("Entrada excessiva.");continue;
        }
        errno=0;
        long val=strtol(linha,&fim,10);
        while (*fim==' '||*fim=='\t'||*fim=='\n'||*fim=='\r')++fim;
        if (fim==linha||*fim||errno||val<INT_MIN||val>INT_MAX) {
            puts("Informe um numero inteiro valido.");continue;
        }
        *out=(int)val;return 1;
    }
}
static void popular(int *v, size_t n, unsigned int seed) {
    srand(seed);
    for (size_t i=0;i<n;++i) v[i]=rand()%100;
}
static void exibir(const int *v,size_t n) {
    size_t m=n<50?n:50;
    for(size_t i=0;i<m;++i) printf("%d%s",v[i],i+1==m?"\n":" ");
    if(n>m) printf("Exibidos %zu dos %zu elementos; restante omitido.\n",m,n);
}
static int confirmar(size_t n) {
    if(n<=LIMIAR_LENTO) return 1;
    puts("ATENCAO: algoritmo quadratico com mais de 10000 elementos.");
    puts("Para 150000 elementos, o custo pode ser muito elevado.");
    int confirma;
    if(!ler_inteiro("Executar mesmo assim? 1 sim, 0 nao: ",&confirma))return 0;
    return confirma==1;
}
int main(void) {
    int nn;
    if(!ler_inteiro("Quantidade de elementos (1..150000): ",&nn))return 0;
    if(nn<1||nn>(int)MAX_ELEMENTOS) {
        fputs("Quantidade fora da faixa.\n",stderr);return 1;
    }
    size_t n=(size_t)nn;
    int *v[3]={0};
    for(int i=0;i<3;++i) {
        v[i]=calloc(n,sizeof *v[i]);
        if(!v[i]) { perror("calloc");for(int j=0;j<3;++j)free(v[j]);return 1; }
    }
    int prontos[3]={0},ordenados[3]={0},op;
    puts("Bolha, Selecao e Insercao — demonstracao didatica");
    for(;;) {
        puts("1/2/3 preencher | 4/5/6 exibir | 7 busca sequencial");
        puts("8 bolha | 9 selecao | 10 insercao | 11 busca binaria | 12 sair");
        if(!ler_inteiro("Opcao: ",&op)||op==12)break;
        if(op>=1&&op<=3) {
            int k=op-1;popular(v[k],n,(unsigned)(2026+17*k));
            prontos[k]=1;ordenados[k]=0;printf("Vetor %d preenchido.\n",k+1);
        } else if(op>=4&&op<=6) {
            int k=op-4;
            if(!prontos[k]) puts("Preencha este vetor primeiro.");
            else exibir(v[k],n);
        } else if(op==8||op==9||op==10) {
            int k=op-8;
            if(!prontos[k]) { puts("Preencha este vetor primeiro.");continue; }
            if(!confirmar(n)) { puts("Ordenacao cancelada.");continue; }
            if(k==0) ordenar_bolha(v[k],n);
            else if(k==1) ordenar_selecao(v[k],n);
            else ordenar_insercao(v[k],n);
            ordenados[k]=1;
            puts("Ordenacao concluida.");
        } else if(op==7||op==11) {
            int k=op==7?0:2,alvo;
            if(!prontos[k]) {puts("Preencha este vetor primeiro.");continue;}
            if(op==11&&!ordenados[k]) {
                puts("Busca binaria exige vetor 3 ordenado; execute a insercao.");
                continue;
            }
            if(!ler_inteiro("Valor procurado: ",&alvo)) break;
            int idx=op==7?buscar_sequencial(v[k],n,alvo):
                           buscar_binaria(v[k],n,alvo);
            if(idx<0)puts("Valor nao encontrado.");
            else printf("Valor encontrado na posicao %d.\n",idx);
        } else puts("Opcao invalida.");
    }
    for(int i=0;i<3;++i)free(v[i]);
    return 0;
}
