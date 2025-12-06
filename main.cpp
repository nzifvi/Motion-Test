#include <iostream>
#include <raylib.h>
#include "Headers/KinematicHandler.h"
#include <map>
#include <memory>
#include "Headers/Entity.h"
#include <thread>

#define HORIZONTAL_ACCELERATION 2
#define VERTICAL_ACCELERATION 4
#define MAX_VELOCITY 50
#define SCREEN_HEIGHT 1200
#define SCREEN_WIDTH 1800
#define TARGET_FPS 60


/*
 * FUTURE IDEAS:
 * 1) Handle entity loading by a daemon thread to allow for progressive inserting and removing from ptrEntities.
 * 2) Handle progressive level construction by a daemon thread.
 * 3) Handle enemies targeting player by a daemon thread.
 */

void collisionWorkerFunction(bool* ptrIsGameRunningFlag, std::map<std::string, Entity>* ptrEntities);

int main() {
    bool            isGameRunningFlag = true;

    std::map<std::string, Entity>* ptrEntities = new std::map<std::string, Entity>;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ahhhhhh");

    ptrEntities->insert(
        {"p0",
        Entity(
            SCREEN_WIDTH/2,
            SCREEN_HEIGHT/2,
            5, MAX_VELOCITY,
            LoadTexture("C:/Users/benja/CLionProjects/untitled9/Images/test.png"),
            200,
            100,
            true
            )
        }
    );

    ptrEntities->insert(
    {"p1",
    Entity(
        (3*SCREEN_WIDTH)/4,
        (SCREEN_HEIGHT)/2,
        5, MAX_VELOCITY,
        LoadTexture("C:/Users/benja/CLionProjects/untitled9/Images/test.png"),
        200,
        100,
        false
        )
    }
);

    std::thread collisionWorker(collisionWorkerFunction, &isGameRunningFlag, ptrEntities);
    collisionWorker.detach();


    SetTargetFPS(TARGET_FPS);
    while (!WindowShouldClose()) {
        std::shared_ptr<Vector2> ptrSharedAcceleration = ptrEntities->at("p0").getKinematicHandler().getAcceleration();

        if (IsKeyDown(KEY_W)) {ptrSharedAcceleration->y = -VERTICAL_ACCELERATION;}
        if (IsKeyDown(KEY_S)) {ptrSharedAcceleration->y = VERTICAL_ACCELERATION;}
        if (IsKeyDown(KEY_A)) {ptrSharedAcceleration->x = -HORIZONTAL_ACCELERATION;}
        if (IsKeyDown(KEY_D)) {ptrSharedAcceleration->x = HORIZONTAL_ACCELERATION;}
        if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
            ptrSharedAcceleration->x = 0;
        }
        if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) {
            ptrSharedAcceleration->y = 0;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < ptrEntities->size(); i++) {
            DrawTextureRec(
                ptrEntities->at("p" + std::to_string(i)).getTexture(),
                {0, 0, ptrEntities->at("p" + std::to_string(i)).getRect().width, ptrEntities->at("p" + std::to_string(i)).getRect().height},
                *ptrEntities->at("p" + std::to_string(i)).getKinematicHandler().getPosition(),
                BLACK
            );
        }

        //std::string xVel = "x velocity: " + std::to_string(static_cast<int>(particles.at(PARTICLE).getXVelocity())) + " pixels/60fps";
        //std::string yVel = "y velocity: " + std::to_string(static_cast<int>(particles.at(PARTICLE).getYVelocity())) + " pixels/60fps";
        //std::string currentKE = "KE: " + std::to_string(static_cast<double>(particles.at(PARTICLE).getKE())/1000) + "kJ";
        //DrawText(xVel.c_str(), 10, 10, 42, BLACK);
        //DrawText(yVel.c_str(), 10, 42, 42, BLACK);
        //DrawText(currentKE.c_str(), 10, 84, 42, BLACK);
        EndDrawing();
    }

    isGameRunningFlag = false;
    delete ptrEntities;

    CloseWindow();

    return 0;
}

void collisionWorkerFunction(bool* ptrIsGameRunningFlag, std::map<std::string, Entity>* ptrEntities) {
    while (*ptrIsGameRunningFlag) {
        for (auto& [key, entity] : *ptrEntities) {
            const float y = entity.getKinematicHandler().getYPos();

            if (y < 0 || y + entity.getRect().height > SCREEN_HEIGHT) { // TESTED
                ptrEntities->at("p0").getKinematicHandler().deflect(Vector2{1, 0});
            }
            if (key != "p0" && boundCheck(ptrEntities->at("p0"), entity) && entity.getIsCollisionEnabled()) { // UNTESTED
                Vector2 collision = buildCollisionVector(ptrEntities->at("p0").getRect(), entity.getRect());
                ptrEntities->at("p0").getKinematicHandler().deflect(collision);
            }

            entity.update();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // REPLACE WITH PERFECT SYNC USING MUTEX AND LOCKS RATHER THAN A FIXED RATE WHICH CAUSES UPDATE DELAY
    }
}