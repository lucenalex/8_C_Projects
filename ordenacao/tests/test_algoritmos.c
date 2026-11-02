#include "../algoritmos.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void testar_caso(const int *dados, size_t n) {
    int *a=malloc((n?n:1)*sizeof *a);
    int *b=malloc((n?n:1)*sizeof *b);
    int *c=malloc((n?n:1)*sizeof *c);
    assert(a&&b&&c);
    memcpy(a,dados,n*sizeof *a);
    memcpy(b,dados,n*sizeof *b);
    memcpy(c,dados,n*sizeof *c);
    ordenar_bolha(a,n);
    ordenar_selecao(b,n);
    ordenar_insercao(c,n);
    assert(esta_ordenado(a,n));
    assert(memcmp(a,b,n*sizeof *a)==0);
    assert(memcmp(a,c,n*sizeof *a)==0);
    for (size_t i=0;i<n;++i) {
        int pos=buscar_binaria(a,n,a[i]);
        assert(pos>=0 && (size_t)pos<n && a[pos]==a[i]);
        assert(buscar_sequencial(dados,n,dados[i])>=0);
    }
    assert(buscar_binaria(a,n,10001)==-1);
    free(a);free(b);free(c);
}
int main(void) {
    const int empty[1]={0},one[1]={7};
    const int reversed[8]={8,7,6,5,4,3,2,1};
    const int repeated[8]={-5,-5,0,0,2,2,2,5};
    testar_caso(empty,0);
    testar_caso(one,1);
    testar_caso(reversed,8);
    testar_caso(repeated,8);
    for (size_t n=2;n<=128;++n) {
        int arr[128];
        for(size_t i=0;i<n;++i) arr[i]=(int)((i*73+n*17)%127)-63;
        testar_caso(arr,n);
    }
    printf("PASS: 3 sort algorithms, 2 searches, lengths 0..128, duplicates and negatives\n");
    return 0;
}
