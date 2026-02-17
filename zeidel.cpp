#include <iostream>
#include <cmath>

using namespace std;

int main() {
    const int n = 5;
    
    double A[n][n+1] = {
        {32, 4, 1, 4, 3, 54},
        {5, 29, 3, 3, 5, 83},
        {1, 5, 21, 1, 3, 79},
        {3, 3, 2, 38, 2, 93},
        {1, 2, 4, 4, 50, 75}
    };
    
    double X[n] = {0};
    double H[n] = {0};
    
    int it = 0;
    bool boo = false;
    
    while (!boo && it < 100) {
        it++;
        
        for (int i = 0; i < n; i++) {
            H[i] = X[i];
        }
        
        for (int i = 0; i < n; i++) {
            double sum = A[i][n];
            
            for (int j = 0; j < i; j++) {
                sum -= A[i][j] * X[j];
            }
            
            for (int j = i + 1; j < n; j++) {
                sum -= A[i][j] * H[j];
            }
            
            X[i] = sum / A[i][i];
        }
    
    cout << "Итераций: " << it << endl;
    for (int i = 0; i < n; i++) {
        cout << "x" << i << " = " << X[i] << endl;
    }
}}