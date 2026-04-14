#include <iostream>
#include <vector>
#include "core_numeric.h"

using namespace std;

int main() {
    auto lang = "C++";
    cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++)
        cout << "i = " << i << endl;

    // Vector de prueba con enteros
    vector<int> v{1, 2, 3, 4};

    cout << "\n=== Pruebas con contenedor (int) ===\n";

    auto s = core_numeric::sum(v);
    cout << "Sum: " << s << endl;                          // 10

    auto m = core_numeric::mean(v);
    cout << "Mean: " << m << endl;                         // 2.5

    auto var = core_numeric::variance(v);
    cout << "Variance: " << var << endl;                   // 1.25

    auto mx = core_numeric::max(v);
    cout << "Max: " << mx << endl;                         // 4

    auto r = core_numeric::transform_reduce(v, [](int x){ return x * x; });
    cout << "Transform Reduce (x^2): " << r << endl;      // 30

    // Vector de prueba con doubles
    vector<double> vd{1.0, 2.0, 3.0, 4.0};

    cout << "\n=== Pruebas con contenedor (double) ===\n";

    auto sd = core_numeric::sum(vd);
    cout << "Sum: " << sd << endl;                         // 10.0

    auto md = core_numeric::mean(vd);
    cout << "Mean: " << md << endl;                        // 2.5

    auto vard = core_numeric::variance(vd);
    cout << "Variance: " << vard << endl;                  // 1.25

    auto mxd = core_numeric::max(vd);
    cout << "Max: " << mxd << endl;                        // 4.0

    cout << "\n=== Pruebas variadic ===\n";

    auto s2 = core_numeric::sum_variadic(1, 2, 3, 4);
    cout << "Sum Variadic: " << s2 << endl;                // 10

    auto m2 = core_numeric::mean_variadic(1, 2, 3, 4);
    cout << "Mean Variadic: " << m2 << endl;               // 2.5

    auto v2 = core_numeric::variance_variadic(1, 2, 3, 4);
    cout << "Variance Variadic: " << v2 << endl;           // 1.25

    auto mx2 = core_numeric::max_variadic(1, 2, 7, 4);
    cout << "Max Variadic: " << mx2 << endl;               // 7

    return 0;
}