#include "./include/raylib/src/raylib.h"
#include "./include/cuadricula.h"
#include "./include/juego.h"
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
    
    Button_t Game_Over_Replay_button;
    Button_t Game_Over_Close_Window_button;
    
    Game_Over_Replay_button.rect = { (Rectangle){100.0, 400.0, 200.0, 100.0} };
    Game_Over_Replay_button.text = "REPLAY";
    Game_Over_Replay_button.color = WHITE;

    Game_Over_Close_Window_button.rect = { (Rectangle){320.0, 400.0, 200.0, 100.0} };
    Game_Over_Close_Window_button.text = "CLOSE";
    Game_Over_Close_Window_button.color = WHITE;

    j.nuevo_bloque(c);
    
    game_state game_state_t;

    game_state_t = MAIN_MENU;

    while (!WindowShouldClose()) {
        switch (game_state_t) {
            case GAME:
                PlayMusicStream(j.music);
                UpdateMusicStream(j.music);
                if (j.gameOver){
                    StopMusicStream(j.music);
                    j.draw_game_over_screen(Game_Over_Replay_button, Game_Over_Close_Window_button);

                    if (CheckCollisionPointRec(GetMousePosition(), Game_Over_Replay_button.rect) ){
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                            j.resetear_cuadricula(c);
                            j.gameOver = false;
                            game_state_t = GAME;
                            break;
                        }
                    }
                    if (CheckCollisionPointRec(GetMousePosition(), Game_Over_Close_Window_button.rect)){
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                            return 0;
                            break;
                        }
                    }
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
                    break;
                    case MAIN_MENU:
                        j.draw_main_menu(game_state_t);
                        break;
                    case SETTINGS:
                        j.draw_settings_menu(game_state_t);
                        break;
                }
        }
    }
    return 0;
}
