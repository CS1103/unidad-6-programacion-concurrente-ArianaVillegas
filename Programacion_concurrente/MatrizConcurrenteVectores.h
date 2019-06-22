#ifndef TRABAJO_PROGRAMACION_CONCURRENTE_MATRIZCONCURRENTEVECTORES_H
#define TRABAJO_PROGRAMACION_CONCURRENTE_MATRIZCONCURRENTEVECTORES_H

#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <ctime>
#include <vector>
using namespace std;

typedef int cantidad, coor;
typedef int contenido;
const cantidad n_t = 2;
int t_partes;
int max_id = n_t - 1;
template<typename T>
void multiplicar__(cantidad t_id, T&a, T& b, T& resultado){

    cantidad limite = ( t_id < max_id ) ? (t_id+1)*t_partes : a.filas;
//Limite de cada hilo, en el caso del ultimo sera hasta el final (= o + que el resto de hilos)


    for (cantidad i = t_id*t_partes; i<limite; i++){

        for (cantidad j = 0; j<b.columnas; j++){
            contenido temp = 0;

            for (cantidad k = 0; k<a.columnas; k++){
                temp = temp + (a.m[i][k]) * (b.m[k][j]);
            }//Se calcula un elemento de la matriz resultante
            resultado.m[i][j] = temp;//Se almacena el nuevo elemento
        }

        //Se calcula una fila entera de la matriz resultante
    }//Se calcula todas las filas de la matriz resultante

}
class MatrizConcurrenteVectores{
    vector<vector<contenido>> m;
    cantidad filas;
    cantidad columnas;
    template <typename T>
    friend void multiplicar__(cantidad t_id, T&a, T& b, T& resultado);
public:
    MatrizConcurrenteVectores(cantidad filas, cantidad columnas, contenido relleno):filas{filas}, columnas{columnas}{
        for (cantidad i = 0; i<filas; i++){
            vector<contenido> temp;
            for (cantidad j = 0; j<columnas; j++){ temp.push_back(relleno); }
            m.emplace_back(temp);
        }
    }
    std::string printMatriesString() {
        std::string r = "";
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                r += std::to_string(m[i][j]) + " ";
            }
            r += "\n";
        }
        return r;
    }
    MatrizConcurrenteVectores operator*(const MatrizConcurrenteVectores& m_2){
        MatrizConcurrenteVectores b = m_2;
        MatrizConcurrenteVectores a = *this;
        vector<thread> tr;
        cantidad t_id = 0;
        MatrizConcurrenteVectores resultado(filas, m_2.columnas, 1);

        float t_partes_d = (float)(m_2.filas) / (float)n_t;
        t_partes = (int)t_partes_d;
        //printf("\n# de filas por hilo: %d\n (si no es entera la division, el ultimo hilo tendra mas filas)\n", t_partes);


        auto start = chrono::system_clock::now();
        for (t_id = 0; t_id<n_t; t_id++){
            tr.emplace_back(multiplicar__<MatrizConcurrenteVectores>, t_id, ref(a), ref(b), ref(resultado));
        }

        for (t_id = 0; t_id<n_t; t_id++){
            tr[t_id].join();
        }
        auto end = chrono::system_clock::now();

        chrono::duration<double> elapsed_seconds = end-start;
        /*
        cout <<
             "elapsed time: " << elapsed_seconds.count() << "s\n";
        cout<<endl;
        */
        return resultado;
    }
    void imprimir_matriz(){
        printf("\n");
        printf("\n");
        printf("MATRIZ\n");
        printf("(puede estar desfasada por variacion de # digitos)\n");
        printf("------------------------------\n\n");
        for (cantidad i = 0; i<filas; i++){for (cantidad j = 0; j<columnas; j++){ printf("%d  ",m[i][j]); } printf("\n");}
    }
};

#endif //TRABAJO_PROGRAMACION_CONCURRENTE_MATRIZCONCURRENTEVECTORES_H
