#ifndef TRABAJO_PROGRAMACION_CONCURRENTE_MATRIZVECTORES_H
#define TRABAJO_PROGRAMACION_CONCURRENTE_MATRIZVECTORES_H

#include <vector>
#include <iostream>
#include <random>

template <typename T1>
class MatrizVectores{
    int filas=0;
    int columnas=0;
    std::vector<std::vector<T1>> matriz;
public:
    MatrizVectores(){};
    MatrizVectores(int filas, int columnas, std::vector<std::vector<T1>> matriz):filas(filas),columnas(columnas),matriz(matriz){};
    int Filas(){return filas;};
    int Columnas(){return columnas;};
    void RellanrMatriz(int filas, int columnas);
    void DatoDeMatriz(int x);
    std::string printMatriesString() {
        std::string r = "";
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                r += std::to_string(matriz[i][j]) + " ";
            }
            r += "\n";
        }
        return r;
    }
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
    MatrizVectores operator*(MatrizVectores b){
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
        MatrizVectores resultado(filas,b.Columnas(),rm);
        return resultado;
    }
};

#endif //TRABAJO_PROGRAMACION_CONCURRENTE_MATRIZVECTORES_H
