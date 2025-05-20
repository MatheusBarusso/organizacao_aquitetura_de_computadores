<h1>Organização e Arquitetura de Computadores - UTFPRTD</h1>
<h2>Projeto de Raspberry Pi 3 para disciplina de Organização e Arquitetura de Computadores</h2>

Este projeto busca analisar as diferenças de performance e tempo de execução para utilização de um Thread e múltiplos Threads. O algoritmo desenvolvido possui as seguintes funções:
<ul>
  <li>Gera duas matrizes 1000x1000 com números aleatórios</li>
  <li>Multiplica essas duas matrizes</li>
  <li>Calcula a inversa da matriz resultante</li>
  <li>Mede a somatória de tempo gasto em cada uma das operações acima</li>
</ul>

<h2>Instruções para Compilação:</h2>
<h3>Aplicação Single-Thread</h3>
g++ -O3 single_thread.cpp -o single_thread

<h3>Aplicação Multi-Thread</h3>
g++ -std=c++11 -fopenmp -O3 multi_thread.cpp -o multi_thread
