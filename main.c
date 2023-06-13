/*
** EPITECH PROJECT, 2023
** 2D-Runner [WSL: Ubuntu-20.04]
** File description:
** main
*/

#include "raylib.h"
#include <stdlib.h>
#include "window.h"

void createWindow(const int screenWidth, const int screenHeigth, const int framerate)
{
    InitWindow(screenWidth, screenHeigth, "My 2D Runner");
    SetTargetFPS(framerate);
}

void initWindowInfos(Window_t *window)
{
    window->framerate   = 60;
    window->width       = 1920;
    window->heigth      = 1080;
}

int main(int argc, char *argv[])
{
    // Not using argc nor argv yet
    (void)argc; (void)argv;

    Window_t window;
    
    initWindowInfos(&window);
    createWindow(window.width, window.heigth, window.framerate);

    Image menuBackgroundSprite = LoadImage("assets/menu_bg.png"); // On RAM
    Texture2D menuBackgroundTexture = LoadTextureFromImage(menuBackgroundSprite); // On VRAM
    UnloadImage(menuBackgroundSprite); // free RAM

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(menuBackgroundTexture, (window.width/2 - menuBackgroundTexture.width/2), (window.heigth/2 - menuBackgroundTexture.height/2), WHITE);
        EndDrawing();
    }
    UnloadTexture(menuBackgroundTexture);
    CloseWindow();
    return EXIT_SUCCESS;
}