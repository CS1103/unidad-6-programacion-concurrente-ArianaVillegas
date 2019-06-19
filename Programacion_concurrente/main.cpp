#include <iostream>
#include "Matriz.h"

int main() {
    Matriz<double> a;
    Matriz<double> b;
    Matriz<double> c;
    a.RellanrMatriz(2,2);
    b.RellanrMatriz(2,2);

    a.PrintMatriz();
    b.PrintMatriz();

    c=a*b;

    c.PrintMatriz();

    return 0;
}