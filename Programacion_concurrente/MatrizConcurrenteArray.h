#ifndef TRABAJO_PROGRAMACION_CONCURRENTE_MATRIZCONCURRENTEARRAY_H
#define TRABAJO_PROGRAMACION_CONCURRENTE_MATRIZCONCURRENTEARRAY_H
#include <iostream>
#include <vector>
#include <future>

template <typename Class>
void MultiplicacionParcial(int Param0, int Param1, int Param2, int Param3, Class m1, Class m2, Class m3) {
    for(int i = Param0; i < Param1; i++)
        for(int j = 0; j < Param2; j++)
            for(int k = 0; k < Param3; k++)
                m1.get_m()[i][j] += m2.get_m()[i][k] * m3.get_m()[k][j];

}

class MatrizConcurrenteArray {
    int numHilos = 2;
    int filas;
    int columnas;
    int** m;
    friend MatrizConcurrenteArray operator* (const MatrizConcurrenteArray &m_1, const MatrizConcurrenteArray &m_2);
public:

    MatrizConcurrenteArray(int filas, int columnas): filas{filas}, columnas{columnas} {
        m = new int*[filas];
        for (int i = 0; i < filas; i++) {
            m[i] = new int[columnas];
        }
    }
    MatrizConcurrenteArray() {
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

    void fill_matriz_withX(int x) {
        for (int i = 0; i < filas; i++)
            for (int j = 0; j < columnas; j++)
                m[i][j] = x;
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

    void fill_matriz() {
        for (int i = 0; i < filas; i++)
            for (int j = 0; j < columnas; j++)
                m[i][j] = 10;
    }

};

MatrizConcurrenteArray operator* (const MatrizConcurrenteArray &m_1, const MatrizConcurrenteArray &m_2) {
    MatrizConcurrenteArray _m(m_1.filas, m_2.columnas);
    _m.fillWith0();

    std::vector <std::thread> h3;

    int param = 0;
    int paso = m_1.filas / m_1.numHilos;
    if ( m_1.filas%m_1.numHilos == 0 ) {
        for (int i = 0; i < m_1.numHilos; i++) {
            int temp = param;
            param += paso;
            h3.emplace_back(MultiplicacionParcial<MatrizConcurrenteArray>, temp, param, m_2.columnas, m_1.columnas,
                            std::ref(_m),
                            std::ref(m_1), std::ref(m_2));
        }
    }
    else {
        for (int i = 0; i < m_1.numHilos-1; i++) {
            int temp = param;
            param += paso;
            h3.emplace_back(MultiplicacionParcial<MatrizConcurrenteArray>, temp, param, m_2.columnas, m_1.columnas,
                            std::ref(_m),
                            std::ref(m_1), std::ref(m_2));
        }
        int temp = param;
        param += paso + 1;
        h3.emplace_back(MultiplicacionParcial<MatrizConcurrenteArray>, temp, param, m_2.columnas, m_1.columnas,
                        std::ref(_m),
                        std::ref(m_1), std::ref(m_2));
    }

    for (int i = 0; i < m_1.numHilos; i++) {
        h3[i].join();
    }

    return _m;
}

#endif //TRABAJO_PROGRAMACION_CONCURRENTE_MATRIZCONCURRENTEARRAY_H
