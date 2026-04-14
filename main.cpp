#include <iostream>
#include <vector>

// Incluimos nuestra librería
#include "core_numeric.h"

using namespace std;

int main() {
    auto lang = "C++";

    cout << "Hello and welcome to "
         << lang << "!\n";

    for (int i = 1; i <= 5; i++) {

        cout << "i = "
             << i << endl;
    }
    // Creamos un vector de prueba
    vector<int> v{1,2,3,4};

    cout << "\n=== Pruebas con contenedor ===\n";

    // Punto 1 + 2
    auto s = sum(v);
    cout << "Sum: " << s << endl;

    // Punto 2
    auto m = mean(v);
    cout << "Mean: " << m << endl;

    // Punto 3
    auto var = variance(v);
    cout << "Variance: "<< var << endl;

    // Punto 4
    auto mx = ::max(v);
    cout << "Max: "<< mx << endl;

    // Punto 5
    auto r = transform_reduce(v,[](int x){return x * x;});

    cout << "Transform Reduce: "<< r << endl;

    cout << "\n=== Pruebas variadic ===\n";

    auto s2 =sum_variadic(1,2,3,4);

    cout << "Sum Variadic: "<< s2 << endl;

    auto m2 =mean_variadic(1,2,3,4);

    cout << "Mean Variadic: "<< m2 << endl;

    auto v2 =variance_variadic(1,2,3,4);

    cout << "Variance Variadic: "<< v2 << endl;

    auto mx2 = ::max_variadic(1,2,7,4);

    cout << "Max Variadic: "<< mx2 << endl;
    return 0;
}