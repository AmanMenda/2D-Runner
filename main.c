#include <stdlib.h>
#include "runner.h"
#include "window.h"

int current_screen = MENU_SCREEN;

void createWindow(const int screenWidth, const int screenheight, const int framerate)
{
    InitWindow(screenWidth, screenheight, "My 2D Runner");
    SetTargetFPS(framerate);
}

void initWindowInfos(Window_t *window)
{
    window->framerate   = 120;
    window->width       = 800;
    window->height      = 600;
}

Texture2D extractTextureFromImage(char const *imagePath)
{
    Image image         = LoadImage(imagePath);
    Texture2D texture   = LoadTextureFromImage(image);

    UnloadImage(image);
    return texture;
}

int main(int argc, char *argv[])
{
    // Not using argc nor argv yet
    (void)argc; (void)argv;

    // Game_t      game;
    Window_t    window;

    initWindowInfos(&window);
    InitAudioDevice();
    createWindow(window.width, window.height, window.framerate);
    Texture2D menuBackground = LoadTexture("assets/png/menu.png");
    Shader backgroundShader = LoadShader(0, TextFormat("shaders/wave.fs", 330));

    // Menu Text
    Font gameMenuFont = LoadFont("assets/fonts/Julee-Regular.ttf");
    Vector2 gameNamePosition = {(float)window.width/2 - 115, (float)100};
    Vector2 menuMessage = {(float)window.width/2 - 140, (float)500};
    float seconds = 0;

    while (!WindowShouldClose())
    {
        seconds += GetFrameTime();
        BeginDrawing();
            ClearBackground(RAYWHITE);

            //Apply shader to everything between Begin and End
            DrawTexture(menuBackground, 0, 0, WHITE);
            DrawTexture(menuBackground, menuBackground.width, 0, WHITE);
            DrawTextEx(gameMenuFont, "2D RUNNER", gameNamePosition, 60, .0f, WHITE);
            if (((int)seconds % 2) == 0)
                DrawTextEx(gameMenuFont, "Press any key to start", menuMessage, 30, 5.0f, WHITE);
            else
                DrawTextEx(gameMenuFont, "Press any key to start", menuMessage, 30, 5.0f, BLANK);

        EndDrawing();
    }
    UnloadShader(backgroundShader);
    UnloadTexture(menuBackground);
    UnloadFont(gameMenuFont);

    CloseAudioDevice();
    CloseWindow();
    return EXIT_SUCCESS;
}