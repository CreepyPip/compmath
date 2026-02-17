#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    const int n = 5;
    
    double A[n][n+1] = {
        {2, 2, 5, 1, 8, 18},
        {1, 1, 9, 5, 4, 20},
        {7, 3, 8, 7, 8, 33},
        {3, 4, 8, 6, 7, 28},
        {5, 8, 1, 5, 8, 27}
    };
    
    double L[n][n] = {0};
    double U[n][n] = {0};
    double X[n] = {0};
    double Y[n] = {0};
  
    double AA[n][n+1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            AA[i][j] = A[i][j];
        }
    }
    
    for (int k = 0; k < n; k++) {
        int R = k;
        double V = fabs(AA[k][k]);
        for (int i = k + 1; i < n; i++) {
            if (fabs(AA[i][k]) > V) {
                V = fabs(AA[i][k]);
                R = i;
            }
        }
        
        if (R != k) {
            for (int j = k; j <= n; j++) {
                swap(AA[k][j], AA[R][j]);
            }
        }
        
        for (int j = k; j < n; j++) {
            double sum = 0;
            for (int m = 0; m < k; m++) {
                sum += L[k][m] * U[m][j];
            }
            U[k][j] = AA[k][j] - sum;
        }
        
        for (int i = k; i < n; i++) {
            if (i == k) {
                L[k][k] = 1.0;
            } else {
                double sum = 0;
                for (int m = 0; m < k; m++) {
                    sum += L[i][m] * U[m][k];
                }
                L[i][k] = (AA[i][k] - sum) / U[k][k];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * Y[j];
        }
        Y[i] = AA[i][n] - sum;
    }
    
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += U[i][j] * X[j];
        }
        X[i] = (Y[i] - sum) / U[i][i];
    }
    
    
    cout << "Решение системы:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "]= " << ("{:.3f}", X[i]) << endl;
    }
    
    return 0;
}