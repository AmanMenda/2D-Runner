/*
** EPITECH PROJECT, 2023
** 2D-Runner [WSL: Ubuntu-20.04]
** File description:
** main
*/

#include <stdlib.h>
#include "runner.h"
#include "window.h"

#define NUM_FRAMES  3 // Number of frames (rectangles) for the button sprite texture
enum screen
{
    MENU_SCREEN,
    GAME_SCREEN,
    SETTINGS_SCREEN,
    HTP_SCREEN // How-to-play
};

int current_screen = MENU_SCREEN;

void createWindow(const int screenWidth, const int screenheight, const int framerate)
{
    InitWindow(screenWidth, screenheight, "My 2D Runner");
    SetTargetFPS(framerate);
}

void initWindowInfos(Window_t *window)
{
    window->framerate   = 60;
    window->width       = 600;
    window->height      = 480;
}

Texture2D extractTextureFromImage(char const *imagePath)
{
    Image image         = LoadImage(imagePath);
    Texture2D texture   = LoadTextureFromImage(image);

    UnloadImage(image);
    return texture;
}

Button_t createButton(
    char const *buttonSprite,
    char const *buttonSound,
    Vector2 buttonPosition
    )
{
    Button_t button;

    button.sprite = LoadTexture(buttonSprite);
    button.sound  = LoadSound(buttonSound);
    button.frameHeight = (float)(button.sprite.height / NUM_FRAMES);
    button.baseRect = (Rectangle){0, 0, (float)button.sprite.width, button.frameHeight};
    button.bounds = (Rectangle){buttonPosition.x, buttonPosition.y, button.sprite.width, button.frameHeight};
    button.state = NORMAL;
    button.action = false;

    return button;
}

void buttonUpdateLiveState(Button_t *button, Vector2 cursorPos)
{
    if (CheckCollisionPointRec(cursorPos, button->bounds))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            button->state = PRESSED;
        }
        else
        {
            button->state = HOVER;
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            button->action = true;
    }
    else
    {
        button->state = NORMAL;
    }
}

void buttonSetRectAtCurrentState(Button_t *button)
{
    button->baseRect.y = button->frameHeight * button->state;
}

void buttonExecuteActionIfPressed(Button_t *button)
{
    if (button->action)
    {
        PlaySound(button->sound);
        current_screen = GAME_SCREEN;
    }
}

int main(int argc, char *argv[])
{
    // Not using argc nor argv yet
    (void)argc; (void)argv;

    // Game_t      game;
    Window_t    window;

    initWindowInfos(&window);
    InitAudioDevice();
    createWindow(window.width, window.height, window.framerate);
    Texture2D menuBackground = LoadTexture("assets/png/space.png");
    Shader backgroundShader = LoadShader(0, TextFormat("shaders/wave.fs", 330));

    int secondsLoc = GetShaderLocation(backgroundShader, "secondes");
    int freqXLoc = GetShaderLocation(backgroundShader, "freqX");
    int freqYLoc = GetShaderLocation(backgroundShader, "freqY");
    int ampXLoc = GetShaderLocation(backgroundShader, "ampX");
    int ampYLoc = GetShaderLocation(backgroundShader, "ampY");
    int speedXLoc = GetShaderLocation(backgroundShader, "speedX");
    int speedYLoc = GetShaderLocation(backgroundShader, "speedY");

    // Shader uniform values that can be updated at any time
    float freqX = 25.0f;
    float freqY = 25.0f;
    float ampX = 5.0f;
    float ampY = 5.0f;
    float speedX = 8.0f;
    float speedY = 8.0f;

    float screenSize[2] = { (float)GetScreenWidth(), (float)GetScreenHeight() };
    SetShaderValue(backgroundShader, GetShaderLocation(backgroundShader, "size"), &screenSize, SHADER_UNIFORM_VEC2);
    SetShaderValue(backgroundShader, freqXLoc, &freqX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(backgroundShader, freqYLoc, &freqY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(backgroundShader, ampXLoc, &ampX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(backgroundShader, ampYLoc, &ampY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(backgroundShader, speedXLoc, &speedX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(backgroundShader, speedYLoc, &speedY, SHADER_UNIFORM_FLOAT);
    float seconds = 0.0f;



    // Menu Text
    Font gameNameFont = LoadFont("assets/fonts/ShortBaby.ttf");
    Vector2 gameNamePosition = {(float)window.width/2 - 85, (float)50};
    Button_t shareButton = createButton(
        "assets/png/button.png",
        "assets/buttonfx.wav",
        (Vector2){100, 100}
    );

    Vector2 cursorPos;

    while (!WindowShouldClose())
    {
        seconds += GetFrameTime();
        SetShaderValue(backgroundShader, secondsLoc, &seconds, SHADER_UNIFORM_FLOAT);
        cursorPos = GetMousePosition();
        shareButton.action = false;

        buttonUpdateLiveState(&shareButton, cursorPos);
        buttonExecuteActionIfPressed(&shareButton);
        buttonSetRectAtCurrentState(&shareButton);


        BeginDrawing();
            ClearBackground(RAYWHITE);

            //Apply shader to everything between Begin and End
            BeginShaderMode(backgroundShader);
                DrawTexture(menuBackground, 0, 0, WHITE);
                DrawTexture(menuBackground, menuBackground.width, 0, WHITE);
            EndShaderMode();


            DrawTextureRec(
                shareButton.sprite,
                shareButton.baseRect,
                (Vector2){ shareButton.bounds.x, shareButton.bounds.y }, WHITE); // Draw button frame
            DrawTextEx(gameNameFont, "2D RUNNER", gameNamePosition, 30, .0f, WHITE);


        EndDrawing();
    }
    UnloadShader(backgroundShader);         // Unload shader
    UnloadTexture(menuBackground);       // Unload texture

    UnloadTexture(shareButton.sprite);  // Unload button texture
    UnloadSound(shareButton.sound);  // Unload sound

    CloseAudioDevice();
    CloseWindow();
    return EXIT_SUCCESS;
}