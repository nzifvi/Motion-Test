//
// Created by benja on 01.12.2025.
//

#include "EntityLoader.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "raylib.h"

// CONSTRUCTOR(S) AND DESTRUCTOR(S):

EntityLoader::EntityLoader() {

}

// PRIVATE NON-ENCAPSULATION FUNCTION MEMBER(S):

// PUBLIC NON-ENCAPSULATION FUNCTION MEMBER(S):
void EntityLoader::enqueueRequest(EntityTypes typeToLoad, const int initialXOrdinate, const int initialYOrdinate) {
    loadRequests.push(LoadRequest(typeToLoad, initialXOrdinate, initialYOrdinate));
}

     Entity EntityLoader::processQueue() {
    if (!loadRequests.empty()) {
        LoadRequest currentRequest = loadRequests.front();
        loadRequests.pop();

        if (std::ifstream ctrlFile(currentRequest.controlFilepath); ctrlFile.is_open()) {
            std::string line;
            bool isAnimated;
            bool hasCollision;
            int frameCount;
            int rectWidth;
            int rectHeight;

            int linesRead = 0;
            while (getline(ctrlFile, line)) {
                if (linesRead == 0) {
                    if (line == "1") {
                        isAnimated = true;
                    }else {
                        isAnimated = false;
                    }
                }else if (linesRead == 1) {
                    if (line == "1") {
                        hasCollision = true;
                    }else {
                        hasCollision = false;
                    }
                }else if (linesRead == 2) {
                    frameCount = std::stoi(line);
                }else if (linesRead == 3) {
                    rectWidth = std::stoi(line);
                }else if (linesRead == 4) {
                    rectHeight = std::stoi(line);
                }else {
                    throw new std::invalid_argument("File " + currentRequest.controlFilepath + " has more lines than expected");
                }
                linesRead++;
            }
            ctrlFile.close();
                return Entity(
                    currentRequest.initialXOrdinate,
                    currentRequest.initialYOrdinate,
                    LoadTexture(currentRequest.textureFilepath.c_str()),
                    rectWidth,
                    rectHeight,
                    hasCollision,
                    frameCount,
                    isAnimated
                    );
        }else {
            throw new std::runtime_error("RUNTIME ERROR: " + currentRequest.controlFilepath + "\n");
        }

        Texture2D loadedTexture = LoadTexture(currentRequest.textureFilepath.c_str());
    }
}
