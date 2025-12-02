//
// Created by benja on 28.11.2025.
//

#include "Particle.h"
#include <cmath>
#include <algorithm>

Particle::Particle(const float mass, const float kineticEnergy, const float maxVelocity):
ptrPosition(std::make_shared<Vector2>(Vector2{0, 0})),
ptrVelocity(std::make_shared<Vector2>(Vector2{0, 0})),
ptrAcceleration(std::make_shared<Vector2>(Vector2{0, 0})),
mass(mass), kineticEnergy(kineticEnergy), maxVelocity(maxVelocity){}

Particle::Particle(const float initialXOrdinate, const float initialYOrdinate, const float mass, const float kineticEnergy, const float maxVelocity):
ptrPosition(std::make_shared<Vector2>(Vector2{initialXOrdinate, initialYOrdinate})),
ptrVelocity(std::make_shared<Vector2>(Vector2{0, 0})),
ptrAcceleration(std::make_shared<Vector2>(Vector2{0, 0})),
mass(mass), kineticEnergy(kineticEnergy), maxVelocity(maxVelocity){}


Particle::Particle(std::shared_ptr<Vector2> acc, const float xVelocity, const float yVelocity, const float initialXOrdinate, const float initialYOrdinate, const float mass, const float kineticEnergy, const float maxVelocity):
ptrPosition(std::make_shared<Vector2>(Vector2(initialXOrdinate, initialYOrdinate))),
ptrVelocity(std::make_shared<Vector2>(Vector2(xVelocity, yVelocity))),
ptrAcceleration(acc),
mass(mass), kineticEnergy(kineticEnergy), maxVelocity(maxVelocity) {}

Particle::~Particle() {

}

void Particle::update() {
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

void Particle::updateKE() {
    const float velocityMagnitude = std::sqrt((getXVelocity() * getXVelocity()) + (getYVelocity() * getYVelocity()));
    const float newKineticEnergy = (mass*velocityMagnitude)/2;
    kineticEnergy = static_cast<float>(KE_AMPLIFIER) * (kineticEnergy + (newKineticEnergy - kineticEnergy));
}

float Particle::getMass() const {
    return mass;
}

float Particle::getMaxVelocity() const {
    return maxVelocity;
}

float Particle::getXAcceleration() const {
    return ptrAcceleration->x;
}

float Particle::getYAcceleration() const {
    return ptrAcceleration->y;
}

float Particle::getXVelocity() const {
    return ptrVelocity->x;
}

float Particle::getYVelocity() const {
    return ptrVelocity->y;
}

float Particle::getXPos() const {
    return ptrPosition->x;
}

float Particle::getYPos() const {
    return ptrPosition->y;
}

float Particle::getKE() const {
    return kineticEnergy;
}

std::shared_ptr<Vector2> Particle::getAcceleration() const {
    return ptrAcceleration;
}

std::shared_ptr<Vector2> Particle::getVelocity() const {
    return ptrVelocity;
}

std::shared_ptr<Vector2> Particle::getPosition() const {
    return ptrPosition;
}


void Particle::setXAcceleration(const float acceleration) const {
    ptrAcceleration->x = acceleration;
}

void Particle::setYAcceleration(const float acceleration) const {
    ptrAcceleration->y = acceleration;
}

void Particle::updateXPos() const{
    ptrVelocity->x = ptrVelocity->x + ptrAcceleration->x;
    ptrPosition->x = ptrPosition->x + (ptrVelocity->x * 1) + (ptrAcceleration->x)/2;
}

void Particle::updateXPos(const float acceleration) const {
    ptrVelocity->x = ptrVelocity->x + acceleration;
    ptrPosition->x = ptrPosition->x + (ptrVelocity->x * 1) + (acceleration)/2;
}

void Particle::updateYPos() const {
    ptrVelocity->y = ptrVelocity->y + ptrAcceleration->y;
    ptrPosition->y = ptrPosition->y + (ptrVelocity->y * 1) + (ptrAcceleration->y)/2;
}

void Particle::updateYPos(const float acceleration) const {
    ptrVelocity->y = ptrVelocity->y + acceleration;
    ptrPosition->y = ptrPosition->y + (ptrVelocity->y * 1) + (acceleration)/2;
}

void Particle::forceDisplacement(const float xDisplacement, const float yDisplacement) const {
    ptrPosition->x += xDisplacement;
    ptrPosition->y += yDisplacement;
}
