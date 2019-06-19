#include <iostream>
#include <thread>
#include <assert.h>
#include <sys/time.h>
#include <future>
#include "Matriz.h"
#include "Matriz_Concurrente.h"

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

    //CONCURRENTE

    struct timeval start;
    struct timeval finish;
    long compTime;
    double Time_1;
    double Time_2;
    
    //--Concurrente

    Matriz_Concurrente _m1(5, 5);
    Matriz_Concurrente _m2(5, 5);
    _m1.fill_matriz();
    _m2.fill_matriz();
    _m1.printMatries();
    _m2.printMatries();

    gettimeofday(&start, 0);
    Matriz_Concurrente _m3 = _m1*_m2;
    gettimeofday(&finish, 0);

    compTime=(finish.tv_sec - start.tv_sec)*1000000;
    compTime=compTime+(finish.tv_usec - start.tv_usec);
    Time_2=(double)compTime;
    std::cout << "El tiempo que se demoro usando hilos fue "<< (double)Time_2/1000000.0 <<" Secs \n";

    std::cout << std::endl;
    _m3.printMatries();

    return 0;
}