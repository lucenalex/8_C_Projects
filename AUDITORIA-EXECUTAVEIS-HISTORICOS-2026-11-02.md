# Auditoria arquivística dos 16 executáveis históricos de C e Fortran

**Data:** 02/11/2026  
**Escopo:** `8_C_Projects`, 16 executáveis em `*/bin/Debug/*.exe`, sem execução de nenhum deles.  
**Método:** inspeção dos objetos binários originais extraídos de um bundle Git restaurado, verificação de SHA-256 e Git blob SHA, interpretação estática dos cabeçalhos PE e correspondência com projetos Code::Blocks.

## Resultado

- **16/16 arquivos** identificados como **PE32+ x86-64**, subsistema de console Windows.
- Total dos arquivos: **5.363.932 bytes** (aproximadamente 5,12 MiB).
- Todos pertencem a um projeto `.cbp` de mesmo nome que declara um destino `bin/Debug`, embora a lista de fontes de alguns projetos tenha mudado desde a geração dos executáveis.
- As datas COFF embutidas estão entre **18/09/2022 e 31/01/2023**. São somente metadados do cabeçalho; não demonstram, isoladamente, autoria nem a data real da compilação.
- O commit encontrado pelo `git log -- <caminho>` para a última adição/alteração de cada binário é `8f3744a` (20/02/2023, horário do commit).
- Imports estáticos mais comuns: `KERNEL32.dll` e `msvcrt.dll`. Exceções: `example.exe` também importa `libgfortran-5.dll`; `criar_arquivo.exe`, `libwinpthread-1.dll`. A presença de import **não comprova** que a DLL esteja atualmente disponível.

Ver [manifesto por arquivo com SHA-256 e Git blob SHA](MANIFESTO-EXECUTAVEIS-HISTORICOS-2026-11-02.csv) para a identificação inequívoca de cada executável.

## Decisão por executável

| Projeto / executável | Prioridade de conservação | Fundamentação | Situação |
|---|---|---|---|
| `Controle_Academico.exe` | Alta | Exemplo antigo de gestão de cadastros; permite preservar a evolução didática anterior às correções | Preservar |
| `EDB_AULA_2022_11_09.exe` | Regular | Exemplo introdutório, aparentemente reproduzível, mas ainda sem equivalência binária comprovada | Preservar |
| `EDB_SL2_Desafio_1.exe` | Alta | Representa versão histórica anterior à reestruturação da agenda | Preservar |
| `MinMaxFuction.exe` | Regular | Exercício anterior à validação robusta de dimensões e entradas | Preservar |
| `busca_binaria_1.exe` | Regular | Versão anterior ao conjunto ampliado de testes e entradas | Preservar |
| `busca_linear_binaria.exe` | Regular | Registra a implementação didática original de dois vetores | Preservar |
| `criar_arquivo.exe` | Alta | Algoritmos de ordenação e gravação do exercício antigo; dependência `libwinpthread-1.dll`. **Não executar** sobre arquivos de trabalho | Preservar |
| `example.exe` | Alta | Único exemplo Fortran entre os 16, dependente de `libgfortran-5.dll` | Preservar |
| `gerador_nomes_aleatorios.exe` | Regular | Demonstração antiga de operações de arquivo, anterior às proteções de entrada/escrita | Preservar |
| `lista_linear_1.exe` | Regular | Exercício original de lista e busca | Preservar |
| `lista_nomes_masculinos.exe` | Regular | Exemplo histórico de registros binários de comprimento fixo | Preservar |
| `listas_encadeadas.exe` | Regular | Versão anterior à separação entre módulo e testes de lista | Preservar |
| `ordenacao.exe` | Alta | Versão original de algoritmos posteriormente corrigidos para limites e deslocamentos | Preservar |
| `racunho.exe` | Regular | Experimento didático de ponteiros e propriedade de memória | Preservar |
| `registro_eleitores.exe` | Alta | Versão antiga de exercício com cadastros; inspecionar somente com dados artificiais em ambiente isolado | Preservar |
| `urna_eletronica.exe` | Alta | Protótipo acadêmico original anterior ao simulador atual. **Não é software eleitoral homologado** | Preservar |

São **7 arquivos de prioridade arquivística alta e 9 de prioridade regular**. Prioridade regular **não significa autorização de exclusão**. A decisão para os 16 é conservar como evidência do desenvolvimento histórico até política de retenção explicitamente aprovada.

## Critérios técnicos de preservação

1. **Fonte atual e binário antigo são objetos diferentes.** O [workflow Windows](https://github.com/lucenalex/8_C_Projects/actions/runs/41485112296) compilou e linkou os 17 projetos Code::Blocks atuais, mas **não reproduziu byte a byte** nenhum dos 16 arquivos antigos.
2. O histórico Git é suficiente para recuperar os arquivos versionados enquanto o histórico permanecer íntegro; há também [backup Git completo restaurável](https://github.com/lucenalex/8_C_Projects/actions/runs/41489491376). Cópias exportadas e armazenadas fora do GitHub são recomendadas porque os artefatos Actions expiram.
3. Executáveis são **evidência arquivística não confiável**, e não meios preferenciais para executar exemplos. Para ensino, utilizar fontes atuais recompilados e testados, em ambiente controlado.
4. Os hashes do manifesto identificam o conteúdo. Um hash íntegro **não certifica segurança**, procedência do compilador nem ausência de código malicioso.
5. A diferença entre datas de cabeçalho e commits de origem não permite reconstruir toda a cadeia de compilação, opções, SDKs ou DLLs.
6. Nenhum executável foi executado nesta análise, e nenhum foi removido.

## Verificação reproduzível e sem execução

```bash
python3 tools/audit_historical_pe.py
```

O verificador compara **os 16 hashes SHA-256, 16 Git blob SHA e tamanhos**, confirma assinaturas PE, arquitetura x64, subsistema console, timestamp COFF e associação com arquivos `.cbp`; também sinaliza imports adicionais conhecidos. A verificação automatizada está em `.github/workflows/audit-historical-pe.yml`. Um resultado PASS significa **integridade estática do inventário**, não validação funcional.

## Pendências da próxima etapa

- Estabelecer política de armazenamento arquivístico de executáveis antigos fora do diretório usual de build sem apagar ou reescrever o histórico; qualquer mudança requer decisão separada.
- Se for necessário avaliar comportamento antigo, preparar ambiente Windows isolado, entradas sintéticas e registro dos hashes; não executar esses programas diretamente no computador pessoal.
- Para o repositório `7_Fortran_Projects`, continuar bloqueada qualquer limpeza ampla antes de validação real com Intel `ifx/ifort` e Visual Studio e da recuperação ou classificação definitiva dos projetos incompletos.
- O [PR #2 de limpeza ampla](https://github.com/lucenalex/8_C_Projects/pull/2) permanece em rascunho e **não deve ser integrado**: sua proposta de retirada de executáveis já não corresponde à política de preservação aqui documentada.

**Conclusão:** manter os 16 `.exe` históricos em repositório e em backup, com inventário técnico e distinção clara entre versões antigas e fontes atuais.
