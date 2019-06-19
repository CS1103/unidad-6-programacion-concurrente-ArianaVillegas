#ifndef TRABAJO_PROGRAMACION_CONCURRENTE_MATRIZ_CONCURRENTE_H
#define TRABAJO_PROGRAMACION_CONCURRENTE_MATRIZ_CONCURRENTE_H
#include <iostream>
#include <vector>
#include <future>

template <typename Class>
void MultiplicacionParcial(int Param1, int Param2, int Param3, Class m1, Class m2, Class m3) {
    for(int i = 0; i < Param1; i++)
        for(int j = 0; j < Param2; j++)
            for(int k = 0; k < Param3; k++) {
                m1.get_m()[i][j] += m2.get_m()[i][k] * m3.get_m()[k][j];
            }

}

class Matriz_Concurrente {
    int numHilos = 2;
    int filas;
    int columnas;
    int** m;
    friend Matriz_Concurrente operator* (const Matriz_Concurrente &m_1, const Matriz_Concurrente &m_2);
public:

    Matriz_Concurrente(int filas, int columnas): filas{filas}, columnas{columnas} {
        m = new int*[filas];
        for (int i = 0; i < filas; i++) {
            m[i] = new int[columnas];
        }
    }
    Matriz_Concurrente() {
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

    void printMatries () {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                std::cout << m[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void fill_matriz() {
        for (int i = 0; i < filas; i++)
            for (int j = 0; j < columnas; j++)
                m[i][j] = rand()%15;
    }

};

Matriz_Concurrente operator* (const Matriz_Concurrente &m_1, const Matriz_Concurrente &m_2) {
    Matriz_Concurrente _m(m_1.filas, m_2.columnas);
    _m.fillWith0();

    std::vector <std::thread> h3;

    int param = 0;
    int paso = (m_1.filas/m_1.numHilos)-1;
    for (int i = 0; i < m_1.numHilos; i++) {
        int temp = param;
        param += paso;
        h3.emplace_back(MultiplicacionParcial<Matriz_Concurrente>, temp, m_2.columnas, m_1.columnas, std::ref(_m), std::ref(m_1), std::ref(m_2));
        param++;
    }

    for (int i = 0; i < m_1.numHilos; i++) {
        h3[i].join();
    }

    return _m;
}

#endif //TRABAJO_PROGRAMACION_CONCURRENTE_MATRIZ_CONCURRENTE_H
