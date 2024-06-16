#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex)
{

    worldPos = pos;
    texture = idle_tex;
    idle = idle_tex;
    run = run_tex;
    width = texture.width / maxFrames;
    heigth = texture.height;
    speed = 2.0f;
}

Vector2 Enemy::getScreenPos()
{

    return Vector2{
        Vector2Subtract(worldPos, target->getWorldPos())};
}

void Enemy::tick(float dt)
{
    if (!getAlive())
        return;

    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());

    if (Vector2Length(velocity) < enemyRadius)
        velocity = {};

    texture = LoadTexture("assets/goblin_run.png");
    BaseCharacter::tick(dt);

    if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * dt);
    }
}
