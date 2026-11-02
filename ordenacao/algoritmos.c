#include "algoritmos.h"

/* Bolha: indices j e j+1 satisfazem j+1 < n-i. */
void ordenar_bolha(int *a, size_t n) {
    for (size_t i=0; i<n; ++i) {
        int trocou=0;
        for (size_t j=0; j+1<n-i; ++j) {
            if (a[j]>a[j+1]) {
                int t=a[j]; a[j]=a[j+1]; a[j+1]=t;
                trocou=1;
            }
        }
        if (!trocou) break;
    }
}
void ordenar_selecao(int *a, size_t n) {
    for (size_t i=0; i<n; ++i) {
        size_t menor=i;
        for (size_t j=i+1; j<n; ++j)
            if (a[j]<a[menor]) menor=j;
        if (menor!=i) {
            int t=a[i]; a[i]=a[menor]; a[menor]=t;
        }
    }
}
void ordenar_insercao(int *a, size_t n) {
    for (size_t i=1; i<n; ++i) {
        int valor=a[i];
        size_t j=i;
        while (j>0 && a[j-1]>valor) {
            a[j]=a[j-1];
            --j;
        }
        a[j]=valor;
    }
}
int buscar_sequencial(const int *a, size_t n, int alvo) {
    for (size_t i=0; i<n; ++i) if (a[i]==alvo) return (int)i;
    return -1;
}
/* Retorna qualquer ocorrencia para arrays ordenados crescentemente. */
int buscar_binaria(const int *a, size_t n, int alvo) {
    size_t inicio=0, fim=n;
    while (inicio<fim) {
        size_t m=inicio+(fim-inicio)/2;
        if (a[m]<alvo) inicio=m+1;
        else fim=m;
    }
    return inicio<n && a[inicio]==alvo ? (int)inicio : -1;
}
int esta_ordenado(const int *a, size_t n) {
    for (size_t i=1; i<n; ++i)
        if (a[i-1]>a[i]) return 0;
    return 1;
}
