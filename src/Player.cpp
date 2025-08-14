// src/Player.cpp
#include "Player.h"
#include "constants.h"
#include "raylib.h"
#include "raymath.h"

Player::Player(): 
    health(DEFAULT_HEALTH),
    attackDamage(DEFAULT_ATTACK),
    mana(DEFAULT_MANA),
    velocity(DEFAULT_VELOCITY),
    jump(DEFAULT_JUMP),
    speed(DEFAULT_SPEED),
    onGround(DEFAULT_ONGROUND),
    position(cfg::player::START_POS) {}

void Player::updateHealth(float amount) {
    health += amount;
    if (health < 0.0f) 
        health = 0.0f;
}

float Player::getHealth() const { 
    return health; }

void Player::updateAttackDamage(float amount) {
    attackDamage += amount;
}

float Player::getAttackDamage() const { 
    return attackDamage; }

void Player::updateMana(float amount) {
    mana += amount;
    if (mana < 0.0f) mana = 0.0f;
}

float Player::getMana() const { 
    return mana; }

void Player::updateVelocity(Vector2 delta) {
    velocity = { velocity.x + delta.x, velocity.y + delta.y };
}

Vector2 Player::getVelocity() const { 
    return velocity; }

void Player::updateSpeed(float amount){
    speed+=amount;
}

float Player::getSpeed() const{
    return speed;
}

void Player::updatePosition() {
    
    if (IsKeyPressed(KEY_R)) {
      position.x = cfg::player::START_POS.x;
      position.y = cfg::player::START_POS.y;
      velocity = {0,0};
      onGround =true;
    }
    //player gravity
    // if(!onGround){
    //     velocity.y+=cfg::world::GRAVITY;
    //     position.y+=velocity.y;

    // }
    //horizontal movement
    if (IsKeyDown(KEY_D)) velocity.x= speed;
    else if (IsKeyDown(KEY_A)) velocity.x = -speed;
    else{velocity.x=0;}

    //this is for jump I guess
    if (onGround&& (IsKeyDown(KEY_W)||IsKeyDown(KEY_SPACE))){
        velocity.y = jump;
        onGround=false;
    }
    //applying gravity
    velocity.y+=cfg::world::GRAVITY;

    position.x+=velocity.x;
    position.y+=velocity.y;

    onGround=false;
    // ground  colission
    if (position.y + cfg::player::SIZE >= cfg::world::GROUND_Y) {
        position.y = cfg::world::GROUND_Y - cfg::player::SIZE;
        velocity.y = 0.0;
        onGround=true;
    }

}

// void Player::updatePosition(bool platform){

// }

Vector2 Player::getPosition() const { 
    return position; }

void Player::updateJump(float amount){
    jump+=amount;
}
float Player::getJump() const{
    return jump;
}

