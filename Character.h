#include "raylib.h"

class Character
{
public:
    Character(int screenWidth, int screenHeight);
    Vector2 getWorldPos() { return worldPos; }
    void tick(float dt);
    void sprint(bool isRunning) { isRunning ? speed = 16.0f : speed = 8.0f; }
    void undoMovement() { worldPos = worldPosLastFrame; }

private:
    Texture2D texture{LoadTexture("assets/characters/main.png")};
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
};
