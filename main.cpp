#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int width, int height);
    void tick(float dt);
    void sprint(bool isRunning) { isRunning ? speed = 16.0f : speed = 8.0f; }

private:
    Texture2D texture{LoadTexture("assets/characters/player.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    // Animation Vars
    float runningTime{};
    int frame{1};
    int animationFrame{1};
    const int maxFrames{6};
    const float updateTime{1.0f / 12.0f};
    float speed{8.0f};
    float righLeft{1.0};
};

void Character::setScreenPos(int width, int height)
{
    screenPos.x = (float)width / 2.0f - 4.0f * (0.5 * (float)texture.width / 6);
    screenPos.y = (float)height / 2.0f - 4.0f * (0.5 * (float)texture.height / 10);
};

void Character::tick(float dt)
{
    Vector2 direction{};

    if (IsKeyDown(KEY_F))
    {
        animationFrame = 7;
    }

    if (IsKeyDown(KEY_A))
    {
        direction.x -= 1.0;
        animationFrame = 4;
    }
    if (IsKeyDown(KEY_D))
    {
        direction.x += 1.0;
        animationFrame = 4;
    }
    if (IsKeyDown(KEY_W))
    {
        direction.y -= 1.0;
        animationFrame = 5;
    }
    if (IsKeyDown(KEY_S))
    {
        direction.y += 1.0;
        animationFrame = 3;
    }
    if (Vector2Length(direction) != 0.0)
    {
        // Set worldPos  += direction

        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));

        direction.x < 0.0f ? righLeft = -1.f : righLeft = 1.f;
    }
    else
    {
        animationFrame = 0;
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

    Rectangle source{frame * (float)texture.width / 6, (float)animationFrame * (float)texture.height / 10, righLeft * (float)texture.width / 6.f, (float)texture.height / 10};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * (float)texture.width / 6, 4.0f * (float)texture.height / 10};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

int main()
{

    const int windowWidth(1800);
    const int windowHeight(900);

    InitWindow(windowWidth, windowHeight, "RPG Game");

    Texture2D map = LoadTexture("assets/game_map.png");

    Vector2 mapPos{0.0, 0.0};

    Character knight;
    knight.setScreenPos(windowWidth, windowHeight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLUE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0, 8.0, WHITE);
        knight.tick(GetFrameTime());

        EndDrawing();
    }

    UnloadTexture(map);

    CloseWindow();
}