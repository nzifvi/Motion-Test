//
// Created by benja on 01.12.2025.
//

#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "KinematicHandler.h"
#include <iostream>

class Entity {
private:
    Texture2D        entityTexture;
    Rectangle        entityRectangle;
    KinematicHandler entityKinematicHandler;
    bool             isCollisionEnabled;

public:
    Entity(const float initialXOrdinate, const float initialYOrdinate, const float mass, const float maxVelocity, Texture2D texture, const float rectHeight, const float rectWidth, const bool isCollisionEnabled);

    ~Entity() = default;

    Rectangle         getRect() const {return entityRectangle;}
    KinematicHandler& getKinematicHandler() {return entityKinematicHandler;}
    Texture2D         getTexture() const {return entityTexture;}
    bool              getIsCollisionEnabled() const {return isCollisionEnabled;}

    void update();

    void setRect(const Rectangle& rect) {entityRectangle = rect;}
    void setTexture(const Texture& texture) {entityTexture = texture;}
};

inline bool boundCheck(Entity e1, Entity e2);
inline Vector2 buildCollisionVector(const Vector2& v, const Vector2& o);

inline bool boundCheck(Entity e1, Entity e2) {
    const bool xOverlap = e1.getKinematicHandler().getXPos() < e2.getKinematicHandler().getXPos() + e2.getRect().width &&
                          e1.getKinematicHandler().getXPos() + e1.getRect().width > e2.getKinematicHandler().getXPos();
    // HORIZONTAL COLLISION DETECTED
    const bool yOverlap = e1.getKinematicHandler().getYPos() < e2.getKinematicHandler().getYPos() + e2.getRect().height &&
                          e1.getKinematicHandler().getYPos() + e1.getRect().height < e2.getKinematicHandler().getXPos();
    // VERTICAL COLLISION NOT DETECTED
    if (xOverlap && !yOverlap) {
        std::cout << "horizontal collision detected\n";
    }
    else if (yOverlap && !xOverlap) {
        std::cout << "vertical collision detected\n";
    }
    else if (xOverlap && yOverlap) {
        std::cout << "horizontal and vertical collision detected\n";
    }
    return xOverlap && yOverlap;
}

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
