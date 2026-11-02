/* Lista linear e busca: limite explicito de alocacao e entradas. */
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LISTA 100000
static int ler_inteiro(int *saida) {
    char buf[128],*fim;
    if(!fgets(buf,sizeof buf,stdin))return 0;
    size_t n=strcspn(buf,"\n");
    if(buf[n]!='\n'&&!feof(stdin)) {
        int c;while((c=getchar())!='\n'&&c!=EOF){}
        return -1;
    }
    errno=0;long val=strtol(buf,&fim,10);
    while(*fim=='\n'||*fim=='\r'||*fim==' '||*fim=='\t')++fim;
    if(fim==buf||*fim||errno||val<INT_MIN||val>INT_MAX)return -1;
    *saida=(int)val;return 1;
}
static int posicao(int alvo,const int *v,int n) {
    for(int i=0;i<n;++i)if(v[i]==alvo)return i;
    return -1;
}
int main(void) {
    int n;
    printf("Tamanho da lista (0..100000): ");fflush(stdout);
    if(ler_inteiro(&n)!=1||n<0||n>MAX_LISTA) {
        fputs("Tamanho invalido\n",stderr);return 1;
    }
    int *v=calloc(n?(size_t)n:1,sizeof *v);
    if(!v){perror("calloc");return 1;}
    for(int i=0;i<n;++i) {
        printf("Elemento %d: ",i+1);fflush(stdout);
        if(ler_inteiro(&v[i])!=1) {
            fputs("Elemento invalido\n",stderr);free(v);return 1;
        }
    }
    int alvo;printf("Valor buscado: ");fflush(stdout);
    if(ler_inteiro(&alvo)!=1) {free(v);return 1;}
    int idx=posicao(alvo,v,n);
    if(idx<0)puts("O dado nao pertence a lista.");
    else printf("Posicao: %d\n",idx);
    free(v);return 0;
}
