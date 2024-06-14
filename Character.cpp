#include "Character.h"
#include "raymath.h"

Character::Character(int screenWidth, int screenHeight)
{
    width = texture.width / maxFrames;
    heigth = texture.height;

    screenPos = {
        (float)screenWidth / 2.0f - (float)scale * (0.5f * (float)width),
        (float)screenHeight / 2.0f - (float)scale * (0.5f * (float)heigth)};
}

void Character::tick(float dt)
{
    Vector2 direction{};

    worldPosLastFrame = worldPos;

    sprint(IsKeyDown(KEY_LEFT_SHIFT));

    if (IsKeyDown(KEY_A))
    {
        direction.x -= 1.0;
    }
    if (IsKeyDown(KEY_D))
    {
        direction.x += 1.0;
    }
    if (IsKeyDown(KEY_W))
    {
        direction.y -= 1.0;
    }
    if (IsKeyDown(KEY_S))
    {
        direction.y += 1.0;
    }
    if (Vector2Length(direction) != 0.0)
    {
        // Set worldPos  += direction

        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));

        direction.x < 0.0f ? righLeft = -1.f : righLeft = 1.f;

        texture = LoadTexture("assets/characters/run.png");
    }
    else
    {
        texture = LoadTexture("assets/characters/main.png");
    }

    //
    runningTime += dt;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    Rectangle source{frame * (float)width, 0.0f, righLeft * (float)width, (float)heigth};
    Rectangle dest{screenPos.x, screenPos.y, scale * (float)width, scale * (float)heigth};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}
