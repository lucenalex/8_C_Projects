#include "../simulador.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static void testar_demo(void) {
    Urna u={0};
    assert(urna_carregar_demo(&u)==1);
    assert(u.total_eleitores==200&&u.total_candidatos==20&&u.total_votos==0);
    assert(urna_buscar_eleitor(&u,1)!=NULL);
    assert(urna_buscar_eleitor(&u,200)!=NULL);
    assert(urna_buscar_eleitor(&u,201)==NULL);
    assert(urna_buscar_candidato(&u,101)!=NULL);
    assert(urna_buscar_candidato(&u,120)!=NULL);
    assert(urna_buscar_candidato(&u,999)==NULL);
    assert(urna_inserir_eleitor(&u,1,"Duplicado")==-1);
    assert(urna_inserir_candidato(&u,101,"Duplicado","PBA")==-1);
    assert(urna_inserir_candidato(&u,500,"Invalido","NAO")==-2);
    assert(urna_votar(&u,999,101)==0);
    assert(urna_votar(&u,1,999)==-1);
    assert(urna_votar(&u,1,101)==1);
    assert(urna_votar(&u,1,101)==-2);
    assert(urna_votar(&u,2,105)==1);
    assert(urna_votar(&u,3,101)==1);
    assert(u.total_votos==3);
    assert(urna_buscar_candidato(&u,101)->votos==2);
    assert(urna_buscar_candidato(&u,105)->votos==1);
    assert(urna_excluir_eleitor(&u,1)==-1);
    assert(urna_excluir_candidato(&u,101)==-1);
    assert(urna_excluir_eleitor(&u,4)==1);
    assert(urna_buscar_eleitor(&u,4)==NULL);
    assert(urna_inserir_eleitor(&u,4,"Eleitor ficticio 004")==1);
    assert(urna_excluir_candidato(&u,120)==1);
    assert(urna_buscar_candidato(&u,120)==NULL);
    assert(urna_inserir_candidato(&u,120,"Novo candidato","PBE")==1);

    FILE *fp=tmpfile();
    assert(fp);
    urna_exibir_resultado(&u,fp);
    assert(fflush(fp)==0);
    rewind(fp);
    char buf[8192]={0};
    size_t lidos=fread(buf,1,sizeof buf-1,fp);
    assert(lidos>0&&!ferror(fp));
    assert(strstr(buf,"TOTAL DE VOTOS: 3"));
    assert(strstr(buf,"PARTIDO PBA: 2 votos"));
    assert(strstr(buf,"PARTIDO PBB: 1 votos"));
    char *a=strstr(buf,"101 | ");
    char *b=strstr(buf,"105 | ");
    assert(a&&b&&a<b);
    assert(fclose(fp)==0);

    assert(urna_exportar_eleitores(&u,"eleitores_demo.csv")==1);
    assert(urna_exportar_eleitores(&u,"eleitores_demo.csv")==0);
    fp=fopen("eleitores_demo.csv","r");assert(fp);
    int linhas=0;char linha[200];
    while(fgets(linha,sizeof linha,fp))++linhas;
    assert(!ferror(fp));assert(fclose(fp)==0);
    assert(linhas==201);
    urna_limpar(&u);
    assert(!u.total_votos&&!u.total_eleitores&&!u.total_candidatos);
    urna_limpar(&u);
}
static void testar_capacidades(void) {
    Urna u={0};
    for(int i=1;i<=MAX_ELEITORES;++i)
        assert(urna_inserir_eleitor(&u,i,"Eleitor ficticio")==1);
    assert(urna_inserir_eleitor(&u,MAX_ELEITORES+1,"Excesso")==0);
    for(int i=1;i<=MAX_CANDIDATOS;++i)
        assert(urna_inserir_candidato(&u,i,"Candidato ficticio","PBA")==1);
    assert(urna_inserir_candidato(&u,MAX_CANDIDATOS+1,"Excesso","PBA")==0);
    urna_limpar(&u);
}
int main(void) {
    testar_demo();
    testar_capacidades();
    puts("PASS: 200 eleitores e 20 candidatos ficticios, busca binaria, voto unico, exclusao, CSV, resultado e capacidades");
    return 0;
}
