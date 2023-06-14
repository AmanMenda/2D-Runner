#include "raylib.h"

static Texture2D extractTextureFromImage(char const *imagePath)
{
    Image image         = LoadImage(imagePath);
    Texture2D texture   = LoadTextureFromImage(image);

    UnloadImage(image);
    return texture;
}
