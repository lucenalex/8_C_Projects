#ifndef LISTAS_ENCADEADAS_LISTA_H
#define LISTAS_ENCADEADAS_LISTA_H
#include <stddef.h>
typedef struct No {
    int valor;
    struct No *proximo;
} No;
/* 1=sucesso, 0=falha de memoria. */
int lista_inserir(No **cabeca, int valor);
int lista_contem(const No *cabeca, int valor);
/* 1=removeu uma ocorrencia, 0=nao encontrou. */
int lista_remover(No **cabeca, int valor);
size_t lista_tamanho(const No *cabeca);
void lista_limpar(No **cabeca);
#endif
