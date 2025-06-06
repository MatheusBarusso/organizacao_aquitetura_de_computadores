#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <omp.h>

using namespace std;
using namespace std::chrono;
using Matrix = vector<vector<double>>;

const int SIZE = 1000;               
const int MAX_THREADS = 16;          
const double SINGULARITY_THRESHOLD = 1e-5; 


Matrix generateRandomMatrix(int rows, int cols) {
    random_device rd;
    vector<mt19937> gens(MAX_THREADS);
    for (auto& gen : gens) {
        gen.seed(rd());
    }
    uniform_real_distribution<> dis(0.0, 1.0);

    Matrix matrix(rows, vector<double>(cols));
    
    #pragma omp parallel for collapse(2) num_threads(MAX_THREADS)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int tid = omp_get_thread_num();
            matrix[i][j] = dis(gens[tid]);
        }
    }
    return matrix;
}


Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    int m = A.size();
    int n = A[0].size();
    int p = B[0].size();
    
    Matrix result(m, vector<double>(p, 0.0));
    
    #pragma omp parallel for num_threads(MAX_THREADS)
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

Matrix inverseMatrix(Matrix A) {
    int n = A.size();
    
    Matrix inv(n, vector<double>(n, 0.0));
    
    #pragma omp parallel for num_threads(MAX_THREADS)
    for (int i = 0; i < n; ++i) {
        inv[i][i] = 1.0;
    }
    
    
    for (int col = 0; col < n; ++col) {
        int max_row = col;
        double max_val = abs(A[col][col]);
        
        for (int row = col + 1; row < n; ++row) {
            if (abs(A[row][col]) > max_val) {
                max_val = abs(A[row][col]);
                max_row = row;
            }
        }
        
        if (max_row != col) {
            swap(A[col], A[max_row]);
            swap(inv[col], inv[max_row]);
        }
        
        if (abs(A[col][col]) < SINGULARITY_THRESHOLD) {
            throw runtime_error("Matrix is singular or nearly singular");
        }
        
        double pivot = A[col][col];
        #pragma omp parallel for num_threads(MAX_THREADS)
        for (int j = 0; j < n; ++j) {
            A[col][j] /= pivot;
            inv[col][j] /= pivot;
        }
        
        #pragma omp parallel for num_threads(MAX_THREADS)
        for (int i = 0; i < n; ++i) {
            if (i != col && abs(A[i][col]) > SINGULARITY_THRESHOLD) {
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
    omp_set_num_threads(MAX_THREADS);
    cout << "Configurado para Raspberry Pi com " << MAX_THREADS << " threads\n";
    cout << "Tamanho da matriz: " << SIZE << "x" << SIZE << "\n\n";
    
    cout << "Gerando matrizes aleatorias..." << endl;
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
        
        cout << "\nVerificacao (elemento [0][0]): " << invC[0][0] << endl;
        
    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << endl;
        cerr << "Recomendacao: Reduza o tamanho da matriz ou ajuste o limiar de singularidade" << endl;
    }
    
    auto total_end = high_resolution_clock::now();
    cout << "\nTempo total: " 
         << duration_cast<milliseconds>(total_end - start).count() / 1000.0 
         << " segundos" << endl;
    
    return 0;
}