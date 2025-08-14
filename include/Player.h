// src/Player.h
#pragma once
#include "raylib.h"

class Player {
private:
    // compile-time defaults , hope it works george dont blame me 
    static constexpr float   DEFAULT_HEALTH = 10.0f;
    static constexpr float   DEFAULT_ATTACK = 2.0f;
    static constexpr float   DEFAULT_MANA   = 2.0f;
    static constexpr Vector2 DEFAULT_VELOCITY  = { 0.0f, 0.0f };
    static constexpr float DEFAULT_JUMP = -15.0f;
    static constexpr float DEFAULT_SPEED = 5.0f;
    static constexpr bool DEFAULT_ONGROUND= true;
  
    // runtime state
    float   health;
    float   attackDamage;
    float   mana;
    Vector2 velocity;
    Vector2 position;
    float jump;
    float speed;
    bool onGround;

    public:
    Player();

    void  updateHealth(float amount);
    float getHealth() const;

    void  updateAttackDamage(float amount);
    float getAttackDamage() const;

    void  updateMana(float amount);
    float getMana() const;

    void updateVelocity(Vector2 delta);
    Vector2 getVelocity() const;

    void updateSpeed(float amount);
    float getSpeed() const;

    void updatePosition();
    Vector2 getPosition() const;
    void updatePosition(bool platform);

    void updateJump(float amount);
    float getJump() const;


};
