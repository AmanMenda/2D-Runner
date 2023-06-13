/*
** EPITECH PROJECT, 2023
** 2D-Runner [WSL: Ubuntu-20.04]
** File description:
** runner
*/

#pragma once
#include "raylib.h"

typedef enum buttonState
{
    NORMAL,
    HOVER,
    PRESSED
} btnState;

typedef struct button
{
    Texture2D   sprite;
    bool        action;
    Sound       sound;
    btnState    state;
    float       frameHeight;
    Rectangle   baseRect;
    Rectangle   bounds;
} Button_t;