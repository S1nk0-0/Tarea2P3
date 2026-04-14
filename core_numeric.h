#ifndef TAREA2_CORE_NUMERIC_H
#define TAREA2_CORE_NUMERIC_H


#include <bits/stdc++.h>
#include <concepts>
#include <iterator>
#include <type_traits>
#include <utility>
using namespace std;

// Punto 1)
// Definicion de conceptos
// Iterable permite recorrer un contenedor
// Addable permite sumar elementos
// Divisible permite dividir valores
// Comparable concept propio creado para comparar valores

template < typename C >
concept Iterable = requires ( C c ) {
    begin (c) ;
    end (c) ;
};

template < typename T >
concept Addable = requires ( T a , T b ) {
    {a + b} -> std::same_as <T >;
};

template < typename T >
concept Divisible = requires ( T a ,size_t n ) {
    {a/n} -> std::same_as <T >;
};

// TAREA: Crear uno adicional y aplicarlo
template < typename T >
concept Comparable = requires ( T a ,T n ){
    {a > n} -> std::same_as<bool>; // devuelve un bool
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


// Punto 2)
template <Iterable C>
requires Addable<typename C :: value_type> and Divisible <typename C :: value_type>
auto mean(const C& container) {
    using T = C::value_type;
    T total = sum(container);

    double cuenta = 0.0; // double para no perder decimales
    for (const auto & value : container) cuenta++;
    // También se usa if constexpr que es parte del Punto 7
    if constexpr (is_integral_v<T>) {
        return static_cast<double>(total) / cuenta; // castea int a double
    } else {
        // si ya es float, dividimos normalmente
        return total / cuenta;
    }

}


// Punto 3)
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


// Punto 4)
template <Iterable C>
requires Comparable<typename C::value_type> // necesitamos que se pueda comparar
auto max(const C& container) {

    auto maximo = *std::begin(container); // hacemos que el max sea el primero

    for (const auto& valor : container) {
        if (valor > maximo) {
            maximo = valor;
        }// si valor es mayor, se le asigna a max

    }

    return maximo;
}

// Punto 5)
//Lo que hace esto es Aplica una funcion y luego suma los resultados
template <Iterable C, typename F>
requires Addable<decltype(std::declval<F>()(
           std::declval<typename C::value_type>()))>
auto transform_reduce(const C& container, F funcion_transformadora) {

    using T = decltype(funcion_transformadora(
                      *std::begin(container)));

    T suma_total{}; // se inicializa en 0

    for (const auto& valor : container) {
        suma_total = suma_total +
                     funcion_transformadora(valor);
    }
    // Esta función aplica una función a cada elemento
    // y luego suma todos los resultados.
    return suma_total;
}

//Punto 6)
template <Addable T, Addable... Args>
auto sum_variadic(T first, Args... args) {
    return (first + ... + args);
}
// sum_variadic permite sumar múltiples valores
// usando templates variadic y expresiones de plegado


template <Addable T, Addable... Args>
auto mean_variadic(T first, Args... args) {
    auto suma = sum_variadic(first, args...);
    // contamos cuantos valors hay
    constexpr size_t cantidad =
            1 + sizeof...(args);
    // Punto 7: uso del if constexpr
    if constexpr (is_integral_v<decltype(suma)>) {

        return static_cast<double>(suma)
               / cantidad;
    } else {
        return suma / cantidad;

    }
}
// mean_variadic calcula el promedio
// usando sum_variadic.
// sizeof...(args) cuenta cuántos valores
// adicionales hay.
// Se usa if constexpr para convertir a doubles cuando los vlores son enteros



template <Addable T, Addable... Args>
auto variance_variadic(T first, Args... args) {

    auto promedio =
        mean_variadic(first, args...);

    auto suma_diferencias = 0.0;

    constexpr size_t cantidad =
            1 + sizeof...(args);

    // Creamos arreglo temporal
    auto valores =
    {static_cast<double>(first),
     static_cast<double>(args)...};

    for (auto valor : valores) {

        auto diferencia =
                valor - promedio;

        suma_diferencias +=
                diferencia * diferencia;
    }

    return suma_diferencias /
           cantidad;
}
// variance_variadic calcula la varianza
// usando mean_variadic


template <Comparable T,
          Comparable... Args>
auto max_variadic(T first, Args... args) {

    T maximo = first;

    auto valores = {args...};

    for (auto valor : valores) {

        if (valor > maximo) {
            maximo = valor;
        }
    }

    return maximo;
}
// max_variadic encuentra el máximo
// entre múltiples valores
#endif //TAREA2_CORE_NUMERIC_H

