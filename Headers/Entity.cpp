//
// Created by benja on 01.12.2025.
//

#include "Entity.h"

Entity::Entity(const float initialXOrdinate, const float initialYOrdinate, const float mass, const float maxVelocity, Texture2D texture, const float rectHeight, const float rectWidth, const bool isCollisionEnabled):
entityKinematicHandler(initialXOrdinate, initialYOrdinate, mass, 0, maxVelocity),
entityRectangle(Rectangle(initialXOrdinate, initialYOrdinate, rectWidth, rectHeight)),
entityTexture(texture),
isCollisionEnabled(isCollisionEnabled){

}

void Entity::update() {
    entityKinematicHandler.update();
    entityRectangle.x = entityKinematicHandler.getXPos();
    entityRectangle.y = entityKinematicHandler.getYPos();
}
