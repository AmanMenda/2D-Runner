#include "../Headers/runner.h"

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
    DrawTextEx(menu->font, "2D RUNNER", menu->gameNamePos, 60, .0f, WHITE);
    if (((int)seconds % 2) == 0)
        DrawTextEx(menu->font, "Press 'SPACE' to start", menu->menuMessagePos, 30, 5.0f, WHITE);
    else
        DrawTextEx(menu->font, "Press 'SPACE' to start", menu->menuMessagePos, 30, 5.0f, BLANK);
}
