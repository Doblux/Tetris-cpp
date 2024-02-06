#include "cuadricula.h"
#include <iostream>

using namespace std;

cuadricula::cuadricula(){
    _lineas_completas = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            c[i][j] = 0;
        }
    }
}

void cuadricula::imprimir_cuadricula(cuadricula& c){
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 10; j++){
            cout << c.c[i][j] << " ";
        }
        cout << endl;
    }
}

bool cuadricula::esLinea(int arreglo[10]){
    bool res = true;
    for (int i = 0; i < 10; i++){
        res = res && (arreglo[i] != 0);
    }
    return res;
}


void cuadricula::limpiarLinea(int line, cuadricula&c){
    for (int i = 0; i < 10; i++){
        c.c[line][i] = 0;
    }
}

void cuadricula::mover_linea_abajo(int linea, int numeroDeLineas, cuadricula& c){
    for (int i = 0; i < 10; i++){
        c.c[linea + numeroDeLineas][i] = c.c[linea][i];
        c.c[linea][i] = 0;
    }
}

void cuadricula::ajustar_lineas_rellenas(cuadricula& c){
    int completed_lines = 0;
    for (int i = 19; i >= 0; i--){
        if (esLinea(c.c[i])){
            limpiarLinea(i, c);
            completed_lines++;
            _lineas_completas++;
        } else if (completed_lines > 0) {
            mover_linea_abajo(i, completed_lines, c);
        }
    }
}

