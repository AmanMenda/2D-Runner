/*
** EPITECH PROJECT, 2023
** 2D-Runner [WSL: Ubuntu-20.04]
** File description:
** runner
*/

#pragma once
    #include "raylib.h"
    #include "window.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define NUM_FRAMES  3 // Number of frames (rectangles) for the button sprite texture

    extern int current_screen;
    extern float seconds;

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

typedef struct menu
{
    Font        font;
    Sound       clickSound;
    Music       musicStream;
    Vector2     gameNamePos;
    Vector2     menuMessagePos;
    Texture2D   background;
} Menu_t;

typedef struct game
{
    Menu_t mainMenu;
    Texture2D background;
    Rectangle backgroundRect;
    Rectangle backgroundRectOffset;
} Game_t;

void menu_dtor(Menu_t *menu);

void setup_main_menu(Window_t *window, Menu_t *menu);

void main_menu_handler(Menu_t *menu);