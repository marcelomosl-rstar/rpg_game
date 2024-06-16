#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
}

Rectangle BaseCharacter::getCollisionRec()
{

    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        heigth * scale};
}

void BaseCharacter::tick(float dt)
{

    worldPosLastFrame = worldPos;

    runningTime += dt;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // Set worldPos  += direction

        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

        velocity.x < 0.0f ? righLeft = -1.f : righLeft = 1.f;

        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    Rectangle source{frame * (float)width, 0.0f, righLeft * (float)width, (float)heigth};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * (float)width, scale * (float)heigth};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}