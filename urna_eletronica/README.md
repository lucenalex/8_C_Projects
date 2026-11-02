# Urna eletrônica — simulador didático de estruturas de dados

> **Exclusivamente educacional.** Este código **não é** uma urna eleitoral real, não segue procedimentos de certificação, auditoria, sigilo, autenticação, controle de acesso ou legislação eleitoral, e **não deve ser utilizado para qualquer votação real**.

Esta pasta era um protótipo de prova de Estrutura de Dados com listas encadeadas para candidatos e eleitores. A revisão adicionou uma demonstração funcional em memória, usando **apenas nomes fictícios gerados automaticamente**.

## Funcionalidades demonstradas

- Inicialização com **200 eleitores fictícios** (códigos 1–200) e **20 candidatos fictícios** (números 101–120), distribuídos igualmente entre PBA, PBB, PBC, PBD e PBE.
- Cadastro e exclusão programática de elementos de listas encadeadas, com proteção para registros associados a votos.
- Índices de ponteiros ordenados e **busca binária** de códigos/numerações; os nós propriamente ditos permanecem em listas encadeadas.
- Um voto fictício por eleitor fictício; votos armazenados temporariamente em lista encadeada.
- Classificação dos candidatos por total decrescente de votos e apuração demonstrativa por partido.
- Exportação **opcional** dos eleitores fictícios em `eleitores_demo.csv`, sem sobrescrever arquivo preexistente. O CSV tem 200 registros se não houver exclusões.

## Compilação e testes

```bash
cd urna_eletronica
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror main.c simulador.c -o simulador_demo
./simulador_demo
bash tools/test_urna.sh
```

O projeto `urna_eletronica.cbp` foi atualizado para vincular `simulador.c`; a compilação específica com Code::Blocks no Windows **não foi homologada**.

## Estrutura

- `simulador.h`: tipos públicos, limites e API.
- `simulador.c`: listas, índices de busca, votos sintéticos, contagem, exportação e desalocação.
- `main.c`: menu educacional, entradas numéricas validadas e avisos.
- `tests/test_simulador.c`: testes de capacidade, voto único, índice binário, exclusão, apuração e CSV.
- `tests/test_cli.py`: testes de menu com dados sintéticos, diretório temporário e proteção contra sobrescrita.
- `tools/test_urna.sh`: compilação estrita com sanitizador UBSan e regressões.

## Limites científicos e técnicos

O uso de listas encadeadas e índices auxiliares de ponteiros demonstra estruturas de dados. Em aplicações de produção, seriam necessárias políticas de segurança, integridade, persistência, recuperação, privacidade e autenticação **não implementadas aqui**. Nenhuma identidade real é cadastrada. O arquivo CSV demonstra apenas dados inventados, criados localmente sob comando explícito. Não há conexão com a internet ou dispositivos eleitorais. A apuração não representa qualquer eleição real.

**Preservação:** o protótipo original está recuperável pelo histórico Git. Nenhum arquivo compilado foi removido nesta mudança.

Data de revisão: 02/11/2026.
