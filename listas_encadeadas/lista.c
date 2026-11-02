#include "lista.h"
#include <stdlib.h>
int lista_inserir(No **cabeca, int valor) {
    if (!cabeca) return 0;
    No *novo=malloc(sizeof *novo);
    if (!novo) return 0;
    novo->valor=valor;novo->proximo=*cabeca;*cabeca=novo;
    return 1;
}
int lista_contem(const No *cabeca, int valor) {
    for(const No *p=cabeca;p;p=p->proximo)
        if(p->valor==valor)return 1;
    return 0;
}
int lista_remover(No **cabeca,int valor) {
    if (!cabeca)return 0;
    No **p=cabeca;
    while(*p && (*p)->valor!=valor)p=&(*p)->proximo;
    if(!*p)return 0;
    No *alvo=*p;*p=alvo->proximo;free(alvo);return 1;
}
size_t lista_tamanho(const No *cabeca) {
    size_t n=0;for(const No *p=cabeca;p;p=p->proximo)++n;
    return n;
}
void lista_limpar(No **cabeca) {
    if(!cabeca)return;
    while(*cabeca) {
        No *p=*cabeca;*cabeca=p->proximo;free(p);
    }
}
