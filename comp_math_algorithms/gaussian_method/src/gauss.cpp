#include <iostream>
#include <vector>
#include <cmath> 
#define N_MAX 1000000

int gauss(std::vector<std::vector<float>>& a, std::vector<float>& b, std::vector<float>& X, int n){
    if (n < 2)
        return 2;
    else if (n > N_MAX)
        return 3;

    for (int k = 0; k < n; k++){
        float max_koef = 0;
        int max_row = -1;
        for (int j = k; j < n; j++){
            if (fabs(a[j][k]) > fabs(max_koef)) {
                max_koef = a[j][k];
                max_row = j;
            }
        }

        if (max_row == -1)
            return 1;

        if (max_row != k) {
            std::swap(a[k], a[max_row]);
            std::swap(b[k], b[max_row]);
        }

        for (int i = k + 1; i < n; i++){
            float koef_i = a[i][k];
            for (int j = 0; j < n; j++){
                a[i][j] = a[i][j] - a[k][j] * (koef_i / max_koef);
            }
            b[i] = b[i] - b[k] * (koef_i / max_koef);
        }
    }
    X[n - 1] = b[n - 1] / a[n - 1][n - 1];
    for (int k = n - 2; k >= 0; k--){
        float sum = b[k];
        for (int i = n - 1; i > k; i--){
            sum += (-1) * a[k][i] * X[i];
        }
        X[k] = sum / a[k][k];
    }
    return 0;
}