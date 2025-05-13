#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

using namespace std;
using namespace std::chrono;

// Alias para matriz como vector<vector<double>> para facilitar
using Matrix = vector<vector<double>>;

// Função para gerar uma matriz com valores aleatórios entre 0 e 1
Matrix generateRandomMatrix(int rows, int cols) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    Matrix matrix(rows, vector<double>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}

// Multiplicação otimizada de matrizes (ordem dos loops ajustada para melhor cache locality)
Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    int m = A.size();
    int n = A[0].size();
    int p = B[0].size();
    
    Matrix result(m, vector<double>(p, 0.0));
    
    for (int i = 0; i < m; ++i) {
        for (int k = 0; k < n; ++k) {
            double temp = A[i][k];
            for (int j = 0; j < p; ++j) {
                result[i][j] += temp * B[k][j];
            }
        }
    }
    return result;
}

// Função para calcular a matriz inversa usando eliminação de Gauss-Jordan
Matrix inverseMatrix(Matrix A) {
    int n = A.size();
    
    // Criar matriz identidade
    Matrix inv(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        inv[i][i] = 1.0;
    }
    
    // Eliminação de Gauss-Jordan
    for (int col = 0; col < n; ++col) {
        // Pivotamento parcial: encontrar a linha com maior elemento na coluna atual
        int max_row = col;
        for (int row = col + 1; row < n; ++row) {
            if (abs(A[row][col]) > abs(A[max_row][col])) {
                max_row = row;
            }
        }
        
        // Trocar linhas se necessário
        if (max_row != col) {
            swap(A[col], A[max_row]);
            swap(inv[col], inv[max_row]);
        }
        
        // Verificar se a matriz é singular
        if (abs(A[col][col]) < 1e-10) {
            throw runtime_error("Matrix is singular or nearly singular");
        }
        
        // Normalizar a linha atual
        double pivot = A[col][col];
        for (int j = 0; j < n; ++j) {
            A[col][j] /= pivot;
            inv[col][j] /= pivot;
        }
        
        // Eliminar outras linhas
        for (int i = 0; i < n; ++i) {
            if (i != col && abs(A[i][col]) > 1e-10) {
                double factor = A[i][col];
                for (int j = 0; j < n; ++j) {
                    A[i][j] -= A[col][j] * factor;
                    inv[i][j] -= inv[col][j] * factor;
                }
            }
        }
    }
    
    return inv;
}

int main() {
    const int SIZE = 1000;
    
    cout << "Gerando matrizes aleatorias " << SIZE << "x" << SIZE << "..." << endl;
    auto start = high_resolution_clock::now();
    
    Matrix A = generateRandomMatrix(SIZE, SIZE);
    Matrix B = generateRandomMatrix(SIZE, SIZE);
    
    auto gen_end = high_resolution_clock::now();
    cout << "Tempo para gerar matrizes: " 
         << duration_cast<milliseconds>(gen_end - start).count() / 1000.0 
         << " segundos" << endl;
    
    cout << "Multiplicando matrizes..." << endl;
    Matrix C = multiplyMatrices(A, B);
    
    auto mult_end = high_resolution_clock::now();
    cout << "Tempo para multiplicar matrizes: " 
         << duration_cast<milliseconds>(mult_end - gen_end).count() / 1000.0 
         << " segundos" << endl;
    
    cout << "Calculando matriz inversa..." << endl;
    try {
        Matrix invC = inverseMatrix(C);
        
        auto inv_end = high_resolution_clock::now();
        cout << "Tempo para calcular inversa: " 
             << duration_cast<milliseconds>(inv_end - mult_end).count() / 1000.0 
             << " segundos" << endl;
        
        // Verificação rápida (opcional)
        cout << "\nVerificando inversa (elemento [0][0]): " << invC[0][0] << endl;
        
    } catch (const exception& e) {
        cerr << "Erro ao calcular matriz inversa: " << e.what() << endl;
    }
    
    auto total_end = high_resolution_clock::now();
    cout << "\nTempo total de execucao: " 
         << duration_cast<milliseconds>(total_end - start).count() / 1000.0 
         << " segundos" << endl;
    
    return 0;
}