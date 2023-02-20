#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
typedef struct no{
    int codigo;
    char nome[50];
    char inst[5];
    struct no *proximo;
}registro;
registro *criar_registro(){
    return NULL;
}
int vazia(registro *reg){
    return (reg == NULL);
}
registro* exclusao(registro *reg, int cod){
    registro *anterior = NULL;  /**> ponteiro para o membro anterior <**/
    registro *percorre = reg; /**> ponteiro para percorrer o registro <**/
    /**> procura elemento no registro, guardando anterior <**/
    while( (percorre!=NULL) && (percorre->codigo != cod) ){
        anterior = percorre;
        percorre = percorre -> proximo;
    }
    /**> verifica se achou o membro <**/
    if(percorre == NULL){
        return reg; /**> não achou: retorna registro original <**/
    }
    /**> retira o elemento <**/
    if(anterior == NULL){
        /**> retira o elemento do inicio <**/
        reg = percorre->proximo;
    }
    else{
        /**> retira elemento do meio da lista <**/
        anterior -> proximo = percorre->proximo;
    }
    free(percorre);
    return reg;
};
registro *insercao(registro *reg){
    registro *novo = (registro*) calloc(1,sizeof(registro));
    printf("código: ");
    scanf("%d",&novo->codigo);
    printf("\nnome: ");
    gets(novo->nome);getchar();
    printf("instituição: ");getchar();
    gets(novo->inst);
    novo->proximo = reg;
    return novo;
};
void imprime_registro(registro *reg){
    registro *pessoa;
    for(pessoa = reg; pessoa != NULL; pessoa = pessoa->proximo){
        printf("codigo = %d\n",pessoa->codigo);
        printf("nome = %s\n",pessoa->nome);
        printf("partido = %s\n",pessoa->inst);
    }
}
int main(){
    setlocale(LC_ALL,"pbr");
    FILE *file = fopen("nomes_masculinos.bin","wb");
    /** declara registros de candidatos e eleitores não inicializados*/
    registro *candidatos;
    registro *eleitores;
    /** cria e inicializa registros vazios */
    candidatos = criar_registro();
    eleitores = criar_registro();
    printf("Insira os dados do eleitor!\n");
    insercao(eleitores);

    return 0;
}

