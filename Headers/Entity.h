//
// Created by benja on 01.12.2025.
//

#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "KinematicHandler.h"
#include "SheetAnimation.h"
#include <iostream>

enum class EntityType {
    BaseEntity,
    Enemy,
    Player,
    Prop,

};

class Entity {
private:
    std::shared_ptr<Texture2D> entityTexture = nullptr;;
    Rectangle        entityRectangle;
    KinematicHandler entityKinematicHandler;
    bool             isCollisionEnabled;
    bool             isAnimated;
    bool             isOffset;
    SheetAnim        entitySheet;
    int              totalFrames;

    int frameIndex = 0;
    float frameTime = 0.0f;
    float frameWidth;
    float frameHeight;
    Rectangle sourceRect = {0};
    float updateTime = 1.0f/786.0f;

public:
    virtual EntityType getType() const {
        return EntityType::BaseEntity;
    }
    // CONSTRUCTOR(S) AND DESTRUCTOR(S):
    Entity(const float initialXOrdinate, const float initialYOrdinate, Texture2D texture, const float rectHeight, const float rectWidth, const bool isCollisionEnabled, const int totalFrames, const bool isAnim);

    virtual ~Entity() = default;

    // NON-ENCAPSULATION FUNCTION MEMBER(S):
    virtual void update();

    // ENCAPSULATION FUNCTION MEMBER(S):
    Rectangle         getErect() const {return entityRectangle;}
    KinematicHandler& getKinematicHandler() {return entityKinematicHandler;}
    Texture2D         getTexture() const {return *entityTexture;}
    bool              getIsCollisionEnabled() const {return isCollisionEnabled;}
    SheetAnim&        getSheetAnim() {return entitySheet;}
    bool              getIsAnimated() const {return isAnimated;}
    Rectangle         getSheetSourceRect() const { return sourceRect;}


    void setRect(const Rectangle& rect) {entityRectangle = rect;}

    void updateTexture() {
       /* float frameWidth = entityTexture->width/totalFrames;
        float frameHeight = entityTexture->height/totalFrames;
        int frameIndex = 0;
        float frameTime = 0.0f;
        float updateTime = 1.0f/12.0f;*/

        /*if (isAnimated == true) {
            entitySheet.Alogic(entityKinematicHandler.getXVelocity(),isAnimated, frameWidth, frameHeight, frameIndex, frameTime, updateTime);
        }*/
        if (isAnimated == true) {
            frameTime += GetFrameTime();
            if (frameTime >= updateTime) {
                frameTime = 0.0f;
                frameIndex++;
                if (frameIndex >= totalFrames) {
                    frameIndex = 0;
                }
            }
        }
        int previousHorizontalDirection;
        if (entityKinematicHandler.getXAcceleration() < 0) {
            sourceRect.width = -frameWidth;
            previousHorizontalDirection = entityKinematicHandler.getXAcceleration();
        } else {
            sourceRect.width = frameWidth;
            previousHorizontalDirection = entityKinematicHandler.getXAcceleration();
        }
        if (entityKinematicHandler.getXAcceleration() == 0 && previousHorizontalDirection < 0) {
            sourceRect.width = -frameWidth;
        }

        sourceRect.x = frameIndex * frameWidth;
        sourceRect.y = 0.0f;
        sourceRect.height = frameHeight;

    }
};

inline Vector2 buildCollisionVector(const Rectangle& v, const Rectangle& o) {
    Vector2 collisionVector(0, 0);
    if (o.x >= v.x + v.width || o.x <= v.x) {
        collisionVector.y = o.height;
    } else if (o.y <= v.y || o.y >= v.y + v.height) {
        collisionVector.x = o.width;
    }
    return collisionVector;
}

#endif //ENTITY_H
