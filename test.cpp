#include <vector>
#include <string>
#include "core_numeric.h"

using namespace std;

int main() {
    vector<int> v{1,2,3};

    auto s = sum(v);
    auto m = mean(v);
    auto v1 = variance(v);
    auto mx = ::max(v);

    auto r =transform_reduce(v,[](int x){return x*x;});

    auto s2 =sum_variadic(1,2,3);

    auto m2 =mean_variadic(1,2,3);

    auto v2 =variance_variadic(1,2,3);

    auto mx2 =::max_variadic(1,5,2);

    vector<string> words{"hola","mundo"};

}