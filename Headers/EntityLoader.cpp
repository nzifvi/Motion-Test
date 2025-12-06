//
// Created by benja on 01.12.2025.
//

#include "EntityLoader.h"
#include <filesystem>
#include <iostream>
#include <stdexcept>

EntityLoader::EntityLoader() {

}

void EntityLoader::enqueueRequest(std::string filePath) {
    loadRequests.push(LoadRequest(filePath));
}

Entity EntityLoader::processQueue() {
    if (!loadRequests.empty()) {
        LoadRequest currentRequest = loadRequests.front();
        loadRequests.pop();
        Texture2D* ptrT = new Texture2D;
        //ptrT = &LoadTexture(currentRequest.filePath.c_str());
        //Entity temp(ptrT);
    }
}
