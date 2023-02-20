// Bibliotecas Utilizadas
#include <stdio.h> // Para entrada e sa�da padr�es
#include <stdlib.h> // Biblioteca padr�o
#include <string.h>
#include <locale.h>
#define tam 3
// Dados de Produ��o
/**
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

        Codificar um programa, usando aloca��o din�mica e struct que armazene
        30 alunos com os campos nome, matricula, disciplina e m�dia, para as
        disciplinas POO, AOC e MATDISC usando vetor. Crie uma fun��o que cal-
        le a m�dia das m�dias.

    Dados de Manuten��o do programa

      Data            Programador                  Descri��o da Mudan�a
    ========    ======================      =================================
    2022/4/9    Alexsandro Lucena Mota      - C�digo original (vers�o 0.1).

*/

// Declara��o de Vari�veis Globais e/ou Novos tipos.
typedef struct{
     char nome_disc[12]; // 12 bytes
    float media;// 4 bytes
}tp_disc; // 16 bytes
typedef struct{
      char nome[76]; // 76 bytes
       int matricula; // 4 bytes
   tp_disc disciplina[3]; // 16X3 = 48 bytes
}tp_alunos; // 64 bytes

// Lista de Prot�tipos de Fun��es e Procedimentos
void boletim();
void digitar_media();
int  media_das_Medias();

// Escopo da Fun��o Main
int main(){
    setlocale(LC_ALL,"ptb");
    // Apresenta��o do programa ao usu�rio
    printf("PROGRAMA CONTROLE ACAD�MICO\n\n");
    printf("Prop�sito:\n");
    printf("\tFaz a gest�o de Controle Acad�micos de alunos: cadastra  nome,\n");
    printf("\tmatricula, disciplina e m�dia do aluno em cada disciplina. De-\n");
    printf("\ttermina ainda o coeficiente de rendimento do aluno (media  das\n");
    printf("\tm�dias das disciplinas nas quais o aluno est� matriculado.  \n\n");

    /*
    printf("tamanho to tipo char: %lld\n", sizeof(char));
    printf("tamanho to tipo float: %lld\n", sizeof(float));
    printf("tamanho to tipo tp_disc: %lld\n", sizeof(tp_disc));
    printf("tamanho to tipo tp_alunos: %lld\n", sizeof(tp_alunos));
    */

    // Entrada de dados
    int opcao = 0, indice = 0; // incializa a vari�vel opcao e indice com valor 0.
    tp_alunos *aluno[tam]; // ponteiro para novos alunos

    // aloca��o din�mica
    for(int i = 0; i < tam; i++){
        aluno[i] = malloc(sizeof(tp_alunos));
        if(aluno[i] == NULL){
            printf("Erro: Mem�ria Insuficiente!\n");
            exit(1);
        }
    }

    // Inicializa��o das m�dias com o valor nulo
    for(int i = 0; i < tam; i++ ){
        for(int j = 0; j < 3; j++){
            aluno[i]->disciplina[j].media = 0.;
        }
    }

    // Cadastramento de Alunos
    do{ // o usu�rio poder� informar at� tam alunos no cadastro
        printf("Deseja Cadastrar um novo aluno?\n");
        printf("\t1 - Sim \t2-N�o\n");
        printf("Informe a op��o escolhida: ");
        scanf("%d", &opcao); // usu�rio informa a op��o escolhida.
        getchar(); // limpa o buffer do teclado
        if( (opcao < 1) || (opcao > 2)){ /*> Para inv�lidar outros valores
                                            que n�o sejam 1 ou 2.
                                         */
            printf("\n\n\tOP��O INV�LIDA!\n");
        }else if( (opcao == 1) ){ // Em caso de 1, cadastrar o aluno
            printf("\n");
            if( indice == tam){ // Para impedir o n�mero tam de alunos seja estourado
                printf("N�o � poss�vel incluir novos alunos!\n");
                printf("Limite m�ximo excedito!\n\n");
                system("pause");
                printf("Pressione qualquer tecla para sair do cadastro.\n");
                opcao = 2;
            }else{ //Cadastrar nome do aluno e assoicar uma matricula
                printf("Informe o nome: ");
                gets(aluno[indice]->nome);
                aluno[indice]->matricula = indice + 1;
                printf("Aluno matriculado com sucesso!\n");
                printf("Matricula n�. %d.\n\n",aluno[indice]->matricula);

                //Matricula de alunos em disciplinas
                printf("Deseja realizar a matricula deste aluno em disciplinas?\n");
                printf("\t1 - Sim \t2-N�o\n");
                printf("Informe a op��o escolhida: ");
                int opmat = 0;
                scanf("%d",&opmat);
                do{
                    if( (opmat < 1 ) || (opmat > 2) ){ // Evita que usu�rio digite um
                            // valor idesejado.
                        printf("\n\n\tOP��O INV�LIDA!\n");
                    }else if( opmat == 1){// Apresenta a lista de disciplinas dispon�veis
                        printf("\n");
                        printf("Lista de disciplinas dispon�veis para matricula:\n");
                        printf("1 - Programa��o Orientada a Objetos (POO);\n");
                        printf("2 - Arquitetura e Organiza��o de Computadores (AOC);\n");
                        printf("3 - Matem�tica Discreta (MATDISC).\n\n");
                        int quant_disc = 0; // Para n�mero de disciplinas a se matricular
                        do{
                            printf("Informe em quantas disciplinas deseja se matricular: ");
                            scanf("%d", &quant_disc);
                            if( (quant_disc < 1) || (quant_disc > 3) ){
                                printf("\n\n\tOP��O INV�LIDA!\n");
                            }
                        }while((quant_disc < 1) || (quant_disc > 3));
                        int cod_disc = 0;
                        for(int j = 0; j < quant_disc; j++){
                            printf("Digite o c�digo da disciplina: ");
                            scanf("%d",&cod_disc);
                            if(cod_disc == 1){
                                strcpy( aluno[j]->disciplina[cod_disc].nome_disc,"POO");
                            }else if(cod_disc == 2){
                                strcpy( aluno[j]->disciplina[cod_disc].nome_disc,"AOC");
                            }else if(cod_disc == 3){
                                strcpy( aluno[j]->disciplina[cod_disc].nome_disc,"MATDISC");
                            }
                        }
                        printf("\n");
                        opmat = 2;
                    }else if( opmat == 2){} // Em caso de 2, sair sem fazer nada.
                }while(opmat != 2);
                indice++; // p�s-incremento do indice.
            }
        }else if( (opcao == 2) ){} // Em caso de 2, sair sem fazer nada.
    }while(opcao != 2);
    printf("\n");
    // Informar Boletim, M�dias ou Sair do Programa
    //  A - Tomada de Decis�o
    printf("Informe o que deseja fazer:\n");
    do{
        printf("\t1 - Visualizar Boletim \t2 - Sair do Progrma\n");
        printf("Informe a op��o escolhida: ");
        scanf("%d",&opcao);
        if( (opcao < 1) || (opcao > 2)){ /*> Para inv�lidar outros valores
                                            que n�o sejam 1 ou 2.
                                         */
            printf("\n\n\tOP��O INV�LIDA!\n");
        }else if( (opcao == 1) ){ // Visualizar Boletim
            int opdisc = 0;
            do{
                printf("Qual disciplina deseja visulizar o Boletim:\n");
                printf("\t1 - POO \t2 - AOC \t3 - MATDISC\n");
                printf("Informe a op��o escolhida: ");
                scanf("%d",&opdisc);
                if((opdisc < 1) || (opdisc >3)){
                    printf("\n\n\tOP��O INV�LIDA!\n");
                }
            }while( (opdisc < 1) || (opdisc >3));
            boletim(opdisc,indice,*aluno[indice]);
        }else if( opcao == 2){
            opcao = 2;
        }
    }while(opcao != 2);
    return 0;
}

void digitar_media(int indice, char nm_d[8],tp_alunos *aluno[]){
    int opmt = 0, dig_md = 0;
    do{
        printf("Informe a matricula do aluno: ");
        scanf("%d",&opmt);
        for(int j = 0; j < indice; j++){
            for(int k = 0; k < 3; k++){
                if( strcmp(nm_d,aluno[j]->disciplina[k].nome_disc) == 0){
                    if( opmt == aluno[j]->matricula){
                        printf("\n");
                        printf("Informe a m�dia do aluno: ");
                        scanf("%f",&aluno[j]->disciplina[k].media);
                    }
                }
            }
        }
        getchar();
        printf("\n");
        printf("Continuar digitando m�dias para esta disciplina?\n");
        printf("\t1 - Sim \t2 - N�o\n");
        printf("Informe a escolha: ");
        scanf("%d",&dig_md);
    }while(dig_md != 2);
}

void boletim(int opdisc,int indice,tp_alunos *aluno[]){
    printf("\n");
    char nm_d[8];
    if(opdisc == 1){
        strcpy(nm_d, "POO");
    }else if(opdisc == 2){
        strcpy(nm_d, "AOC");
    }else if(opdisc == 3){
        strcpy(nm_d, "MATDISC");
    }

    printf("Boletim da disciplina %s\n\n",nm_d);

    for(int j = 0; j < indice; j++){
        for(int k = 0; k < 3; k++){
            if( strcmp(nm_d,aluno[j]->disciplina[k].nome_disc) == 0){
                printf("Matricula: %d",aluno[j]->matricula);
                printf("\tNome: %s",aluno[j]->nome);
                printf("\tM�dia: %.2f\n",aluno[j]->disciplina[k].media);
            }
        }
    }
    printf("\n");
    int opmd = 0;
    printf("Deseja informar a m�dia dos alunos?\n");
    do{
        printf("\t1 - Sim \t2 - N�o\n");
        scanf("%d",&opmd);
        if( (opmd < 1) || (opmd > 2) ){
            printf("\n\n\tOP��O INV�LIDA!\n");
            printf("\n\n\tODigite uma op��o V�LIDA!\n");
        }
    }while((opmd < 1) || (opmd > 2));

    if(opmd == 1){
       // digitar_media(indice, nm_d,aluno);
    }else if(opmd == 2){}
}

