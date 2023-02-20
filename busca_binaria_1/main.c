#include <stdio.h>
#include <stdlib.h>

int pertece();
int main(){
    printf("Busque um dos dados contidos na lisa L={14, 27, 39, 46, 55, 63, 71, 80, 92}!\n");
    int tam = 9;
    int L[9] = {14, 27, 39, 46, 55, 63, 71, 80, 92};
    printf("O programa busca o dado 63 na lista dada!");
    int dado = 63;
    int resultado = pertece(dado,L,tam);
    if(resultado == 1){
        printf("Dado encontrado! Pertence a lista.\n");
    }else{
        printf("Dado não encontrado! Não pertence a lista.\n");
    }

    return 0;
}
int pertece(int x, int L[],int n){
    int i = 0, f = n - 1, m = 0;
    while( i <= f){
        m = (i + f)/2;
        if( x == L[m]){
            return 1;
        }else if( x < L[m]){
            f = m - 1;
        }else{
            i = m + 1;
        }
    }
    return 0;
}
