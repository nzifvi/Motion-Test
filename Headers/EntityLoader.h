//
// Created by benja on 01.12.2025.
//

#ifndef ENTITYLOADER_H
#define ENTITYLOADER_H

#include "raylib.h"
#include "Particle.h"
#include "Entity.h"
#include <vector>

struct FileDetails {
    std::string fileName;
    std::string fileType;
};

class EntityLoader {
private:
    std::string                          directoryPath;
    std::vector<FileDetails>          fileDetails;

public:
    EntityLoader(const std::string& directoryPath, const std::vector<FileDetails>& fileDetails);

    std::vector<Entity> loadEntities();
};



#endif //ENTITYLOADER_H
