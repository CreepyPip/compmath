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


    for (int k = 0; k < n; ++k)
    {
        b = A[np][np];
        
        for (int i = np; i < n; ++i)
        {
            for (int j = np; j <= n; ++j)
            {
                if (j == np && i == np)
                {
                    A[i][j] = A[i][j] / b;
                } 
                
                else if (j != np && i == np)
                {
                    A[i][j] = A[i][j] / b;    
                } 
                
                else if (j == np && i != np)
                {
                    s = A[i][j] / A[np][np];
                    A[i][j] = 0;
                }
                
                if (j != np && i != np)
                {
                    A[i][j] = A[i][j] - A[np][j] * s;
                } 
            }
        }
        np++;
    }

    np = n;
    
    for (int k = n-1; k > 0; --k)
    {
        np = np - 1;
        
        for (int i = np-1; i >= 0; i = i-1)
        {
            s = A[i][np];
            for (int j = np; j <= n; j++)
            {
                if (j == np) 
                {
                    A[i][j] = 0;
                }
                else
                {
                    A[i][j] = A[i][j] - A[np][j] * s;
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
        cout << format("x[{}", i) << "]= ";
        cout << format("{:.3f}", A[i][n]) << "; ";
    }

    cout << endl << format("Проверка:") << endl;
    cout << format("-7.45x0 + 0.52x1 + 4.61x2 + 2.11x3 - 9.67x4 = ") << -7.45* A[0][n]+ 0.52 *A[1][n]+ 4.61*A[2][n]+ 2.11 *A[3][n] -9.67 *A[4][n];

}