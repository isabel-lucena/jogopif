/* main.c  -  PESSOA C
 * Abre a janela da raylib e roda o laço principal do jogo. */
#include <stdio.h>
#include "raylib.h"
#include "jogo.h"

int main(void) {
    Jogo jogo;

    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "escaPIF");
    SetTargetFPS(FPS);                  /* 60 quadros por segundo */

    if (!jogoIniciar(&jogo)) {          /* algum mapa não abriu */
        jogoLiberar(&jogo);
        CloseWindow();
        printf("Erro: mapa nao encontrado. Rode o jogo da pasta do projeto (make run).\n");
        return 1;
    }

    while (!WindowShouldClose()) {      /* ESC ou o X da janela fecham */
        jogoAtualizar(&jogo);           /* 1. teclado e regras */

        BeginDrawing();                 /* 2. desenho */
        ClearBackground(COR_FUNDO);
        jogoDesenhar(&jogo);
        EndDrawing();
    }

    jogoLiberar(&jogo);                 /* 3. free em tudo */
    CloseWindow();
    return 0;
}
