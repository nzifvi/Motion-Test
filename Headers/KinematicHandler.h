//
// Created by benja on 28.11.2025.
//

#ifndef KINEMATIC_HANDLER_H
#define KINEMATIC_HANDLER_H

#include <raylib.h>
#include <memory>
#include <cmath>

#define MAX_VELOCITY 50
#define MASS 5

class KinematicHandler {
private:
    std::shared_ptr<Vector2> ptrPosition;
    std::shared_ptr<Vector2> ptrVelocity;
    std::shared_ptr<Vector2> ptrAcceleration;

    float HORIZONTAL_RESISTIVE_FORCE = 1.0f;
    float VERTICAL_RESISTIVE_FORCE   = 1.0f;
    int   KE_AMPLIFIER               = 8;

    float kineticEnergy = 0;

public:
    KinematicHandler();
    KinematicHandler(const float initialXOrdinate, const float initialYOrdinate);
    KinematicHandler(std::shared_ptr<Vector2> acc, const float xVelocity, const float yVelocity, const float initialXOrdinate, const float initialYOrdinate);

    ~KinematicHandler();

    void update();
    void deflect(const Vector2& vec);

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
    void setXVelocity(const float newVelocity) const {ptrVelocity->x = newVelocity;}
    void setYVelocity(const float newVelocity) const {ptrVelocity->y = newVelocity;}
    void updateXPos() const;
    void updateXPos(const float acceleration) const;
    void updateYPos() const;
    void updateYPos(const float acceleration) const;
    void updateKE();
    void forceDisplacement(const float xDisplacement, const float yDisplacement) const;
};

#endif //PARTICLE_H
