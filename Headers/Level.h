//
// Created by benja on 06.12.2025.
//

#ifndef LEVEL_H
#define LEVEL_H

#include "Entity.h"
#include <map>
#include <stdexcept>

enum ComponentType {
    CONNECTOR,
    BETWEEN_CONNECTORS
};

struct LevelPart {
    Entity entity;
    ComponentType type;
    LevelPart(const Entity e, const ComponentType t) : entity(e), type(t) {}
};

class Level {
private:
    std::map<std::string, LevelPart>* ptrLevelComponents = nullptr;
    std::map<std::string, Entity>* ptrLevelEnemies = nullptr;



public:
    // CONSTRUCTOR(S) AND DESTRUCTOR(S):
    Level();
    ~Level();

    // NON-ENCAPSULATION FUNCTION MEMBER(S):

    // ENCAPSULATION FUNCTION MEMBER(S):
    void addEntityToComponentsMap(const std::string key, const Entity entity, const ComponentType type) const;
    void addEntityToEnemiesMap(const std::string key, const Entity entity) const;

    void removeEntityFromComponentsMap(const std::string& key);
    void removeEntityFromEnemiesMap(const std::string& key);

    LevelPart getEntityFromComponentsMap(const std::string& key);
    Entity getEntityFromEnemiesMap(const std::string& key);
};



#endif //LEVEL_H
