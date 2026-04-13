#ifndef TAREA2_CORE_NUMERIC_H
#define TAREA2_CORE_NUMERIC_H

#include <concepts>
#include <iterator>
using namespace std;

//



// Definicion de conceptos

template < typename C >
concept Iterable = requires ( C c ) {
    begin (c) ;
    end (c) ;
};

template < typename T >
concept Addable = requires ( T a , T b ) {
    {a + b} -> same_as <T >;
};

template < typename T >
concept Divisible = requires ( T a ,size_t n ) {
    {a/n} -> same_as <T >;
};

// TAREA: Crear uno adicional y aplicarlo
template < typename T >
concept Comparable = requires ( T a ,T n ){
    {a > n} -> same_as<bool>; // devuelve un bool
};


// Algoritmos

template <Iterable C>
requires Addable <typename C :: value_type>
auto sum (const C& container)
{
    using T = C :: value_type ;
    T result {}; // Para tipos numericos (int, double, float)
    // Se inicializa en 0.
    // Para clases se llama al constructor por defecto

    for ( const auto & value : container )
        result = result + value ;
    return result ;
}


template <Iterable C>
requires Addable<typename C :: value_type> and Divisible <typename C :: value_type>
auto mean(const C& container) {
    using T = C::value_type;
    T total = sum(container);

    double cuenta = 0.0; // double para no perder decimales
    for (const auto & value : container) cuenta++;

    if constexpr (is_integral_v<T>) {
        return static_cast<double>(total) / cuenta; // castea int a double
    } else {
        // si ya es float, dividimos normalmente
        return total / cuenta;
    }
}

template <Iterable C>
requires Addable<typename C::value_type> && Divisible<typename C::value_type>
auto variance(const C& container) {
    auto promedio = mean(container);

    decltype(promedio) suma_diferencias = 0; // decltype declara el tipo de promedio
    size_t cuenta = 0;

    // calculamos la varianza
    for (const auto& valor : container) { // entramos en el container
        auto diferencia = static_cast<decltype(promedio)> (valor) - promedio;
        // declaramos el type de promedio y lo casteamos en la resta
        suma_diferencias += diferencia * diferencia;
        cuenta++;
    }

    // dividimos entre la cantidad total para obtener la varianza
    return suma_diferencias / cuenta;
}

template <Iterable C>
requires Comparable<typename C::value_type> // necesitamos que se pueda comparar
auto max(const C& container) {

    auto max = *std::begin(container); // hacemos que el max sea el primero

    for (const auto& valor : container) {
        if (valor > max) {
            max = valor; // si valor es mayor, se le asigna a max
        }
    }

    return max;
}

template <Iterable C, typename F>
auto transform_reduce(const C& container, F funcion_transformadora) {

    auto suma_total; // no se como declararlo helppp
    // Recorremos el contenedor
    for (const auto& valor : container) {
        // Aplicamos la función al valor y lo sumamos al total
        suma_total = suma_total + funcion_transformadora(valor);
    }

    return suma_total;
}

#endif //TAREA2_CORE_NUMERIC_H

