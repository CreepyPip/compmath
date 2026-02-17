#include <iostream>
#include <cmath>

using namespace std;

int main() {
    const int n = 5;

	double A[n][n+1] = {
        {9, 9, 0, 0, 0, 18},
		{7, 3, 6, 0, 0, 16},
		{0, 3, 4, 5, 0, 12},
		{0, 0, 2, 6, 5, 13},
		{0, 0, 0, 6, 4, 10}
    };

    double c[n-1];
    double r[n-1];
    double l[n-1];
    double f[n];
    double x[n];
    double p[n];
    double q[n];

    for (int i = 0; i < n - 1; ++i)
    {
        c[i] = A[i][i];
    	r[i] = A[i][i+1];
    	l[i] = A[i+1][i];
    }

    for (int i = 0; i < n - 1; ++i)
    {
    	f[i] = A[i][n];
    }

    p[0] = f[0]/c[0];
    q[0] = r[0]/c[0];

    for (int i = 1; i < n; ++i)
    {
        p[i] = (f[i]-l[i]*p[i-1])/(c[i]-l[i]*p[i-1]);
        q[i] = (r[i])/(c[i]-l[i]*p[i-1]);
    }

    for (int i = n; i >= 0; --i)
    {
        if (i == n)
        {
            x[i] == p[i];
        }
        else
        {
            x[i] == p[i]-q[i]*x[i+1];
        }
    }

    for (int i = 0; i < n; ++i)
    {
        cout << format("{:.2f}", q[i]) << " ";
    }

}