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

    Título: Agenda - Desafio 1

    Propósito do Programa:

        Usando struct e ponteiros, implemente uma agenda (nome, endereço,
        telefone ( códigos: do país, da operadora e da cidade e o número do
        telefone), e-mail e data de nascimento) com a capacidade para 200
        contatos. Elabore uma função para adicionar os contatos e outra, usando
        a busca binária, para procurar na agenda uma determinada pessoa. E
        também uma função para exibir todos os contatos bem como a exclusão.
        Oferecer um menu,com as seguintes opções:
            1.Adicionar um contato
            2.Procurar um contato
            3.Exibir agenda
            4.Excluir um contato

    Dados de Manutenção do programa

      Data            Programador                  Descrição da Mudança
    ==========    ======================      =================================
    2023/08/01    Alexsandro Lucena Mota      - Código original (versão 0.1).
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define TAM 200

typedef struct{
    char first_name[15];
    char midle_name[15];
    char  last_name[15];
}Nome;
typedef struct Endereco{
    char tipo[15];
    char nome[45];
    char numero[5];
    char cep[9];
    char bairro[15];
    char cidade[15];
    char uf[3];
    char pais[15];
}Ende;
typedef struct Telefone{
    char ddi[5]; // código do páis: exemplo +55 Brasil
    char cop[3]; // código da operadora: 15 vivo
    char ddd[3]; // código da cidade: 98 São Luís
    char ntf[9];// número do telefone: 9 9101 3194
}Fone;
typedef struct{
    int dia;
    int mes;
    int ano;
}Data;
typedef struct{
    Nome nome_contato;
    Ende endereco;
    Fone telefone;
    char email[50];
    Data dt_nasc;
}Contato;
void adicionar_contato(Contato *pessoa, int max_id);
void procurar_contato(Contato *pessoa); // com busca binária
void exibir_contatos(Contato *pessoa, int max_id);
void excluir_contato(Contato *pessoa, int max_id);
int menu();
void cabecalho();

int main(){
    setlocale(LC_ALL,"Portuguese");
    Contato Pessoa[TAM]; // Um vetor é um ponteiro
    int opcao = 0, id_contato = 0;
    do{
        do{
            cabecalho();
            opcao=menu();
        }while( (opcao < 0) || (opcao > 4) );
        switch(opcao){
            case 1:
                if( id_contato < TAM  ){
                    adicionar_contato(Pessoa,id_contato);
                    id_contato++;
                }
                else{
                    printf("\n\t");
                    printf("Agenda cheia!\n\t");
                    printf("Não é possível inserir novos contatos.\n\t");
                    printf("Exclua um contato antigo para inserir um novo.\n\t");
                    system("pause");
                }
                break;
            case 2:
                procurar_contato(Pessoa);
                break;
            case 3:
                exibir_contatos(Pessoa,id_contato-1);
                break;
            case 4:
                excluir_contato(Pessoa,id_contato-1);
                id_contato--;
                break;
        }
    }while(opcao != 0);
    return 0;
}
void cabecalho(){
    system("cls");
    printf("\n\t");// \t corresponde a 7 espaços
    printf("\n\t############## AGENDA ##############\n");
}
int menu(){
    int choose;
    printf("\n\t");
    printf("MENU DE OPÇÕES.\n");
    printf("\n\t");
    printf("0. Sair da Agenda;\n\t");
    printf("1. Adicionar um contato;\n\t");
    printf("2. Procurar um contato;\n\t");
    printf("3. Exibir agenda;\n\t");
    printf("4. Excluir um contato.\n\n\t");
    printf("Digite sua escolha: ");
    fflush(stdin);
    scanf("%d",&choose);
    if((choose < 0) || (choose > 4)){
        printf("\n\tOPÇÃO INVÁLIDA!\n\t");
        printf("Informe uma opção conforme o Menu de Opções!\n\t");
        printf("Pressione qualquer tecla para retonar ao Menu de opções.\n\n\t");
        system("pause");
    }
    return choose;
}
void adicionar_contato(Contato *pessoa, int max_id){
    cabecalho();
    printf("\n\t");
    printf("CADASTRO DE CONTATOS.\n");
    printf("\n\t");
    // Insere o nome do novo contato
    printf("Insira dos dados do novo contato!\n\n\t");
    printf("Nome:\n\t\t");
    printf("Primeiro Nome: ");
    fflush(stdin);
    scanf("15[^\n]",(pessoa + max_id)->nome_contato.first_name);
    printf("\t\tNome do Meio: ");
    fflush(stdin);
    scanf("15[^\n]",(pessoa + max_id)->nome_contato.midle_name);
    printf("\t\tSobrenome (último nome): ");
    fflush(stdin);
    scanf("15[^\n]",(pessoa + max_id)->nome_contato.last_name);
    printf("\n\t");
    // Insere a data de nascimento do novo contato
    printf("Data de nascimento:\n\t\t");
    printf("Dia: ");
    fflush(stdin);
    scanf("%d",&pessoa[max_id].dt_nasc.dia);
    printf("\t\tMês: ");
    fflush(stdin);
    scanf("%d",&pessoa[max_id].dt_nasc.mes);
    printf("\t\tAno: ");
    fflush(stdin);
    scanf("%d",&pessoa[max_id].dt_nasc.ano);
    printf("\n\t");
    // Insere o endereço do novo contato
    printf("Endereço:\n\t\t");
    printf("Logradouro (rua, avendia, etc.): ");
    fflush(stdin);
    scanf("15[^\n]",(pessoa + max_id)->endereco.tipo);
    printf("\t\tNome do logradouro: ");
    fflush(stdin);
    scanf("45[^\n]",(pessoa + max_id)->endereco.nome);
    printf("\t\tNúmero : ");
    fflush(stdin);
    scanf("5[^\n]",(pessoa + max_id)->endereco.numero);
    printf("\t\tCEP: ");
    fflush(stdin);
    scanf("9[^\n]",(pessoa + max_id)->endereco.cep);
    printf("\t\tBairro: ");
    fflush(stdin);
    scanf("15[^\n]",(pessoa + max_id)->endereco.bairro);
    printf("\t\tCidade: ");
    fflush(stdin);
    scanf("15[^\n]",(pessoa + max_id)->endereco.cidade);
    printf("\t\tUF: ");
    fflush(stdin);
    scanf("3[^\n]",(pessoa + max_id)->endereco.uf);
    printf("\t\tPaís: ");
    fflush(stdin);
    scanf("15[^\n]",(pessoa + max_id)->endereco.pais);
    printf("\n\t");
    // Insere o telefone do novo contato
    printf("Telefone:\n\t\t");
    printf("DDI (Código do País): ");
    fflush(stdin);
    scanf("5[^\n]",(pessoa + max_id)->telefone.ddi);
    printf("\t\tCódigo da operadora): ");
    fflush(stdin);
    scanf("3[^\n]",(pessoa + max_id)->telefone.cop);
    printf("\t\tDDD (Código da cidade): ");
    fflush(stdin);
    scanf("3[^\n]",(pessoa + max_id)->telefone.ddd);
    printf("\t\tNúmero : ");
    fflush(stdin);
    scanf("9[^\n]",(pessoa + max_id)->telefone.ntf);
    printf("\n\t");
    // Insere o email do novo contato
    printf("E-mail : ");
    fflush(stdin);
    scanf("50[^\n]",(pessoa + max_id)->email);
    printf("\n\t");
    // Mensagem ao usuário
    printf("Cadastro bem-sucedito!\n\n\t");
    printf("Pressione qualquer tecla para retonar ao Menu de opções.\n\n\t");
    system("pause");
}
void procurar_contato(Contato *pessoa){
    cabecalho();
    printf("\n\t");
    printf("BUSCAR CONTATO.\n");
    //busca binária
    printf("Pressione qualquer tecla para retonar \n\t");
    printf("ao Menu de opções.                     \n\n\t");
    system("pause");
}
void exibir_contato(Contato *pessoa,int i){
    printf("CONTATO %d:\n\t", i + 1);
    printf("   Nome: %s", pessoa[i].nome_contato.first_name);
    printf(" %s", pessoa[i].nome_contato.midle_name);
    printf(" %s\n\t", pessoa[i].nome_contato.last_name);
    printf("   Data de Nascimento: %d/", pessoa[i].dt_nasc.dia);
    printf(" %d/", pessoa[i].dt_nasc.mes);
    printf(" %d.\n\t", pessoa[i].dt_nasc.ano);
    printf("   Endereço:\n\t");
    printf("      %s: ", pessoa[i].endereco.tipo);
    printf("      %s, ", pessoa[i].endereco.nome);
    printf("      %s, ", pessoa[i].endereco.numero);
    printf("      %s,\n\t", pessoa[i].endereco.bairro);
    printf("      %s, ", pessoa[i].endereco.cep);
    printf("      %s - ", pessoa[i].endereco.cidade);
    printf("      %s, ", pessoa[i].endereco.uf);
    printf("      %s.", pessoa[i].endereco.pais);
    printf("   Telefone: ");
    printf("      +%s ", pessoa[i].telefone.ddi);
    printf("      %s, ", pessoa[i].telefone.cop);
    printf("      (%s) ", pessoa[i].telefone.ddd);
    printf("      %s.\n\t", pessoa[i].telefone.ntf);
    printf("   E-mail: %s\n\t",pessoa[i].email);
    printf("-------------------------------------\n\t");
}
void exibir_contatos(Contato *pessoa, int max_id){
    cabecalho();
    printf("\n\t");
    printf("LISTA DE CONTATOS.\n");
    printf("\n\t");
    printf("-------------------------------------\n\t");
    for(int i = 0; i < max_id; i++){
        exibir_contato(pessoa,i);
    }
    printf("Pressione qualquer tecla para retonar \n\t");
    printf("ao Menu de opções.                     \n\n\t");
    system("pause");
}
void excluir_contato(Contato *pessoa, int max_id){
    int id_cont;
    cabecalho();
    printf("\n\t");
    printf("EXCLUIR CONTATO.\n");
    do{
        printf("\n\t");
        printf("Informe o Id do contato a ser excluido: ");
        fflush(stdin);
        scanf("%d",&id_cont);
        if(id_cont > max_id){
            printf("\n\tO id informado não possui contato cadastrado.");
            printf("\n\tInforme um id inferior a %d.",max_id);
        }
    }while(id_cont > max_id);
    exibir_contato(pessoa,(id_cont - 1));
    int escolha;
    do{
        printf("\n\t");
        printf("Deseja excluir esse Contato? (1) SIM\t(2) NÃO.\n\t");
        fflush(stdin);
        scanf("%d",&escolha);
        if((escolha != 1) && (escolha != 2)){
            printf("\n\tOPÇÃO INVÁLIDA!\n\t");
            printf("Pressione qualquer tecla para retonar ao Menu de opções.\n\n\t");
            system("pause");
        }
    }while((escolha != 1) && (escolha != 2));
    if(escolha == 1){
        for(int i = id_cont - 1; i < max_id; i++){
            strcpy(pessoa[i].nome_contato.first_name,pessoa[i+1].nome_contato.first_name);
            strcpy(pessoa[i].nome_contato.midle_name,pessoa[i+1].nome_contato.midle_name);
            strcpy(pessoa[i].nome_contato.last_name,pessoa[i+1].nome_contato.last_name);
            pessoa[i].dt_nasc.dia = pessoa[i+1].dt_nasc.dia;
            pessoa[i].dt_nasc.mes = pessoa[i+1].dt_nasc.mes;
            pessoa[i].dt_nasc.ano = pessoa[i+1].dt_nasc.ano;
            strcpy(pessoa[i].endereco.tipo,pessoa[i+1].endereco.tipo);
            strcpy(pessoa[i].endereco.nome,pessoa[i+1].endereco.nome);
            strcpy(pessoa[i].endereco.numero,pessoa[i+1].endereco.numero);
            strcpy(pessoa[i].endereco.cep,pessoa[i+1].endereco.cep);
            strcpy(pessoa[i].endereco.bairro,pessoa[i+1].endereco.bairro);
            strcpy(pessoa[i].endereco.cidade,pessoa[i+1].endereco.cidade);
            strcpy(pessoa[i].endereco.uf,pessoa[i+1].endereco.uf);
            strcpy(pessoa[i].endereco.pais,pessoa[i+1].endereco.pais);
            strcpy(pessoa[i].telefone.ddi,pessoa[i+1].telefone.ddi);
            strcpy(pessoa[i].telefone.cop,pessoa[i+1].telefone.cop);
            strcpy(pessoa[i].telefone.ddd,pessoa[i+1].telefone.ddd);
            strcpy(pessoa[i].telefone.ntf,pessoa[i+1].telefone.ntf);
            strcpy(pessoa[i].email,pessoa[i+1].email);
            printf("\n\t");
        }
        // Mensagem ao usuário
            printf("Cadastro bem-sucedito!\n\n\t");
            printf("Pressione qualquer tecla para retonar ao Menu de opções.\n\n\t");
            system("pause");
    }
    printf("Pressione qualquer tecla para retonar \n\t");
    printf("ao Menu de opções.                     \n\n\t");
    system("pause");
}

