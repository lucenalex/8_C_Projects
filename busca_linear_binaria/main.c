/* Dois vetores de 8 elementos: busca linear e busca binaria crescente. */
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 8
static int numero(const char *rotulo,int *out) {
    char buf[128],*fim;
    for(;;){
        fputs(rotulo,stdout);fflush(stdout);
        if(!fgets(buf,sizeof buf,stdin))return 0;
        size_t n=strcspn(buf,"\n");
        if(buf[n]!='\n'&&!feof(stdin)) {
            int c;while((c=getchar())!='\n'&&c!=EOF){}
            puts("Entrada muito longa.");continue;
        }
        errno=0;long v=strtol(buf,&fim,10);
        while(*fim=='\n'||*fim=='\r'||*fim==' '||*fim=='\t')++fim;
        if(fim==buf||*fim||errno||v<INT_MIN||v>INT_MAX){
            puts("Numero invalido.");continue;
        }
        *out=(int)v;return 1;
    }
}
static int cmp(const void *a,const void *b){
    int x=*(const int*)a,y=*(const int*)b;
    return (x>y)-(x<y);
}
static int linear(const int *v,int alvo){
    for(int i=0;i<TAM;++i)if(v[i]==alvo)return i;
    return -1;
}
static int binaria(const int *v,int alvo) {
    int baixo=0,alto=TAM;
    while(baixo<alto) {
        int meio=baixo+(alto-baixo)/2;
        if(v[meio]<alvo)baixo=meio+1;
        else alto=meio;
    }
    return baixo<TAM&&v[baixo]==alvo?baixo:-1;
}
static int preencher(int *v,int ordenar) {
    for(int i=0;i<TAM;++i) {
        char prompt[40];snprintf(prompt,sizeof prompt,"Elemento %d: ",i+1);
        if(!numero(prompt,&v[i]))return 0;
    }
    if(ordenar)qsort(v,TAM,sizeof v[0],cmp);
    return 1;
}
static void mostrar(const int *v){
    for(int i=0;i<TAM;++i)printf("%d%s",v[i],i==TAM-1?"\n":" ");
}
int main(void){
    int v1[TAM]={0},v2[TAM]={0},p1=0,p2=0,op,alvo,idx;
    for(;;){
        puts("1 Preencher desordenado | 2 Preencher ordenado | 3 Busca linear");
        puts("4 Busca binaria | 5 Mostrar 1 | 6 Mostrar 2 | 7 Sair");
        if(!numero("Opcao: ",&op)||op==7)break;
        switch(op){
            case 1:if(!preencher(v1,0))return 0;p1=1;break;
            case 2:if(!preencher(v2,1))return 0;p2=1;break;
            case 3:case 4:
                if((op==3&&!p1)||(op==4&&!p2)) {
                    puts("Preencha o vetor correspondente.");break;
                }
                if(!numero("Valor procurado: ",&alvo))return 0;
                idx=op==3?linear(v1,alvo):binaria(v2,alvo);
                if(idx<0)puts("Nao encontrado.");
                else printf("Valor encontrado na posicao %d\n",idx);
                break;
            case 5:if(p1)mostrar(v1);else puts("Preencha o vetor 1.");break;
            case 6:if(p2)mostrar(v2);else puts("Preencha o vetor 2.");break;
            default:puts("Opcao invalida.");
        }
    }
    return 0;
}
