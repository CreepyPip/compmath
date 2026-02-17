#include <iostream>
#include <iomanip>
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

    double L[n][n] = {0};
    double U[n][n] = {0};

    for (int i = 0; i < n; i++) {
        for (int k = 0; k <= i; k++) {
            double sum = 0;
            for (int j = 0; j < k; j++) {
                sum += L[i][j] * U[j][k];
            }
            L[i][k] = A[i][k] - sum;
        }

        for (int k = i; k < n; k++) {
            if (i == k) {
                U[i][i] = 1;
            } else {
                double sum = 0;
                for (int j = 0; j < i; j++) {
                    sum += L[i][j] * U[j][k];
                }
                U[i][k] = (A[i][k] - sum) / L[i][i];
            }
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

    double X[n][n] = {0};
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (j < i) {
                X[i][j] = 0;
            } else if (j == i) {
                X[i][j] = 1;
            } else {
                double sum = 0;
                for (int m = i + 1; m <= j; m++) {
                    sum += U[i][m] * X[m][j];
                }
                X[i][j] = -sum;
            }
        }
    }

    double AI[n][n] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int m = 0; m < n; m++) {
                AI[i][j] += X[i][m] * Y[m][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout <<format ("{:.0f}",AI[i][j])<< " ";
        }
        cout << endl;
    }

}