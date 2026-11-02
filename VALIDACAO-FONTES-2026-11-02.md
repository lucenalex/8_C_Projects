# Validação incremental de fontes — C e Fortran (2026-11-02)

## Protocolo de verificação

A auditoria examinou a árvore Git em `main` após a organização documental e verificou estaticamente **20 fontes C** e um arquivo Fortran (`example/main.f90`) pela integração GitHub. Foram coletadas inclusões, nomes de funções potencialmente perigosas, rotinas de acesso a arquivos e dependências visíveis.

Um script de verificação está disponível em `tools/check_sources.sh`. Ele utiliza `gcc -std=c11 -Wall -Wextra -Wpedantic -fsyntax-only` e `gfortran -std=f2018 -Wall -Wextra -fsyntax-only`. **Não executa** os programas, não altera fontes e escreve CSV e logs em pasta temporária externa ao repositório.

Em checkout local autorizado:

```bash
bash tools/check_sources.sh
# Ou: bash tools/check_sources.sh /tmp/relatorios-c
```

O próprio script foi verificado sintaticamente (`bash -n`) e testado num conjunto local reduzido com **5 fontes** (4 Fortran e 1 C), obtendo 5 resultados PASS. **Não foi executado contra o checkout completo deste repositório**, que não pôde ser clonado neste ambiente por restrição de rede.

## Testes compilados e executados nesta auditoria

| Fonte | Estado |
|---|---|
| `busca_binaria_1/main.c` | Compila com GCC, executa busca por 63 |
| `EDB_AULA_2022_11_09/main.c` | Compila com GCC, imprime Hello world |

Esses dois casos não validam os demais projetos, testes de entradas malformadas, interoperabilidade com Code::Blocks ou executáveis do Windows.

## Riscos concretos encontrados em leitura estática

- **Uso da função `gets()`** nas fontes `Controle_Academico/main.c`, `Dois_Vetores_Ordenacao/main.c`, `gerador_nomes_aleatorios/main.c` e `registro_eleitores/main.c`. A função não faz controle do limite do buffer; substituir por `fgets()` com tamanho explícito e validação da entrada antes de confiar nesses programas.
- **Falha de E/S provável:** em `gerador_nomes_aleatorios/main.c`, o arquivo `exemplo.txt` é aberto em modo de leitura (`"r"`) e há tentativa posterior de gravar nele usando `fputc`. Isso não constitui um teste de execução, mas é um problema lógico identificável diretamente no fonte.
- **Dependência de terminal Windows:** diversos programas chamam `system("pause")`, cuja operação não é portátil. A existência de `system` também exige revisão de segurança e de contexto de execução.
- **Dados e entradas:** `criar_arquivo/main.c` utiliza um arquivo chamado `um_milhao_de_numeros.txt`, e há projetos de cadastro/eleitores. Conferir dados reais versus fictícios antes de realizar testes de execução com entrada/saída.

## Regra de integração

A proposta de remoção de **33 arquivos gerados** está no PR #2 (`cleanup/generated-artifacts-2026-11-02`), **em rascunho**. Ela não foi integrada à `main`. Antes do merge, são exigidos teste completo dos projetos em ambiente compatível, conferência das dependências de binários e backup Git externo restaurável.

**Não** inferir segurança, portabilidade ou reprodutibilidade de binários antigos a partir da compilação de dois exemplos ou do teste apenas sintático.
