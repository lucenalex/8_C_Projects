# Validação funcional — cadastro e arquivos C (02/11/2026)

**Branch de origem:** `fix/legacy-file-and-records-2026-11-02`  
**Objetivo:** corrigir os quatro exercícios antigos sem remover os executáveis, dados e histórico.

## Correções

| Exercício | Defeito confirmado | Alteração |
|---|---|---|
| `lista_nomes_masculinos` | Abria um arquivo binário, mas não executava `fwrite`; usava `strcpy(fgets(...))`, indexação insegura e não liberava o buffer de caracteres | Escrita de registros binários de 15 bytes, limite de 20 nomes, entrada limitada e `free` |
| `gerador_nomes_aleatorios` | Entrada vazia ou truncada podia ser gravada diretamente | Validar entrada antes de abrir `exemplo.txt`, preservando o conteúdo existente em `a+` |
| `registro_eleitores` | Entrada maior que o buffer deixava caracteres pendentes para serem interpretados como novos comandos | Drenar restante da linha e rejeitar a operação sem cadastrar registro parcial |
| `Controle_Academico` | Opções numéricas ou médias muito longas deixavam caracteres no fluxo de entrada | Consumir a linha longa antes de continuar a leitura de um novo número |

## Verificação reprodutível

```bash
python3 tools/test_legacy_records.py
```

O script cria uma pasta temporária, compila os quatro arquivos com `gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -fsanitize=undefined`, executa cenários com nomes **fictícios**, verifica os arquivos produzidos por bytes e apaga o diretório temporário ao terminar. Não executa binários antigos e não sobrescreve os dados armazenados no Git.

**GitHub Actions:** [execução 41467483898](https://github.com/lucenalex/8_C_Projects/actions/runs/41467483898) — teste de sintaxe **23/23 PASS**, 0 FAIL, 22 avisos em outros arquivos, suíte da agenda e 4 programas de cadastro/arquivos aprovados.

## Limitações

- O arquivo `nomes_masculinos.bin` usa registros fixos de 15 bytes **sem cabeçalho ou especificação multiplataforma**; é um formato didático, não um banco de dados.
- `gerador_nomes_aleatorios` demonstra leitura e append de nomes; **não gera nomes aleatórios**, apesar do nome histórico do repositório.
- `registro_eleitores` é apenas demonstração de lista encadeada com registros fictícios, não um sistema eleitoral real.
- `Controle_Academico` oferece cadastro, matrícula, média e boletim na memória; não é um sistema escolar para dados reais.
- UBSan e casos automatizados não provam ausência absoluta de falhas, nem substituem inspeção de portabilidade Windows/Code::Blocks.
- Arquivos antigos `.exe`, `.o` e outros artefatos não foram removidos; seu descarte depende de aprovação separada.

**Critério de aceite:** teste concluído no checkout GitHub e diff limitado a fontes, teste e documentação.
