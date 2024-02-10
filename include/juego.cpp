#include "juego.h"
#include "cuadricula.h"
#include <raylib.h>
#include <string>
#include <utility>

juego::juego(){
    const int screenWidth = 660;
    const int screenHeight = 640;
    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);
    InitAudioDevice();
    music = LoadMusicStream("Music/Tetris.mp3");
    PlayMusicStream(music);
    _img_blocks = LoadTexture("assets/Tetris.png");
//    _img_blocks.mipmaps = 1;
//    _img_blocks.width = 510;
//    _img_blocks.height = 30;

    _score = 0;
    _actual_id = 0;
    rotation_state = 0;
    gameOver = false;
    puedo_seguir_bajando = true;
    _blocks[0] = { make_pair(-1, -1) };
    _blocks[1] = { make_pair(1, 3), make_pair(1, 4), make_pair(1, 5), make_pair(1, 6) }; // tetromino_I
    _blocks[2] = { make_pair(0, 3), make_pair(0, 4), make_pair(1, 3), make_pair(1, 4) }; // tetromino_O
    _blocks[3] = { make_pair(0, 4), make_pair(1, 4), make_pair(2, 4), make_pair(2, 5) }; // tetromino_L
    _blocks[4] = { make_pair(0, 5), make_pair(1, 5), make_pair(2, 5), make_pair(2, 4) }; // tetromino_Inverse_L
    _blocks[5] = { make_pair(0, 3), make_pair(0, 4), make_pair(1, 4), make_pair(1, 5) }; // tetromino_Z
    _blocks[6] = { make_pair(0, 5), make_pair(0, 4), make_pair(1, 4), make_pair(1, 3) }; // tetromino_Inverse_Z
    _blocks[7] = { make_pair(0, 3), make_pair(0, 4), make_pair(0, 5), make_pair(1, 4) }; // tetromino_T

    offset_tetroI[0] = { make_pair(-1, 1), make_pair(0, 0), make_pair(1, -1), make_pair(2, -2) }; // cambiar de original a 1 hay que sumar eso( 0 --> 1 )
    offset_tetroI[1] = { make_pair(1, -1), make_pair(0, 0), make_pair(-1, 1), make_pair(-2, 2) }; // volver al original
    offset_tetroL[0] = { make_pair(1, -1), make_pair(0, 0), make_pair(-1, 1), make_pair(-2, 0) };
    offset_tetroL[1] = { make_pair(1, 1), make_pair(0, 0), make_pair(-1, -1), make_pair(0, -2) };
    offset_tetroL[2] = { make_pair(-1, 1), make_pair(0, 0), make_pair(1, -1), make_pair(2, 0) };
    offset_tetroL[3] = { make_pair(-1, -1), make_pair(0, 0), make_pair(1, 1), make_pair(0, 2) };
    offset_tetroLInverse[0] = { make_pair(1, -1), make_pair(0, 0), make_pair(-1, 1), make_pair(-2, 0) };
    offset_tetroLInverse[1] = { make_pair(1, 1), make_pair(0, 0), make_pair(-1, 0), make_pair(0, 1) };
    offset_tetroLInverse[2] = { make_pair(-1, -1), make_pair(0, 0), make_pair(1, 0), make_pair(2, 1) };
    offset_tetroLInverse[3] = { make_pair(-1, 1), make_pair(0, 0), make_pair(1, -1), make_pair(0, -2) };
    offset_tetroZ[0] = { make_pair(0, 2), make_pair(1, 1), make_pair(0, 0), make_pair(1, -1) };
    offset_tetroZ[1] = { make_pair(0, -2), make_pair(-1, -1), make_pair(0, 0), make_pair(-1, 1) };
    offset_tetroZInverse[0] = { make_pair(0, -1), make_pair(1, 0), make_pair(0, 1), make_pair(1, 2) };
    offset_tetroZInverse[1] = { make_pair(0, 1), make_pair(-1, 0), make_pair(0, -1), make_pair(-1, -2) };
    offset_tetroT[0] = { make_pair(-1, 1), make_pair(0, 0), make_pair(0, 0), make_pair(0, 0) };
    offset_tetroT[1] = { make_pair(0, 0), make_pair(0, 0), make_pair(0, 0), make_pair(-1, -1) };
    offset_tetroT[2] = { make_pair(0, 0), make_pair(0, 0), make_pair(1, -1), make_pair(0, 0) };
    offset_tetroT[3] = { make_pair(1, -1), make_pair(0, 0), make_pair(-1, 1), make_pair(1, 1) };
}

juego::~juego(){
    UnloadTexture(_img_blocks);
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
}

void juego::draw_grid(cuadricula& cuadricula){
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 10; j++){
            float x_cord = 20.0 + 30.0 * j;
            float y_cord = 20.0 + 30.0 * i;
            switch (cuadricula.c[i][j]) {
                case 0: DrawRectangle(20 + 30 * j, 20 + 30 * i, 30, 30, BLACK); 
                    break;
                case 1:// imagen, rectangulo adentro de la imagen, posicion en la ventana, color
                    DrawTextureRec(_img_blocks, (Rectangle){0, 0, 30, 30}, (Vector2){x_cord, y_cord}, WHITE);
                    break;
                case 2:
                    DrawTextureRec(_img_blocks, (Rectangle){30, 0, 30, 30}, (Vector2){x_cord, y_cord}, WHITE);
                    break;
                case 3:
                    DrawTextureRec(_img_blocks, (Rectangle){60, 0, 30, 30}, (Vector2){x_cord, y_cord}, WHITE);
                    break;
                case 4:
                    DrawTextureRec(_img_blocks, (Rectangle){90, 0, 30, 30}, (Vector2){x_cord, y_cord}, WHITE);
                    break;
                case 5:
                    DrawTextureRec(_img_blocks, (Rectangle){120, 0, 30, 30}, (Vector2){x_cord, y_cord}, WHITE);
                    break;
                case 6:
                    DrawTextureRec(_img_blocks, (Rectangle){150, 0, 30, 30}, (Vector2){x_cord, y_cord}, WHITE);
                    break;
                case 7:
                    DrawTextureRec(_img_blocks, (Rectangle){180, 0, 30, 30}, (Vector2){x_cord, y_cord}, WHITE);
                    break;
            }
        }
    }
}

void juego::nuevo_bloque(cuadricula& c){
    puedo_seguir_bajando = true;
    rotation_state = 0;
    int r = GetRandomValue(1, 7);
    _actual_id = r;
    _bloque_actual = _blocks[r];
    for (int i = 0; i < _bloque_actual.size(); i++) {
        int h = _bloque_actual[i].first; // coordenada i para cuadricula
        int k = _bloque_actual[i].second; // coordenada j para cuadricula (i, j)
        if (c.c[h][k] != 0)
        {
            gameOver = true;
            return;
        } else {
            c.c[h][k] = _actual_id;
        }
    }
}

bool juego::entraElBloque(cuadricula& c, vector<pair<int, int>>& bloque_actual){
    for (int i = 0; i < bloque_actual.size(); i++) {
        int h = bloque_actual[i].first;
        int k = bloque_actual[i].second;
        if (c.c[h][k] != 0){
            return false;
        }
    }
    return true;
}

bool juego::estaEnRango(cuadricula& c, vector<pair<int, int>>& bloque_actual){
    bool res = true;
    for (int i = 0; i < bloque_actual.size(); i++){
        int h = bloque_actual[i].first;
        int k = bloque_actual[i].second;
        res = res && ((0 <= h && h < 20) && (0 <= k && k < 10));
    }
    return res;
}

pair<int, int> juego::obtenerIndex_de_los_offset(int& id, vector<pair<int, int>>& bloque_actual, int i){
    // I , O , L, Linverse, Z, Zinverse, T
    switch (id) {
        case 1: return make_pair(bloque_actual[i].first + offset_tetroI[rotation_state][i].first, bloque_actual[i].second + offset_tetroI[rotation_state][i].second);
        case 2: return make_pair(bloque_actual[i].first, bloque_actual[i].second);
        case 3: return make_pair(bloque_actual[i].first + offset_tetroL[rotation_state][i].first, bloque_actual[i].second + offset_tetroL[rotation_state][i].second);
        case 4: return make_pair(bloque_actual[i].first + offset_tetroLInverse[rotation_state][i].first, bloque_actual[i].second + offset_tetroLInverse[rotation_state][i].second);
        case 5: return make_pair(bloque_actual[i].first + offset_tetroZ[rotation_state][i].first, bloque_actual[i].second + offset_tetroZ[rotation_state][i].second);
        case 6: return make_pair(bloque_actual[i].first + offset_tetroZInverse[rotation_state][i].first, bloque_actual[i].second + offset_tetroZInverse[rotation_state][i].second);
        case 7: return make_pair(bloque_actual[i].first + offset_tetroT[rotation_state][i].first, bloque_actual[i].second + offset_tetroT[rotation_state][i].second);
    }
    return make_pair(0, 0);
}

void juego::ActualizarEstadoDeRotacion(int id){
    // I , O , L, Linverse, Z, Zinverse, T
    switch (id) {
        case 0: return;
        case 1: rotation_state++; rotation_state = rotation_state % 2; break; // I
        case 2: return; // O
        case 3: rotation_state++; rotation_state = rotation_state % 4; break; // L
        case 4: rotation_state++; rotation_state = rotation_state % 4; break; // Linverse
        case 5: rotation_state++; rotation_state = rotation_state % 2; break; // Z
        case 6: rotation_state++; rotation_state = rotation_state % 2; break; // Zinverse
        case 7: rotation_state++; rotation_state = rotation_state % 4; break; // T
    }
}

// no termina nunca el ciclo --> arreglar
void juego::rotar(cuadricula& c){
    vector<pair<int, int>> pieza_rotada = {};
    for (int i = 0; i < _bloque_actual.size(); i++){
        // obtener indice i y j de la pieza ya rotada
        pair<int, int> coord_rotada = obtenerIndex_de_los_offset(_actual_id, _bloque_actual, i);
        pieza_rotada.push_back(coord_rotada);
    }
    // relleno de 0 la cuadricula ya que tengo los 2 bloques que me interesan _bloque_actual y pieza_rotada
    for (int i = 0; i < _bloque_actual.size(); i++){
        int h = _bloque_actual[i].first;
        int k = _bloque_actual[i].second;
        c.c[h][k] = 0;
    }
    bool entra = estaEnRango(c, pieza_rotada) && entraElBloque(c, pieza_rotada); // es para el bloque ya rotado
    if (entra){
        _bloque_actual = pieza_rotada;
        for (int i = 0; i < _bloque_actual.size(); i++){
            int h = _bloque_actual[i].first;
            int k = _bloque_actual[i].second;
            c.c[h][k] = _actual_id;
        }
        ActualizarEstadoDeRotacion(_actual_id);
    } else {
        for (int i = 0; i < _bloque_actual.size(); i++){
            int h = _bloque_actual[i].first;
            int k = _bloque_actual[i].second;
            c.c[h][k] = _actual_id;
        }
        return;
    }
}


void juego::mover_izquierda(cuadricula& c){
    vector<pair<int, int>> pieza_movida = {};
    for (int i = 0; i < _bloque_actual.size(); i++){
        int pieza_movida_x = _bloque_actual[i].first;
        int pieza_movida_y = _bloque_actual[i].second - 1;
        pieza_movida.push_back(make_pair(pieza_movida_x, pieza_movida_y));
    }
    for (int i = 0; i < _bloque_actual.size(); i++)
    {
        int h = _bloque_actual[i].first;
        int k = _bloque_actual[i].second;
        c.c[h][k] = 0;
    }
    bool entra = estaEnRango(c, pieza_movida) && entraElBloque(c, pieza_movida);
    if (entra) {
        _bloque_actual = pieza_movida;
        for (int i = 0; i < _bloque_actual.size(); i++)
        {
            int h = _bloque_actual[i].first;
            int k = _bloque_actual[i].second;
            c.c[h][k] = _actual_id;
        }
    } else {
        for (int i = 0; i < _bloque_actual.size(); i++)
        {
            int h = _bloque_actual[i].first;
            int k = _bloque_actual[i].second;
            c.c[h][k] = _actual_id;
        }
    }
}



void juego::mover_derecha(cuadricula& c){
    vector<pair<int, int>> pieza_movida = {};
    for (int i = 0; i < _bloque_actual.size(); i++){
        int pieza_movida_x = _bloque_actual[i].first;
        int pieza_movida_y = _bloque_actual[i].second + 1;
        pieza_movida.push_back(make_pair(pieza_movida_x, pieza_movida_y));
    }
    for (int i = 0; i < _bloque_actual.size(); i++)
    {
        int h = _bloque_actual[i].first;
        int k = _bloque_actual[i].second;
        c.c[h][k] = 0;
    }
    bool entra = estaEnRango(c, pieza_movida) && entraElBloque(c, pieza_movida);
    if (entra) {
        _bloque_actual = pieza_movida;
        for (int i = 0; i < _bloque_actual.size(); i++)
        {
            int h = _bloque_actual[i].first;
            int k = _bloque_actual[i].second;
            c.c[h][k] = _actual_id;
        }
    } else {
        for (int i = 0; i < _bloque_actual.size(); i++)
        {
            int h = _bloque_actual[i].first;
            int k = _bloque_actual[i].second;
            c.c[h][k] = _actual_id;
        }
    }
}


void juego::mover_hacia_abajo(cuadricula& c){
    vector<pair<int, int>> pieza_movida = {};
    for (int i = 0; i < _bloque_actual.size(); i++){
        int pieza_movida_x = _bloque_actual[i].first + 1;
        int pieza_movida_y = _bloque_actual[i].second;
        pieza_movida.push_back(make_pair(pieza_movida_x, pieza_movida_y));
    }
    for (int i = 0; i < _bloque_actual.size(); i++)
    {
        int h = _bloque_actual[i].first;
        int k = _bloque_actual[i].second;
        c.c[h][k] = 0;
    }
    bool entra = estaEnRango(c, pieza_movida) && entraElBloque(c, pieza_movida);
    if (entra) {
        _bloque_actual = pieza_movida;
        for (int i = 0; i < _bloque_actual.size(); i++)
        {
            int h = _bloque_actual[i].first;
            int k = _bloque_actual[i].second;
            c.c[h][k] = _actual_id;
        }
    } else {
        for (int i = 0; i < _bloque_actual.size(); i++)
        {
            int h = _bloque_actual[i].first;
            int k = _bloque_actual[i].second;
            c.c[h][k] = _actual_id;
        }
        puedo_seguir_bajando = false;
    }
}


void juego::draw_interface(){
    DrawRectangle(0, 0, 20, 640, LIGHTGRAY);
    DrawRectangle(0, 620, 340, 20, LIGHTGRAY);
    DrawRectangle(320, 0, 20, 640, LIGHTGRAY);
    DrawRectangle(0, 0, 660, 20, LIGHTGRAY);
    DrawRectangle(340, 115, 320, 20, LIGHTGRAY);
    DrawText(__text__.c_str(), 355, 40, 55, PURPLE);
    DrawText(std::to_string(_score).c_str(), 555, 40, 55, WHITE);
}

void juego::actualizar_score(cuadricula&c){
    _score = 10 * c._lineas_completas;
}

