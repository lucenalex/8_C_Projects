#ifndef ORDENACAO_ALGORITMOS_H
#define ORDENACAO_ALGORITMOS_H
#include <stddef.h>
void ordenar_bolha(int *dados, size_t n);
void ordenar_selecao(int *dados, size_t n);
void ordenar_insercao(int *dados, size_t n);
int buscar_sequencial(const int *dados, size_t n, int alvo);
int buscar_binaria(const int *dados, size_t n, int alvo);
int esta_ordenado(const int *dados, size_t n);
#endif
