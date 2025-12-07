#include <iostream>
#include <raylib.h>
#include "raymath.h"
#include "Headers/KinematicHandler.h"
#include <map>
#include <memory>
#include "Headers/Entity.h"
#include <thread>
#include "Headers/EntityLoader.h"
#include <random>
#include <vector>
#include <ctime>
#include <mutex>

#define HORIZONTAL_ACCELERATION 2
#define VERTICAL_ACCELERATION 4
#define MAX_VELOCITY 50
#define SCREEN_HEIGHT 1080
#define SCREEN_WIDTH 1920
#define TARGET_FPS 60
#define PLAYER_ID "player"
#define ENEMY_TYPE_AMOUNT 0

struct EntityPair {
    EntityTypes type;
    Entity entity;
    EntityPair(const EntityTypes type, Entity entity) : type(type), entity(entity) {}
};


void movementUpdaterWorkerFunction(bool* ptrIsGameRunningFlag, std::map<std::string, Entity>* ptrEntities, std::vector<EntityPair>* ptrEnemies);
void enemySpawnerWorkerFunction(bool* ptrIsGameRunningFlag, std::vector<EntityPair>* ptrEnemies, EntityLoader* ptrEntityLoader);
void levelLoaderWorkerFunction();

// GLOBAL MUTEXES
std::mutex queueMutex;
std::mutex entitiesMutex;
std::mutex enemiesMutex;

int main() {
    // ININITIALISATION STAGE
    bool isGameRunningFlag = true;

    std::map<std::string, Entity>* ptrEntities = new std::map<std::string, Entity>;
    EntityLoader* ptrEntityLoader = new EntityLoader();
    std::vector<EntityPair>* ptrEnemies = new std::vector<EntityPair>;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ahhhhhh");
    InitAudioDevice();
    Music background_music = LoadMusicStream("C:/Users/benja/CLionProjects/untitled9/Audio/fireball.mp3");
    PlayMusicStream(background_music);

    ptrEntityLoader->enqueueRequest(EntityTypes::PlatformPlank, SCREEN_WIDTH / 4, (3*SCREEN_HEIGHT)/4);
    ptrEntityLoader->enqueueRequest(EntityTypes::Cat, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    ptrEntities->insert({"obj1", ptrEntityLoader->processQueue()});
    ptrEntities->insert({PLAYER_ID, ptrEntityLoader->processQueue()});


    
    std::thread movementUpdaterWorker(movementUpdaterWorkerFunction, &isGameRunningFlag, ptrEntities, ptrEnemies);
    std::thread enemySpawnerWorker(enemySpawnerWorkerFunction, &isGameRunningFlag, ptrEnemies, ptrEntityLoader);
    movementUpdaterWorker.detach();
    enemySpawnerWorker.detach();

    Texture2D BackgroundTexture = LoadTexture("C:/Users/benja/CLionProjects/untitled9/Images/Background.png");

    SetTargetFPS(TARGET_FPS);

    // GAME LOOP
    while (!WindowShouldClose()) {
        UpdateMusicStream(background_music);
        {
            //std::lock_guard<std::mutex> lock(entitiesMutex);
            std::shared_ptr<Vector2> ptrSharedAcceleration = ptrEntities->at(PLAYER_ID).getKinematicHandler().getAcceleration();

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
        }

        {
            //std::lock_guard<std::mutex> lock(queueMutex);
            const int loadBatchAmount = ptrEntityLoader->getQueueSize();
            for (int i = 0; i < loadBatchAmount; i++) {
                ptrEnemies->push_back(EntityPair(ptrEntityLoader->getFrontType(), ptrEntityLoader->processQueue()));
            }
        }


        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureRec(BackgroundTexture,{0,0,SCREEN_WIDTH,SCREEN_HEIGHT}, {0,0}, WHITE);
        {
            //std::lock_guard<std::mutex> lock1(entitiesMutex);
            for (auto& [key, entity] : *ptrEntities) {
                DrawTextureRec(
                entity.getTexture(),
                entity.getSheetSourceRect()
                /*{0,0, entity.getErect().width, entity.getErect().height}*/,
                *entity.getKinematicHandler().getPosition(),
                WHITE
                );
            }
        }
        {
            //std::lock_guard<std::mutex> lock2(enemiesMutex);
            for (int i = 0; i < ptrEnemies->size(); i++) {
                DrawTextureRec(
                    ptrEnemies->at(i).entity.getTexture(),
                    ptrEnemies->at(i).entity.getSheetSourceRect(),
                    *ptrEnemies->at(i).entity.getKinematicHandler().getPosition(),
                    WHITE
                );
            }
        }
        EndDrawing();
    }

    isGameRunningFlag = false;
    delete ptrEntities;
    delete ptrEntityLoader;
    delete ptrEnemies;
    UnloadMusicStream(background_music);

    CloseWindow();

    return 0;
}

void movementUpdaterWorkerFunction(bool* ptrIsGameRunningFlag, std::map<std::string, Entity>* ptrEntities, std::vector<EntityPair>* ptrEnemies) {
    while (*ptrIsGameRunningFlag) {
        {
            //std::lock_guard<std::mutex> lock(entitiesMutex);
            for (auto& [key, entity] : *ptrEntities) {
                const float y = entity.getKinematicHandler().getYPos();

                if (y < 0 || y + entity.getErect().height > SCREEN_HEIGHT) { // TESTED
                    ptrEntities->at(PLAYER_ID).getKinematicHandler().deflect(Vector2{1, 0});
                }
                if (key != PLAYER_ID && CheckCollisionRecs(ptrEntities->at(PLAYER_ID).getErect(), entity.getErect()) && entity.getIsCollisionEnabled()) { // UNTESTED
                    Vector2 collision = buildCollisionVector(ptrEntities->at(PLAYER_ID).getErect(), entity.getErect());
                    ptrEntities->at(PLAYER_ID).getKinematicHandler().deflect(collision);
                }
                entity.update();
            }
            for (int i = 0; i < ptrEnemies->size(); i++) {
                if (ptrEnemies->at(i).type == EntityTypes::Fireball) {
                    if (CheckCollisionRecs(ptrEntities->at(PLAYER_ID).getErect(), ptrEnemies->at(i).entity.getErect())) {

                    }else {
                        if (ptrEnemies->at(i).type == EntityTypes::Fireball) {
                            ptrEnemies->at(i).entity.getKinematicHandler().setXAcceleration(-1);
                        }
                    }
                }
                ptrEnemies->at(i).entity.update();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // REPLACE WITH PERFECT SYNC USING MUTEX AND LOCKS RATHER THAN A FIXED RATE WHICH CAUSES UPDATE DELAY
    }
}

void enemySpawnerWorkerFunction(bool *ptrIsGameRunningFlag, std::vector<EntityPair>* ptrEnemies, EntityLoader* ptrEntityLoader) {
    time_t timestamp = time(&timestamp);
    struct tm lastTime = *localtime(&timestamp);
    constexpr int delay = 1;

    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> screenIntervalDistribution(0, SCREEN_HEIGHT);
    std::uniform_int_distribution<> spawnEnemeyTypeDistribution(0, ENEMY_TYPE_AMOUNT);

    while (ptrIsGameRunningFlag) {
        time_t timestamp = time(&timestamp);
        struct tm newTime = *localtime(&timestamp);
        constexpr int delay = 1;
        {
            //std::lock_guard<std::mutex> lock(enemiesMutex);
            for (int i = 0; i < ptrEnemies->size(); i++) {
                if (ptrEnemies->at(i).entity.getKinematicHandler().getXPos() + ptrEnemies->at(i).entity.getErect().width < 0) {
                    ptrEnemies->erase(ptrEnemies->begin() + i);
                    std::cout << "enemy deleted\n";
                    i--;
                }
            }
            if (newTime.tm_sec -  lastTime.tm_sec > delay) {
                std::cout << "generated new enemy\n";
                lastTime = newTime;
                {
                    if (ptrEntityLoader->getQueueSize() < 25) {
                        //std::lock_guard<std::mutex> queueLock(queueMutex);
                        const int chosenEnemyTypeToSpawn = spawnEnemeyTypeDistribution(gen);
                        switch (chosenEnemyTypeToSpawn) {
                            case 0: // FIREBALL
                                ptrEntityLoader->enqueueRequest(EntityTypes::Fireball, SCREEN_WIDTH - 10, screenIntervalDistribution(gen));
                                break;
                        }
                    }
                }

            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // REPLACE WITH PERFECT SYNC USING MUTEX AND LOCKS RATHER THAN A FIXED RATE WHICH CAUSES UPDATE DELAY
    }
}
