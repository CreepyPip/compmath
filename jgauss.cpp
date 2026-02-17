#include <iostream>

using namespace std;

int main() {
    int n = 5;
    int np = 0;
    double A[n][n+1] ={
    {-7.45, 0.52, 4.61, 2.11, -9.67, 0.44},
    {3.8, 0.67, 2.17, -4.31, -0.72, -9.54},
    {2.7, 8.82, 4.7, -9.1, -2.23, -8.89},
    {7.97, -7.44, 7.77, 9.12, -7.19, 5.69},
    {-1.08, 3.29, 4.08, -8.68, 9.43, -1.09}};

    double b = 0;
    double s = 0;
    double d = 0;
    double x[n-1];

    for (int k = 0; k < n; ++k)
    {
        for (int i = np; i < n; ++i)
        {
            for (int j = np; j <= n; ++j)
            {
                if (j == np && i == np)
                {
                    b = A[i][j];
                    A[i][j] = A[i][j] / b;
                } 
    
                else if (j != np && i == np)
                {
                    A[i][j] = A[i][j] / b;    
                } 
    
                else if (j == np && i != np)
                {
                    if (i > np) {
                        s = A[i][j] / A[np][np];
                        for (int col = np; col <= n; ++col) {
                            A[i][col] = A[i][col] - A[np][col] * s;
                        }
                    }
                    A[i][j] = 0;
                }
            }
        }
        
        for (int i = 0; i < np; ++i)
        {
            s = A[i][np];
            for (int j = np; j <= n; ++j)
            {
                A[i][j] = A[i][j] - A[np][j] * s;
            }
            A[i][np] = 0;
        }
        
        np++;
    }


    for (int i = 0; i < n; i++) 
    {
        d = A[i][i];
        if (d != 0) {
            for (int j = 0; j <= n; j++) {
                if (j == i) {
                    A[i][j] = 1;
                } else if (j == n) {
                    A[i][j] = A[i][j] / d;
                }
            }
        }
    }
    

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << format("{:.3f}", A[i][j]) << " ";
        }
        cout << endl;
    }
    
    for (int i = 0; i < n; ++i)
    {
        x[i] = A[i][n];
        cout << format("x[{}",i) << "]= ";
        cout << format("{:.3f}",x[i]) << "";
    }
}