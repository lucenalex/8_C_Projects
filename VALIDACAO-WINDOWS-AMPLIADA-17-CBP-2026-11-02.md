# Validação ampliada dos projetos Code::Blocks — 02/11/2026

## Resultado observado

Execução <https://github.com/lucenalex/8_C_Projects/actions/runs/41481747271>: **17/17 projetos compilados e linkados com êxito** no Windows Server 2022, MSYS2 UCRT64, usando GCC e GFortran. O projeto `example` é Fortran; os demais são C.

Os onze projetos anteriormente aprovados permaneceram aprovados. Os **seis projetos adicionais** são:

- `EDB_AULA_2022_11_09` — GCC C
- `MinMaxFuction` — GCC C
- `busca_binaria_1` — GCC C
- `criar_arquivo` — GCC C
- `example` — GFortran Fortran
- `racunho` — GCC C

## O que foi testado

`tools/validate_codeblocks_projects.py` analisa cada arquivo `.cbp`, verifica se as unidades mencionadas existem, seleciona GCC ou GFortran conforme o código, compila e executa somente o linker, produzindo executáveis de teste em pasta temporária, sob `-Wall -Wextra -Wpedantic -Werror`. Nenhum binário antigo do repositório foi executado ou alterado. O teste não abre o IDE Code::Blocks.

## Interpretação dos resultados

Compilar todas as unidades de 17 projetos **não prova equivalência binária** com os executáveis históricos `.exe`, nem conformidade funcional dos seis programas que foram somente compilados. Testes funcionais existentes cobrem os exemplos corrigidos das etapas anteriores. `criar_arquivo` ainda exige exame próprio antes de executar por produzir arquivos de dados e usar algoritmos quadráticos.

## Próxima limpeza segura

- **17 arquivos `.o` rastreados, totalizando 181.536 bytes:** são produtos intermediários de compilação, já recuperáveis nos commits históricos; elegíveis a proposta de limpeza separada com manifesto SHA. Não representam economia imediata de 181 KB no armazenamento Git (histórico preservado).
- **16 executáveis `.exe` históricos:** manter preservados, apesar das compilações bem-sucedidas, até decisão por projeto sobre valor histórico e equivalência funcional.
- O PR #2 original propõe retirar objetos **e** executáveis; **não integrar em seu formato atual**.
- Antes de qualquer nova exclusão, manter bundles atualizados e testar a restauração.

Este relatório documenta a comprovação de compilação **Windows/MinGW**, não certificação de execução ou hardware real.
