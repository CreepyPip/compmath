#include <iostream>
#include <cmath>

using namespace std;

const int n = 5;

int main() {
    double A[n][n] = {
        {9, 2, 5, 4, 3},
        {2, 7, 1, 4, 5},
        {5, 1, 7, 5, 2},
        {4, 4, 5, 6, 4},
        {3, 5, 2, 4, 7}
    };

    double L[n][n] = {0};

    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int k = 0; k < i; k++) {
            sum += L[i][k] * L[i][k];
        }
        L[i][i] = sqrt(A[i][i] - sum);

        for (int j = i + 1; j < n; j++) {
            sum = 0;
            for (int k = 0; k < i; k++) {
                sum += L[j][k] * L[i][k];
            }
            L[j][i] = (A[j][i] - sum) / L[i][i];
        }
    }

    double Y[n][n] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > i) {
                Y[i][j] = 0;
            } else if (j == i) {
                Y[i][j] = 1.0 / L[i][i];
            } else {
                double sum = 0;
                for (int m = j; m < i; m++) {
                    sum += L[i][m] * Y[m][j];
                }
                Y[i][j] = -sum / L[i][i];
            }
        }
    }

    double AI[n][n] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int m = 0; m < n; m++) {
                AI[i][j] += Y[m][i] * Y[m][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << format ("{:.3f}",AI[i][j]) << " ";
        }
        cout << endl;
    }

}