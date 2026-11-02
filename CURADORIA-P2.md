# Curadoria proposta — C (2026-11-02)

## Inventário
Árvore da branch `main` original: 125 arquivos, 8.783.236 bytes. Identificados 16 executáveis `.exe` e 17 objetos `.o`, presentes principalmente em subpastas `bin/Debug/` e `obj/Debug/`. Muitos `.cbp` representam configurações úteis de Code::Blocks.

## Decisões por categoria
- **Preservar:** código C e C++ quando houver, projeto `.cbp`, PDFs autorais, recursos e datasets necessários a reprodução.
- **Não excluir por extensão apenas:** `.bin` e `.txt`, pois podem ser dados legítimos.
- **Candidatos à remoção após recompilação:** `bin/Debug/`, `obj/Debug/`, `*.layout`, `*.depend` e binários/objetos produzidos automaticamente.
- **Verificar antes de reorganizar:** `Controle_Academico/`, `registro_eleitores/`, `urna_eletronica/` e `gerador_nomes_aleatorios/` quanto à presença de dados pessoais reais versus amostras fictícias.

## Procedimento futuro
Gerar manifesto por SHA, revisar entrada/saída e reprodutibilidade, compilar projetos representativos, abrir PR de limpeza contendo lista exata de remoções e executar merge apenas com resultados verificáveis.

**Esta branch adiciona documentação e `.gitignore`, sem remover arquivos ou reescrever histórico.**
