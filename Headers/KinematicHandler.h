//
// Created by benja on 28.11.2025.
//

#ifndef KINEMATIC_HANDLER_H
#define KINEMATIC_HANDLER_H

#include <raylib.h>
#include <memory>
#include <cmath>

class KinematicHandler {
private:
    std::shared_ptr<Vector2> ptrPosition;
    std::shared_ptr<Vector2> ptrVelocity;
    std::shared_ptr<Vector2> ptrAcceleration;

    const float HORIZONTAL_RESISTIVE_FORCE = 1.0f;
    const float VERTICAL_RESISTIVE_FORCE   = 1.0f;
    const int   KE_AMPLIFIER               = 8;

    float maxVelocity;
    float mass;
    float kineticEnergy;

public:
    KinematicHandler(const float mass, const float kineticEnergy, const float maxVelocity);
    KinematicHandler(const float initialXOrdinate, const float initialYOrdinate, const float mass, const float kineticEnergy, const float maxVelocity);
    KinematicHandler(std::shared_ptr<Vector2> acc, const float xVelocity, const float yVelocity, const float initialXOrdinate, const float initialYOrdinate, const float mass, const float kineticEnergy, const float maxVelocity);

    ~KinematicHandler();

    void update();
    void deflect(const Vector2& vec);

    float getMass() const;
    float getMaxVelocity() const;
    float getXPos() const;
    float getYPos() const;
    float getXVelocity() const;
    float getYVelocity() const;
    float getXAcceleration() const;
    float getYAcceleration() const;
    float getKE() const;
    std::shared_ptr<Vector2> getAcceleration() const;
    std::shared_ptr<Vector2> getVelocity() const;
    std::shared_ptr<Vector2> getPosition() const;

    void setXAcceleration(const float acceleration) const;
    void setYAcceleration(const float acceleration) const;
    void updateXPos() const;
    void updateXPos(const float acceleration) const;
    void updateYPos() const;
    void updateYPos(const float acceleration) const;
    void updateKE();
    void forceDisplacement(const float xDisplacement, const float yDisplacement) const;
};

#endif //PARTICLE_H
