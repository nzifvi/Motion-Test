//
// Created by benja on 01.12.2025.
//

#ifndef ENTITYLOADER_H
#define ENTITYLOADER_H

#include "raylib.h"
#include "KinematicHandler.h"
#include "Entity.h"
#include <queue>

struct LoadRequest {
    std::string filePath;
    LoadRequest(const std::string& filePath) {
        this->filePath = filePath;
    }
};

class EntityLoader {
private:
    std::queue<LoadRequest> loadRequests;

public:
    EntityLoader();

    void enqueueRequest(std::string filePath);
    Entity processQueue();
};



#endif //ENTITYLOADER_H
