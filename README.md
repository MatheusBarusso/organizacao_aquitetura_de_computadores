<h1>Instruções para Compilação</h1>

<h2>Aplicação Single-Thread</h2>
g++ -O3 single_thread.cpp -o single_thread

<h2>Aplicação Multi-Thread</h2>
g++ -std=c++11 -fopenmp -O3 multi_thread.cpp -o multi_thread
