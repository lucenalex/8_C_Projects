# Política de retenção dos projetos C e binários históricos — 02/11/2026

Esta política complementa [AUDITORIA-EXECUTAVEIS-HISTORICOS-2026-11-02.md](AUDITORIA-EXECUTAVEIS-HISTORICOS-2026-11-02.md), [manifesto SHA](MANIFESTO-EXECUTAVEIS-HISTORICOS-2026-11-02.csv), [relatório de limpeza dos objetos](RELATORIO-LIMPEZA-OBJETOS-2026-11-02.md) e a [política científica principal do acervo LaTeX](https://github.com/lucenalex/6_LaTeX_Projects/blob/main/POLITICA-PRESERVACAO-CIENTIFICA-2026-11-02.md).

## Matriz de retenção

| Material | Política |
|---|---|
| Fontes C, Fortran, cabeçalhos e projetos `.cbp` | Preservação de versões e históricos; alterações somente por branch, PR e testes |
| **16 executáveis PE x64 históricos** | **Retenção arquivística: preservar os 16**; nenhum foi declarado substituível por equivalência binária |
| **17 objetos `.o` já retirados da HEAD** | Retidos no histórico Git e no backup pré-limpeza; manifesto com blob SHA no repositório |
| Programas atuais recompilados para testes | Artefatos de CI temporários, sem substituição dos `.exe` históricos |
| PDFs, arquivos compactados, dados e desenhos | Preservar enquanto origem, licença e conteúdo não forem classificados |
| Configurações, READMEs, logs de testes e manifests | Preservar como evidência de procedência/reprodutibilidade |
| Exemplos com dados fictícios | Usar somente entradas controladas; não assumir adequação para dados reais |

**Escopo e limitações:** a auditoria [Actions 41492513685](https://github.com/lucenalex/8_C_Projects/actions/runs/41492513685) verificou os 16 arquivos PE por cabeçalho, tamanho e hashes sem executá-los. A matriz Windows recompilou 17 projetos a partir das fontes atuais, **não os mesmos artefatos de 2022–2023**. Nenhuma certificação funcional dos binários históricos foi efetuada.

## Gates antes de alterações destrutivas

1. Identificar caminhos fechados, Git SHA/sha256, conteúdo, função didática e relações com outros repositórios.
2. Verificar se há valor de edição, direitos autorais, dados identificáveis ou dependências do ambiente antigo.
3. Atualizar backup Git completo, com verificação de `SHA256SUMS`, clone espelhado e `git fsck`. Guardar cópias fora do GitHub.
4. Validar fonte e binário em ambiente de testes isolado quando necessário, sem afirmar equivalência apenas por compilação.
5. Registrar decisão aprovada, revisão e proposta de PR independente. Não usar limpeza global por extensão.

**Decisão atual:** o [PR #2](https://github.com/lucenalex/8_C_Projects/pull/2) continua em rascunho e **não está autorizado para merge**. O [PR #16](https://github.com/lucenalex/8_C_Projects/pull/16) concluiu somente a retirada dos objetos `.o` da árvore atual; os executáveis são retidos.

O snapshot Git mais recente precisa ser renovado após novos commits de políticas e auditorias. O workflow `.github/workflows/backup-bundle.yml` permite gerar, verificar e restaurar um bundle quando disparado. Artefatos com prazo de retenção não substituem cópia independente permanente.
