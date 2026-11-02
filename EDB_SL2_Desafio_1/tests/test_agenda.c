#include "../agenda.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static Contato contato(const char *primeiro, const char *sobrenome) {
    Contato c = {0};
    snprintf(c.nome_contato.first_name, sizeof c.nome_contato.first_name,
             "%s", primeiro);
    snprintf(c.nome_contato.last_name, sizeof c.nome_contato.last_name,
             "%s", sobrenome);
    return c;
}
static void testar_datas(void) {
    assert(data_valida((Data){29,2,2024}));
    assert(data_valida((Data){29,2,2000}));
    assert(!data_valida((Data){29,2,1900}));
    assert(!data_valida((Data){31,4,2026}));
    assert(!data_valida((Data){0,1,2000}));
    assert(!data_valida((Data){1,13,2000}));
}
static void testar_busca_e_remocao(void) {
    Agenda agenda = {0};
    Contato z = contato("Zoe", "Z"), a = contato("Alice", "A"),
            m = contato("Mario", "M");
    assert(agenda_buscar(&agenda, &z.nome_contato) == -1);
    assert(agenda_inserir(&agenda, &z) == 1);
    assert(agenda_inserir(&agenda, &a) == 1);
    assert(agenda_inserir(&agenda, &m) == 1);
    assert(agenda.quantidade == 3);
    assert(strcmp(agenda.contatos[0].nome_contato.first_name,"Alice") == 0);
    assert(strcmp(agenda.contatos[1].nome_contato.first_name,"Mario") == 0);
    assert(strcmp(agenda.contatos[2].nome_contato.first_name,"Zoe") == 0);
    Nome lower = {0}; strcpy(lower.first_name, "alice");
    strcpy(lower.last_name, "a");
    assert(agenda_buscar(&agenda, &lower) == 0);
    assert(agenda_inserir(&agenda, &a) == -1);
    assert(agenda.quantidade == 3);
    assert(agenda_excluir(&agenda, &m.nome_contato) == 1);
    assert(agenda_buscar(&agenda, &m.nome_contato) == -1);
    assert(agenda.quantidade == 2);
    assert(agenda_excluir(&agenda, &m.nome_contato) == 0);
    assert(agenda_excluir(&agenda, &a.nome_contato) == 1);
    assert(agenda_excluir(&agenda, &z.nome_contato) == 1);
    assert(agenda.quantidade == 0);
}
static void testar_capacidade(void) {
    Agenda agenda = {0};
    for (int i=0; i<TAM; ++i) {
        Contato c = contato("Teste", "X");
        snprintf(c.nome_contato.first_name, sizeof c.nome_contato.first_name,
                 "Nome%03d", TAM-i-1);
        assert(agenda_inserir(&agenda, &c) == 1);
    }
    assert(agenda.quantidade == TAM);
    for (size_t i=1; i<agenda.quantidade; ++i)
        assert(agenda_comparar_nomes(&agenda.contatos[i-1].nome_contato,
                                    &agenda.contatos[i].nome_contato) < 0);
    Contato extra = contato("Extra","E");
    assert(agenda_inserir(&agenda, &extra) == 0);
    Contato primeiro = contato("Nome000","X");
    assert(agenda_excluir(&agenda, &primeiro.nome_contato) == 1);
    assert(agenda_inserir(&agenda, &extra) == 1);
    assert(agenda.quantidade == TAM);
}
int main(void) {
    testar_datas();
    testar_busca_e_remocao();
    testar_capacidade();
    puts("PASS: datas, busca binaria, ordenacao, duplicatas, remocao, capacidade 200");
    return 0;
}
