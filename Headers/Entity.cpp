//
// Created by benja on 01.12.2025.
//

#include "Entity.h"

Entity::Entity(const float initialXOrdinate, const float initialYOrdinate, Texture2D texture, const float rectHeight, const float rectWidth, const bool isCollisionEnabled, const int totalFrames, const bool isAnim):
entityKinematicHandler(initialXOrdinate, initialYOrdinate),
entityRectangle(Rectangle(initialXOrdinate, initialYOrdinate, rectWidth, rectHeight)),
entityTexture(std::make_shared<Texture2D>(texture)),
isCollisionEnabled(isCollisionEnabled),
totalFrames(totalFrames),
isAnimated(isAnim){
    frameWidth = entityTexture->width / totalFrames;
    frameHeight = entityTexture->height;
    sourceRect = {0.0f, 0.0f, frameWidth, frameHeight};

}

void Entity::update() {
    entityKinematicHandler.update();
    entityRectangle.x = entityKinematicHandler.getXPos();
    entityRectangle.y = entityKinematicHandler.getYPos();
    updateTexture();
}