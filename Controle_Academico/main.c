// Bibliotecas Utilizadas
#include <stdio.h> // Para entrada e saída padrões
#include <stdlib.h> // Biblioteca padrão
#include <string.h>
#include <locale.h>
#define tam 3
// Dados de Produção
/**
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

    Propósito do Programa:

        Codificar um programa, usando alocação dinâmica e struct que armazene
        30 alunos com os campos nome, matricula, disciplina e média, para as
        disciplinas POO, AOC e MATDISC usando vetor. Crie uma função que cal-
        le a média das médias.

    Dados de Manutenção do programa

      Data            Programador                  Descrição da Mudança
    ========    ======================      =================================
    2022/4/9    Alexsandro Lucena Mota      - Código original (versão 0.1).

*/

// Declaração de Variáveis Globais e/ou Novos tipos.
typedef struct{
     char nome_disc[12]; // 12 bytes
    float media;// 4 bytes
}tp_disc; // 16 bytes
typedef struct{
      char nome[76]; // 76 bytes
       int matricula; // 4 bytes
   tp_disc disciplina[3]; // 16X3 = 48 bytes
}tp_alunos; // 64 bytes

// Lista de Protótipos de Funções e Procedimentos
void boletim();
void digitar_media();
int  media_das_Medias();

// Escopo da Função Main
int main(){
    setlocale(LC_ALL,"ptb");
    // Apresentação do programa ao usuário
    printf("PROGRAMA CONTROLE ACADÊMICO\n\n");
    printf("Propósito:\n");
    printf("\tFaz a gestão de Controle Acadêmicos de alunos: cadastra  nome,\n");
    printf("\tmatricula, disciplina e média do aluno em cada disciplina. De-\n");
    printf("\ttermina ainda o coeficiente de rendimento do aluno (media  das\n");
    printf("\tmédias das disciplinas nas quais o aluno está matriculado.  \n\n");

    /*
    printf("tamanho to tipo char: %lld\n", sizeof(char));
    printf("tamanho to tipo float: %lld\n", sizeof(float));
    printf("tamanho to tipo tp_disc: %lld\n", sizeof(tp_disc));
    printf("tamanho to tipo tp_alunos: %lld\n", sizeof(tp_alunos));
    */

    // Entrada de dados
    int opcao = 0, indice = 0; // incializa a variável opcao e indice com valor 0.
    tp_alunos *aluno[tam]; // ponteiro para novos alunos

    // alocação dinâmica
    for(int i = 0; i < tam; i++){
        aluno[i] = malloc(sizeof(tp_alunos));
        if(aluno[i] == NULL){
            printf("Erro: Memória Insuficiente!\n");
            exit(1);
        }
    }

    // Inicialização das médias com o valor nulo
    for(int i = 0; i < tam; i++ ){
        for(int j = 0; j < 3; j++){
            aluno[i]->disciplina[j].media = 0.;
        }
    }

    // Cadastramento de Alunos
    do{ // o usuário poderá informar até tam alunos no cadastro
        printf("Deseja Cadastrar um novo aluno?\n");
        printf("\t1 - Sim \t2-Não\n");
        printf("Informe a opção escolhida: ");
        scanf("%d", &opcao); // usuário informa a opção escolhida.
        getchar(); // limpa o buffer do teclado
        if( (opcao < 1) || (opcao > 2)){ /*> Para inválidar outros valores
                                            que não sejam 1 ou 2.
                                         */
            printf("\n\n\tOPÇÃO INVÁLIDA!\n");
        }else if( (opcao == 1) ){ // Em caso de 1, cadastrar o aluno
            printf("\n");
            if( indice == tam){ // Para impedir o número tam de alunos seja estourado
                printf("Não é possível incluir novos alunos!\n");
                printf("Limite máximo excedito!\n\n");
                system("pause");
                printf("Pressione qualquer tecla para sair do cadastro.\n");
                opcao = 2;
            }else{ //Cadastrar nome do aluno e assoicar uma matricula
                printf("Informe o nome: ");
                gets(aluno[indice]->nome);
                aluno[indice]->matricula = indice + 1;
                printf("Aluno matriculado com sucesso!\n");
                printf("Matricula nº. %d.\n\n",aluno[indice]->matricula);

                //Matricula de alunos em disciplinas
                printf("Deseja realizar a matricula deste aluno em disciplinas?\n");
                printf("\t1 - Sim \t2-Não\n");
                printf("Informe a opção escolhida: ");
                int opmat = 0;
                scanf("%d",&opmat);
                do{
                    if( (opmat < 1 ) || (opmat > 2) ){ // Evita que usuário digite um
                            // valor idesejado.
                        printf("\n\n\tOPÇÃO INVÁLIDA!\n");
                    }else if( opmat == 1){// Apresenta a lista de disciplinas disponíveis
                        printf("\n");
                        printf("Lista de disciplinas disponíveis para matricula:\n");
                        printf("1 - Programação Orientada a Objetos (POO);\n");
                        printf("2 - Arquitetura e Organização de Computadores (AOC);\n");
                        printf("3 - Matemática Discreta (MATDISC).\n\n");
                        int quant_disc = 0; // Para número de disciplinas a se matricular
                        do{
                            printf("Informe em quantas disciplinas deseja se matricular: ");
                            scanf("%d", &quant_disc);
                            if( (quant_disc < 1) || (quant_disc > 3) ){
                                printf("\n\n\tOPÇÃO INVÁLIDA!\n");
                            }
                        }while((quant_disc < 1) || (quant_disc > 3));
                        int cod_disc = 0;
                        for(int j = 0; j < quant_disc; j++){
                            printf("Digite o código da disciplina: ");
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
                indice++; // pós-incremento do indice.
            }
        }else if( (opcao == 2) ){} // Em caso de 2, sair sem fazer nada.
    }while(opcao != 2);
    printf("\n");
    // Informar Boletim, Médias ou Sair do Programa
    //  A - Tomada de Decisão
    printf("Informe o que deseja fazer:\n");
    do{
        printf("\t1 - Visualizar Boletim \t2 - Sair do Progrma\n");
        printf("Informe a opção escolhida: ");
        scanf("%d",&opcao);
        if( (opcao < 1) || (opcao > 2)){ /*> Para inválidar outros valores
                                            que não sejam 1 ou 2.
                                         */
            printf("\n\n\tOPÇÃO INVÁLIDA!\n");
        }else if( (opcao == 1) ){ // Visualizar Boletim
            int opdisc = 0;
            do{
                printf("Qual disciplina deseja visulizar o Boletim:\n");
                printf("\t1 - POO \t2 - AOC \t3 - MATDISC\n");
                printf("Informe a opção escolhida: ");
                scanf("%d",&opdisc);
                if((opdisc < 1) || (opdisc >3)){
                    printf("\n\n\tOPÇÃO INVÁLIDA!\n");
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
                        printf("Informe a média do aluno: ");
                        scanf("%f",&aluno[j]->disciplina[k].media);
                    }
                }
            }
        }
        getchar();
        printf("\n");
        printf("Continuar digitando médias para esta disciplina?\n");
        printf("\t1 - Sim \t2 - Não\n");
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
                printf("\tMédia: %.2f\n",aluno[j]->disciplina[k].media);
            }
        }
    }
    printf("\n");
    int opmd = 0;
    printf("Deseja informar a média dos alunos?\n");
    do{
        printf("\t1 - Sim \t2 - Não\n");
        scanf("%d",&opmd);
        if( (opmd < 1) || (opmd > 2) ){
            printf("\n\n\tOPÇÃO INVÁLIDA!\n");
            printf("\n\n\tODigite uma opção VÁLIDA!\n");
        }
    }while((opmd < 1) || (opmd > 2));

    if(opmd == 1){
       // digitar_media(indice, nm_d,aluno);
    }else if(opmd == 2){}
}

