#include "window.h"

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

void setup_window(Window_t *window)
{
    initWindowInfos(window);
    InitAudioDevice();
    createWindow(window->width, window->height, window->framerate);
}