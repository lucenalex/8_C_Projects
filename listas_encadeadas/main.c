/* Lista simplesmente encadeada: insercao, busca, remocao e desalocacao. */
#include "lista.h"
#include <stdio.h>
int main(void) {
    No *lista=NULL;
    if(!lista_inserir(&lista,23)||!lista_inserir(&lista,45)) {
        fputs("Falha de alocacao\n",stderr);
        lista_limpar(&lista);return 1;
    }
    for(const No *p=lista;p;p=p->proximo)printf("informacao = %d\n",p->valor);
    printf("Contem 23: %s\n",lista_contem(lista,23)?"sim":"nao");
    (void)lista_remover(&lista,45);
    printf("Tamanho apos remover 45: %zu\n",lista_tamanho(lista));
    lista_limpar(&lista);
    return lista==NULL?0:1;
}
