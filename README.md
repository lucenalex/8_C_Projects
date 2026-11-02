# Estudos de C e Estruturas de Dados — código, testes e acervo histórico

Coleção de exercícios didáticos independentes em C, com um exemplo adicional em Fortran. **Não constitui uma biblioteca única nem software homologado para uso real.**

**Documentação atualizada em 02/11/2026**, com referência à evidência dos workflows do GitHub Actions e à política de preservação do código anterior no histórico Git.

## Onde encontrar os projetos

| Grupo | Pastas |
|---|---|
| Busca e ordenação | `busca_binaria_1/`, `busca_linear_binaria/`, `ordenacao/`, `Dois_Vetores_Ordenacao/` |
| Estruturas encadeadas e listas | `lista_linear_1/`, `listas_encadeadas/`, `lista_nomes_masculinos/` |
| Arquivos e dados de demonstração | `criar_arquivo/`, `gerador_nomes_aleatorios/`, `registro_eleitores/` |
| Cadastros e aplicações de sala de aula | `Controle_Academico/`, `EDB_SL2_Desafio_1/`, `MinMaxFuction/`, `urna_eletronica/` |
| Experimentos de aprendizagem | `EDB_AULA_2022_11_09/`, `example/` (**Fortran**), `racunho/`, `java1/` |

## O que foi efetivamente validado

| Verificação | Resultado e referência |
|---|---|
| Compilação dos projetos Code::Blocks no Windows/MinGW | **17/17 projetos aprovados** na [matriz Windows inicial ampliada](https://github.com/lucenalex/8_C_Projects/actions/runs/41481747271), incluindo `example` com GFortran |
| Verificação global de sintaxe no Linux após novas correções | **27 PASS, 0 FAIL, 2 SKIP históricos justificados, 0 avisos**; [GitHub Actions 41485112281](https://github.com/lucenalex/8_C_Projects/actions/runs/41485112281) |
| Exercícios principais | Testes funcionais de agenda, controle acadêmico, arquivos, registros, listas encadeadas, busca/ordenação e simulador didático |
| Seis exercícios anteriormente sem testes de execução | **6/6 cenários funcionais aprovados**; [relatório dos seis](VALIDACAO-FUNCIONAL-SEIS-PROJETOS-2026-11-02.md) |
| Windows depois das últimas correções | Matriz do novo PR em execução/revisão; **não confundir com o resultado anterior** |
| Equivalência com `.exe` antigos e execução na interface Code::Blocks | **Não comprovadas** |

Dois arquivos classificados explicitamente como `SKIP` são placeholders históricos sem código-fonte executável: `main.c` (raiz, composto por bytes NUL) e `urna_eletronica/Untitled1.c` (whitespace). Eles **não foram apagados**.

## Como executar os testes localmente

Requisitos: compiladores GCC e GFortran, Python 3 e Bash em ambiente Linux compatível.

```bash
# Auditoria de sintaxe sem executar programas arbitrários
bash tools/check_sources.sh

# Testes dirigidos, usando somente dados artificiais e pastas temporárias
bash tools/smoke_tests.sh
bash EDB_SL2_Desafio_1/tools/test_agenda.sh
python3 tools/test_legacy_records.py
python3 tools/test_search_sort_lists.py
bash urna_eletronica/tools/test_urna.sh
python3 tools/test_six_legacy_projects.py
```

O workflow `.github/workflows/source-syntax.yml` executa as verificações no GitHub Actions. `tools/validate_codeblocks_projects.py` lê as unidades declaradas nos arquivos `.cbp` e compila os projetos em runner Windows/GCC UCRT64, mas não inicia o IDE nem testa executáveis Windows antigos.

## Segurança, limitações e preservação

- `urna_eletronica` é um **simulador educacional com eleitores e candidatos fictícios**. Não é urna homologada e não pode ser empregado em votação real.
- A agenda e o controle acadêmico são demonstrações em memória e não devem armazenar dados pessoais reais.
- `criar_arquivo` usa somente entradas/arquivos sintéticos nos testes. O enunciado histórico de um milhão de elementos é **incompatível com uma demonstração prática baseada em três algoritmos `O(n^2)`**; a execução agora é limitada e protege contra sobrescrita.
- A versão original dos programas permanece recuperável no histórico Git. Um teste verde **não comprova ausência completa de defeitos**, compatibilidade Windows/GUI nem identidade de binários gerados.
- O [PR #2](https://github.com/lucenalex/8_C_Projects/pull/2) de remoção ampla de 33 artefatos e o [PR #16](https://github.com/lucenalex/8_C_Projects/pull/16), restrito a 17 arquivos `.o`, continuam **em rascunho e sem integração**. **Nenhum executável `.exe` histórico foi removido.**
- Há backup Git independente de revisão anterior restaurado e verificado; após qualquer merge novo, atualizar snapshot antes de excluir arquivos. `.gitignore` **não remove objetos já rastreados**.

## Documentação técnica

- [Curadoria dos projetos](CURADORIA-P2.md)
- [Validação inicial de fontes](VALIDACAO-FONTES-2026-11-02.md)
- [Correções e avisos](AUDITORIA-AVISOS-2026-11-02.md)
- [Validação de arquivos e cadastros](VALIDACAO-REGISTROS-ARQUIVOS-2026-11-02.md)
- [Validação inicial Code::Blocks/Windows](VALIDACAO-WINDOWS-CODEBLOCKS-2026-11-02.md)
- [Ampliação para 17 projetos Code::Blocks](VALIDACAO-WINDOWS-AMPLIADA-17-CBP-2026-11-02.md)
- [Validação funcional dos seis exemplos finais](VALIDACAO-FUNCIONAL-SEIS-PROJETOS-2026-11-02.md)

**Direitos autorais:** não foi confirmada licença de distribuição geral na raiz. Materiais de terceiros devem ser avaliados individualmente antes de republicação.
