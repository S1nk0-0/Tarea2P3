#include <vector>
#include <string>
#include "core_numeric.h"
// Clase Coordenada2D: soporta suma y comparación por magnitud
struct Coordenada2D {
    double x, y;
    // Necesario para Addable
    Coordenada2D operator+(const Coordenada2D& otro) const {
        return {x + otro.x, y + otro.y};
    }
    // Necesario para Comparable
    bool operator>(const Coordenada2D& otro) const {
        return (x*x + y*y) > (otro.x*otro.x + otro.y*otro.y);
    }
};
// Clase Vector3D: soporta suma, división por size_t y comparación
struct Vector3D {
    double x, y, z;
    // Suma (Addable)
    Vector3D operator+(const Vector3D& otro) const {
        return {x + otro.x, y + otro.y, z + otro.z};
    }
    // RESTA (NECESARIA para variance)
    Vector3D operator-(const Vector3D& otro) const {
        return {
            x - otro.x,
            y - otro.y,
            z - otro.z
        };
    }
    // Multiplicación (para diferencia * diferencia)
    Vector3D operator*(const Vector3D& otro) const {
        return {
            x * otro.x,
            y * otro.y,
            z * otro.z
        };
    }
    // División (para mean y variance)
    Vector3D operator/(std::size_t n) const {
        return {
            x / n,
            y / n,
            z / n
        };
    }
    // Comparación (para max)
    bool operator>(const Vector3D& otro) const {
        return (x*x + y*y + z*z) >
               (otro.x*otro.x +
                otro.y*otro.y +
                otro.z*otro.z);
    }
};
int main() {
    // --- Tipos primitivos ---
    std::vector<int> vi{1, 2, 3, 4};
    auto si  = core_numeric::sum(vi);          //  int cumple Addable
    auto mi  = core_numeric::mean(vi);         //  int cumple Addable + Divisible
    auto vi2 = core_numeric::variance(vi);     //  reutiliza mean
    auto mxi = core_numeric::max(vi);          //  int cumple Comparable

    auto ri = core_numeric::transform_reduce(vi, [](int x){ return x * x; });
    // la lambda retorna int, que cumple Addable

    std::vector<double> vd{1.0, 2.5, 3.7};
    auto sd  = core_numeric::sum(vd);          //double cumple Addable
    auto md  = core_numeric::mean(vd);         //  double cumple Addable + Divisible
    auto vd2 = core_numeric::variance(vd);
    auto mxd = core_numeric::max(vd);          // double cumple Comparable

    // Variadic con tipos primitivos
    auto sv  = core_numeric::sum_variadic(1, 2, 3);
    auto mv  = core_numeric::mean_variadic(1, 2, 3);
    auto vv  = core_numeric::variance_variadic(1, 2, 3);
    auto mxv = core_numeric::max_variadic(1, 5, 2);

    //Clases propias

    // Coordenada2D con sum y max (Addable + Comparable)
    std::vector<Coordenada2D> coords{{1.0, 0.0}, {0.0, 3.0}, {2.0, 2.0}};
    auto sc  = core_numeric::sum(coords);      // Coordenada2D cumple Addable
    auto mxc = core_numeric::max(coords);      // Coordenada2D cumple Comparable

    // Vector3D con sum, mean, variance, max (todos los concepts)
    std::vector<Vector3D> vecs{{1,0,0}, {0,2,0}, {0,0,3}};
    auto sv3  = core_numeric::sum(vecs);       //  Vector3D cumple Addable
    auto mv3  = core_numeric::mean(vecs);      //  Vector3D cumple Addable + Divisible
    auto vv3  = core_numeric::variance(vecs);  //
    auto mxv3 = core_numeric::max(vecs);       //  Vector3D cumple Comparable

    // CASOS QUE NO DEBEN COMPILAR
    // (descomenta cada bloque para verificar el error)

    // 1err caso string no cumple el concept Addable (same_as<T>)
    // std::vector<std::string> words{"hola", "mundo"};
    // auto ss = core_numeric::sum(words);
    // --- string::operator+ retorna string, pero same_as<string> falla
    // porque el resultado de "a"+"b" no satisface { a+b } -> same_as<string>
    // en el contexto del concept (no hay operator+ entre dos const string& que retorne string con same_as)

    // 2do cas string no cumple Divisible
    // std::vector<std::string> words{"hola", "mundo"};
    // auto ms = core_numeric::mean(words);
    // --- std::string no tiene operator/(size_t), falla concept Divisible

    // 3er caso string no cumple Comparable (no tiene operator> que retorne bool)
    // std::vector<std::string> words{"hola", "mundo"};
    // auto mxs = core_numeric::max(words);
    // ---- aunque string tiene operator>, el concept Comparable está pensado
    // para tipos numéricos. Este caso falla el concept Addable en variance.

    // 4to caso int no es Iterable
    // int x = 5;
    // auto si2 = core_numeric::sum(x);
    // ---- int no tiene std::begin/std::end, falla concept Iterable

    // 5to caso Coordenada2D no cumple Divisible (no tiene operator/)
    // auto mc = core_numeric::mean(coords);
    //----Coordenada2D no tiene operator/(size_t), falla concept Divisible

    // 6to caso variadic con tipos mezclados incompatibles
    // auto bad = core_numeric::sum_variadic(1, 2.5, 3);
    // ----1 y 3 son int, 2.5 es double — no todos cumplen Addable<T>
    // con el mismo T (el pack no puede deducir un tipo común)

    return 0;
}