#include "simulador.h"
#include <stdlib.h>
#include <string.h>

/* Vetores de ponteiros permanecem ordenados; busca binaria O(log N).
 * Os nos propriamente ditos continuam numa lista simplesmente encadeada.
 */
static size_t pos_eleitor(const Urna *u,int codigo) {
    size_t a=0,b=u->total_eleitores;
    while(a<b) {
        size_t m=a+(b-a)/2;
        if(u->indice_eleitores[m]->codigo<codigo)a=m+1;
        else b=m;
    }
    return a;
}
static size_t pos_candidato(const Urna *u,int numero) {
    size_t a=0,b=u->total_candidatos;
    while(a<b) {
        size_t m=a+(b-a)/2;
        if(u->indice_candidatos[m]->numero<numero)a=m+1;
        else b=m;
    }
    return a;
}
Eleitor *urna_buscar_eleitor(const Urna *u,int codigo) {
    size_t i=pos_eleitor(u,codigo);
    return i<u->total_eleitores&&u->indice_eleitores[i]->codigo==codigo
           ?u->indice_eleitores[i]:NULL;
}
Candidato *urna_buscar_candidato(const Urna *u,int numero) {
    size_t i=pos_candidato(u,numero);
    return i<u->total_candidatos&&u->indice_candidatos[i]->numero==numero
           ?u->indice_candidatos[i]:NULL;
}
static int nome_cabe(const char *s,size_t capacidade) {
    return s && *s && strlen(s)<capacidade;
}
int urna_inserir_eleitor(Urna *u,int codigo,const char *nome) {
    if(!u||codigo<=0||!nome_cabe(nome,sizeof(((Eleitor*)0)->nome)) ||
       strchr(nome,';')||strchr(nome,'\n')) return -2;
    if(urna_buscar_eleitor(u,codigo))return -1;
    if(u->total_eleitores==MAX_ELEITORES)return 0;
    Eleitor *e=calloc(1,sizeof *e);
    if(!e)return -2;
    e->codigo=codigo;
    strcpy(e->nome,nome);
    size_t i=pos_eleitor(u,codigo);
    if(i<u->total_eleitores)
        memmove(u->indice_eleitores+i+1,u->indice_eleitores+i,
                (u->total_eleitores-i)*sizeof u->indice_eleitores[0]);
    u->indice_eleitores[i]=e;
    ++u->total_eleitores;
    e->proximo=u->eleitores;u->eleitores=e;
    return 1;
}
static int partido_valido(const char *partido) {
    const char *validos[]={"PBA","PBB","PBC","PBD","PBE"};
    for(size_t i=0;i<sizeof validos/sizeof validos[0];++i)
        if(partido && strcmp(partido,validos[i])==0)return 1;
    return 0;
}
int urna_inserir_candidato(Urna *u,int numero,const char *nome,const char *partido) {
    if(!u||numero<=0||!nome_cabe(nome,sizeof(((Candidato*)0)->nome)) ||
       !partido_valido(partido))return -2;
    if(urna_buscar_candidato(u,numero))return -1;
    if(u->total_candidatos==MAX_CANDIDATOS)return 0;
    Candidato *c=calloc(1,sizeof *c);
    if(!c)return -2;
    c->numero=numero;strcpy(c->nome,nome);strcpy(c->partido,partido);
    size_t i=pos_candidato(u,numero);
    if(i<u->total_candidatos)
        memmove(u->indice_candidatos+i+1,u->indice_candidatos+i,
                (u->total_candidatos-i)*sizeof u->indice_candidatos[0]);
    u->indice_candidatos[i]=c;++u->total_candidatos;
    c->proximo=u->candidatos;u->candidatos=c;
    return 1;
}
int urna_excluir_eleitor(Urna *u,int codigo) {
    if(!u)return 0;
    Eleitor *e=urna_buscar_eleitor(u,codigo);
    if(!e)return 0;
    if(e->votou)return -1;
    Eleitor **p=&u->eleitores;
    while(*p && *p!=e)p=&(*p)->proximo;
    if(!*p)return 0;
    *p=e->proximo;
    size_t i=pos_eleitor(u,codigo);
    if(i+1<u->total_eleitores)
        memmove(u->indice_eleitores+i,u->indice_eleitores+i+1,
                (u->total_eleitores-i-1)*sizeof u->indice_eleitores[0]);
    --u->total_eleitores;u->indice_eleitores[u->total_eleitores]=NULL;
    free(e);return 1;
}
int urna_excluir_candidato(Urna *u,int numero) {
    if(!u)return 0;
    Candidato *c=urna_buscar_candidato(u,numero);
    if(!c)return 0;
    if(c->votos)return -1;
    Candidato **p=&u->candidatos;
    while(*p && *p!=c)p=&(*p)->proximo;
    if(!*p)return 0;
    *p=c->proximo;
    size_t i=pos_candidato(u,numero);
    if(i+1<u->total_candidatos)
        memmove(u->indice_candidatos+i,u->indice_candidatos+i+1,
                (u->total_candidatos-i-1)*sizeof u->indice_candidatos[0]);
    --u->total_candidatos;u->indice_candidatos[u->total_candidatos]=NULL;
    free(c);return 1;
}
int urna_votar(Urna *u,int codigo,int numero) {
    if(!u)return -3;
    Eleitor *e=urna_buscar_eleitor(u,codigo);
    if(!e)return 0;
    Candidato *c=urna_buscar_candidato(u,numero);
    if(!c)return -1;
    if(e->votou)return -2;
    Voto *v=malloc(sizeof *v);
    if(!v)return -3;
    v->codigo_eleitor=codigo;v->numero_candidato=numero;
    v->proximo=u->votos;u->votos=v;
    e->votou=1;++c->votos;++u->total_votos;
    return 1;
}
int urna_carregar_demo(Urna *u) {
    if(!u||u->total_eleitores||u->total_candidatos)return 0;
    for(int i=1;i<=200;++i) {
        char nome[48];
        snprintf(nome,sizeof nome,"Eleitor ficticio %03d",i);
        if(urna_inserir_eleitor(u,i,nome)!=1)goto erro;
    }
    const char *partidos[]={"PBA","PBB","PBC","PBD","PBE"};
    for(int i=0;i<20;++i) {
        char nome[48];
        snprintf(nome,sizeof nome,"Candidato ficticio %02d",i+1);
        if(urna_inserir_candidato(u,101+i,nome,partidos[i/4])!=1)goto erro;
    }
    return 1;
erro:
    urna_limpar(u);return 0;
}
int urna_exportar_eleitores(const Urna *u,const char *arquivo) {
    if(!u||!arquivo)return 0;
    FILE *fp=fopen(arquivo,"w");
    if(!fp)return 0;
    int erro=fputs("codigo;nome_ficticio;votou\n",fp)==EOF;
    for(size_t i=0;i<u->total_eleitores&&!erro;++i) {
        const Eleitor *e=u->indice_eleitores[i];
        if(fprintf(fp,"%d;%s;%d\n",e->codigo,e->nome,e->votou)<0)erro=1;
    }
    if(fclose(fp)!=0)erro=1;
    return !erro;
}
void urna_exibir_candidatos(const Urna *u,FILE *saida) {
    for(size_t i=0;i<u->total_candidatos;++i){
        const Candidato *c=u->indice_candidatos[i];
        fprintf(saida,"%d | %s | %s\n",c->numero,c->nome,c->partido);
    }
}
static int comparar_resultado(const void *x,const void *y) {
    const Candidato *a=*(const Candidato *const *)x;
    const Candidato *b=*(const Candidato *const *)y;
    if(a->votos!=b->votos)return a->votos>b->votos?-1:1;
    return (a->numero>b->numero)-(a->numero<b->numero);
}
void urna_exibir_resultado(const Urna *u,FILE *saida) {
    Candidato *ordenados[MAX_CANDIDATOS];
    for(size_t i=0;i<u->total_candidatos;++i)
        ordenados[i]=u->indice_candidatos[i];
    qsort(ordenados,u->total_candidatos,sizeof ordenados[0],comparar_resultado);
    fprintf(saida,"TOTAL DE VOTOS: %zu\n",u->total_votos);
    for(size_t i=0;i<u->total_candidatos;++i) {
        const Candidato *c=ordenados[i];
        fprintf(saida,"%d | %s | %s | %u votos\n",
                c->numero,c->nome,c->partido,c->votos);
    }
    const char *partidos[]={"PBA","PBB","PBC","PBD","PBE"};
    unsigned totais[5]={0};
    for(size_t i=0;i<u->total_candidatos;++i)
        for(size_t j=0;j<5;++j)
            if(strcmp(u->indice_candidatos[i]->partido,partidos[j])==0)
                totais[j]+=u->indice_candidatos[i]->votos;
    for(size_t j=0;j<5;++j)
        fprintf(saida,"PARTIDO %s: %u votos\n",partidos[j],totais[j]);
}
void urna_limpar(Urna *u) {
    if(!u)return;
    while(u->eleitores){Eleitor *n=u->eleitores;u->eleitores=n->proximo;free(n);}
    while(u->candidatos){Candidato *n=u->candidatos;u->candidatos=n->proximo;free(n);}
    while(u->votos){Voto *n=u->votos;u->votos=n->proximo;free(n);}
    memset(u,0,sizeof *u);
}
