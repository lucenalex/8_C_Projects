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

        Crie uma programa para preencher 2 vetores: Um não ordenado e o outro
		ordenado. Ambos com tamanho 8. Usar funções. Crie um  menu  de  texto
		com as seguintes opções:
			1)Preencher vetor 1
			2)Preencher vetor 2
			3)Busca Sequencial (vetor 1)
			4)Busca Binária (vetor 2)
			5)Imprimir vetor 1
			6)Imprimir vetor 2
			7)Sair

    Dados de Manutenção do programa

      Data            Programador                  Descrição da Mudança
    ========    ======================      =================================
    2022/4/17    Alexsandro Lucena Mota      - Código original (versão 0.1).

*/

// Declaração de Variáveis Globais e/ou Novos tipos.

// Lista de Protótipos de Funções e Procedimentos
int media_das_Medias();

// Escopo da Função Main
int main(){
    setlocale(LC_ALL,"ptb");
    // Apresentação do programa ao usuário
    printf("PROGRAMA DOIS VETORES\n\n");
    printf("Propósito:\n");
    printf("\tpreencher 2 vetores de tamanho 8: um ordenado e o outro não.\n");

    /*
		printf("tamanho to tipo char: %lld\n", sizeof(char));
		printf("tamanho to tipo float: %lld\n", sizeof(float));
		printf("tamanho to tipo tp_disc: %lld\n", sizeof(tp_disc));
		printf("tamanho to tipo tp_alunos: %lld\n", sizeof(tp_alunos));
    */

    // Entrada de dados
    int opcao = 0, indice = 0; // incializa a variável opcao e indice com valor 0.
    tp_alunos *aluno = NULL; // ponteiro para novos alunos
        aluno = malloc(sizeof(tp_alunos));
    //(aluno + i).disciplina = malloc(3*sizeof(tp_disc));
    if(aluno == NULL){
        printf("Erro: Memória Insuficiente!\n");
        exit(1);
    }
    for(int i = 0; i < tam; i++ ){
        for(int j = 0; j < 3; j++){
            (aluno + i)->disciplina[j].media = 0.;
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
                printf("Limite máximo excedito!\n");
                system("pause");
                printf("Pressione qualquer tecla para sair do cadastro.\n");
                opcao = 2;
            }else{ //Cadastrar nome do aluno e assoicar uma matricula
                printf("Informe o nome: ");
                gets((aluno + indice)->nome);
                (aluno + indice)->matricula = indice + 1;
                printf("Aluno matriculado com sucesso!\n");
                printf("Matricula nº. %d.\n\n",(aluno + indice)->matricula);

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
                                strcpy( (aluno + j)->disciplina[cod_disc].nome_disc,"POO");
                            }else if(cod_disc == 2){
                                strcpy( (aluno + j)->disciplina[cod_disc].nome_disc,"AOC");
                            }else if(cod_disc == 3){
                                strcpy( (aluno + j)->disciplina[cod_disc].nome_disc,"MATDISC");
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
            if(opdisc == 1){
                printf("\n");
                printf("Boletim da disciplina POO\n\n");
                for(int j = 0; j < indice; j++){
                    printf("Matricula: %d",(aluno + j)->matricula);
                    printf("\tNome: %s",(aluno + j)->nome);
                    printf("\tMédia: %.2f\n",(aluno + j)->disciplina[1].media);
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
                int opmt = 0;
                int dig_md = 0;
                if(opmd == 1){
                    do{
                        printf("Informe a matricula do aluno: ");
                        scanf("%d",&opmt);
                        for(int k = 0; k < indice; k++){
                            if( opmt == (aluno + k)->matricula){
                                printf("\n");
                                printf("Informe a média do aluno: ");
                                scanf("%f",&(aluno + k)->disciplina[1].media);
                            }
                        }
                        getchar();
                        printf("\n");
                        printf("Continuar digitando médias para esta disciplina?\n");
                        printf("\t1 - Sim \t2 - Não\n");
                        printf("Informe a escolha: ");
                        scanf("%d",&dig_md);
                    }while(dig_md != 2);
                }else if(opmd == 2){}
            }else if(opdisc == 2){
                printf("\n");
                printf("Boletim da disciplina AOC\n\n");
                for(int j = 0; j < indice; j++){
                    printf("Matricual: %d",(aluno + j)->matricula);
                    printf("\tNome: %s",(aluno + j)->nome);
                    printf("\tMédia: %.2f\n",(aluno + j)->disciplina[2].media);
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
                int opmt = 0;
                int dig_md = 0;
                if(opmd == 1){
                    do{
                        printf("Informe a matricula do aluno: ");
                        scanf("%d",&opmt);
                        for(int k = 0; k < indice; k++){
                            if( opmt == (aluno + k)->matricula){
                                scanf("%f",&(aluno + k)->disciplina[2].media);
                            }
                        }
                        getchar();
                        printf("\n");
                        printf("Continuar digitando médias para esta disciplina?\n");
                        printf("\t1 - Sim \t2 - Não\n");
                        printf("Informe a escolha: ");
                        scanf("%d",&dig_md);
                    }while(dig_md != 2);
                }else if(opmd == 2){}
            }if(opdisc == 3){
                printf("\n");
                printf("Boletim da disciplina MATDISC\n\n");
                for(int j = 0; j < indice; j++){
                    printf("Matricula: %d",(aluno + j)->matricula);
                    printf("\tNome: %s",(aluno + j)->nome);
                    printf("\tMédia: %.2f\n",(aluno + j)->disciplina[3].media);
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
                int opmt = 0;
                int dig_md = 0;
                if(opmd == 1){
                    do{
                        printf("Informe a matricula do aluno: ");
                        scanf("%d",&opmt);
                        for(int k = 0; k < indice; k++){
                            if( opmt == (aluno + k)->matricula ){
                                scanf("%f",&(aluno + k)->disciplina[3].media);
                            }
                        }
                        printf("\n");
                        printf("Continuar digitando médias para esta disciplina?\n");
                        printf("\t1 - Sim \t2 - Não\n");
                        printf("Informe a escolha: ");
                        getchar();
                        scanf("%d",&dig_md);
                    }while(dig_md != 2);
                }else if(opmd == 2){}
            }
        }else if( opcao == 2){
            opcao = 2;
        }
    }while(opcao != 2);
    return 0;
}
