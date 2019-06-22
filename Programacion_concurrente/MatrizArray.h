#ifndef TRABAJO_PROGRAMACION_CONCURRENTE_MATRIZARRAY_H
#define TRABAJO_PROGRAMACION_CONCURRENTE_MATRIZARRAY_H
#include <iostream>
#include <vector>

class MatrizArray {

    int filas;
    int columnas;
    int** m;

public:
    MatrizArray(int filas, int columnas): filas{filas}, columnas{columnas} {
        m = new int*[filas];
        for (int i = 0; i < filas; i++) {
            m[i] = new int[columnas];
        }
    }
    ~MatrizArray() {
        for (int i = 0; i < filas; ++i)
            delete [] m[i];
        delete [] m;
    }

    int** get_m() { return m; }

    void fillWith0() {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                m[i][j] = 0;
            }
        }
    };

    MatrizArray operator* (const MatrizArray &m_2) {
        MatrizArray _m(filas, m_2.columnas);
        _m.fillWith0();
        for(int i = 0; i < filas; i++)
            for(int j = 0; j < m_2.columnas; j++)
                for(int k = 0; k < columnas; k++) {
                    _m.get_m()[i][j] += m[i][k] * m_2.m[k][j];
                }
        return _m;
    }

    void printMatries () {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                std::cout << m[i][j] << " ";
            }
            std::cout << std::endl;
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

    void fill_matriz_withX(int x) {
        for (int i = 0; i < filas; i++)
            for (int j = 0; j < columnas; j++)
                m[i][j] = x;
    }

    void fill_matriz() {
        for (int i = 0; i < filas; i++)
            for (int j = 0; j < columnas; j++)
                m[i][j] = 10;
    }

};

#endif //TRABAJO_PROGRAMACION_CONCURRENTE_MATRIZARRAY_H
