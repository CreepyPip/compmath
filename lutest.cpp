#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

const double EPSILON = 0.0000001;

// Функция для получения количества строк матрицы
int getRowsCount(const vector<vector<double>>& matrix) {
    return matrix.size();
}

// Функция для получения количества столбцов матрицы
int getColumnsCount(const vector<vector<double>>& matrix) {
    if (matrix.empty()) return 0;
    return matrix[0].size();
}

// Функция для печати матрицы
void printMatrix(const vector<vector<double>>& matrix) {
    cout << fixed << setprecision(6);
    for (const auto& row : matrix) {
        for (double val : row) {
            cout << setw(12) << val << " ";
        }
        cout << endl;
    }
}

// Основная функция LU-разложения и решения СЛАУ
void luCalculate(vector<vector<double>>& myMatrix) {
    int n = getRowsCount(myMatrix);
    
    // Проверяем, что матрица квадратная и имеет вектор правой части
    if (n == 0 || getColumnsCount(myMatrix) != n + 1) {
        cerr << "Некорректные размеры матрицы!" << endl;
        return;
    }
    
    // Матрицы L и U
    vector<vector<double>> L(n, vector<double>(n, 0.0));
    vector<vector<double>> U(n, vector<double>(n, 0.0));
    
    // Векторы решений
    vector<double> X(n, 0.0);
    vector<double> Y(n, 0.0);
    
    // Инициализация диагонали U единицами
    for (int k = 0; k < n; k++) {
        U[k][k] = 1.0;
    }
    
    // Шаг 1: Разложение матрицы A на L*U
    
    // Первый столбец L
    for (int i = 0; i < n; i++) {
        L[i][0] = myMatrix[i][0];
    }
    
    // Первая строка U
    for (int j = 0; j < n; j++) {
        if (fabs(L[0][0]) < EPSILON) {
            cerr << "Деление на ноль! Матрица вырождена." << endl;
            return;
        }
        U[0][j] = myMatrix[0][j] / L[0][0];
    }
    
    cout << "Шаг 1: Начальная инициализация" << endl;
    
    // Основной цикл разложения
    for (int k = 1; k < n; k++) {
        // Вычисление столбца k матрицы L
        for (int i = k; i < n; i++) {
            double sum = 0.0;
            for (int m = 0; m < k; m++) {
                sum += L[i][m] * U[m][k];
            }
            L[i][k] = myMatrix[i][k] - sum;
        }
        
        // Вычисление строки k матрицы U
        for (int j = k + 1; j < n; j++) {
            double sum = 0.0;
            for (int m = 0; m < k; m++) {
                sum += L[k][m] * U[m][j];
            }
            
            if (fabs(L[k][k]) < EPSILON) {
                cerr << "Деление на ноль! Матрица вырождена." << endl;
                return;
            }
            U[k][j] = (myMatrix[k][j] - sum) / L[k][k];
        }
    }
    
    cout << "\nМатрица L:" << endl;
    printMatrix(L);
    cout << "\nМатрица U:" << endl;
    printMatrix(U);
    
    // Шаг 2: Решение LY = B
    
    cout << "\nШаг 2: Решение LY = B" << endl;
    
    // Правая часть уравнения (последний столбец расширенной матрицы)
    vector<double> B(n);
    for (int i = 0; i < n; i++) {
        B[i] = myMatrix[i][n]; // Последний столбец - вектор правой части
    }
    
    // Прямая подстановка для LY = B
    if (fabs(L[0][0]) < EPSILON) {
        cerr << "Деление на ноль! Матрица вырождена." << endl;
        return;
    }
    Y[0] = B[0] / L[0][0];
    
    for (int k = 1; k < n; k++) {
        double sum = 0.0;
        for (int m = 0; m < k; m++) {
            sum += L[k][m] * Y[m];
        }
        
        if (fabs(L[k][k]) < EPSILON) {
            cerr << "Деление на ноль! Матрица вырождена." << endl;
            return;
        }
        Y[k] = (B[k] - sum) / L[k][k];
    }
    
    cout << "\nВектор Y:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "y[" << i + 1 << "] = " << fixed << setprecision(6) << Y[i] << endl;
    }
    
    // Шаг 3: Решение UX = Y
    
    cout << "\nШаг 3: Решение UX = Y" << endl;
    
    // Обратная подстановка для UX = Y
    X[n - 1] = Y[n - 1]; // Так как U[n-1][n-1] = 1
    
    for (int k = n - 2; k >= 0; k--) {
        double sum = 0.0;
        for (int m = k + 1; m < n; m++) {
            sum += U[k][m] * X[m];
        }
        X[k] = Y[k] - sum;
    }
    
    cout << "\nВектор решений X:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i + 1 << "] = " << fixed << setprecision(6) << X[i] << endl;
    }
}

int main() {
    // Пример использования
    // Расширенная матрица системы: 3x3 матрица коэффициентов + столбец правой части
    vector<vector<double>> matrix = {
        {2.0,  1.0, -1.0,  8.0},   // 2x + y - z = 8
        {-3.0, -1.0, 2.0,  -11.0}, // -3x - y + 2z = -11
        {-2.0, 1.0,  2.0,  -3.0}   // -2x + y + 2z = -3
    };
    
    cout << "Исходная расширенная матрица:" << endl;
    printMatrix(matrix);
    cout << endl;
    
    luCalculate(matrix);
    
    return 0;
}