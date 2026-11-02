#ifndef AGENDA_H
#define AGENDA_H
#include <stddef.h>
#define TAM 200
typedef struct { char first_name[32], middle_name[32], last_name[32]; } Nome;
typedef struct {
    char tipo[24], nome[80], numero[12], cep[12], bairro[48],
         cidade[48], uf[3], pais[40];
} Endereco;
typedef struct { char ddi[6], cop[8], ddd[4], ntf[16]; } Telefone;
typedef struct { int dia, mes, ano; } Data;
typedef struct {
    Nome nome_contato;
    Endereco endereco;
    Telefone telefone;
    char email[96];
    Data dt_nasc;
} Contato;
typedef struct { Contato contatos[TAM]; size_t quantidade; } Agenda;
/* Ordenacao case-insensitive ASCII; acentos UTF-8 preservam a forma literal. */
int agenda_comparar_nomes(const Nome *a, const Nome *b);
int agenda_buscar(const Agenda *agenda, const Nome *nome);
/* 1=inserido, 0=lotado, -1=nome completo duplicado. */
int agenda_inserir(Agenda *agenda, const Contato *contato);
/* 1=removido, 0=ausente. */
int agenda_excluir(Agenda *agenda, const Nome *nome);
int data_valida(Data data);
#endif
