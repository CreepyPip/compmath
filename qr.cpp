#include <iostream>
#include <cmath>

using namespace std;

const int n = 5;

int main() {
    double A[n][n] = {
        {2, 6, 5, 5, 4},
        {4, 2, 4, 1, 6},
        {6, 2, 6, 4, 9},
        {7, 9, 5, 6, 7},
        {2, 5, 7, 5, 6}
    };
    
    double Q[n][n];
    double R[n][n];
    double B[n][n];
    
    for (int t = 0; t < 50; ++t) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                Q[i][j] = A[i][j];
                R[i][j] = 0;
            }
        }
        
        for (int j = 0; j < n; ++j) {
            double ss = 0;
            for (int i = 0; i < n; ++i) {
                ss += Q[i][j] * Q[i][j];
            }
            ss = sqrt(ss);
            
            R[j][j] = ss;
            
            for (int i = 0; i < n; ++i) {
                Q[i][j] = Q[i][j] / ss;
            }
            
            for (int k = j + 1; k < n; ++k) {
                double d = 0;
                for (int i = 0; i < n; ++i) {
                    d += Q[i][j] * Q[i][k];
                }
                R[j][k] = d;
                
                for (int i = 0; i < n; ++i) {
                    Q[i][k] = Q[i][k] - Q[i][j] * d;
                }
            }
        }
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                B[i][j] = 0;
                for (int k = 0; k < n; ++k) {
                    B[i][j] += R[i][k] * Q[k][j];
                }
            }
        }
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                A[i][j] = B[i][j];
            }
        }
    }
    
    for (int i = 0; i < n; ++i) {
        cout << A[i][i] << endl;
    }
    
}