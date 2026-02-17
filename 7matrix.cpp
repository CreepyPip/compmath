#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int n = 5;

int main() {
    double A[n][n] = {
        {2, 1, 2, 3, 9},
        {2, 5, 3, 5, 4},
        {2, 1, 5, 5, 7},
        {4, 8, 3, 7, 7},
        {1, 7, 5, 7, 5}
    };

    double B[n][2*n];
    double p;
    double f;

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            B[i][j] = A[i][j];
        }
        for (int j = n; j < 2*n; ++j) 
        {
            B[i][j] = (j - n == i) ? 1.0 : 0.0;
        }
    }

    for (int k = 0; k < n; ++k) 
    {
        if (abs(B[k][k]) < 1e-10) 
        {
            for (int i = k+1; i < n; ++i) 
            {
                if (abs(B[i][k]) > 1e-10) 
                {
                    for (int j = 0; j < 2*n; ++j) 
                    {
                        B[k][j] += B[i][j];
                    }
                    break;
                }
            }
        }

        p = B[k][k];
        for (int j = 0; j < 2*n; ++j) 
        {
            B[k][j] /= p;
        }

        for (int i = 0; i < n; ++i) 
        {
            if (i != k) {
                f = B[i][k];
                for (int j = 0; j < 2*n; ++j) 
                {
                    B[i][j] -= f * B[k][j];
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) 
    {
        for (int j = n; j < 2*n; ++j) 
        {
            cout << format("{:.0f}", B[i][j])<< " ";
        }
        cout << endl;
    }

}