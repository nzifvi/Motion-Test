//
// Created by benja on 01.12.2025.
//

#ifndef ENTITYLOADER_H
#define ENTITYLOADER_H


#include "Entity.h"
#include <queue>
#include <fstream>

#define BACKGROUND_CTRL_FILEPATH "C:/Users/benja/CLionProjects/untitled9/EntityControlFiles/BackgroundControl.txt"
#define BACKGROUND_FILEPATH "C:/Users/benja/CLionProjects/untitled9/Images/Background.png"

#define SOLDIER_IDLE_CTRL_FILEPATH "C:/Users/benja/CLionProjects/untitled9/EntityControlFiles/SoldierIdleControl.txt"
#define SOLDIER_IDLE_FILEPATH "C:/Users/benja/CLionProjects/untitled9/Images/SoldierIdle.png"

#define CAT_CTRL_FILEPATH "C:/Users/benja/CLionProjects/untitled9/EntityControlFiles/CatControl.txt"
#define CAT_FILEPATH "C:/Users/benja/CLionProjects/untitled9/Images/Cat.png"

#define WALL_COBBLE_CTRL_FILEPATH "C:/Users/benja/CLionProjects/untitled9/EntityControlFiles/WallCobbleControl.txt"
#define WALL_COBBLE_FILEPATH "C:/Users/benja/CLionProjects/untitled9/Images/WallCobble.png"

#define PLATFORM_PLANK_CTRL_FILEPATH "C:/Users/benja/CLionProjects/untitled9/EntityControlFiles/PlatformPlankControl.txt"
#define PLATFORM_PLANK_FILEPATH "C:/Users/benja/CLionProjects/untitled9/Images/PlatformPlank.png"

#define DAVID_CTRL_FILEPATH "C:/Users/benja/CLionProjects/untitled9/EntityControlFiles/David.txt"
#define DAVID_FILEPATH

#define FIREBALL_CTRL_FILEPATH "C:/Users/benja/CLionProjects/untitled9/EntityControlFiles/FireballControl.txt"
#define FIREBALL_FILEPATH "C:/Users/benja/CLionProjects/untitled9/Images/Fireball.png"

enum EntityTypes {
    Background,
    SoldierIdle,
    Cat,
    WallCobble,
    PlatformPlank,
    David,
    Fireball
};

struct LoadRequest {
    std::string textureFilepath;
    std::string controlFilepath;
    EntityTypes typeToLoad;
    const int initialXOrdinate;
    const int initialYOrdinate;
    LoadRequest(const EntityTypes typeToLoad, const int initialXOrdinate, const int initialYOrdinate): typeToLoad(typeToLoad), initialXOrdinate(initialXOrdinate), initialYOrdinate(initialYOrdinate) {
        switch (typeToLoad) {
            case Background:
                textureFilepath = BACKGROUND_FILEPATH;
                controlFilepath = BACKGROUND_CTRL_FILEPATH;
                break;
            case SoldierIdle:
                textureFilepath = SOLDIER_IDLE_FILEPATH;
                controlFilepath = SOLDIER_IDLE_CTRL_FILEPATH;
                break;
            case Cat:
                textureFilepath = CAT_FILEPATH;
                controlFilepath = CAT_CTRL_FILEPATH;
                break;
            case WallCobble:
                textureFilepath = WALL_COBBLE_FILEPATH;
                controlFilepath = WALL_COBBLE_CTRL_FILEPATH;
                break;
            case PlatformPlank:
                textureFilepath = PLATFORM_PLANK_FILEPATH;
                controlFilepath = PLATFORM_PLANK_CTRL_FILEPATH;
                break;
            case Fireball:
                textureFilepath = FIREBALL_FILEPATH;
                controlFilepath = FIREBALL_CTRL_FILEPATH;
                break;
            default:
                break;
        }
    }
};


class EntityLoader {
private:
    std::queue<LoadRequest> loadRequests;

    // NON-ENCAPSULATION FUNCTION MEMBER(S):
public:
    // CONSTRUCTOR(S) AND DESTRUCTOR(S):
    EntityLoader();

    // PUBLIC NON-ENCAPSULATION FUNCTION MEMBER(S):
    void enqueueRequest(EntityTypes typeToLoad, const int initialXOrdinate, const int initialYOrdinate);
    Entity processQueue();


    // ENCAPSULATION FUNCTION MEMBER(S):
    int getQueueSize(){return loadRequests.size();}
    EntityTypes getFrontType(){return loadRequests.front().typeToLoad;}
};



#endif //ENTITYLOADER_H
