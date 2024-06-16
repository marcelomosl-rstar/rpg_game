#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{

    const int windowWidth(384);
    const int windowHeight(384);

    InitWindow(windowWidth, windowHeight, "RPG Game");

    Texture2D map = LoadTexture("assets/game_map.png");

    Vector2 mapPos{0.0, 0.0};
    float mapScale{4.0f};

    Character knight{windowWidth, windowHeight, LoadTexture("assets/characters/main.png"), LoadTexture("assets/characters/run.png")};

    Prop props[2]{
        {Vector2{600.0f, 300.0f}, LoadTexture("assets/rock.png")},
        {Vector2{800.0f, 500.0f}, LoadTexture("assets/log.png")}};

    Enemy goblin{
        Vector2{1000.0f, 300.0f},
        LoadTexture("assets/goblin_idle.png"),
        LoadTexture("assets/goblin_run.png")};

    Enemy slime{
        Vector2{1000.0f, 300.0f},
        LoadTexture("assets/characters/slime_idle.png"),
        LoadTexture("assets/characters/slime_run.png")};

    Enemy *enemies[]{
        &goblin,
        &slime};

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GREEN);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);

        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // draw the props
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if (!knight.getAlive())
        {
            DrawText("GAME OVER!", 55.f, 45.f, 40, RED);

            EndDrawing();

            continue;
        }
        else
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);

            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        // Draw the Character
        knight.tick(GetFrameTime());

        if (
            knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        for (auto prop : props)
        {

            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
                knight.undoMovement();
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }

    UnloadTexture(map);

    CloseWindow();
}
