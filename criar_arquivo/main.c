/* Exercicio historico de ordenacao: versao segura e reproduzivel.
 * Por padrao, demonstra 10 elementos; a ideia original de 1 milhao de
 * elementos seria inviavel com tres algoritmos quadraticos O(n^2).
 * Nenhum arquivo e criado sem --output; escrita exclusiva evita sobrescrita.
 */
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFAULT_N 10
#define MAX_N 10000
#define SLOW_N 2000

static void bolha(int *a, size_t n) {
    for (size_t i=0; i<n; ++i) {
        int trocou=0;
        for (size_t j=0; j+1<n-i; ++j) {
            if (a[j] > a[j+1]) {
                int temp=a[j]; a[j]=a[j+1]; a[j+1]=temp; trocou=1;
            }
        }
        if (!trocou) break;
    }
}
static void selecao(int *a, size_t n) {
    for (size_t i=0; i<n; ++i) {
        size_t menor=i;
        for (size_t j=i+1; j<n; ++j) if (a[j]<a[menor]) menor=j;
        if (menor!=i) {
            int temp=a[menor]; a[menor]=a[i]; a[i]=temp;
        }
    }
}
static void insercao(int *a, size_t n) {
    for (size_t i=1; i<n; ++i) {
        int chave=a[i];
        size_t j=i;
        while (j>0 && a[j-1]>chave) { a[j]=a[j-1]; --j; }
        a[j]=chave;
    }
}
static int inteiro(const char *texto, unsigned *out) {
    char *end;
    if (!texto || !*texto || *texto=='-') return 0;
    errno=0;
    unsigned long valor=strtoul(texto,&end,10);
    if (errno || end==texto || *end || valor>UINT_MAX) return 0;
    *out=(unsigned)valor;
    return 1;
}
static void uso(const char *prog) {
    fprintf(stderr,"Uso: %s [--count N] [--seed N] [--allow-slow] [--output ARQUIVO]\n",prog);
}
int main(int argc, char **argv) {
    unsigned quantidade=DEFAULT_N,seed=2026;
    int permitir_lento=0;
    const char *saida=NULL;
    for (int i=1; i<argc; ++i) {
        if (!strcmp(argv[i],"--count") && i+1<argc) {
            if (!inteiro(argv[++i],&quantidade)) { uso(argv[0]);return 2; }
        } else if (!strcmp(argv[i],"--seed") && i+1<argc) {
            if (!inteiro(argv[++i],&seed)) { uso(argv[0]);return 2; }
        } else if (!strcmp(argv[i],"--output") && i+1<argc) {
            saida=argv[++i];
            if (!*saida) { uso(argv[0]);return 2; }
        } else if (!strcmp(argv[i],"--allow-slow")) {
            permitir_lento=1;
        } else { uso(argv[0]);return 2; }
    }
    if (quantidade<1 || quantidade>MAX_N) {
        fprintf(stderr,"Quantidade fora do intervalo 1..%d.\n",MAX_N);
        return 2;
    }
    if (quantidade>SLOW_N && !permitir_lento) {
        fprintf(stderr,"Ordenacoes O(n^2) acima de %d exigem --allow-slow.\n",SLOW_N);
        return 2;
    }
    size_t n=quantidade;
    int *orig=malloc(n*sizeof *orig);
    int *a=malloc(n*sizeof *a);
    int *b=malloc(n*sizeof *b);
    int *c=malloc(n*sizeof *c);
    if (!orig || !a || !b || !c) {
        perror("malloc");
        free(orig);free(a);free(b);free(c);
        return 1;
    }
    srand(seed);
    for(size_t i=0;i<n;++i) orig[i]=rand()%1000000;
    memcpy(a,orig,n*sizeof *orig);
    memcpy(b,orig,n*sizeof *orig);
    memcpy(c,orig,n*sizeof *orig);
    if (saida) {
        FILE *fp=fopen(saida,"wx");
        if (!fp) {
            perror("Arquivo nao criado (talvez ja exista)");
            free(orig);free(a);free(b);free(c);return 1;
        }
        int erro=0;
        for(size_t i=0;i<n;++i) if (fprintf(fp,"%d\n",orig[i])<0) {erro=1;break;}
        if(fclose(fp)!=0) erro=1;
        if(erro) {
            fprintf(stderr,"Erro de escrita do arquivo de dados.\n");
            free(orig);free(a);free(b);free(c);return 1;
        }
    }
    clock_t t0=clock();
    bolha(a,n);
    clock_t t1=clock();
    selecao(b,n);
    clock_t t2=clock();
    insercao(c,n);
    clock_t t3=clock();
    int iguais=memcmp(a,b,n*sizeof *a)==0 && memcmp(a,c,n*sizeof *a)==0;
    for(size_t i=1;i<n;++i) if (a[i-1]>a[i]) iguais=0;
    printf("Elementos: %zu | Semente: %u\n",n,seed);
    printf("Ordenacoes concordam: %s\n",iguais?"SIM":"NAO");
    printf("Tempos CPU (s): bolha=%.6f; selecao=%.6f; insercao=%.6f\n",
           (double)(t1-t0)/CLOCKS_PER_SEC,
           (double)(t2-t1)/CLOCKS_PER_SEC,
           (double)(t3-t2)/CLOCKS_PER_SEC);
    if (saida)printf("Arquivo criado sem sobrescrita: %s\n",saida);
    free(orig);free(a);free(b);free(c);
    return iguais?0:1;
}
