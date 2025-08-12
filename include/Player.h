// src/Player.h
#pragma once
#include "raylib.h"

class Player {
private:
    // compile-time defaults , hope it works george dont blame me 
    static constexpr float   DEFAULT_HEALTH = 10.0f;
    static constexpr float   DEFAULT_ATTACK = 2.0f;
    static constexpr float   DEFAULT_MANA   = 2.0f;
    static constexpr Vector2 DEFAULT_SPEED  = { 10.0f, 10.0f };
    static constexpr float DEFAULT_JUMP = -15.0f;

    // runtime state
    float   health;
    float   attackDamage;
    float   mana;
    Vector2 speed;
    Vector2 position;
    float jump;

    public:
    Player();

    void  updateHealth(float amount);
    float getHealth() const;

    void  updateAttackDamage(float amount);
    float getAttackDamage() const;

    void  updateMana(float amount);
    float getMana() const;

    void    updateSpeed(Vector2 delta);
    Vector2 getSpeed() const;

    void    updatePosition();
    Vector2 getPosition() const;
};
