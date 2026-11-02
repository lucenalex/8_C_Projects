#!/usr/bin/env python3
"""Testes com entradas ficticias e tempo limite; sem dados pessoais reais."""
import subprocess
import sys
from pathlib import Path

EXEC = str(Path(sys.argv[1]).resolve())

def pessoa(primeiro, sobrenome, data=('29','2','2024'), email='teste@example.org'):
    return [primeiro, '', sobrenome, *data, 'Rua','Teste','42','65000000',
            'Centro','Sao Luis','MA','Brasil','55','15','98','999999999',email]

def rodar(entradas):
    p = subprocess.run([EXEC], input='\n'.join(entradas)+'\n', text=True,
                       capture_output=True, timeout=8, check=True)
    return p.stdout

def contar(saida, texto, n=1):
    assert saida.count(texto) >= n, (
        f"Esperado {texto!r} {n} vezes, encontrado {saida.count(texto)}\n"
        f"{saida[-1000:]}"
    )

def testar_cadastro_busca_exclusao():
    entradas = ['1', *pessoa('Zoe','Z'), '1', *pessoa('Alice','A'),
                '1', *pessoa('Mario','M'), '3',
                '2', 'alice', '', 'a',
                '4', 'Mario', '', 'M', '2',
                '4', 'Mario', '', 'M', '1',
                '2', 'Mario', '', 'M', '1', *pessoa('Alice','A'), '3', '0']
    saida = rodar(entradas)
    for trecho in ('Contato adicionado. Total: 3', 'Contato encontrado:',
                   'Exclusão cancelada.', 'Contato excluído. Total: 2',
                   'Contato não encontrado.', 'Nome completo já cadastrado.',
                   'Total de contatos: 2'):
        contar(saida, trecho)
    print('PASS: busca, ordenacao, exclusao e duplicatas')

def testar_entradas_invalidas():
    entradas = ['-1','inválido','4','1',
                'N'*90,'Alice','','A','31','2','2024','29','2','2024',
                'Rua','Teste','1','65000000','Centro','Sao Luis',
                'Maranhao','MA','Brasil','55','15','98','999999999',
                'invalido','a@example.org','3','0']
    saida = rodar(entradas)
    contar(saida,'Informe um inteiro entre 0 e 4.',2)
    contar(saida,'Agenda vazia.')
    contar(saida,'Entrada muito longa; tente novamente.',2)
    contar(saida,'Data inválida;')
    contar(saida,'E-mail inválido;')
    contar(saida,'Contato adicionado. Total: 1')
    print('PASS: entradas invalidas e recuperacao')

def testar_eof():
    contar(rodar(['1','Alice']),'Agenda encerrada.')
    print('PASS: EOF sem cadastro parcial')

if __name__ == '__main__':
    testar_cadastro_busca_exclusao()
    testar_entradas_invalidas()
    testar_eof()
