/*******************************************************************************
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

PROVA PRÁTICA DE ESTRUTURA DE DADOS (AVALIAÇÃO 1):
TÍTULO: URNA ELETRÔNICA		DATA DE ENTREGA: 05/11/2022

Propósito do Programa: Implementação de uma URNA ELETRÔNICA em C.

Inicialmente usando um registro de eleitores e outro de candidatos com struct,
sendo as mesmas dinâmicas (isto é, fazendo uso de lista encadeada), forneça as
funções de inserção e exclusão. Em seguida desenvolva uma função para a votação
fazendo uso de um registro de votos. Existirão pelo menos 20 candidatos a
vereador a serem distribuídos nos seguintes partidos: PBA, PBB, PBC, PBD e PBE.
Um eleitor poderá votar em um candidato cadastrado mas primeiro ele informará na
urna o seu código e depois o número do candidato desejado. Ao buscar um
candidato ou eleitor aplique a busca binária. Utilize um menu de opções.
Finalmente, usando o registro RESULTADO montar um lista cotendo os candidatos
por ordem descendente de votos e também dos partidos. Salve as informações do
registro dos eleitores em um arquivo com pelo menos 200 eleitores.

Dados de Manutenção do programa

Data          Programador                 Descrição da Mudança
==========    ======================      =================================
2022/13/10    Alexsandro Lucena Mota      - Código original (versão 0.1).
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
/******************************************************************************/
/**> Inicialmente, com struct:
     - 1 registro de eleitores;
     - 1 resgistro de candidatos
     fornecer as funções de inserção e exclusão. <**/

/**> Estrutura para registro de eleitores e candidatos <**/
typedef struct no{
    int  id;
    char nome[50];
    char filiacao[5];
    struct no *proximo;
}registro;
/******************************************************************************/
/**> criação: retorna um registro vazio <**/
registro *criar_registro(){
    return NULL;
};
//----------------------------------------------------------------------------//
/**> vazia: retorna 1 se o registro está vazia, do contrário 0 <**/
int vazia(registro *reg){
    return (reg == NULL);
};
//----------------------------------------------------------------------------//
/**> inserção: retorna registro atualizado <**/
registro *insercao(registro *reg, int codigo, char name[], char partido[]){
    registro *novo = (registro*) calloc(1,sizeof(registro));
    novo->id = codigo;
    strcpy(novo->nome,name);
    strcpy(novo->filiacao,partido);
    novo->proximo = reg;
    return novo;
};
//---------------------------------------------------------------------------//
/**> exclusão: exclui um membro do registro <**/
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
    /** declara registros de candidatos e eleitores não inicializados*/
    registro *candidatos;
    registro *eleitores;
    /** cria e inicializa registros vazios */
    candidatos = criar_registro();
    eleitores = criar_registro();
/**

Em seguida:
    - 1 função para a votação fazendo uso de um registro de votos.
      Existirão pelo menos 20 candidatos a vereador a serem distribuídos nos
    seguintes partidos: PBA, PBB, PBC, PBD e PBE.
    - 1 eleitor poderá votar em um candidato cadastrado mas primeiro ele
    informará na urna o seu código e depois o número do candidato desejado.

    Ao buscar um candidato ou eleitor aplique a busca binária.
    Utilize um menu de opções.

    Finalmente, usando o registro RESULTADO montar um lista cotendo os
    candidatos por ordem descendente de votos e também dos partidos.

    Salve as informações do registro dos eleitores em um arquivo com
    pelo menos 200 eleitores.*/
    return 0;
}
/******************************************************************************/
