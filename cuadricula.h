#ifndef __CUADRICULA__
#define __CUADRICULA__

#include <vector>
using namespace std;

class cuadricula {
public:
    cuadricula();
    int c[20][10];
    void imprimir_cuadricula(cuadricula& c);
    void ajustar_lineas_rellenas(cuadricula& c);
    int _lineas_completas;
private:
    bool esLinea(int arreglo[10]);
    void limpiarLinea(int line, cuadricula&c);
    void mover_linea_abajo(int linea, int numeroDeLineas, cuadricula& c);
};

#endif
