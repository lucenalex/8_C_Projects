# Manutenção de alertas do compilador C — 02/11/2026

## Evidência de regressão
Após os ajustes no fluxo de leitura do exercício `EDB_SL2_Desafio_1/main.c`, o GitHub Actions passou com **21/21 verificações sintáticas e 5 testes funcionais pré-existentes**. Os avisos passaram de **40 para 24**, redução de 16.

## Problema corrigido
O código original possuía 16 chamadas como `scanf("15[^\\n]", campo)`, sem o especificador de conversão `%`, o que deixava de preencher os campos e gerava avisos `-Wformat-extra-args`. Foram substituídas por formatos com limite inferior à capacidade do vetor e espaço inicial para ignorar separadores de entrada. Exemplo: `scanf(" %14[^\\n]", campo)` para um campo de 15 caracteres.

**Preservação de codificação:** alterações de bytes ASCII aplicadas diretamente ao arquivo original sem decodificação ou recodificação dos textos antigos em português. Nenhum arquivo binário ou dado foi removido.

## Limites
- A compilação sintática agora apresenta 24 avisos remanescentes, sobretudo pontos e vírgulas excedentes fora de funções, variáveis não utilizadas e um arquivo `main.c` de conteúdo inválido/vazio herdado do acervo.
- O exercício `EDB_SL2_Desafio_1` não possui teste funcional completo de inclusão, busca e exclusão; o ajuste de `scanf` não prova que a agenda inteira funcione.
- Alguns arquivos mantêm `system("pause")`, `system("cls")` e código legado dependente de terminal Windows.
- Não mesclar o PR #2 de limpeza de executáveis com correções de código.

## Próxima intervenção
Conferir o comportamento da agenda com testes sintéticos em ambiente isolado, revisar a busca e exclusão de contatos, tratar arquivos fonte vazios e classificar os 24 avisos sem mascará-los com supressão genérica.
