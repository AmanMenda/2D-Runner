#include "../runner.h"

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