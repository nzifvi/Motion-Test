//
// Created by benja on 07.12.2025.
//

#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "raylib.h"
#include "KinematicHandler.h"
#include "SheetAnimation.h"
#include <iostream>


class Enemy : public Entity{
    private:
    const Entity* playerTarget;
    public:
    EntityType getType() const override {
        return EntityType::Enemy;
    }
    Enemy(const float initialXOrdinate, const float initialYOrdinate, Texture2D texture, const float rectHeight, const float rectWidth, const bool isCollisionEnabled, const int totalFrames, const bool isAnim, const Entity& player);


    void update() override;
    void honing();

};



#endif //ENEMY_H
