//
// Created by benja on 07.12.2025.
//

#include "Enemy.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

Enemy::Enemy(const float initialXOrdinate, const float initialYOrdinate, Texture2D texture, const float rectHeight, const float rectWidth, const bool isCollisionEnabled, const int totalFrames, const bool isAnim, const Entity& player)
: Entity(initialXOrdinate, initialYOrdinate, texture, rectHeight, rectWidth, isCollisionEnabled, totalFrames, isAnim),
    playerTarget(&player)
{}

void Enemy::update(){
  //  honing();
    Entity::update();
}

/*void Enemy::honing() {
    if (!playerTarget) return;

    Vector2 enemyPos = *this->getKinematicHandler().getPosition();
    Vector2 playerPos = *playerTarget->getKinematicHandler().getPosition();

    Vector2 direction = Vector2Subtract(playerPos, enemyPos);

    direction = Vector2Normalize(direction);
    const float ENEMY_ACCELERATION = 150.0f;

    Vector2 velocity = Vector2Scale(direction, ENEMY_ACCELERATION);

    this->getKinematicHandler().setXAcceleration(direction.x * ENEMY_ACCELERATION);
    this->getKinematicHandler().setYAcceleration(direction.y * ENEMY_ACCELERATION);


}*/

