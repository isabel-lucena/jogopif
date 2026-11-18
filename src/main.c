#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "tipos.h"
#include "jogo.h"

int main(void) {
    srand((unsigned int)time(NULL));

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "escaPIF - Fuga do Brum");
    SetTargetFPS(FPS);

    int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    ToggleFullscreen();

    RenderTexture2D telaVirtual = LoadRenderTexture(LARGURA_JANELA, ALTURA_JANELA);
    SetTextureFilter(telaVirtual.texture, TEXTURE_FILTER_BILINEAR);

    Jogo jogo;
    jogoInicializar(&jogo);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        jogoAtualizar(&jogo);
        BeginTextureMode(telaVirtual);
            jogoDesenhar(&jogo);
        EndTextureMode();

        float larguraTela = (float)GetScreenWidth();
        float alturaTela  = (float)GetScreenHeight();

        float escalaX = larguraTela / (float)LARGURA_JANELA;
        float escalaY = alturaTela  / (float)ALTURA_JANELA;
        float escala  = (escalaX < escalaY) ? escalaX : escalaY;

        float larguraFinal = LARGURA_JANELA * escala;
        float alturaFinal  = ALTURA_JANELA * escala;
        float offsetX      = (larguraTela - larguraFinal) * 0.5f;
        float offsetY      = (alturaTela  - alturaFinal)  * 0.5f;

        BeginDrawing();
            ClearBackground(COR_FUNDO);

            Rectangle origem  = { 0.0f, 0.0f, (float)LARGURA_JANELA, -(float)ALTURA_JANELA };
            Rectangle destino = { offsetX, offsetY, larguraFinal, alturaFinal };
            Vector2 pivo      = { 0.0f, 0.0f };

            DrawTexturePro(telaVirtual.texture, origem, destino, pivo, 0.0f, WHITE);
        EndDrawing();
    }
    jogoFinalizar(&jogo);
    UnloadRenderTexture(telaVirtual);
    CloseWindow();
    return 0;
}
