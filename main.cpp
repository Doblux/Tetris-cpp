#include <raylib.h>
#include "./include/cuadricula.h"
#include "./include/juego.cpp"


double lastUpdateTime = 0;

bool EventTriggered(double interval){
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main(){
    juego j;
    cuadricula c;
   
    j.nuevo_bloque(c);
    
    while (!WindowShouldClose()) {
        UpdateMusicStream(j.music);       
        if (j.gameOver){
            string game_over = "GAME OVER";
            BeginDrawing();
            DrawText(game_over.c_str(), 320, 150, 55, RED);
            EndDrawing();

        } else {
            // comienzo del juego
            if (EventTriggered(0.5)){
                j.mover_hacia_abajo(c);
            }
            if (!j.puedo_seguir_bajando){
                c.ajustar_lineas_rellenas(c);
                j.actualizar_score(c);
                j.nuevo_bloque(c);
            }

    
            if (IsKeyPressed(KEY_Z)) j.rotar(c);
            if (IsKeyPressed(KEY_LEFT)) j.mover_izquierda(c);
            if (IsKeyPressed(KEY_RIGHT)) j.mover_derecha(c);
            if (IsKeyPressed(KEY_DOWN)) j.mover_hacia_abajo(c);

            BeginDrawing();
            ClearBackground(BLACK);
            j.draw_grid(c);
            j.draw_interface();
            EndDrawing();
        }
    }
    return 0;
}
