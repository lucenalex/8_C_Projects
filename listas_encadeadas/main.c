/**
Lista encadeada:
- sequência encadeada de elementos, chamados de nós da lista
- nó da lista é representado por dois campos:
  -> a informação armazenada e
  -> o ponteiro para o próximo elemento da lista
- a lista é representada por um ponteiro para o primeiro nó
- o ponteiro do último elemento é NULL

*/
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
/******************************************************************************/
typedef struct no{
    int informacao;
    struct no *proximo;
}Lista;
/******************************************************************************/
Lista *criarlista(){//função de criação: retorna uma lista vazia
    return NULL;
};
/**---------------------------------------------------------------------------*/
int vazia(Lista *lista){//função vazia: retorna 1 se vazia, do contrário 0
    return (lista == NULL);
};
/**---------------------------------------------------------------------------*/
Lista *insere(Lista *lista, int valor){//inserção: retorna lista atualizada
    Lista *novo = (Lista*) calloc(1,sizeof(Lista));
    novo->informacao = valor;
    novo->proximo = lista;
    return novo;
};
/**---------------------------------------------------------------------------*/
void imprime_lista(Lista *lista){// imprime os elementos da lista
    Lista *elementos;
    for(elementos = lista; elementos != NULL; elementos = elementos->proximo){
        printf("informacao = %d\n",elementos->informacao);
    }
}
/**---------------------------------------------------------------------------*/
busca(Lista *lista, int valor);
/**---------------------------------------------------------------------------*/
listagem(Lista *lista);
/**---------------------------------------------------------------------------*/
Lista* retira(Lista *lista, int valor){
    Lista* ant = NULL; // ponteiro para o elemento anterior
    Lista *p = lista;  // ponteiro para percorrer a lista
    // procura elemento na lista, guardando anterior
    while( (p!=NULL) && (p->informacao != valor) ){
        ant = p;
        p = p ->proximo;
    }
    // verifica se achou o elemento
    if(p==NULL){
        return lista;// não achou: retorna a lista original
    }
    // retira o elemento
    if(ant == NULL){
        // retira o elemento do inicio
        lista = p->proximo;
    }
    else{
        //retira elemento do meio da lista
        ant->proximo = p->proximo;
    }
    free(p);
    return lista;
};
/******************************************************************************/
int main(void){
    Lista *_lista;                      /** declara uma lista não inicializada*/
    _lista = criarlista();              /** cria e inicializa uma lista vazia */
    _lista = insere(_lista,23);         /** insere na lista o elemento 23     */
    _lista = insere(_lista,45);         /** insere na lista o elemento 45     */
    imprime_lista(_lista);
    return 0;
}
/******************************************************************************/
