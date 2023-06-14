/*
** EPITECH PROJECT, 2023
** 2D-Runner [WSL: Ubuntu-20.04]
** File description:
** runner
*/

#pragma once
    #include "raylib.h"

    #define NUM_FRAMES  3 // Number of frames (rectangles) for the button sprite texture

    extern int current_screen;

enum screen
{
    MENU_SCREEN,
    GAME_SCREEN,
    SETTINGS_SCREEN,
    HTP_SCREEN // How-to-play
};

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