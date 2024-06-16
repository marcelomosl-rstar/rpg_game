
#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int screenWidth, int screenHeight, Texture2D idle_tex, Texture2D run_tex);
    virtual void tick(float dt) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
    float getHealth() const { return health; }
    void takeDamage(float damage);

private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("assets/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health{100.f};
};

#endif