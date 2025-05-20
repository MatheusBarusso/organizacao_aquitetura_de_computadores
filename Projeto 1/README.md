# Projeto de Raspberry Pi 3 para disciplina de Organização e Arquitetura de Computadores

Este projeto busca analisar as diferenças de performance e tempo de execução para utilização de um Thread e múltiplos Threads. O algoritmo desenvolvido possui as seguintes funções:

  - Gera duas matrizes 1000x1000 com números aleatórios
  - Multiplica essas duas matrizes
  - Calcula a inversa da matriz resultante
  - Mede a somatória de tempo gasto em cada uma das operações acima

## Instruções para Compilação:
### Aplicação Single-Thread

```bash
g++ -O3 single_thread.cpp -o single_thread
```
###Aplicação Multi-Thread
```bash
g++ -std=c++11 -fopenmp -O3 multi_thread.cpp -o multi_thread
```
