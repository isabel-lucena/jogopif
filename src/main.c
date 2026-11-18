#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "tipos.h"
#include "jogo.h"

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "escaPIF - Fuga do Brum");
    SetTargetFPS(FPS);

    Jogo jogo;
    jogoInicializar(&jogo);

    while (!WindowShouldClose()) {
        jogoAtualizar(&jogo);
        jogoDesenhar(&jogo);
    }

    jogoFinalizar(&jogo);
    CloseWindow();

    return 0;
}
