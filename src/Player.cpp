// src/Player.cpp
#include "../include/Player.h"
#include "../include/constants.h"
#include "raylib.h"
#include "raymath.h"

Player::Player()
    : health(DEFAULT_HEALTH), attackDamage(DEFAULT_ATTACK), mana(DEFAULT_MANA),
      speed(DEFAULT_SPEED), jump(DEFAULT_JUMP),
      position(cfg::player::START_POS) {}

void Player::updateHealth(float amount) {
  health += amount;
  if (health < 0.0f)
    health = 0.0f;
}

float Player::getHealth() const { return health; }

void Player::updateAttackDamage(float amount) { attackDamage += amount; }

float Player::getAttackDamage() const { return attackDamage; }

void Player::updateMana(float amount) {
  mana += amount;
  if (mana < 0.0f)
    mana = 0.0f;
}

float Player::getMana() const { return mana; }

void Player::updateSpeed(Vector2 delta) {
  speed = {speed.x + delta.x, speed.y + delta.y};
}

Vector2 Player::getSpeed() const { return speed; }

void Player::updatePosition() {
  if (IsKeyDown(KEY_D))
    position.x += speed.x;
  if (IsKeyDown(KEY_A))
    position.x -= speed.x;
  if (IsKeyDown(KEY_W))
    position.y -= speed.y;
  if (IsKeyDown(KEY_S))
    position.y += speed.y;
}

Vector2 Player::getPosition() const { return position; }
