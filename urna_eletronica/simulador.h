#ifndef SIMULADOR_URNA_DIDATICA_H
#define SIMULADOR_URNA_DIDATICA_H
#include <stddef.h>
#include <stdio.h>
#define MAX_ELEITORES 400
#define MAX_CANDIDATOS 50

/* SIMULADOR EDUCACIONAL: apenas identificadores e nomes ficticios. */
typedef struct Eleitor {
    int codigo;
    char nome[48];
    int votou;
    struct Eleitor *proximo;
} Eleitor;
typedef struct Candidato {
    int numero;
    char nome[48];
    char partido[4];
    unsigned votos;
    struct Candidato *proximo;
} Candidato;
typedef struct Voto {
    int codigo_eleitor;
    int numero_candidato;
    struct Voto *proximo;
} Voto;
typedef struct {
    Eleitor *eleitores;
    Candidato *candidatos;
    Voto *votos;
    Eleitor *indice_eleitores[MAX_ELEITORES];
    Candidato *indice_candidatos[MAX_CANDIDATOS];
    size_t total_eleitores, total_candidatos, total_votos;
} Urna;
Eleitor *urna_buscar_eleitor(const Urna *u,int codigo);
Candidato *urna_buscar_candidato(const Urna *u,int numero);
int urna_inserir_eleitor(Urna *u,int codigo,const char *nome);
int urna_inserir_candidato(Urna *u,int numero,const char *nome,const char *partido);
/* -1=proibido (ja votou ou ja recebeu votos), 0=ausente, 1=removido */
int urna_excluir_eleitor(Urna *u,int codigo);
int urna_excluir_candidato(Urna *u,int numero);
/* 1=voto contado; 0=eleitor ausente; -1=candidato ausente; -2=ja votou; -3=erro de memoria */
int urna_votar(Urna *u,int codigo,int numero);
int urna_carregar_demo(Urna *u);
int urna_exportar_eleitores(const Urna *u,const char *arquivo);
void urna_exibir_candidatos(const Urna *u,FILE *saida);
void urna_exibir_resultado(const Urna *u,FILE *saida);
void urna_limpar(Urna *u);
#endif
