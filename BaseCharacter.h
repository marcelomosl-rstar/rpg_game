

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void sprint(bool isRunning) { isRunning ? speed = 16.0f : speed = 8.0f; }
    void undoMovement() { worldPos = worldPosLastFrame; }
    Rectangle getCollisionRec();
    virtual void tick(float dt);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }

protected:
    Texture2D texture{};
    Texture2D idle{};
    Texture2D run{};
    Vector2 screenPos{};
    Vector2 worldPos{};
    // Animation Vars
    float runningTime{};
    int frame{1};
    int animationFrame{1};
    int maxFrames{6};
    float updateTime{1.0f / 12.0f};
    float speed{8.0f};
    float righLeft{1.0};
    int width{};
    int heigth{};
    float scale{4.0f};
    Vector2 worldPosLastFrame{};
    Vector2 velocity{};

private:
    bool alive{true};
};

#endif