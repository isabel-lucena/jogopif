#include "raylib.h"

int main(void) {

    InitWindow(1000, 700, "escaPIF");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Bem-vinda ao escaPIF!",
                 300, 300, 30, DARKBLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}