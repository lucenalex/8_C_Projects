#include "../lista.h"
#include <assert.h>
#include <stdio.h>
int main(void) {
    No *l=NULL;
    assert(!lista_remover(&l,42));
    assert(!lista_contem(l,42));
    assert(lista_tamanho(l)==0);
    for(int i=0;i<1000;++i)assert(lista_inserir(&l,i));
    assert(lista_tamanho(l)==1000);
    assert(lista_contem(l,0)&&lista_contem(l,999)&&!lista_contem(l,-1));
    assert(lista_remover(&l,999)); /* cabeca */
    assert(lista_remover(&l,500)); /* meio */
    assert(lista_remover(&l,0)); /* cauda */
    assert(!lista_remover(&l,999)); /* ausente */
    assert(lista_tamanho(l)==997);
    assert(lista_inserir(&l,42)&&lista_inserir(&l,42));
    assert(lista_remover(&l,42));
    assert(lista_contem(l,42));
    assert(lista_remover(&l,42));
    assert(!lista_contem(l,42));
    lista_limpar(&l);
    assert(l==NULL);
    lista_limpar(&l); /* idempotente */
    puts("PASS linked list: 1000 nodes, head/middle/tail, duplicates, cleanup");
    return 0;
}
