/******************************************************************************
    Clientes:
        Universidade Estadual do Maranhão
        Centro de Ciências Tecnológicas
        Departamento de Engenharia da Computação
        Curso de Engenharia da Computação
        Disciplina: Estrutura de Dados Básica (ASL092N321)
        Semestre: 2022.2         Turma: 01
        Professores:
            Lúis Carlos Fonseca
            Pedro Brandão Neto

    Autores:
        Alunos:
            Alexsandro Lucena Mota   Código: 20210024710

    Título: Atividade Prática

    Propósito do Programa:

        Crie uma programa para preencher 2 vetores: Um não ordenado e o outro
        ordenado. Ambos com tamanho 8. Usar funções. Crie um menu de texto com
        as seguintes opções:
            1) Preencher vetor 1
            2) Preencher vetor 2
            3) Busca Sequencial (vetor 1)
            4) Busca Binária (vetor 2)
            5) Imprimir vetor 1
            6) Imprimir vetor 2
            7) Sair.

    Dados de Manutenção do programa

      Data            Programador                  Descrição da Mudança
    ==========    ======================      =================================
    2022/12/10    Alexsandro Lucena Mota      - Código original (versão 0.1).
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define tam 8

/*****************************************************************************/
int  menu_select();
void preencher_vetor();
int  busca_sequencial();
int  busca_binaria();
void imprimir_vetor();
/*****************************************************************************/
int main(){
    printf("PROGRAMA DOIS VETORES: ORDENADO E NAO ORDENADO\n");
    int choose = 0, *vetor1 = NULL, *vetor2 = NULL;
    int elemento_vetor = 0, retorno = 0;
    vetor1 = (int *) malloc(tam*sizeof(int));
    if(vetor1 == NULL){ // teste de alocação de memória
        printf("Erro: Memória Insuficiente!\n");
        exit(1);
    }
    vetor2 = (int *) malloc(tam*sizeof(int));
    if(vetor2 == NULL){ // teste de alocação de memória
        printf("Erro: Memória Insuficiente!\n");
        exit(1);
    }
    for(int i = 0; i < tam; i++){
        *(vetor1 + i) = NULL;
        *(vetor2 + i) = NULL;
    }
    do{
        printf("\n");
        choose = menu_select();
        switch(choose){
            case 1:
                printf("\n");
                printf("Preencha o vetor sem se preocupar com a ordem: ");
                preencher_vetor(vetor1);
                break;
            case 2:
                printf("\n");
                printf("Preencha o vetor de forma ordenada, ou seja, ");
                printf("em ordem crescente ou descrescente: ");
                preencher_vetor(vetor2);
                break;
            case 3:
                printf("Informe o valor que deseja buscar: ");
                scanf("%d",&elemento_vetor);
                retorno = busca_sequencial(elemento_vetor,vetor1);
                if(retorno == -1){
                    printf("Valor nao encontrado. ");
                    printf("Nao eh uma componente deste vetor.\n");
                }else{
                    printf("valor encontrado na posicao %d do vetor: ", retorno);
                    printf("vetor[%d] = %d.\n", retorno, *(vetor1 + retorno));
                }
                break;
            case 4:
                printf("Informe o valor que deseja buscar: ");
                scanf("%d",&elemento_vetor);
                retorno = busca_binaria(elemento_vetor,vetor2);
                if(retorno == -1){
                    printf("Valor nao encontrado. ");
                    printf("Nao eh uma componente deste vetor.\n");
                }else{
                    printf("valor encontrado na posicao %d do vetor: ", retorno);
                    printf("vetor[%d] = %d.\n", retorno, *(vetor2 + retorno));
                }
                break;
            case 5:
                printf("\n");
                printf("vetor_1 = { ");
                imprimir_vetor(vetor1);
                printf("}\n");
                break;
            case 6:
                printf("\n");
                printf("vetor_2 = { ");
                imprimir_vetor(vetor2);
                printf("}\n");
                break;
            case 7:
                printf("\nVoce escolheu sair do programa.\n");
                exit(0);//return 0;
        }
    }while(choose != 7);
    free(vetor1);
    free(vetor2);
    return 0;
}
/*****************************************************************************/
int menu_select(){
    int ch = 0;
    do{
        printf("Menu de Opcoes\n");
        printf("\t1 - Preencher vetor 1 (Desordenado)\n");
        printf("\t2 - Preencher vetor 2 (Ordenado)\n");
        printf("\t3 - Busca Sequencial (vetor 1)\n");
        printf("\t4 - Busca Binária (vetor 2)\n");
        printf("\t5 - Imprimir vetor 1\n");
        printf("\t6 - Imprimir vetor 2\n");
        printf("\t7 - Sair.\n");
        printf("Entre com a opcao desejada: ");
        scanf("%d",&ch); /** Lê do teclado a seleção */
        if((ch < 1) || (ch > 7)){
            printf("\nOpcao Invalida! Tente novamente.\n");
        }
    }while( (ch < 1) || (ch > 7) );
    return ch;
}
/*---------------------------------------------------------------------------*/
void preencher_vetor(int *vetor){
    for(int i = 0; i < tam; i++){
        scanf("%d",vetor + i);
    }
};
/*---------------------------------------------------------------------------*/
int busca_sequencial(int valor, int *vetor){
    printf("\n");
    for(int i = 0; i < tam; i++){
        if(valor == *(vetor + i)){
            return i;
        }
    }
    return -1;
};
/*---------------------------------------------------------------------------*/
int busca_binaria(int valor,int *vetor){
    printf("\n");
    int inicio = 0, fim = tam - 1, pmedia = 0;
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
void imprimir_vetor(int *vetor){
    for(int i = 0; i < tam; i++){
        printf("%d ",*(vetor + i));
    }
};
/*---------------------------------------------------------------------------*/
