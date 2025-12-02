//
// Created by benja on 01.12.2025.
//

#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "Particle.h"

class Entity {
private:
    Texture2D* ptrEntityTexure;
    Particle*  ptrEntityParticle;

public:
    Entity(Texture2D entitiyTexture);
};



#endif //ENTITY_H
