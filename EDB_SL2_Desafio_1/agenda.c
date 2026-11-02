#include "agenda.h"
#include <ctype.h>
#include <string.h>

static int comparar_campo(const char *a, const char *b) {
    for (;;) {
        unsigned char aa = (unsigned char)*a;
        unsigned char bb = (unsigned char)*b;
        int ca = tolower(aa), cb = tolower(bb);
        if (ca != cb) return (ca > cb) ? 1 : -1;
        if (aa == '\0') return 0;
        ++a; ++b;
    }
}
int agenda_comparar_nomes(const Nome *a, const Nome *b) {
    int diff = comparar_campo(a->first_name, b->first_name);
    if (diff != 0) return diff;
    diff = comparar_campo(a->middle_name, b->middle_name);
    if (diff != 0) return diff;
    return comparar_campo(a->last_name, b->last_name);
}
static size_t posicao_insercao(const Agenda *agenda, const Nome *nome) {
    size_t baixo = 0, alto = agenda->quantidade;
    while (baixo < alto) {
        size_t meio = baixo + (alto - baixo) / 2;
        if (agenda_comparar_nomes(&agenda->contatos[meio].nome_contato, nome) < 0)
            baixo = meio + 1;
        else alto = meio;
    }
    return baixo;
}
int agenda_buscar(const Agenda *agenda, const Nome *nome) {
    size_t pos = posicao_insercao(agenda, nome);
    if (pos == agenda->quantidade ||
        agenda_comparar_nomes(&agenda->contatos[pos].nome_contato, nome) != 0)
        return -1;
    return (int)pos;
}
int agenda_inserir(Agenda *agenda, const Contato *contato) {
    if (agenda->quantidade >= TAM) return 0;
    size_t pos = posicao_insercao(agenda, &contato->nome_contato);
    if (pos < agenda->quantidade &&
        agenda_comparar_nomes(&agenda->contatos[pos].nome_contato,
                             &contato->nome_contato) == 0) return -1;
    if (pos < agenda->quantidade)
        memmove(&agenda->contatos[pos + 1], &agenda->contatos[pos],
                (agenda->quantidade - pos) * sizeof(Contato));
    agenda->contatos[pos] = *contato;
    ++agenda->quantidade;
    return 1;
}
int agenda_excluir(Agenda *agenda, const Nome *nome) {
    int pos = agenda_buscar(agenda, nome);
    if (pos < 0) return 0;
    size_t indice = (size_t)pos;
    if (indice + 1 < agenda->quantidade)
        memmove(&agenda->contatos[indice], &agenda->contatos[indice + 1],
                (agenda->quantidade - indice - 1) * sizeof(Contato));
    --agenda->quantidade;
    memset(&agenda->contatos[agenda->quantidade], 0, sizeof(Contato));
    return 1;
}
int data_valida(Data d) {
    static const int dias_mes[12] =
        {31,28,31,30,31,30,31,31,30,31,30,31};
    if (d.ano < 1800 || d.ano > 2100 ||
        d.mes < 1 || d.mes > 12 || d.dia < 1) return 0;
    int bissexto = (d.ano % 4 == 0 &&
                    (d.ano % 100 != 0 || d.ano % 400 == 0));
    int limite = dias_mes[d.mes - 1] + ((d.mes == 2 && bissexto) ? 1 : 0);
    return d.dia <= limite;
}
