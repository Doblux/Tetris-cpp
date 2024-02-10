#ifndef __JUEGO__
#define __JUEGO__

#include "cuadricula.cpp"
#include "cuadricula.h"
#include <map>
#include <raylib.h>
#include <vector>
#include <utility>

using namespace std;

// TO DO

//typedef enum {
//    MAIN_MENU,
//    
//} game_state;


class juego {
public:
    juego();
    ~juego();
    void draw_grid(cuadricula& c);
    void draw_interface();
    void nuevo_bloque(cuadricula& c);
    bool gameOver;
    bool puedo_seguir_bajando;
    bool entraElBloque(cuadricula& c, vector<pair<int, int>>& bloque_actual);
    bool estaEnRango(cuadricula& c, vector<pair<int, int>>& bloque_actual);
    void rotar(cuadricula& c);
    void mover_izquierda(cuadricula& c);
    void mover_derecha(cuadricula& c);
    void mover_hacia_abajo(cuadricula& c);
    pair<int, int> obtenerIndex_de_los_offset(int& id, vector<pair<int, int>>& bloque_actual, int i);
    void actualizar_score(cuadricula& c);
    Music music;
private:
    void ActualizarEstadoDeRotacion(int id);
    // offsets de las rotaciones
    map<int, vector<pair<int, int>>> offset_tetroI;
    map<int, vector<pair<int, int>>> offset_tetroL;
    map<int, vector<pair<int, int>>> offset_tetroLInverse;
    map<int, vector<pair<int, int>>> offset_tetroZ;
    map<int, vector<pair<int, int>>> offset_tetroZInverse;
    map<int, vector<pair<int, int>>> offset_tetroT;
    map<int, vector<pair<int, int>>> _blocks;
    vector<pair<int, int>> _bloque_actual;
    int _actual_id;
    int rotation_state;
    int _score;
    string __text__ = "SCORE:";
    Texture2D _img_blocks;
};

#endif
