/**<| DADOS DE PRODU��O (BEGIN) |>**********************************************
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

    Prop�sito do Programa:

        Implementar uma fun��o miniMax(v,n,a,b) que receba um vetor v,
        contendo n n�meros, e devolva a e b, respectivamente, os valores
        m�nimo e m�ximo entre aqueles armazenados em v.

    Dados de Manuten��o do programa

      Data            Programador                  Descri��o da Mudan�a
    ========    ======================      =================================
    2022/4/9    Alexsandro Lucena Mota      - C�digo original (vers�o 0.1).
    2022/5/9    Alexsandro Lucena Mota      - Acrescimento de coment�rio para
                                              facilitar a manuten��o.
    2022/5/9    Alexsandro Lucena Mota      - Adaptando o programa para aloca��o
                                              din�mica.
    2022/5/9    Alexsandro Lucena Mota      - Implementado o teste de aloca��o
                                              de mem�ria;
                                              Implementado a libera��o de
                                              mem�ria;
                                              Implementado, ap�s libera��o de
                                              mem�ria alocada, a atribui��o NULL
                                              aos ponteiros para evitar que
                                              fiquem soltos.
    2022/17/9   Alexsandro Lucena Mota      - Inclus�o do & na vari�veis vetor e
                                              return_vector quando a fun��o
                                              miniMax() � chamada no escopo da
                                              main.
***<| DADOS DE PRODU��O (END) |>***********************************************/

// Bibliotecas Utilizadas
#include <stdio.h>  // Para entrada e sa�da padr�es
#include <stdlib.h> // Biblioteca padr�o
#include <locale.h>


// Lista de Prot�tipos de Fun��es e Procedimentos
int miniMax();

/**<| ESCOPO DA MAIN FUNCTION (BEGIN) |>***************************************/
int main(){
    setlocale(LC_ALL ,"ptb");
    // Apresenta��o do programa ao usu�rio
    printf("PROGRAMA miniMax\n\n");
    printf("Prop�sito:\n");
    printf("\tRecebe um vetor de dimens�o n e retorna o me-\n");
    printf("\tnor e o maior valor entre suas componentes.\n\n");

    // Entrada de dados
    printf("Entre com a dimens�o do vetor!\n");
    int dim = 0; // incializa a vari�vel dim com valor 0.
    printf("DIM = ");
    scanf("%d", &dim); // usu�rio informa a dimens�o do vetor (array).
    printf("Entre com as componentes (valores inteiros) do vetor!\n");
    int *vetor; // ponteiro vetor (aponta para um endere�o de mem�ria.
    vetor = (int *) malloc (dim*sizeof(int)); /* - alocando mem�ria para vetor;
                                                 - o vetor � do tipo inteiro
                                                 - sizeof(int) retorna o quantidade
                                                   de bytes ocupados pelo tipo int: 4bytes.
                                                 - dim dar o n�mero de componentes do vetor;
                                                   dim multiplica o sizeof(int) provendo o
                                                   n�mero de bytes necess�rio para alocar o
                                                   vetor
                                              */
    if(vetor == NULL){ // teste de aloca��o de mem�ria
        printf("Erro: Mem�ria Insuficiente!\n");
        exit(1);
    }
    for(int i = 0; i < dim; i++){
        scanf("%d", vetor + i); // usu�ro informa os valores de entrada do vetor
    }

    // Ecoando as informa��es entrada
    printf("As componentes informadas foram:\n");
    for(int i = 0; i < dim; i++){
        printf("v[%d] = %d\n", i + 1, *(vetor + i));
    }

    // Sa�da de dados
    int *return_vector; // para passagem de par�mentos de refer�ncia na fun��o miniMax
    return_vector = (int *) malloc (2*sizeof(int)); // retornar� somente duas compontentes
    if(return_vector == NULL){ // teste de aloca��o de mem�ria
        printf("Erro: Mem�ria Insuficiente!\n");
        exit(1);
    }
    miniMax(vetor,dim,return_vector);
    free(vetor); // liberando a mem�ria alocada
    vetor = NULL; // para evitar que o ponteiro fique solto
    printf("O menor valor entre as componentes �: %d.\n", *return_vector);
    printf("O maior valor entre as componentes �: %d.\n", *(return_vector + 1));
    free(return_vector); // liberando a mem�ria alocada
    return_vector = NULL; // para evitar que o ponteiro fique solto

    // Retorno da fun��o
    return 0;
}
/**<| ESCOPO DA MAIN FUNCTION (END) |>*****************************************/
//------------------------------------------------------------------------------
/**<| LISTA DE FUN��ES E PROCEDIMENTOS (BEGIN) |>******************************/
int miniMax(int*in_vector,int num, int*out_vector){
/**<| MINIMAX FUNCTION |>---------------------------------------------------

    Prop�sito:
        Recebe um vetor, sua dimens�o, e retornar o menor
        e menor valor (inteiros) entre suas componentes.
--------------------------------------------------------------------------*/

    // Atribui��es necess�rias
     int minnum = *in_vector; // incializa a vari�vel local minnum
     int maxnum = *in_vector; // incializa a vari�vel local maxnum

     // Rotina para determinar o menor e o maior valor
     for(int i = 1; i < num; i++){
        if( *(in_vector + i) > maxnum){
            maxnum = *(in_vector + i);
        }else if( *(in_vector + i) < minnum){
            minnum = *(in_vector + i);
        }
     }

     /*
        Atribuido as sa�das aos respectivos endere�os de mem�ria
        para acesso externo a fun��o miniMax
    */
     *(out_vector + 0) = minnum;
     *(out_vector + 1) = maxnum;

     // Retorno da fun��o
     return 0;
}
