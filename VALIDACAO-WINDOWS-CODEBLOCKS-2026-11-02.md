# Auditoria de compilação Windows/Code::Blocks — 02/11/2026

## Escopo e evidências

O [workflow Windows](https://github.com/lucenalex/8_C_Projects/actions/runs/41475391889) foi executado em **Windows Server 2022**, com **GCC UCRT64** instalado por MSYS2. Resultado: **11/11 projetos compilados e linkados** com sucesso, a partir das unidades (`Unit filename`) declaradas nos arquivos `.cbp`.

O verificador `tools/validate_codeblocks_projects.py` não executa binários antigos. Analisa XML, verifica se todos os fontes listados existem e gera executáveis em pasta temporária. A compilação é feita com `-std=c11 -Wall -Wextra -Wpedantic -Werror`. Os arquivos gerados não são adicionados ao repositório.

### Projetos validados

`Controle_Academico`, `Dois_Vetores_Ordenacao`, `EDB_SL2_Desafio_1`, `busca_linear_binaria`, `gerador_nomes_aleatorios`, `lista_linear_1`, `lista_nomes_masculinos`, `listas_encadeadas`, `ordenacao`, `registro_eleitores` e `urna_eletronica`.

## Quatro avisos históricos classificados

1. `criar_arquivo/main.c`: o ponto e vírgula excedente fora de função foi corrigido no código.
2. `main.c` na raiz: arquivo histórico formado somente por **7.834 bytes nulos**; não contém código-fonte C utilizável. Conservado, com classificação `SKIP_NULL_PLACEHOLDER` condicionada a verificar que **todos os bytes** continuam nulos.
3. `urna_eletronica/Untitled1.c`: arquivo histórico de 1 byte (nova linha), sem conteúdo. Conservado com classificação `SKIP_EMPTY_PLACEHOLDER`, condicionada a verificar que permanece vazio/whitespace.

No Linux, o [GitHub Actions 41475626481](https://github.com/lucenalex/8_C_Projects/actions/runs/41475626481) registrou **29 arquivos examinados, 27 PASS, 0 FAIL, 2 SKIP explicitados, 0 avisos**. Testes de regressão e execução controlada de exemplos permaneceram aprovados.

## Limites

- Compilar/linkar com GCC UCRT64 **não** equivale a executar a interface gráfica do IDE Code::Blocks, nem a certificar segurança/funcionamento de todos os programas sob Windows.
- O relatório valida somente os onze projetos selecionados, não os demais `.cbp` históricos.
- Os executáveis Windows já rastreados no Git não foram reproduzidos bit a bit e não foram removidos.
- O fluxo Windows não utiliza Intel Fortran; validação `ifx/ifort` permanece pendente no repositório Fortran.

**Encaminhamento:** preservar os binários antigos até verificar a necessidade de cada artefato; não integrar automaticamente o PR #2 de limpeza.
