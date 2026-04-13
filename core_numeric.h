#ifndef TAREA2_CORE_NUMERIC_H
#define TAREA2_CORE_NUMERIC_H


# include < concepts >
# include < iterator >
using namespace std;

template < typename C >
concept Iterable = requires ( C c ) {
    begin (c) ;
    end (c) ;
};

template < typename T >
concept Addable = requires ( T a , T b ) {
    { a + b } -> same_as <T >;
};

template < typename T >
concept Divisible = requires ( T a , size_t n ) {
    { a / n } -> same_as <T >;
};
// TAREA: Crear uno adicional y aplicarlo


#endif //TAREA2_CORE_NUMERIC_H
