#include <iostream>
#include <thread>
#include <assert.h>
#include <sys/time.h>
#include "MatrizArray.h"
#include "MatrizConcurrenteArray.h"
#include "MatrizVectores.h"
#include "MatrizConcurrenteVectores.h"

int main() {

    struct timeval start;
    struct timeval finish;
    long compTime;
    double Time_1;
    double Time_2;

    ///--Asserts Matrices with arrays
    //--Assert Multiplication--Fill with 10--Matriz Par
    MatrizArray a(2,2);
    a.fill_matriz();
    MatrizArray b(2,2);
    b.fill_matriz();
    MatrizArray as(2,2);
    as.fill_matriz_withX(200);
    assert(as.printMatriesString() == (a*b).printMatriesString());
    MatrizConcurrenteArray _a(2,2);
    _a.fill_matriz();
    MatrizConcurrenteArray _b(2,2);
    _b.fill_matriz();
    MatrizConcurrenteArray _as(2,2);
    _as.fill_matriz_withX(200);
    assert(_as.printMatriesString() == (_a*_b).printMatriesString());

    //--Assert Multiplication--Fill with 15--Matriz Impar
    MatrizArray a1(3,3);
    a1.fill_matriz_withX(15);
    MatrizArray b1(3,3);
    b1.fill_matriz_withX(15);
    MatrizArray as1(3,3);
    as1.fill_matriz_withX(675);
    assert(as1.printMatriesString() == (a1*b1).printMatriesString());
    MatrizConcurrenteArray _a1(3,3);
    _a1.fill_matriz_withX(15);
    MatrizConcurrenteArray _b1(3,3);
    _b1.fill_matriz_withX(15);
    MatrizConcurrenteArray _as1(3,3);
    _as1.fill_matriz_withX(675);
    assert(_as1.printMatriesString() == (_a1*_b1).printMatriesString());

    ///--Asserts Matrices con Vectors
    //--Assert Multiplication--Fill with 10--Matriz Par
    MatrizVectores<int> d;
    d.RellanrMatriz(2,2);
    MatrizVectores<int> e;
    e.RellanrMatriz(2,2);
    MatrizVectores<int> as2;
    as2.RellanrMatriz(2,2);
    as2.DatoDeMatriz(200);
    assert(as2.printMatriesString() == (d*e).printMatriesString());
    MatrizConcurrenteVectores _d(2,2,10);
    MatrizConcurrenteVectores _e(2,2,10);
    MatrizConcurrenteVectores _as2(2,2,200);
    assert(_as2.printMatriesString() == (_d*_e).printMatriesString());

    //--Assert Multiplication--Fill with 15--Matriz Impar
    MatrizVectores<int> f;
    f.RellanrMatriz(3,3);
    f.DatoDeMatriz(15);
    MatrizVectores<int> g;
    g.RellanrMatriz(3,3);
    g.DatoDeMatriz(15);
    MatrizVectores<int> as3;
    as3.RellanrMatriz(3,3);
    as3.DatoDeMatriz(675);
    assert(as3.printMatriesString() == (f*g).printMatriesString());
    MatrizConcurrenteVectores _f(3,3,15);
    MatrizConcurrenteVectores _g(3,3,15);
    MatrizConcurrenteVectores _as3(3,3,675);
    assert(_as3.printMatriesString() == (_f*_g).printMatriesString());

    ///--Medir Tiempo Para Calcular--Array--1000x1000-10 de Relleno en la Matriz
    //--No Concurrente
    MatrizArray Am1(1000, 1000);
    MatrizArray Am2(1000, 1000);
    Am1.fill_matriz();
    Am2.fill_matriz();
    gettimeofday(&start, 0);
    MatrizArray Amr = Am1*Am2;
    gettimeofday(&finish, 0);

    compTime=(finish.tv_sec - start.tv_sec)*1000000;
    compTime=compTime+(finish.tv_usec - start.tv_usec);
    Time_1=(double)compTime;
    std::cout << "El tiempo que demoro calcular la matriz usando arrays y sin usar hilos fue "<< (double)Time_1/1000000.0 <<" Secs \n";

    //--Concurrente
    MatrizConcurrenteArray Am3(1000, 1000);
    MatrizConcurrenteArray Am4(1000, 1000);
    Am3.fill_matriz();
    Am4.fill_matriz();

    gettimeofday(&start, 0);
    MatrizConcurrenteArray Amr2 = Am3*Am4;
    gettimeofday(&finish, 0);

    compTime=(finish.tv_sec - start.tv_sec)*1000000;
    compTime=compTime+(finish.tv_usec - start.tv_usec);
    Time_2=(double)compTime;
    std::cout << "El tiempo que demoro calcular la matriz usando arrays y usando 2 hilos fue "<< (double)Time_2/1000000.0 <<" Secs \n";

    ///--Medir Tiempo Para Calcular--Vectores--1000x1000-10 de Relleno en la Matriz
    //--No Concurrente
    MatrizVectores<int> Vm1;
    MatrizVectores<int> Vm2;
    MatrizVectores<int> Vr;
    Vm1.RellanrMatriz(1000,1000);
    Vm2.RellanrMatriz(1000,1000);

    gettimeofday(&start, 0);
    Vr = Vm1*Vm2;
    gettimeofday(&finish, 0);

    compTime=(finish.tv_sec - start.tv_sec)*1000000;
    compTime=compTime+(finish.tv_usec - start.tv_usec);
    Time_1=(double)compTime;
    std::cout << "El tiempo que demoro calcular la matriz usando vectores y sin usar hilos fue "<< (double)Time_1/1000000.0 <<" Secs \n";

    //--Concurrente
    MatrizConcurrenteVectores Vm3(1000,1000,10);
    MatrizConcurrenteVectores Vm4(1000,1000,10);

    gettimeofday(&start, 0);
    MatrizConcurrenteVectores Vm5 = Vm3 * Vm4;
    gettimeofday(&finish, 0);

    compTime=(finish.tv_sec - start.tv_sec)*1000000;
    compTime=compTime+(finish.tv_usec - start.tv_usec);
    Time_2=(double)compTime;
    std::cout << "El tiempo que demoro calcular la matriz usando vectores y usando 2 hilos fue "<< (double)Time_2/1000000.0 <<" Secs \n";

    return 0;
}
