/*******************************************************************************
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

PROVA PR�TICA DE ESTRUTURA DE DADOS (AVALIA��O 1):
T�TULO: URNA ELETR�NICA		DATA DE ENTREGA: 05/11/2022

Prop�sito do Programa: Implementa��o de uma URNA ELETR�NICA em C.

Inicialmente usando um registro de eleitores e outro de candidatos com struct,
sendo as mesmas din�micas (isto �, fazendo uso de lista encadeada), forne�a as
fun��es de inser��o e exclus�o. Em seguida desenvolva uma fun��o para a vota��o
fazendo uso de um registro de votos. Existir�o pelo menos 20 candidatos a
vereador a serem distribu�dos nos seguintes partidos: PBA, PBB, PBC, PBD e PBE.
Um eleitor poder� votar em um candidato cadastrado mas primeiro ele informar� na
urna o seu c�digo e depois o n�mero do candidato desejado. Ao buscar um
candidato ou eleitor aplique a busca bin�ria. Utilize um menu de op��es.
Finalmente, usando o registro RESULTADO montar um lista cotendo os candidatos
por ordem descendente de votos e tamb�m dos partidos. Salve as informa��es do
registro dos eleitores em um arquivo com pelo menos 200 eleitores.

Dados de Manuten��o do programa

Data          Programador                 Descri��o da Mudan�a
==========    ======================      =================================
2022/13/10    Alexsandro Lucena Mota      - C�digo original (vers�o 0.1).
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
/******************************************************************************/
/**> Inicialmente, com struct:
     - 1 registro de eleitores;
     - 1 resgistro de candidatos
     fornecer as fun��es de inser��o e exclus�o. <**/

/**> Estrutura para registro de eleitores e candidatos <**/
typedef struct no{
    int  id;
    char nome[50];
    char filiacao[5];
    struct no *proximo;
}registro;
/******************************************************************************/
/**> cria��o: retorna um registro vazio <**/
registro *criar_registro(){
    return NULL;
};
//----------------------------------------------------------------------------//
/**> vazia: retorna 1 se o registro est� vazia, do contr�rio 0 <**/
int vazia(registro *reg){
    return (reg == NULL);
};
//----------------------------------------------------------------------------//
/**> inser��o: retorna registro atualizado <**/
registro *insercao(registro *reg, int codigo, char name[], char partido[]){
    registro *novo = (registro*) calloc(1,sizeof(registro));
    novo->id = codigo;
    strcpy(novo->nome,name);
    strcpy(novo->filiacao,partido);
    novo->proximo = reg;
    return novo;
};
//---------------------------------------------------------------------------//
/**> exclus�o: exclui um membro do registro <**/
registro* exclusao(registro *reg, int cod){
    registro *anterior = NULL;  /**> ponteiro para o membro anterior <**/
    registro *percorre = reg; /**> ponteiro para percorrer o registro <**/
    /**> procura elemento no registro, guardando anterior <**/
    while( (percorre!=NULL) && (percorre->id != cod) ){
        anterior = percorre;
        percorre = percorre -> proximo;
    }
    /**> verifica se achou o membro <**/
    if(percorre == NULL){
        return reg; /**> n�o achou: retorna registro original <**/
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
//----------------------------------------------------------------------------//
/**> imprime a lista de pessoas registradas <**/
void imprime_registro(registro *reg){
    registro *pessoa;
    for(pessoa = reg; pessoa != NULL; pessoa = pessoa->proximo){
        printf("codigo = %d\n",pessoa->id);
        printf("nome = %s\n",pessoa->nome);
        printf("partido = %s\n",pessoa->filiacao);
    }
}
/******************************************************************************/
int main(){
    setlocale(LC_ALL,"pbr");
    /** declara registros de candidatos e eleitores n�o inicializados*/
    registro *candidatos;
    registro *eleitores;
    /** cria e inicializa registros vazios */
    candidatos = criar_registro();
    eleitores = criar_registro();
/**

Em seguida:
    - 1 fun��o para a vota��o fazendo uso de um registro de votos.
      Existir�o pelo menos 20 candidatos a vereador a serem distribu�dos nos
    seguintes partidos: PBA, PBB, PBC, PBD e PBE.
    - 1 eleitor poder� votar em um candidato cadastrado mas primeiro ele
    informar� na urna o seu c�digo e depois o n�mero do candidato desejado.

    Ao buscar um candidato ou eleitor aplique a busca bin�ria.
    Utilize um menu de op��es.

    Finalmente, usando o registro RESULTADO montar um lista cotendo os
    candidatos por ordem descendente de votos e tamb�m dos partidos.

    Salve as informa��es do registro dos eleitores em um arquivo com
    pelo menos 200 eleitores.*/
    return 0;
}
/******************************************************************************/
