#include "gauss.cpp"
#include "analyze.cpp"
#include <random>
#include <fstream> 
#include <chrono>
#include <iostream>
#include <cstdlib>

const float MIN_NUMBER = -1000.0f;
const float MAX_NUMBER = 1000.0f;

void randomMatrix(std::vector<std::vector<float>>& A, std::vector<float>& b, int n){
    std::random_device rd;
    std::mt19937 gen(rd() ^ static_cast<unsigned>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()
    ));
    
    std::uniform_real_distribution<float> distrib(MIN_NUMBER, MAX_NUMBER);
    
    for (int i = 0; i < n; i++) {
        std::vector<float> row;
        for (int j = 0; j < n; j++){
            row.push_back(distrib(gen));
        }
        A.push_back(row);
    }

    for (int j = 0; j < n; j++){
        b.push_back(distrib(gen));
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <matrix_size>\n";
        return 1;
    }

    int n = std::atoi(argv[1]);
    if (n <= 0) {
        std::cerr << "Matrix size must be a positive integer.\n";
        return 1;
    }

    std::ofstream outFile("output.txt");

    std::vector<std::vector<float>> A;
    std::vector<float> b;
    std::vector<float> X(n);

    randomMatrix(A, b, n);

    Eigen::MatrixXf eigenA(n, n);
    Eigen::VectorXf eigenB(n);
    Eigen::VectorXf eigenX(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            eigenA(i, j) = A[i][j];
            outFile << A[i][j] << " ";
        }
        eigenB(i) = b[i];
        outFile << " | " << b[i] << "\n";
    }

    int result = gauss(A, b, X, n);
    Eigen::VectorXf results_real;
    if (result == 0) {
        results_real = solveLinearSystem(eigenA, eigenB);
        std::cout << "Result: " << std::endl;
        for (int i = 0; i < X.size(); i++) {
            std::cout << X[i] << " | " << results_real[i] << std::endl;
            eigenX(i) = X[i];
        }
        std::cout << std::endl;
    } else {
        std::cout << "Incorrect input. Code: " << result << std::endl;
    }

    Eigen::VectorXf raz = eigenX - results_real;
    std::cout << "Diff norm: " << raz.norm() << std::endl;
    std::cout << "Residual: " << computeRelativeResidual(eigenA, eigenB, eigenX) << std::endl;
    std::cout << "Cond: " << computeConditionNumber(eigenA) << std::endl;

    outFile.close();
    return 0;
}
