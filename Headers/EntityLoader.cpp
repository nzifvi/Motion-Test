//
// Created by benja on 01.12.2025.
//

#include "EntityLoader.h"
#include <filesystem>
#include <iostream>
#include <stdexcept>

EntityLoader::EntityLoader(const std::string& directoryPath, const std::vector<FileDetails>& fileDetails):
directoryPath(directoryPath), fileDetails(fileDetails) {
    if (fileDetails.empty()) {
        throw new std::runtime_error("ERROR: attempted to load 0 files");
    }
    if (directoryPath == "") {
        throw new std::runtime_error("ERROR: attempted to load files from an undeclared directory");
    }
}

std::vector<Entity> EntityLoader::loadEntities() {
    for (int i = 0; i < fileDetails.size(); i++) {
        try {
            std::vector<Entity> entitiesVector;
            const char* path = (directoryPath + fileDetails[i].fileName + "." + fileDetails[i].fileType).c_str();
            entitiesVector.push_back(Entity(LoadTexture(path)));
        }catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
}
