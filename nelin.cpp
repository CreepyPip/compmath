#include <iostream>
#include <cmath>

using namespace std;

double f1(double x) {
    return 8*x + pow(5, x) + 8;
}

double f1_d(double x) {
    return 8 + pow(5, x) * log(5);
}

double f1_d2(double x) {
    return pow(5, x) * log(5) * log(5);
}

double f2(double x) {
    return 5*x*x*x + 2*x*x - 4;
}

double f2_d(double x) {
    return 15*x*x + 4*x;
}

double f2_d2(double x) {
    return 30*x + 4;
}

const double e = 0.00000001;

int main() {
    int k;
    
    double a = -1.5, b = 0;
    
    k = 0;
    double c;
    
    while ((b - a) / 2.0 > e) {
        c = (a + b) / 2.0;
        k++;
        
        if (f1(c) == 0) break;
        
        if (f1(a) * f1(c) < 0) {
            b = c;
        } else {
            a = c;
        }
    }
    
    cout << "x1a) " << (a + b) / 2.0 << " Итерации " << k << endl;
    
    k = 0;
    double d, z;
    
    while (true) {
        c = (a * f1(b) - b * f1(a)) / (f1(b) - f1(a));
        
        if (f1(a) * f1_d2(a) >= 0) {
            z = a;
        } else {
            z = b;
        }
        d = z - f1(z) / f1_d(z);
        
        k++;
        
        if (c > d) {
            swap(c, d);
        }
        
        if (d - c < 2 * e) break;
        
        a = c;
        b = d;
    }
    
    cout << "x2a) " << (c + d) / 2.0 << " Итерации " << k << endl;
    
    a = 0; 
    b = 1;


    k = 0;
    
    while ((b - a) / 2.0 > e) {
        c = (a + b) / 2.0;
        k++;
        
        if (f2(c) == 0) break;
        
        if (f2(a) * f2(c) < 0) {
            b = c;
        } else {
            a = c;
        }
    }
    
    cout << "x1b) " << (a + b) / 2.0 << " Итерации " << k << endl;


    k = 0;
    
    while (true) {
        c = (a * f2(b) - b * f2(a)) / (f2(b) - f2(a));
        
        if (f2(a) * f2_d2(a) >= 0) {
            z = a;
        } else {
            z = b;
        }
        d = z - f2(z) / f2_d(z);
        
        k++;
        
        if (c > d) {
            swap(c, d);
        }
        
        if (d - c < 2 * e) break;
        
        a = c;
        b = d;
    }
    
    cout << "x2b) " << (c + d) / 2.0 << " Итерации " << k << endl;
}