#include <stdlib.h>
#include "runner.h"
#include "window.h"

int current_screen = MENU_SCREEN;
float seconds = .0f;

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

void menu_dtor(Menu_t *menu)
{
    UnloadMusicStream(menu->musicStream);
    UnloadTexture(menu->background);
    UnloadFont(menu->font);
    UnloadSound(menu->clickSound);
}

void setup_main_menu(Window_t *window, Menu_t *menu)
{
    menu->background        = LoadTexture("assets/png/menu.png");

    // Text on menu
    menu->font              = LoadFont("assets/fonts/Julee-Regular.ttf");
    menu->gameNamePos       = (Vector2){(float)window->width/2 - 115, (float)100};
    menu->menuMessagePos    = (Vector2){(float)window->width/2 - 140, (float)500};

    // Menu sound
    menu->musicStream       = LoadMusicStream("assets/evil-storm.wav");
    menu->clickSound        = LoadSound("assets/ball-tap.wav");
    PlayMusicStream(menu->musicStream);
}

void main_menu_handler(Menu_t *menu)
{
    if (IsKeyPressed(KEY_SPACE))
    {
        PlaySound(menu->clickSound);
        current_screen = GAME_SCREEN;
    }
    UpdateMusicStream(menu->musicStream);
    DrawTexture(menu->background, 0, 0, WHITE);
    DrawTexture(menu->background, menu->background.width, 0, WHITE);
    DrawTextEx(menu->font, "2D RUNNER", menu->gameNamePos, 60, .0f, WHITE);
    if (((int)seconds % 2) == 0)
        DrawTextEx(menu->font, "Press 'SPACE' to start", menu->menuMessagePos, 30, 5.0f, WHITE);
    else
        DrawTextEx(menu->font, "Press 'SPACE' to start", menu->menuMessagePos, 30, 5.0f, BLANK);
}

void setup_window(Window_t *window)
{
    initWindowInfos(window);
    InitAudioDevice();
    createWindow(window->width, window->height, window->framerate);
}

int main(int argc, char *argv[])
{
    // Not using argc nor argv yet
    (void)argc; (void)argv;
    Game_t      game;
    Window_t    window;

    setup_window(&window);
    setup_main_menu(&window, &game.mainMenu);
    while (!WindowShouldClose())
    {
        seconds += GetFrameTime();
        BeginDrawing();
            switch(current_screen)
            {
                case MENU_SCREEN:
                    main_menu_handler(&game.mainMenu);
                    break;
                case GAME_SCREEN:
                    ClearBackground(RAYWHITE);
                    break;
                default:
                    dprintf(2, "Invalid integer value.\n");
                    break;
            }
        EndDrawing();
    }
    menu_dtor(&game.mainMenu);
    CloseAudioDevice();
    CloseWindow();
    return EXIT_SUCCESS;
}