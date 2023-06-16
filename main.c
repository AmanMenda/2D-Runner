#include <stdlib.h>
#include "runner.h"

int current_screen = MENU_SCREEN;
float seconds = .0f;

/**
 * TODO: Refaire cette fonction avec des rects a la place
*/
// void load_layers(Texture2D (*layers)[], Vector2 (*layers_pos)[])
// {
//     (*layers)[0] = LoadTexture("assets/png/Layer1.png");
//     (*layers)[1] = LoadTexture("assets/png/Layer2.png");
//     (*layers)[2] = LoadTexture("assets/png/Layer3.png");
//     (*layers)[3] = LoadTexture("assets/png/Layer4.png");
//     (*layers)[4] = LoadTexture("assets/png/Layer5.png");
//     (*layers)[5] = LoadTexture("assets/png/Layer6.png");

//     (*layers_pos)[0] = (Vector2){0.0f, 0};
//     (*layers_pos)[1] = (Vector2){20.0f, 60};
//     (*layers_pos)[2] = (Vector2){30.0f, 100};
//     (*layers_pos)[3] = (Vector2){40.0f, 140};
//     (*layers_pos)[4] = (Vector2){50.0f, 160};
//     (*layers_pos)[5] = (Vector2){60.0f, 200};
// }


// void draw_game_background(Game_t *game)
// {
//     for (int i = 0; i < 6; i++)
//     {
//         DrawTextureEx((game->layers)[i], (game->layers_pos)[i], 0.0f, 0.0f, WHITE);
//     }
// }

void layers_dtor(Texture2D (*layers)[6])
{
    for (int i = 0; i < 6; i++)
        UnloadTexture((*layers)[i]);
}

void init_game_background(Window_t *window, Game_t *game)
{
    game->background = LoadTexture("assets/png/ResizedReference.png");
    game->backgroundRect = (Rectangle){ 0, 0, game->background.width, game->background.height };
    game->backgroundRectOffset = (Rectangle){ window->width, 0, game->background.width, game->background.height };
}

void parallax_effect(Game_t *game)
{
    game->backgroundRect.x -= 2;
    game->backgroundRectOffset.x -= 2;
    if (game->backgroundRect.x <= -game->background.width)
        game->backgroundRect.x = game->background.width;
    if (game->backgroundRectOffset.x <= -game->background.width)
        game->backgroundRectOffset.x = game->background.width;
    DrawTextureRec(game->background, game->backgroundRect, (Vector2){ 0, 0 }, WHITE);
    DrawTextureRec(game->background, game->backgroundRectOffset, (Vector2){ 0, 0 }, WHITE);
}

int main(int argc, char *argv[])
{
    // Not using argc nor argv yet
    (void)argc; (void)argv;
    Game_t      game;
    Window_t    window;

    setup_window(&window);
    setup_main_menu(&window, &game.mainMenu);
    init_game_background(&window, &game);

    while (!WindowShouldClose())
    {
        seconds += GetFrameTime();
        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch(current_screen)
            {
                case MENU_SCREEN:
                    main_menu_handler(&game.mainMenu);
                    break;
                case GAME_SCREEN:
                    parallax_effect(&game);
                    break;
                default:
                    dprintf(2, "Invalid integer value.\n");
                    break;
            }
        EndDrawing();
    }
    menu_dtor(&game.mainMenu);
    UnloadTexture(game.background);
    CloseAudioDevice();
    CloseWindow();
    return EXIT_SUCCESS;
}