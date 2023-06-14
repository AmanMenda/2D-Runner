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

    // Menu sound
    Music menuSound = LoadMusicStream("assets/evil-storm.wav");
    Sound clickSound = LoadSound("assets/ball-tap.wav");
    PlayMusicStream(menuSound);

    while (!WindowShouldClose())
    {
        seconds += GetFrameTime();
        BeginDrawing();
            if (current_screen == MENU_SCREEN)
            {
                if (IsKeyPressed(KEY_SPACE))
                {
                    PlaySound(clickSound);
                    current_screen = GAME_SCREEN;
                }
                UpdateMusicStream(menuSound);
                DrawTexture(menuBackground, 0, 0, WHITE);
                DrawTexture(menuBackground, menuBackground.width, 0, WHITE);
                DrawTextEx(gameMenuFont, "2D RUNNER", gameNamePosition, 60, .0f, WHITE);
                if (((int)seconds % 2) == 0)
                    DrawTextEx(gameMenuFont, "Press any key to start", menuMessage, 30, 5.0f, WHITE);
                else
                    DrawTextEx(gameMenuFont, "Press any key to start", menuMessage, 30, 5.0f, BLANK);
            }
            if (current_screen == GAME_SCREEN)
                ClearBackground(RAYWHITE);
        EndDrawing();
    }
    UnloadShader(backgroundShader);
    UnloadMusicStream(menuSound);
    UnloadTexture(menuBackground);
    UnloadFont(gameMenuFont);

    CloseAudioDevice();
    CloseWindow();
    return EXIT_SUCCESS;
}