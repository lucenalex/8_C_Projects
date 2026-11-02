# Verificação de compilação e proposta de limpeza — C (2026-11-02)

## Escopo deste branch
- Remoção **apenas neste branch** de 33 caminhos binários `.exe` e `.o` em `bin/Debug/` e `obj/Debug/`.
- Redução nominal de blobs na revisão: **5.545.468 bytes**. Esse número **não** é economia do armazenamento do GitHub ou de histórico.
- Caminhos originais, SHA Git e tamanho no `MANIFESTO-REMOCao-PROPOSTA-2026-11-02.csv`.
- Nenhum arquivo `.c`, `.h`, `.cbp`, dado ou PDF de referência foi selecionado para exclusão.

## Testes realizados
Compilação local pontual com `gcc -std=c11 -Wall -Wextra -Wpedantic`. Fontes obtidas do GitHub conectado e reproduzidas no ambiente temporário para os ensaios; não se realizou checkout completo do repositório.

| Fonte testada | Resultado de compilação | Execução |
|---|---|---|
| `busca_binaria_1/main.c` | Sucesso | Busca do valor 63 retorna “Dado encontrado” |
| `EDB_AULA_2022_11_09/main.c` | Sucesso | “Hello world!” |

**Limitação:** são **2 dos 19 programas em C** com arquivos `.c` identificados. Não houve teste de compilação individual dos demais nem comparação bit a bit com executáveis Windows antigos. O texto transcrito em um teste foi normalizado sem alterar o comportamento observado.

## Decisão de integração
Este PR deve ficar **em modo rascunho**: remover executáveis antigos é conceitualmente reversível pelo histórico, mas ainda exige confirmação de que todos os projetos podem ser compilados e de que não há referência operacional à presença dos executáveis no repositório.

## Condições antes do merge
1. Conferir o manifesto contra o diff.
2. Verificar todas as entradas de código-fonte e dados de execução.
3. Testar compilação/uso em ambiente seguro, sobretudo os projetos com múltiplos arquivos.
4. Manter o commit de preservação `preservation/precleanup-2026-11-02` como referência auxiliar e realizar backup externo antes de integrar.
