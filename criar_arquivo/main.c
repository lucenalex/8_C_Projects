/******************************************************************************
    Clientes:
        Universidade Estadual do Maranhão
        Centro de Ciências Tecnológicas
        Departamento de Engenharia da Computação
        Curso de Engenharia da Computação
        Disciplina: Estrutura de Dados Básica (ASL092N321)
        Semestre: 2022.4         Turma: 01
        Professores:
            Igor Ramos Campos

    Autores:
        Alunos:
            Alexsandro Lucena Mota   Código: 20210024710

    Título: Ordenação

    Propósito do Programa:

        - Gerar arquivo de 1000000 de números;
        - Implementar os algoritimos de ordenação:
            - Burble Sort,
            - Selection Sort,
            - Inserction Sort;
        - Fazer um relatório de performace.

    Dados de Manutenção do programa

      Data            Programador                  Descrição da Mudança
    ==========    ======================      =================================
    2023/30/01    Alexsandro Lucena Mota      - Código original (versão 0.1).

*******************************************************************************/
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>
/******************************************************************************/
#define tam 10 // Quantidade de números a serem gerados
#define BILLION  1000000000.0
/******************************************************************************/
void gerar_vetor_de_numeros(int *vetor,int dim);
//-----------------------------------------------------------------------------
void imprimir_vetor(int *vetor,int dim);
//-----------------------------------------------------------------------------
void bublesort(int *vetor, int dim);
//-----------------------------------------------------------------------------
int menor_item(int *vetor, int dim, int enesimo_item);
void selectionsort(int *vetor, int dim);
//-----------------------------------------------------------------------------
void inserctionsort(int *vetor, int dim);
/******************************************************************************/
int main(){
    setlocale(LC_ALL,"Portuguese");

    printf("\n\t******* PROGRAMA GERA UM MILHÃO DE NÚMEROS E ORDENA *******\n");

    printf("\n\tEste programa irá gerar mil números e armazená-los em\n");
    printf("\n\tum arquivo chamado um_milhao_de_numeros.txt\n");

    printf("\n\t*************** GERANDO UM MILHÃO DE NÚMEROS **************\n\t");
    system("pause");

    int *vetor = NULL;

    vetor = (int *) calloc(tam,sizeof(int));
    if(vetor == NULL){ // teste de alocação de memória
        printf("Erro: Memória Insuficiente!\n");
        exit(1);
    }

    gerar_vetor_de_numeros(vetor,tam);

    printf("\n\tNúmeros gerados com sucesso!\n\t");
    system("pause");

//-----------------------------------------------------------------------------

    printf("\n\t******* CRIANDO O ARQUIVO E SALVANDO OS NÚMEROS *******\n");

    FILE *file;

    file = fopen("um_milhao_de_numeros.txt","w+");

    if(file == NULL){
        printf("\n\tErro na abertura do arquivo.\n");
        system("pause");
        exit(1);
    }
    else{
        printf("\n\tCriação do arquivo foi bem-sucedida!\n");
        printf("\n\tSalvando os números no arquivo.\n");

        for(int i = 0; i < tam; i++){
            fprintf(file,"%d\n",*(vetor + i));
        }
    }

    printf("\n\tFechando o arquivo. \n");

    fclose(file);
//-----------------------------------------------------------------------------
    free(vetor);

    printf("\n\t**************** IMPRESSÃO NA TELA ****************\n");

    printf("\n\tDeseja abrir o arquivo, lê os números e imprimir na tela?");
    printf("\n\t(1) Sim\t(2) Não.\n");

    printf("\n\tInforme a sua escolha: ");
    int choose;

    scanf("%d",&choose);

    if(choose == 1){

        FILE *file;

        file = fopen("um_milhao_de_numeros.txt","r");

        if(file == NULL){
            printf("\n\tErro na abertura do arquivo.\n");
            system("pause");
            exit(1);
        }
        else{
            printf("\n\tAbertura do arquivo foi bem-sucedida!\n");
        }

        rewind(file);// faz o ponteiro retornar ao inicio do arquivo

        int *v_file = NULL;

        v_file = (int *) calloc(tam,sizeof(int));

        if(v_file == NULL){ // teste de alocação de memória
            printf("Erro: Memória Insuficiente!\n");
            exit(1);
        }
        int count =0;
        while(count < tam){
            fscanf(file,"%d",(v_file + count));
            count++;
        }
        printf("\n\tLista de números salvos no arquivo:\n\n");
        imprimir_vetor(v_file,tam);

        free(v_file);

        fclose(file);
    }

    printf("\n\t**************** ORDENAÇÃO DOS NÚMEROS ****************\n");

    printf("\n\tDeseja abrir o arquivo, lê os números e executar os métodos");
    printf("\n\tde ordenação Burble Sort, Select Sort e Inserction Sort,");
    printf("\n\tnessa ordem?(1) Sim.\t(2) Não, sair do programa.");
    printf("\n\tInforme sua decisão: ");

    scanf("%d",&choose);

    if(choose == 1){

        FILE *file;

        file = fopen("um_milhao_de_numeros.txt","r");

        if(file == NULL){
            printf("\n\tErro na abertura do arquivo.\n");
            system("pause");
            exit(1);
        }
        else{
            printf("\n\tAbertura do arquivo foi bem-sucedida!\n");
        }


        struct timespec start, end;

        printf("\n\t1) Burble sort:\n");

        double burble_sort_time = 0.0;

        int *v_burble = NULL;
        v_burble = (int *) calloc(tam,sizeof(int));

        if(v_burble == NULL){ // teste de alocação de memória
            printf("Erro: Memória Insuficiente!\n");
            exit(1);
        }

        rewind(file);

        for(int i = 0; i < tam; i++){
            fscanf(file ,"%d",v_burble + i);
        }

        /* for(int i = 0; i < tam; i++){
               printf("%d,",*(v_burble + i));
           } */

        clock_gettime(CLOCK_REALTIME, &start);

            bublesort(v_burble, tam);

        clock_gettime(CLOCK_REALTIME, &end);

        printf("\n\tOrdenação realizada como sucesso!\n\t");
        system("pause");

        // burble_sort_time = fim - início
        burble_sort_time = (end.tv_sec - start.tv_sec) +
                           (end.tv_nsec - start.tv_nsec) / BILLION;

        printf("\n\tTempo de execução do Burble Sort: %.7f s.\n", burble_sort_time);

        printf("\n\tDeseja imprimir a lista de números ordenados? (1) Sim\t(2) Não");
        printf("\n\tInforme sua decisão: ");
        scanf("%d",&choose);

        if(choose == 1){
            printf("\n\tLista de números salvos em arquivo: ");
            imprimir_vetor(v_burble,tam);
        }

        //free(v_burble);
        //----------------------------------------------------------------------
        printf("\n\t2) Selection sort:\n");

        double selection_sort_time = 0.0;
        int *v_selection = NULL;

        v_selection = (int *) calloc(tam,sizeof(int));

        if(v_selection == NULL){ // teste de alocação de memória
            printf("Erro: Memória Insuficiente!\n");
            exit(1);
        }

        rewind(file);

        for(int i = 0; i < tam; i++){
            fscanf(file,"%d",v_selection + i);
        }

        clock_gettime(CLOCK_REALTIME, &start);

            selectionsort(v_selection, tam);

        clock_gettime(CLOCK_REALTIME, &end);

        printf("\n\tOrdenação realizada como sucesso!\n\t");
        system("pause");

        // selection_sort_time = fim - início
        selection_sort_time = (end.tv_sec - start.tv_sec) +
                              (end.tv_nsec - start.tv_nsec) / BILLION;

        printf("\n\tTempo de execução do Selection Sort: %.7f s.\n", selection_sort_time);

        printf("\n\tDeseja imprimir a lista de números ordenados? (1) Sim,\t(2) Não");
        printf("\n\tInforme sua decisão: ");
        scanf("%d",&choose);

        if(choose == 1){
            printf("\n\tLista de números salvos em arquivo:\n\n");
            imprimir_vetor(v_selection,tam);
        }

        free(v_selection);
        //----------------------------------------------------------------------

        printf("\n\t3) Inserction sort:\n");

        double inserction_sort_time = 0.0;
        int *v_inserction = NULL;

        v_inserction = (int *) calloc(tam,sizeof(int));

        if(v_inserction == NULL){ // teste de alocação de memória
            printf("Erro: Memória Insuficiente!\n");
            exit(1);
        }

        rewind(file);

        for(int i = 0; i < tam; i++){
            fscanf(file,"%d",v_inserction + i);
        }

        clock_gettime(CLOCK_REALTIME, &start);

            inserctionsort(v_inserction, tam);

        clock_gettime(CLOCK_REALTIME, &end);

        printf("\n\tOrdenação realizada como sucesso!\n\t");
        system("pause");

        // inserction_sort_time = fim - início
        inserction_sort_time = (end.tv_sec - start.tv_sec) +
                               (end.tv_nsec - start.tv_nsec) / BILLION;

        printf("\n\tTempo de execução do Inserction Sort: %.7f s.\n", selection_sort_time);

        printf("\n\tDeseja imprimir a lista de números ordenados? (1) Sim\t(2) Não");
        printf("\n\tInforme sua decisão: \n");
        scanf("%d",&choose);

        if(choose == 1){
            printf("\n\tLista de números salvos em arquivo:\n\n");
            imprimir_vetor(v_inserction,tam);
        }

        free(v_inserction);

        fclose(file);

        printf("\n\t");
        system("pause");

        printf("\n\t**************** RELATÓRIO DE PERFOMACE ***************\n");

        printf("\n\t    Burble Sort = %.7f;\n",burble_sort_time);
        printf("\n\t  Selecton Sort = %.7f;\n",selection_sort_time);
        printf("\n\tInserction Sort = %.7f;\n",inserction_sort_time);
    }

    return 0;
}
/******************************************************************************/
void gerar_vetor_de_numeros(int *vetor,int dim){ // Preenche um vetor
    srand(time(NULL)); // Muda o ponto de partida de rand a cada nova execução.
    for(int i = 0; i < dim; i++){ // Varre cada posição do vetor    */
        *(vetor + i) = rand()%tam; // Atribui valor aleatório de 0 até 1000000.
    }
}
/******************************************************************************/
void imprimir_vetor(int *vetor,int dim){
    for(int i = 0; i < dim; i++){
        printf("%d ",*(vetor + i));
    }
    printf("\n");
};
/******************************************************************************/
void bublesort(int *vetor, int dim){// Ordenação por troca
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
/******************************************************************************/
int menor_item(int *vetor, int dim, int enesimo_item){
    int minitem = enesimo_item; // item mínimo recebe o item inicial (valor)
    for(int j = enesimo_item + 1; j < dim; j++){
        if( *(vetor + minitem) > *(vetor + j) ){
            minitem = j; // item mínimo recebe o indice do menor valor da lista
        }
    }
    return minitem;
}
/*****************************************************************************/
void selectionsort(int *vetor, int dim){
    int x = 0, minitem = 0;
    for(int i = 0; i < dim - 1; i++){
        minitem = menor_item(vetor, dim, i);
        x = *(vetor + i);
        *(vetor + i) = *(vetor + minitem);
        *(vetor + minitem) = x;
    }
}
/******************************************************************************/
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
/******************************************************************************/
