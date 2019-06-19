//
// Created by ariana on 19/06/19.
//

#include <iostream>
#include "Matriz.h"

std::random_device r;

template <>
void Matriz<int>::RellanrMatriz(int filas, int columnas){
    Matriz::filas=filas;
    Matriz::columnas=columnas;
    std::vector<int> fila;
    for (int i=0; i<Matriz::filas; i++) {
        fila.clear();
        for (int j = 0; j < Matriz::columnas; j++) {
            fila.push_back(r()%100+1);
        }
        matriz.push_back(fila);
    }
}

template <>
void Matriz<double>::RellanrMatriz(int filas, int columnas){
    Matriz::filas=filas;
    Matriz::columnas=columnas;
    std::vector<double> fila;
    for (int i=0; i<Matriz::filas; i++) {
        fila.clear();
        for (int j = 0; j < Matriz::columnas; j++) {
            fila.push_back((r()%100+1)*1.0/(r()%5+1));
        }
        matriz.push_back(fila);
    }
}