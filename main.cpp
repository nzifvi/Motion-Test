#include <iostream>
#include <raylib.h>
#include "Headers/Particle.h"
#include <map>
#include <memory>

#define HORIZONTAL_ACCELERATION 2
#define VERTICAL_ACCELERATION 4


int main() {
    constexpr int   screenWidth  = 1800;
    constexpr int   screenHeight = 1200;
    constexpr int   fps          = 60;
    constexpr float circleRadius = 10.0f;
    const std::string PARTICLE   = "particle0";

    InitWindow(screenWidth, screenHeight, "ahhhhhh");
    std::map<std::string, Particle> particles;

    particles.insert(
        {PARTICLE,
        Particle(
        static_cast<float>(screenWidth)/2,
        static_cast<float>(screenHeight)/2,
        5, 0, 150)}
    );

    for (int i = 1; i < 5; i++) {
        particles.insert(
            {"particle" + std::to_string(i),
            Particle(
                particles.at(PARTICLE).getAcceleration(),
                particles.at(PARTICLE).getXVelocity(),
                particles.at(PARTICLE).getYVelocity(),
                particles.at(PARTICLE).getXPos(),
                particles.at(PARTICLE).getYPos() + static_cast<float>(30 * i),
                particles.at(PARTICLE).getMass(),
                particles.at(PARTICLE).getKE(),
                particles.at(PARTICLE).getMaxVelocity())}
        );
    }

    SetTargetFPS(fps);
    while (!WindowShouldClose()) {
        std::shared_ptr<Vector2> ptrSharedAcceleration = particles.at(PARTICLE).getAcceleration();

        if (IsKeyDown(KEY_SPACE)) {ptrSharedAcceleration->y = -VERTICAL_ACCELERATION;}
        if (IsKeyDown(KEY_A)) {ptrSharedAcceleration->x = -HORIZONTAL_ACCELERATION;}
        if (IsKeyDown(KEY_D)) {ptrSharedAcceleration->x = HORIZONTAL_ACCELERATION;}
        if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
            ptrSharedAcceleration->x = 0;
        }
        if (!IsKeyDown(KEY_SPACE)) {
            ptrSharedAcceleration->y = 0;
        }

        for (int i = 0; i < particles.size(); i++) {
            particles.at("particle" + std::to_string(i)).update();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < particles.size(); i++) {
            DrawCircle(
                static_cast<int>(particles.at("particle" + std::to_string(i)).getXPos()),
                static_cast<int>(particles.at("particle" + std::to_string(i)).getYPos()),
                circleRadius,
                RED
            );
        }

        std::string xVel = "x velocity: " + std::to_string(static_cast<int>(particles.at(PARTICLE).getXVelocity())) + " pixels/60fps";
        std::string yVel = "y velocity: " + std::to_string(static_cast<int>(particles.at(PARTICLE).getYVelocity())) + " pixels/60fps";
        std::string currentKE = "KE: " + std::to_string(static_cast<double>(particles.at(PARTICLE).getKE())/1000) + "kJ";
        DrawText(xVel.c_str(), 10, 10, 42, BLACK);
        DrawText(yVel.c_str(), 10, 42, 42, BLACK);
        DrawText(currentKE.c_str(), 10, 84, 42, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}