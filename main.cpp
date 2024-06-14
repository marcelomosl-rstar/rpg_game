#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main()
{

    const int windowWidth(384);
    const int windowHeight(384);

    InitWindow(windowWidth, windowHeight, "RPG Game");

    Texture2D map = LoadTexture("assets/game_map.png");

    Vector2 mapPos{0.0, 0.0};
    float mapScale{4.0f};

    Character knight{windowWidth, windowHeight};
    Prop rock{
        Vector2{500.0f, 320.0f}, LoadTexture("assets/rock.png")};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GREEN);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);

        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        rock.Render(knight.getWorldPos());

        knight.tick(GetFrameTime());

        if (
            knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        EndDrawing();
    }

    UnloadTexture(map);

    CloseWindow();
}