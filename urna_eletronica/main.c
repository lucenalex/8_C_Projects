/* Simulador didatico de urna (sem validade eleitoral).
 * Dados integralmente ficticios; nao adequado a eleicoes reais.
 */
#include "simulador.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int ler_numero(const char *pergunta,int *valor) {
    char linha[128],*fim;
    for(;;) {
        fputs(pergunta,stdout);fflush(stdout);
        if(!fgets(linha,sizeof linha,stdin))return 0;
        size_t n=strcspn(linha,"\n");
        if(linha[n]!='\n'&&!feof(stdin)) {
            int ch;while((ch=getchar())!='\n'&&ch!=EOF){}
            puts("Entrada muito longa; tente novamente.");
            continue;
        }
        errno=0;long l=strtol(linha,&fim,10);
        while(*fim==' '||*fim=='\t'||*fim=='\r'||*fim=='\n')++fim;
        if(fim==linha||*fim||errno||l<INT_MIN||l>INT_MAX) {
            puts("Digite um numero inteiro valido.");continue;
        }
        *valor=(int)l;return 1;
    }
}
int main(void) {
    Urna urna={0};
    if(!urna_carregar_demo(&urna)) {
        fputs("Falha na inicializacao dos dados ficticios.\n",stderr);
        return 1;
    }
    puts("SIMULADOR DIDATICO: NENHUMA VALIDADE ELEITORAL.");
    puts("200 eleitores e 20 candidatos FICTICIOS; votos somente em memoria.");
    for(;;) {
        puts("\n0 Sair | 1 Candidatos | 2 Simular voto | 3 Resultado");
        puts("4 Exportar eleitores ficticios | 5 Excluir eleitor nao votante");
        puts("6 Excluir candidato sem votos");
        int op;
        if(!ler_numero("Opcao: ",&op)||op==0)break;
        if(op==1) {
            urna_exibir_candidatos(&urna,stdout);
        } else if(op==2) {
            int e,c;
            if(!ler_numero("Codigo do eleitor ficticio: ",&e)||
               !ler_numero("Numero do candidato ficticio: ",&c))break;
            int status=urna_votar(&urna,e,c);
            if(status==1)puts("Voto ficticio registrado.");
            else if(status==0)puts("Eleitor ficticio nao encontrado.");
            else if(status==-1)puts("Candidato ficticio nao encontrado.");
            else if(status==-2)puts("Eleitor ficticio ja votou.");
            else puts("Erro ao registrar voto ficticio.");
        } else if(op==3) {
            urna_exibir_resultado(&urna,stdout);
        } else if(op==4) {
            if(urna_exportar_eleitores(&urna,"eleitores_demo.csv"))
                puts("Arquivo eleitores_demo.csv criado com dados ficticios.");
            else puts("Falha ao criar CSV (arquivo pode ja existir).");
        } else if(op==5||op==6) {
            int id;
            if(!ler_numero(op==5?"Codigo de eleitor ficticio: ":
                            "Numero de candidato ficticio: ",&id))break;
            int status=op==5?urna_excluir_eleitor(&urna,id):
                              urna_excluir_candidato(&urna,id);
            if(status==1)puts("Registro ficticio excluido.");
            else if(status==0)puts("Registro ficticio nao encontrado.");
            else puts("Exclusao bloqueada: registro associado a voto.");
        } else puts("Opcao invalida.");
    }
    urna_limpar(&urna);
    puts("Simulacao encerrada. Votos descartados da memoria.");
    return 0;
}
