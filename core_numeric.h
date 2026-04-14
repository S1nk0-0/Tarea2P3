#ifndef TAREA2_CORE_NUMERIC_H
#define TAREA2_CORE_NUMERIC_H

#include <iterator>
#include <type_traits>
#include <utility>
#include <concepts>

namespace core_numeric {
template <typename C>
concept Iterable = requires(C c) {
    std::begin(c);
    std::end(c);
};

//Punto 1)
//se usa same_as<T> en lugar de convertible_to<T>
// según lo especificado en el enunciado de la tarea
template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};


    template <typename T>
    concept Divisible = requires (T a, std::size_t n) {
        { a / n } -> std::convertible_to<T>;
    };


    template <typename T>
    concept Multiplicable = requires (T a, T b) {
        { a * b } -> std::convertible_to<T>;
    };
//Comparable Verifica que el tipo soporte el operador > y retorne bool
template <typename T>
concept Comparable = requires(T a, T b) {
    { a > b } -> std::convertible_to<bool>;
};
//  sum Iterable + Addable sobre el tipo de elemento




template <Iterable C>
requires Addable<typename C::value_type>
auto sum(const C& container) {
    using T = typename C::value_type;
    T result{};
    for (const auto& value : container)
        result = result + value;
    return result;
}


// Punto 2) mean ----- Iterable + Addable + Divisible
// Reutiliza sum(). Usa if constexpr para manejar enteros vs flotantes.

template <Iterable C>
requires Addable<typename C::value_type> && Divisible<typename C::value_type>
auto mean(const C& container) {
    using T = typename C::value_type;
    auto total = sum(container);
    std::size_t cuenta = std::size(container);

    // Punto 7: if constexpr — diferencia comportamiento según tipo
    if constexpr (std::is_integral_v<T>) {
        return static_cast<double>(total) / static_cast<double>(cuenta);
    } else {
        return total / cuenta;
    }
}


// Punto 3) variance
// Requiere: Iterable + Addable + Divisible
// Reutiliza mean()
template <Iterable C>
requires Addable<typename C::value_type> &&Divisible<typename C::value_type> &&Multiplicable<typename C::value_type>
auto variance(const C& container) {
    using T = typename C::value_type;
    // Calculamos el promedio reutilizando mean()
    auto promedio = mean(container);
    // Variable para acumular las diferencias cuadradas
    decltype(promedio) suma_diferencias{};
    std::size_t cuenta = 0;
    // Recorremos el contenedor
    for (const auto& valor : container) {
        // Convertimos valor al mismo tipo que promedio
        auto diferencia =
            static_cast<decltype(promedio)>(valor)
            - promedio;
        // Sumamos el cuadrado de la diferencia
        suma_diferencias =
            suma_diferencias +
            (diferencia * diferencia);
        cuenta++;
    }
    // Retornamos la varianza
    return suma_diferencias / cuenta;
}

// Punto 4) max
// Requiere: Iterable + Comparable sobre el tipo de elemento
template <Iterable C>
requires Comparable<typename C::value_type>
auto max(const C& container) {
    auto maximo = *std::begin(container);
    for (const auto& valor : container) {
        if (valor > maximo)
            maximo = valor;
    }
    return maximo;
}

// Punto 5) transform_reduce
// Aplica una función a cada elemento y acumula el resultado
// La función se recibe como parámetro template
template <Iterable C, typename F>
requires Addable<decltype(std::declval<F>()(std::declval<typename C::value_type>()))>
auto transform_reduce(const C& container, F funcion_transformadora) {
    using T = decltype(funcion_transformadora(*std::begin(container)));
    T suma_total{};
    for (const auto& valor : container)
        suma_total = suma_total + funcion_transformadora(valor);
    return suma_total;
}

// Punto 6) Variadic templates + fold expressions

// sum_variadic: usa fold expression para sumar todos los argumentos
template <Addable T, Addable... Args>
auto sum_variadic(T first, Args... args) {
    return (first + ... + args);
}

// mean_variadic: reutiliza sum_variadic, usa if constexpr (Punto 7)
template <Addable T, Addable... Args>
auto mean_variadic(T first, Args... args) {
    auto suma = sum_variadic(first, args...);
    constexpr std::size_t cantidad = 1 + sizeof...(args);

    // Punto 7: if constexpr — enteros retornan double, flotantes usan su tipo
    if constexpr (std::is_integral_v<decltype(suma)>) {
        return static_cast<double>(suma) / static_cast<double>(cantidad);
    } else {
        return suma / static_cast<decltype(suma)>(cantidad);
    }
}

// variance_variadic
template <Addable T, Addable... Args>
auto variance_variadic(T first, Args... args) {
    auto promedio = mean_variadic(first, args...);
    double suma_diferencias = 0.0;
    constexpr std::size_t cantidad = 1 + sizeof...(args);

    // Inicializamos una lista de los valores convertidos a double
    auto valores = {static_cast<double>(first), static_cast<double>(args)...};
    for (auto valor : valores) {
        auto diferencia = valor - promedio;
        suma_diferencias += diferencia * diferencia;
    }
    return suma_diferencias / static_cast<double>(cantidad);
}

// max_variadic: compara todos los argumentos usando el concept Comparable
template <Comparable T, Comparable... Args>
auto max_variadic(T first, Args... args) {
    T maximo = first;
    auto valores = {args...};
    for (auto valor : valores) {
        if (valor > maximo)
            maximo = valor;
    }
    return maximo;
}

}

#endif // TAREA2_CORE_NUMERIC_H
