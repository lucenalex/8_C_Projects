# Limpeza seletiva de arquivos intermediários C — auditoria de 02/11/2026

## Decisão aplicada

O [PR #16](https://github.com/lucenalex/8_C_Projects/pull/16) foi integrado por squash, commit `136786446823b4137b92c56489cf729d1a57aaae`. Ele removeu **somente 17 arquivos `.o` rastreados**, produzidos pelo ambiente Code::Blocks, e adicionou [MANIFESTO-OBJETOS-2026-11-02.csv](MANIFESTO-OBJETOS-2026-11-02.csv).

A comparação Git do PR continha **18 alterações**: 17 exclusões `.o` e um manifesto CSV. Não houve alterações de código-fonte nesse PR, nem remoção de `.exe`, recursos, arquivos-fonte `.c`/`.h`/`.f90`, projetos `.cbp` ou dados.

## Evidência verificada

| Item | Resultado |
|---|---|
| Objetos `.o` rastreados antes | 17, 181.536 bytes brutos |
| Verificação de caminho, tamanho e blob SHA | **17/17 correspondências** com a árvore `main` antes da limpeza |
| Objetos `.o` presentes em `main` após o merge | **0** |
| Executáveis históricos `.exe` presentes em `main` após o merge | **16**, todos preservados |
| Manifesto de objetos com hashes originais | Presente em `main` |
| PR #2, que propunha excluir também executáveis | **Ainda aberto em rascunho e não integrado** |

A remoção na revisão atual **não elimina os blobs do histórico Git** nem significa redução de 181.536 bytes no tamanho total do repositório.

## Backups antes da alteração

Os workflows do GitHub Actions criaram backups Git antes do PR #16:

- **C**: [execução 41489491376](https://github.com/lucenalex/8_C_Projects/actions/runs/41489491376), snapshot de `main` `22756dec4746787027f2b935c6dab96470b6d8a3`, contendo os 17 objetos históricos.
- **Fortran**: [execução 41489512432](https://github.com/lucenalex/7_Fortran_Projects/actions/runs/41489512432), snapshot de `main` `5b20e9b6b785c988b91c94765a1078cb17dbd55b`.

Os dois artefatos ZIP foram baixados no ambiente de auditoria, tiveram `SHA256SUMS.txt` verificado, e seus bundles foram **restaurados em clones Git espelhados externos aos runners**; o `git fsck --full --strict` e a presença do commit esperado passaram.

**Importante:** a retenção dos artefatos no GitHub Actions é de 14 dias. Guardar os arquivos ZIP em um armazenamento externo confiável. Os links de Actions não constituem backup permanente.

## Política futura

- Preservar os **16 executáveis `.exe`** até avaliação de procedência e reprodução do comportamento. A aprovação de compilação de 17 projetos Windows com GCC/GFortran não implica equivalência binária.
- Preservar todos os fontes, projetos Code::Blocks, artefatos de ensino e materiais que possam ser dados originais.
- Não integrar o PR #2 amplo no estado atual; reavaliar apenas caminhos individualmente.
- Para recuperar um `.o` histórico, consultar o commit anterior à remoção ou restaurar o bundle Git completo acima.
- Antes de alterações destrutivas adicionais, atualizar e testar novamente um backup independente.

Atualização documental da curadoria [CURADORIA-P2.md](CURADORIA-P2.md) e do [README.md](README.md).
