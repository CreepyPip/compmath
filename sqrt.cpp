#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    const int n = 5;    
    
    double A[n][n] = {
        {9, 2, 3, 4, 4},
        {2, 7, 3, 5, 3},
        {3, 3, 7, 3, 3},
        {4, 5, 3, 9, 4},
        {4, 3, 3, 4, 3}
    };
    double b[n] = {34, 38, 39, 45, 30};
    double L[n][n] = {0};
    double X[n] = {0};
    double Y[n] = {0};
    
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int k = 0; k < i; k++) {
            sum += L[i][k] * L[i][k];
        }
        
        
        L[i][i] = sqrt(fabs(A[i][i] - sum));
        
        
        for (int j = i + 1; j < n; j++) {
            sum = 0;
            for (int k = 0; k < i; k++) {
                sum += L[j][k] * L[i][k];
            }
            L[j][i] = (A[j][i] - sum) / L[i][i];
        }
    }
    
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * Y[j];
        }
        
        Y[i] = (b[i] - sum) / L[i][i];
    }
    
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += L[j][i] * X[j];
        }
        
        X[i] = (Y[i] - sum) / L[i][i];
    }
    
    cout << "Решение системы" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << ("{:.3f}",X[i]) << endl;
    }
}