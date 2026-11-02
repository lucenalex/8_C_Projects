/* Agenda de contatos — Desafio de Estruturas de Dados Basicas (2022.2).
 * Capacidade de 200 contatos, ordenacao por nome completo e busca binaria.
 * Os dados ficam apenas na memoria; nao gravar informacoes pessoais reais.
 * Esta revisao preserva a proposta didatica, substituindo chamadas inseguras.
 */
#include "agenda.h"
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Retorna 1 se preencheu a linha, 0 em EOF, -1 para linha excessiva. */
static int ler_linha(char *destino, size_t capacidade) {
    char temporario[512];
    if (!fgets(temporario, sizeof temporario, stdin)) return 0;
    size_t n = strcspn(temporario, "\n");
    if (temporario[n] != '\n' && !feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        return -1;
    }
    if (n > 0 && temporario[n - 1] == '\r') --n;
    if (n >= capacidade) return -1;
    memcpy(destino, temporario, n);
    destino[n] = '\0';
    return 1;
}

static int perguntar_texto(const char *rotulo, char *destino,
                          size_t capacidade, int obrigatorio) {
    for (;;) {
        printf("%s: ", rotulo);
        fflush(stdout);
        int resultado = ler_linha(destino, capacidade);
        if (resultado == 0) return 0;
        if (resultado == -1) {
            puts("Entrada muito longa; tente novamente.");
            continue;
        }
        if (obrigatorio && destino[0] == '\0') {
            puts("Este campo é obrigatório.");
            continue;
        }
        return 1;
    }
}

static int perguntar_inteiro(const char *rotulo, int *saida,
                             int minimo, int maximo) {
    char linha[64];
    for (;;) {
        if (!perguntar_texto(rotulo, linha, sizeof linha, 1)) return 0;
        char *fim;
        errno = 0;
        long v = strtol(linha, &fim, 10);
        while (isspace((unsigned char)*fim)) ++fim;
        if (errno == 0 && fim != linha && *fim == '\0' &&
            v >= minimo && v <= maximo && v >= INT_MIN && v <= INT_MAX) {
            *saida = (int)v;
            return 1;
        }
        printf("Informe um inteiro entre %d e %d.\n", minimo, maximo);
    }
}
#define PERGUNTAR(rotulo, campo, obrigatorio) \
    do { if (!perguntar_texto((rotulo), (campo), sizeof(campo), (obrigatorio))) return 0; } while (0)

static int perguntar_nome(Nome *nome) {
    PERGUNTAR("Primeiro nome", nome->first_name, 1);
    PERGUNTAR("Nome do meio (opcional)", nome->middle_name, 0);
    PERGUNTAR("Sobrenome", nome->last_name, 1);
    return 1;
}
static int perguntar_data(Data *data) {
    for (;;) {
        if (!perguntar_inteiro("Dia", &data->dia, 1, 31) ||
            !perguntar_inteiro("Mês", &data->mes, 1, 12) ||
            !perguntar_inteiro("Ano", &data->ano, 1800, 2100)) return 0;
        if (data_valida(*data)) return 1;
        puts("Data inválida; confira os dias do mês e os anos bissextos.");
    }
}
static int perguntar_contato(Contato *contato) {
    memset(contato, 0, sizeof *contato);
    if (!perguntar_nome(&contato->nome_contato)) return 0;
    if (!perguntar_data(&contato->dt_nasc)) return 0;
    PERGUNTAR("Tipo do logradouro", contato->endereco.tipo, 1);
    PERGUNTAR("Nome do logradouro", contato->endereco.nome, 1);
    PERGUNTAR("Número", contato->endereco.numero, 1);
    PERGUNTAR("CEP", contato->endereco.cep, 1);
    PERGUNTAR("Bairro", contato->endereco.bairro, 1);
    PERGUNTAR("Cidade", contato->endereco.cidade, 1);
    PERGUNTAR("UF (até 2 caracteres)", contato->endereco.uf, 1);
    PERGUNTAR("País", contato->endereco.pais, 1);
    PERGUNTAR("DDI", contato->telefone.ddi, 1);
    PERGUNTAR("Operadora", contato->telefone.cop, 1);
    PERGUNTAR("DDD", contato->telefone.ddd, 1);
    PERGUNTAR("Telefone", contato->telefone.ntf, 1);
    for (;;) {
        PERGUNTAR("E-mail", contato->email, 1);
        const char *at = strchr(contato->email, '@');
        if (at && at != contato->email &&
            strchr(at + 1, '.') && at[1] != '\0') return 1;
        puts("E-mail inválido; use o formato nome@dominio.tld.");
    }
}
static void exibir_contato(const Contato *c, size_t indice) {
    printf("[%zu] %s %s %s\n", indice + 1, c->nome_contato.first_name,
           c->nome_contato.middle_name, c->nome_contato.last_name);
    printf("Nascimento: %02d/%02d/%04d\n",
           c->dt_nasc.dia, c->dt_nasc.mes, c->dt_nasc.ano);
    printf("Endereço: %s %s, %s, %s, %s, %s-%s, %s\n",
           c->endereco.tipo, c->endereco.nome, c->endereco.numero,
           c->endereco.bairro, c->endereco.cep, c->endereco.cidade,
           c->endereco.uf, c->endereco.pais);
    printf("Telefone: +%s %s (%s) %s\n", c->telefone.ddi,
           c->telefone.cop, c->telefone.ddd, c->telefone.ntf);
    printf("E-mail: %s\n", c->email);
}
int main(void) {
    Agenda agenda = {0};
    puts("AGENDA — Exercício didático. Dados mantidos apenas em memória.");
    for (;;) {
        int opcao;
        puts("\n0 Sair | 1 Adicionar | 2 Procurar | 3 Exibir todos | 4 Excluir");
        if (!perguntar_inteiro("Opção", &opcao, 0, 4)) break;
        if (opcao == 0) break;
        if (opcao == 1) {
            if (agenda.quantidade >= TAM) {
                puts("Agenda cheia: limite de 200 contatos.");
                continue;
            }
            Contato novo;
            if (!perguntar_contato(&novo)) break;
            int resultado = agenda_inserir(&agenda, &novo);
            if (resultado == 1)
                printf("Contato adicionado. Total: %zu\n", agenda.quantidade);
            else if (resultado == -1) puts("Nome completo já cadastrado.");
            else puts("Agenda cheia.");
        } else if (opcao == 3) {
            printf("Total de contatos: %zu\n", agenda.quantidade);
            for (size_t i = 0; i < agenda.quantidade; ++i)
                exibir_contato(&agenda.contatos[i], i);
        } else {
            if (agenda.quantidade == 0) {
                puts("Agenda vazia.");
                continue;
            }
            Nome nome = {0};
            if (!perguntar_nome(&nome)) break;
            int pos = agenda_buscar(&agenda, &nome);
            if (pos < 0) {
                puts("Contato não encontrado.");
                continue;
            }
            if (opcao == 2) {
                puts("Contato encontrado:");
                exibir_contato(&agenda.contatos[(size_t)pos], (size_t)pos);
            } else {
                exibir_contato(&agenda.contatos[(size_t)pos], (size_t)pos);
                int confirmacao;
                if (!perguntar_inteiro("Confirmar exclusão? (1 sim, 2 não)",
                                      &confirmacao, 1, 2)) break;
                if (confirmacao == 1) {
                    (void)agenda_excluir(&agenda, &nome);
                    printf("Contato excluído. Total: %zu\n", agenda.quantidade);
                } else puts("Exclusão cancelada.");
            }
        }
    }
    puts("Agenda encerrada. Os dados não foram gravados em disco.");
    return 0;
}
