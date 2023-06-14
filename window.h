/*
** EPITECH PROJECT, 2023
** 2D-Runner [WSL: Ubuntu-20.04]
** File description:
** window
*/

#pragma once
#include "raylib.h"

typedef struct window
{
    int width;
    int height;
    int framerate;
} Window_t;

void createWindow(const int screenWidth, const int screenheight, const int framerate);

void initWindowInfos(Window_t *window);

void setup_window(Window_t *window);