#include <stdlib.h>
#include "runner.h"

int current_screen = MENU_SCREEN;
float seconds = .0f;

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