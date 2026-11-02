# Agenda de contatos — Desafio de Estruturas de Dados Básicas (2022.2)

Revisão funcional do exercício acadêmico original de 2023, preservado no histórico Git.

## Requisitos do enunciado

- Capacidade de **200 contatos**.
- Nome completo, endereço, telefone, e-mail e data de nascimento.
- Inclusão, procura, listagem e exclusão.
- **Busca binária**: o vetor é mantido ordenado pelo trio primeiro nome, nome do meio e sobrenome (comparação ASCII sem distinção de maiúsculas/minúsculas).
- Identificação por nome completo: nomes completos idênticos não são cadastrados duas vezes.
- Exclusão só reduz a contagem se confirmada; os elementos posteriores são deslocados sem acessar além do vetor.

## Construir e testar (Linux/macOS com GCC + Python 3)

```bash
cd EDB_SL2_Desafio_1
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror main.c agenda.c -o agenda
./agenda
bash tools/test_agenda.sh
```

No Windows, o arquivo `EDB_SL2_Desafio_1.cbp` foi atualizado para incluir `agenda.c` e `agenda.h` no projeto Code::Blocks. A compilação do projeto Code::Blocks **não foi testada no Windows**.

## Organização

- `agenda.h`: tipos, capacidade e interface do modelo.
- `agenda.c`: ordenação, busca binária, inclusão, exclusão e calendário.
- `main.c`: menu e leitura segura de entradas.
- `tests/test_agenda.c`: datas, ordenação, duplicatas, limite 200, buscas e remoção.
- `tests/test_agenda_cli.py`: cenários fictícios interativos, cancelamento e entradas inválidas.
- `tools/test_agenda.sh`: compilação com UBSan e execução dos testes.

**Privacidade:** nenhum contato é gravado em arquivo ou enviado pela rede; o conteúdo é mantido em memória e perdido ao encerrar. Use dados fictícios em testes. A versão é um **exemplo didático**, não um gerenciador de contatos para produção; não implementa persistência, autenticação, criptografia ou validação formal de e-mail/telefone. Letras acentuadas não recebem equivalência maiúscula/minúscula Unicode na ordenação; o comportamento de colação é explícito e determinístico.

## Restrições e resultados da verificação

- O código original continha busca não implementada, acesso potencial fora dos limites e decréscimo indevido da contagem após cancelamento da exclusão.
- A nova implementação foi verificada localmente com GCC 14.2 + UBSan e testes de integração do menu. Os testes de GitHub Actions serão anexados ao pull request desta mudança.
- As pastas `bin/`, `obj/` e os executáveis históricos permanecem intactos na `main` até decisão separada sobre a limpeza.

Data da intervenção: 02/11/2026.
