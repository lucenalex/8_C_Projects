#include <stdio.h>
#include <stdlib.h>

int posicao();
int pertence();
int main(){
    int tam = 0;
    printf("Informe o tamanho da lista: ");
    scanf("%d",&tam);
    int *L = NULL;
    L = (int*) malloc(tam*sizeof(int));
    printf("\nInforme os dados a serem contidos na lista: ");
    for(int i = 0; i < tam; i++){
        scanf("%d",L + i);
    }
    int dado = 0;
    printf("\nInforme o dadc a ser buscado: ");
    scanf("%d",&dado);
    int resultado_posicao,resultado_dado;
    resultado_posicao = posicao(dado,L,tam);
    resultado_dado = pertence(dado,L,tam);

    if(resultado_posicao == -1 || resultado_dado == 0){
        printf("O dado buscado nao pertence a lista!\n");
    }else{
        printf("O dado pesquisado pertecen a lista!\n");
        printf("A posicao do dado pesquisado eh %d\n",resultado_posicao);
    }

    return 0;
}
int posicao(int valor, int *lista_linear, int indice){
    for(int i = 0; i < indice; i++){
        if(valor == *(lista_linear + i)){
            return i;
        }
    }
    return -1;
}
int pertence(int valor, int *lista_linear, int indice){
    for(int i = 0; i < indice; i++){
        if(valor == *(lista_linear + i)){
            return 1;
        }
    }
    return 0;
}
