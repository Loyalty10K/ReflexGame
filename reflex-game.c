#include <raylib.h>
#include <stdio.h>
#include <time.h>

int main() {
    InitWindow(1500, 800, "Reflex Game");
    SetRandomSeed((unsigned int)time(NULL));
    SetTargetFPS(60);

    int state = 0;
    double phaseStartTime = GetTime();
    double waitTime = GetRandomValue(2000, 5000) / 1000.0;
    double redStartTime = 0;
    double reactionTime = 0;

    while (!WindowShouldClose()) {

        if (state == 0) {
            if (IsKeyPressed(KEY_UP)) {
                state = 3;
            }
            else if (GetTime() - phaseStartTime >= waitTime) {
                state = 1;
                redStartTime = GetTime();
            }
        }
        else if (state == 1) {
            if (IsKeyPressed(KEY_UP)) {
                reactionTime = (GetTime() - redStartTime) * 1000;
                state = 2;
            }
        }
        else if (IsKeyPressed(KEY_SPACE)) {   // state 2 or 3: start a new round
            state = 0;
            phaseStartTime = GetTime();
            waitTime = GetRandomValue(2000, 5000) / 1000.0;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (state == 0) {
            DrawCircle(750, 400, 110, BLUE);
            DrawText("Wait for the red circle, then press the UP arrow", 420, 600, 30, DARKGRAY);
        } else if (state == 1) {
            DrawCircle(750, 400, 110, RED);
            DrawText("NOW!", 700, 600, 40, RED);
        } else if (state == 2) {
            char message[100];
            sprintf(message, "Reaction time: %.0f ms", reactionTime);
            DrawText(message, 550, 380, 40, BLACK);
            DrawText("Press SPACE for a new round", 565, 600, 30, DARKGRAY);
        } else if (state == 3) {
            DrawText("Too early! Wait for the red circle.", 430, 380, 40, RED);
            DrawText("Press SPACE for a new round", 565, 600, 30, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
