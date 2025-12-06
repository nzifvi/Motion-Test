//
// Created by benja on 28.11.2025.
//

#include "KinematicHandler.h"
#include <algorithm>

Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
Vector2 operator*(const float scalar, const Vector2& vec);
float   operator*(const Vector2& rhs, const Vector2& lhs);
float   magnitude(const Vector2& vec);
Vector2 constructUnitVector(const Vector2& vec);
float   angleBetween(const Vector2& v1, const Vector2& v2);
float   radToDeg(const float rad);
void    rotateCW(Vector2& vec);
void    rotateACW(Vector2& vec);

KinematicHandler::KinematicHandler(const float mass, const float kineticEnergy, const float maxVelocity):
ptrPosition(std::make_shared<Vector2>(Vector2{0, 0})),
ptrVelocity(std::make_shared<Vector2>(Vector2{0, 0})),
ptrAcceleration(std::make_shared<Vector2>(Vector2{0, 0})),
mass(mass), kineticEnergy(kineticEnergy), maxVelocity(maxVelocity){}

KinematicHandler::KinematicHandler(const float initialXOrdinate, const float initialYOrdinate, const float mass, const float kineticEnergy, const float maxVelocity):
ptrPosition(std::make_shared<Vector2>(Vector2{initialXOrdinate, initialYOrdinate})),
ptrVelocity(std::make_shared<Vector2>(Vector2{0, 0})),
ptrAcceleration(std::make_shared<Vector2>(Vector2{0, 0})),
mass(mass), kineticEnergy(kineticEnergy), maxVelocity(maxVelocity){}


KinematicHandler::KinematicHandler(std::shared_ptr<Vector2> acc, const float xVelocity, const float yVelocity, const float initialXOrdinate, const float initialYOrdinate, const float mass, const float kineticEnergy, const float maxVelocity):
ptrPosition(std::make_shared<Vector2>(Vector2(initialXOrdinate, initialYOrdinate))),
ptrVelocity(std::make_shared<Vector2>(Vector2(xVelocity, yVelocity))),
ptrAcceleration(acc),
mass(mass), kineticEnergy(kineticEnergy), maxVelocity(maxVelocity) {}

KinematicHandler::~KinematicHandler() {

}

void KinematicHandler::update() {
    if (ptrAcceleration->x == 0.0f) {
        if (ptrVelocity->x > 0.0f) {
            ptrVelocity->x -= std::min(ptrVelocity->x, HORIZONTAL_RESISTIVE_FORCE);
        }else if (ptrVelocity->x < 0.0f) {
            ptrVelocity->x += std::min(-ptrVelocity->x, HORIZONTAL_RESISTIVE_FORCE);
        }
    }else {
        ptrVelocity->x += ptrAcceleration->x;
    }

    if (ptrAcceleration->y == 0.0f) {
        if (ptrVelocity->y > 0.0f) {
            ptrVelocity->y -= std::min(ptrVelocity->y, VERTICAL_RESISTIVE_FORCE);
        }else if (ptrVelocity->y < 0.0f) {
            ptrVelocity->y += std::min(-ptrVelocity->y, VERTICAL_RESISTIVE_FORCE);
        }
    }else {
        ptrVelocity->y += ptrAcceleration->y;
    }

    ptrPosition->x += ptrVelocity->x + (ptrAcceleration->x)/2;
    ptrPosition->y += ptrVelocity->y + (ptrAcceleration->y)/2;

    ptrVelocity->x = std::clamp(ptrVelocity->x, -maxVelocity, maxVelocity);
    ptrVelocity->y = std::clamp(ptrVelocity->y, -maxVelocity, maxVelocity);

    updateKE();
}

void KinematicHandler::deflect(const Vector2& vec) {
    constexpr float velocityLossFactor = 0.90;
    Vector2 unitVecO                     = constructUnitVector(vec);
    Vector2 unitVecV                     = constructUnitVector(*ptrVelocity);
    float temp = unitVecO.x;
    if (ptrVelocity->x < 0 || ptrVelocity->y < 0) {// rotate 90 deg anti-clockwise
        unitVecO.x = unitVecO.y;
        unitVecO.y = temp;
    }else { // rotate 90 deg clockwise
        unitVecO.x = -unitVecO.y;
        unitVecO.y = temp;
    }

    if (ptrVelocity->x > 0 && ptrVelocity->y > 0) {
        rotateACW(unitVecO);
    }else if (ptrVelocity->x < 0 && ptrVelocity->y < 0) {
        rotateCW(unitVecO);
    }else {
        rotateCW(unitVecO);
        rotateCW(unitVecO);
    }

    Vector2 rotationalVector(0, 0);
    rotationalVector = unitVecV - 2*((unitVecV * unitVecO)*unitVecO);
    ptrVelocity->x = velocityLossFactor * rotationalVector.x * magnitude(*ptrVelocity);
    ptrVelocity->y = velocityLossFactor * rotationalVector.y * magnitude(*ptrVelocity);
}

void KinematicHandler::updateKE() {
    const float velocityMagnitude = std::sqrt((getXVelocity() * getXVelocity()) + (getYVelocity() * getYVelocity()));
    const float newKineticEnergy = (mass*velocityMagnitude)/2;
    kineticEnergy = static_cast<float>(KE_AMPLIFIER) * (kineticEnergy + (newKineticEnergy - kineticEnergy));
}

float KinematicHandler::getMass() const {
    return mass;
}

float KinematicHandler::getMaxVelocity() const {
    return maxVelocity;
}

float KinematicHandler::getXAcceleration() const {
    return ptrAcceleration->x;
}

float KinematicHandler::getYAcceleration() const {
    return ptrAcceleration->y;
}

float KinematicHandler::getXVelocity() const {
    return ptrVelocity->x;
}

float KinematicHandler::getYVelocity() const {
    return ptrVelocity->y;
}

float KinematicHandler::getXPos() const {
    return ptrPosition->x;
}

float KinematicHandler::getYPos() const {
    return ptrPosition->y;
}

float KinematicHandler::getKE() const {
    return kineticEnergy;
}

std::shared_ptr<Vector2> KinematicHandler::getAcceleration() const {
    return ptrAcceleration;
}

std::shared_ptr<Vector2> KinematicHandler::getVelocity() const {
    return ptrVelocity;
}

std::shared_ptr<Vector2> KinematicHandler::getPosition() const {
    return ptrPosition;
}


void KinematicHandler::setXAcceleration(const float acceleration) const {
    ptrAcceleration->x = acceleration;
}

void KinematicHandler::setYAcceleration(const float acceleration) const {
    ptrAcceleration->y = acceleration;
}

void KinematicHandler::updateXPos() const{
    ptrVelocity->x = ptrVelocity->x + ptrAcceleration->x;
    ptrPosition->x = ptrPosition->x + (ptrVelocity->x * 1) + (ptrAcceleration->x)/2;
}

void KinematicHandler::updateXPos(const float acceleration) const {
    ptrVelocity->x = ptrVelocity->x + acceleration;
    ptrPosition->x = ptrPosition->x + (ptrVelocity->x * 1) + (acceleration)/2;
}

void KinematicHandler::updateYPos() const {
    ptrVelocity->y = ptrVelocity->y + ptrAcceleration->y;
    ptrPosition->y = ptrPosition->y + (ptrVelocity->y * 1) + (ptrAcceleration->y)/2;
}

void KinematicHandler::updateYPos(const float acceleration) const {
    ptrVelocity->y = ptrVelocity->y + acceleration;
    ptrPosition->y = ptrPosition->y + (ptrVelocity->y * 1) + (acceleration)/2;
}

void KinematicHandler::forceDisplacement(const float xDisplacement, const float yDisplacement) const {
    ptrPosition->x += xDisplacement;
    ptrPosition->y += yDisplacement;
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {
    return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs) {
    return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vector2 operator*(const float scalar, const Vector2& vec) {
    return Vector2(scalar * vec.x, scalar * vec.y);
}

float operator*(const Vector2& rhs, const Vector2& lhs) {
    return rhs.x * lhs.x + rhs.y * lhs.y;
}

float magnitude(const Vector2& vec) {
    return std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

Vector2 constructUnitVector(const Vector2& vec) {
    const float vecMagnitude = magnitude(vec);
    return Vector2(vec.x / vecMagnitude, vec.y / vecMagnitude);
}

float angleBetween(const Vector2& v1, const Vector2& v2) {
    return std::atan((v1*v2)/(magnitude(v1) * magnitude(v2)));
}

float radToDeg(const float rad) {
    return rad * 180 / M_PI;
}

void rotateCW(Vector2& vec) {
    const float temp = -vec.x;
    vec.x = vec.y;
    vec.y = temp;
}

void rotateACW(Vector2& vec) {
    const float temp = vec.x;
    vec.x = -vec.y;
    vec.y = temp;
}
