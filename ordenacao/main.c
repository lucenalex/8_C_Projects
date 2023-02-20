/******************************************************************************
    Clientes:
        Universidade Estadual do Maranh�o
        Centro de Ci�ncias Tecnol�gicas
        Departamento de Engenharia da Computa��o
        Curso de Engenharia da Computa��o
        Disciplina: Estrutura de Dados B�sica (ASL092N321)
        Semestre: 2022.2         Turma: 01
        Professores:
            L�is Carlos Fonseca
            Pedro Brand�o Neto

    Autores:
        Alunos:
            Alexsandro Lucena Mota   C�digo: 20210024710

    T�tulo: Ordena��o - Desafio 1

    Prop�sito do Programa:

        Crie uma programa para preencher arbitrariamente 3 vetores
        com no m�nimo 150000 n�meros inteiros e ent�o ordenar cada
        um deles usando os m�todos bolha, sele��o e inser��o. Crie um
        menu de texto com as seguintes op��es:
             1) Preencher aleatoriamente o primeiro vetor
             2) Preencher aleatoriamente o segundo vetor
             3) Preencher aleatoriamente o terceiro vetor
             4) ImprimirVetor 1
             5) ImprimirVetor 2
             6) ImprimirVetor 3
             7) Busca Sequencial (vetor1)
             8) Ordena��o por trocas - bubbleSort - (vetor1)
             9) Ordena��o por sele��o (vetor2)
            10) Ordena��o por inser��o (vetor3)
            11) Busca Bin�ria (vetor 3)
            12) Sair

    Dados de Manuten��o do programa

      Data            Programador                  Descri��o da Mudan�a
    ==========    ======================      =================================
    2022/13/10    Alexsandro Lucena Mota      - C�digo original (vers�o 0.1).
*******************************************************************************/

#include <stdio.h>  /*> Entrada e Sa�da de Dados                             */
#include <stdlib.h> /*> Para o uso da fun��o rand e srand.                   */
#include <time.h>   /*> Para mudar o ponto de partida da fun��o srand()      */
#define tam 150000      /*> Tamanho dos vetores                                  */

/*****************************************************************************/
void preencher_vetor(int *vetor,int dim){ // Preenche um vetor
    srand(time(NULL)); // Muda o ponto de partida de rand a cada nova execu��o.
    for(int i = 0; i < dim; i++){ // Varre cada posi��o do vetor    */
        *(vetor + i) = rand()%100; // Atribui valor aleat�rio de 0 at� 99.
    }
}
/*---------------------------------------------------------------------------*/
void imprimir_vetor(int *vetor,int dim){
    for(int i = 0; i < dim; i++){
        printf("%d ",*(vetor + i));
    }
};
/*---------------------------------------------------------------------------*/
int busca_sequencial(int valor, int *vetor, int dim){
    printf("\n");
    for(int i = 0; i < dim; i++){
        if(valor == *(vetor + i)){
            return i;
        }
    }
    return -1;
};
/*---------------------------------------------------------------------------*/
void bublesoft(int *vetor, int dim){// Ordena��o por troca
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim - i; j++){
            if( *(vetor + j) > *(vetor + j + 1) ){
                int x = *(vetor + j);
                *(vetor + j ) = *(vetor + j + 1);
                *(vetor + j + 1) = x;
            }
        }
    }
}
/*---------------------------------------------------------------------------*/
int menor_item(int *vetor, int dim, int enesimo_item){
    int minitem = enesimo_item; // item m�nimo recebe o item inicial (valor)
    for(int j = enesimo_item + 1; j < dim; j++){
        if( *(vetor + minitem) > *(vetor + j) ){
            minitem = j; // item m�nimo recebe o indice do menor valor da lista
        }
    }
    return minitem;
}
/*...........................................................................*/
void selectionsort(int *vetor, int dim){
    int x = 0, minitem = 0;
    for(int i = 0; i < dim - 1; i++){
        minitem = menor_item(vetor, dim, i);
        x = *(vetor + i);
        *(vetor + i) = *(vetor + minitem);
        *(vetor + minitem) = x;
    }
};
/*---------------------------------------------------------------------------*/
void inserctionsort(int *vetor, int dim){
    int copia, indice;
    for(int i = 1; i < dim; i++){
        copia = *(vetor + i);
        indice = i - 1;
        do{
            *(vetor + indice + 1) = *(vetor + indice);
            indice--;
        }while( (indice >= 0) && ( copia < *(vetor + indice) ) );
        *(vetor + indice + 1) = copia;
    }
}
/*---------------------------------------------------------------------------*/
int busca_binaria(int valor,int *vetor, int dim){
    printf("\n");
    int inicio = 0, fim = dim - 1, pmedia = 0;
    do{
        pmedia = (fim + inicio)/2;
        if(valor == *(vetor + pmedia)){
            return pmedia;
        }else if(valor < *(vetor + pmedia)){
            fim = pmedia - 1;
        }else{
            inicio = pmedia + 1;
        }
    }while(inicio <= fim);
    return -1;
};
/*---------------------------------------------------------------------------*/
int menu_select(){
    int ch = 0;
    do{
        printf("Menu de Opcoes\n");
        printf("\t 1 - Preencher aleatoriamente o primeiro vetor\n");
        printf("\t 2 - Preencher aleatoriamente o segundo vetor\n");
        printf("\t 3 - Preencher aleatoriamente o terceiro vetor\n");
        printf("\t 4 - Imprimir vetor 1\n");
        printf("\t 5 - Imprimir vetor 2\n");
        printf("\t 6 - Imprimir vetor 3\n");
        printf("\t 7 - Busca Sequencial (vetor 1)\n");
        printf("\t 8 - Ordena��o por trocas - bubbleSort - (vetor1)\n");
        printf("\t 9 - Ordena��o por sele��o (vetor2)\n");
        printf("\t10 - Ordena��o por inser��o (vetor3)\n");
        printf("\t11 - Busca Bin�ria (vetor 3)\n");
        printf("\t12 - Sair.\n");
        printf("Entre com a opcao desejada: ");
        scanf("%d",&ch); /** L� do teclado a sele��o */
        if((ch < 1) || (ch > 12)){
            printf("\nOpcao Invalida! Tente novamente.\n");
        }
    }while( (ch < 1) || (ch > 12) );
    return ch;
}
/*****************************************************************************/
int main(){
    printf("PROGRAMA TRES VETORES: ORDENACAO - Burble, Selection e Insection\n");
    int choose = 0, *vetor1 = NULL, *vetor2 = NULL, *vetor3 = NULL;
    int elemento_vetor = 0, retorno = 0;
    vetor1 = (int *) calloc(tam,sizeof(int));
    if(vetor1 == NULL){ // teste de aloca��o de mem�ria
        printf("Erro: Mem�ria Insuficiente!\n");
        exit(1);
    }
    vetor2 = (int *) calloc(tam, sizeof(int));
    if(vetor2 == NULL){ // teste de aloca��o de mem�ria
        printf("Erro: Mem�ria Insuficiente!\n");
        exit(1);
    }
    vetor3 = (int *) calloc(tam,sizeof(int));
    if(vetor3 == NULL){ // teste de aloca��o de mem�ria
        printf("Erro: Mem�ria Insuficiente!\n");
        exit(1);
    }

    do{
        printf("\n");
        choose = menu_select();
        switch(choose){
            case 1:
                printf("\n");
                preencher_vetor(vetor1,tam);
                printf("Vetor preechido com sucesso!\n");
                system("pause");
                break;
            case 2:
                printf("\n");
                preencher_vetor(vetor2,tam);
                printf("Vetor preechido com sucesso!\n");
                system("pause");
                break;
            case 3:
                printf("\n");
                preencher_vetor(vetor3,tam);
                printf("Vetor preechido com sucesso!\n");
                system("pause");
                break;
            case 4:
                printf("\n");
                printf("vetor_1 = { ");
                imprimir_vetor(vetor1,tam);
                printf("}\n");
                system("pause");
                break;
            case 5:
                printf("\n");
                printf("vetor_2 = { ");
                imprimir_vetor(vetor2,tam);
                printf("}\n");
                system("pause");
                break;
            case 6:
                printf("\n");
                printf("vetor_3 = { ");
                imprimir_vetor(vetor3,tam);
                printf("}\n");
                system("pause");
                break;
            case 7:
                printf("Informe o valor que deseja buscar: ");
                scanf("%d",&elemento_vetor);
                retorno = busca_sequencial(elemento_vetor,vetor1,tam);
                if(retorno == -1){
                    printf("Valor nao encontrado. ");
                    printf("Nao eh uma componente deste vetor.\n");
                }else{
                    printf("valor encontrado na posicao %d do vetor: ", retorno);
                    printf("v[%d] = %d.\n", retorno, *(vetor1 + retorno));
                }
                system("pause");
                break;
            case 8:
                bublesoft(vetor1, tam);
                printf("Ordena��o realizada como sucesso!\n");
                system("pause");
                break;
            case 9:
                selectionsort(vetor2, tam);
                printf("Ordena��o realizada como sucesso!\n");
                system("pause");
                break;
            case 10:
                inserctionsort(vetor3, tam);
                printf("Ordena��o realizada como sucesso!\n");
                system("pause");
                break;
            case 11:
                printf("Informe o valor que deseja buscar: ");
                scanf("%d",&elemento_vetor);
                retorno = busca_binaria(elemento_vetor,vetor3,tam);
                if(retorno == -1){
                    printf("Valor nao encontrado. ");
                    printf("Nao eh uma componente deste vetor.\n");
                }else{
                    printf("valor encontrado na posicao %d do vetor: ", retorno);
                    printf("vetor[%d] = %d.\n", retorno, *(vetor3 + retorno));
                }
                system("pause");
                break;
            case 12:
                printf("\nVoce escolheu sair do programa.\n");
                exit(0);//return 0;
        }
    }while(choose != 12);
    free(vetor1);
    free(vetor2);
    free(vetor3);
    return 0;
}
/*****************************************************************************/
