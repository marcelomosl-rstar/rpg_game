#include "Character.h"
#include "raymath.h"

Character::Character(int screenWidth, int screenHeight, Texture2D idle_tex, Texture2D run_tex) : windowWidth(screenWidth), windowHeight(screenHeight)
{
    texture = idle_tex;
    run = run_tex;
    idle = idle_tex;
    width = texture.width / maxFrames;
    heigth = texture.height;
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        (float)windowWidth / 2.0f - (float)scale * (0.5f * (float)width),
        (float)windowHeight / 2.0f - (float)scale * (0.5f * (float)heigth)};
}

void Character::tick(float dt)
{

    if (!getAlive())
    {
        return;
    }

    sprint(IsKeyDown(KEY_LEFT_SHIFT));

    if (IsKeyDown(KEY_A))
    {
        velocity.x -= 1.0;
    }
    if (IsKeyDown(KEY_D))
    {
        velocity.x += 1.0;
    }
    if (IsKeyDown(KEY_W))
    {
        velocity.y -= 1.0;
    }
    if (IsKeyDown(KEY_S))
    {
        velocity.y += 1.0;
    }

    BaseCharacter::tick(dt);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};

    if (righLeft > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};

        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.0f : 0.0f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};

        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.0f : 0.0f;
    }

    // Draw the sword

    Rectangle source{0.0f, 0.0f, (float)weapon.width * righLeft, (float)weapon.height};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, (weapon.width * scale), (weapon.height * scale)};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
}

void Character::takeDamage(float damage)
{

    health -= damage;

    if (health <= 0.f)
    {
        setAlive(false);
    }
}
