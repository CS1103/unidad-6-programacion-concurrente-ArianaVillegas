//
// Created by ariana on 19/06/19.
//

#ifndef PROGRAMACION_CONCURRENTE_MATRIZ_H
#define PROGRAMACION_CONCURRENTE_MATRIZ_H

#include <vector>
#include <random>

template <typename T1>
class Matriz{
    int filas=0;
    int columnas=0;
    std::vector<std::vector<T1>> matriz;
public:
    Matriz(){};
    Matriz(int filas, int columnas, std::vector<std::vector<T1>> matriz):filas(filas),columnas(columnas),matriz(matriz){};
    int Filas(){return filas;};
    int Columnas(){return columnas;};
    void RellanrMatriz(int filas, int columnas);
    std::vector<std::vector<T1>> GetMatriz(){ return matriz;};
    void PrintMatriz() {
        for (int i=0; i<filas; i++) {
            for (int j = 0; j < columnas; j++) {
                std::cout<<matriz[i][j]<<"  ";
            }
            std::cout<<'\n';
        }
        std::cout<<'\n';
    };
    Matriz operator*(Matriz b){
        std::vector<std::vector<T1>> bm=b.GetMatriz();
        std::vector<std::vector<T1>> rm;
        std::vector<T1> fila;
        T1 multi=0;
        for(int i=0;i<filas;i++){
            fila.clear();
            for(int j=0;j<b.Columnas();j++){
                multi=0;
                for(int k=0;k<columnas;k++){
                    multi+=matriz[i][k]*bm[k][j];
                }
                fila.push_back(multi);
            }
            rm.push_back(fila);
        }
        Matriz resultado(filas,b.Columnas(),rm);
        return resultado;
    }
};


#endif //PROGRAMACION_CONCURRENTE_MATRIZ_H
