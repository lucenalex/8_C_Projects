# Testes funcionais dos seis exercícios históricos — 02/11/2026

## Objetivo e escopo

A compilação de **17 projetos Code::Blocks no Windows/MinGW** foi comprovada anteriormente. Esta rodada acrescenta testes de execução para os seis que ainda não estavam cobertos pelos cenários funcionais específicos. Todos os testes são executados **em pastas temporárias, com dados artificiais**, sem rodar executáveis antigos rastreados no Git.

| Projeto | Teste real | Alterações |
|---|---|---|
| `EDB_AULA_2022_11_09` | Compila e imprime `Hello world!` | Fonte original inalterado |
| `MinMaxFuction` | Mínimo/máximo, valores iguais, um único número, valor negativo extremo; dimensão e entrada inválidas | Validação de dimensão, componentes e alocação; tratamento da vida útil da memória |
| `busca_binaria_1` | Valores no começo/meio/fim, ausentes, argumento inválido | Busca binária com limites seguros e argumento opcional |
| `criar_arquivo` | Resultado concordante de Bubble/Selection/Insertion, arquivo com 30 registros, exclusividade de abertura, limites e proteção contra custo excessivo | Corrigidos Bubble e Insertion, gravação apenas se `--output` for passado, escrita `wx`, tamanho limitado |
| `example` (Fortran) | Leitura correta de inteiro, real, complexo e string; rejeição de entradas inválidas | `IOSTAT` e tratamento de falha nas operações `READ` |
| `racunho` | 20 ponteiros para o mesmo bloco, desalocação sem duplicidade | Corrigido vazamento de memória e demonstrada a relação de alias |

## Evidência executada

- [GitHub Actions Linux 41485112281](https://github.com/lucenalex/8_C_Projects/actions/runs/41485112281): compilação dos seis programas, testes funcionais aprovados; auditoria global de fontes com **27 PASS, 0 FAIL e 2 SKIP** (placeholders históricos); **zero avisos**.
- A compilação Windows de 17/17 projetos da **revisão anterior** está em [41481747271](https://github.com/lucenalex/8_C_Projects/actions/runs/41481747271). A alteração atual precisa ser revalidada no Windows antes do merge.
- Testes C usam `-std=c11 -Werror`, UndefinedBehaviorSanitizer (UBSan) e prazo de execução; o exemplo Fortran usa `-fcheck=all`. Essa proteção **não certifica ausência de bugs**.

Para reproduzir no Ubuntu com GCC, GFortran e Python 3:

```bash
python3 tools/test_six_legacy_projects.py
```

## Caso especial: `criar_arquivo`

O cabeçalho histórico mencionava gerar **um milhão de números**, mas a implementação tinha `#define tam 10` e três algoritmos de complexidade quadrática, com acesso fora dos limites e chamadas `system("pause")`. A revisão **não afirma executar um milhão de elementos** com Bubble/Selection/Insertion. Mantém o exercício didático, mas separa:

```bash
# Apenas computa/valida ordenações com 10 valores. Não grava arquivos.
gcc -std=c11 -Wall -Wextra -Wpedantic criar_arquivo/main.c -o exemplo_ordenacao
./exemplo_ordenacao

# Cria 30 valores artificiais com abertura exclusiva, sem sobrescrever.
./exemplo_ordenacao --count 30 --seed 2026 --output exemplo_numeros.txt
```

- Limite máximo de 10.000 inteiros nesta demonstração. Para mais de 2.000, exige `--allow-slow`; algoritmos `O(n^2)` **não são recomendados para um milhão** de registros.
- `--output` deve ser usado conscientemente em um diretório controlado; `fopen("wx")` não substitui controle de permissões ou gestão de dados.
- Saídas `clock()` medem apenas tempo aproximado de CPU e não são benchmark científico calibrado.

## Integridade e decisões

A intervenção altera apenas os cinco fontes citados, o script de testes, CI e documentação. O programa `EDB_AULA_2022_11_09` foi preservado. Os binários históricos e todos os 17 objetos `.o` da `main` permanecem intocados.

O [PR #2](https://github.com/lucenalex/8_C_Projects/pull/2) de limpeza ampla e o [PR #16](https://github.com/lucenalex/8_C_Projects/pull/16) de limpeza apenas de objetos seguem **em rascunho, sem integração**.

Estes seis programas são **exercícios históricos**, não aplicações para uso operacional. Testes numéricos, memória e I/O de cenários delimitados não substituem testes de todos os casos possíveis.
