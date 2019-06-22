#include <iostream>
#include "MatrizVectores.h"

std::random_device r;

template <>
void MatrizVectores<int>::RellanrMatriz(int filas, int columnas){
    MatrizVectores::filas=filas;
    MatrizVectores::columnas=columnas;
    std::vector<int> fila;
    for (int i=0; i<MatrizVectores::filas; i++) {
        fila.clear();
        for (int j = 0; j < MatrizVectores::columnas; j++) {
            //fila.push_back(r()%100+1);
            fila.push_back(10);
        }
        matriz.push_back(fila);
    }
}

template<>
void MatrizVectores<int>::DatoDeMatriz(int x) {
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            matriz[i][j] = x;
}

template <>
void MatrizVectores<double>::RellanrMatriz(int filas, int columnas){
    MatrizVectores::filas=filas;
    MatrizVectores::columnas=columnas;
    std::vector<double> fila;
    for (int i=0; i<MatrizVectores::filas; i++) {
        fila.clear();
        for (int j = 0; j < MatrizVectores::columnas; j++) {
            fila.push_back((r()%100+1)*1.0/(r()%5+1));
        }
        matriz.push_back(fila);
    }
}