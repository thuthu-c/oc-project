# OC-Project

## 1. Descrição do Trabalho

Implementar um modelo de processador (Parte de Controle/Parte Operativa) "MIPS-like" com o seguinte conjunto de instruções:

- AND —> operação booleana AND
- OR —> operação booleana OR
- XOR —> operação booleana XOR
- NOT —> operação booleana NOT
- CMP —> comparação
- ADD —> soma
- SUB —> subtração
- LD —> leitura em memória
- ST —> armazenamento em memória
- J —> salto incondicional
- JN —> salto condicional; salta se (N)egativo
- JZ —> salto condicional; salta se (Z)ero

## 2. Decisões de Projeto

2.1. Três modos de endereçamento de operandos (registrador, memória e imediato)

## 3. O Trabalho Consiste de

3.1. Implementação do modelo da arquitetura em linguagem para descrição de hardware (SystemC)
3.2. Resultados de simulações da execução de instruções de pelo menos 3 algoritmos na arquitetura
3.3. Análises de desempenho (ciclos de relógio necessários à execução das instruções) em função dos comportamentos do pipeline. Entende-se por comportamentos do pipeline, os tratamentos implementados para as dependências de dados e de controle

## 4. Apresentação

Apresentação dias 30/04 e 02/05 em sala de aula, exemplificando o funcionando do modelo de processador implementado. A apresentação deve mostrar:

4.1. Resultados de simulação (telas ou demonstração)

## 5. Entrega

Entrega dia 30/04/24 via tarefa SIGAA.

O trabalho pode ser feito individualmente ou em duplas.

## Metodologia de Projeto

1. **Parte Operativa**: Implementar os componentes individualmente e testá-los individualmente. (ULA, Banco de Registradores, Memória de Dados, Memória de Instruções, Somador, PC, buffers)
2. **Parte de Controle**: Implementar o Controle através de Máquina de Estados e testar individualmente
3. **Integração**: Integrar a Parte Operativa com a Parte de Controle
