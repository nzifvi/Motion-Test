//
// Created by benja on 06.12.2025.
//

#include "Level.h"

// CONSTRUCTOR(S) AND DESTRUCTOR(S):
Level::Level():
ptrLevelComponents(new std::map<std::string, LevelPart>),
ptrLevelEnemies(new std::map<std::string, Entity>) {

}

Level::~Level() {
    if (ptrLevelComponents != nullptr) {
        delete ptrLevelComponents;
    }
    if (ptrLevelEnemies != nullptr) {
        delete ptrLevelEnemies;
    }
}

// NON-ENCAPSULATION FUNCTION MEMBER(S):

// ENCAPSULATION FUNCTION MEMBER(S):
void Level::addEntityToComponentsMap(const std::string name, const Entity entity, ComponentType type) const {
    if (ptrLevelComponents->find(name) == ptrLevelComponents->end()) {
        ptrLevelComponents->insert(std::pair<std::string, LevelPart>(name, LevelPart(entity, type)));
    }else {
        throw new std::runtime_error("EXCEPTION: Attempted to insert an entity with a key which already exists into level components map");
    }
}

void Level::addEntityToEnemiesMap(const std::string key, const Entity entity) const {
    if (ptrLevelEnemies->find(key) == ptrLevelEnemies->end()) {
        ptrLevelEnemies->insert(std::pair<std::string, Entity>(key, entity));
    }else {
        throw new std::runtime_error("EXCEPTION: Attempted to insert an entity with a key which already exists into level enemies map");
    }
}

void Level::removeEntityFromComponentsMap(const std::string& key) {
    if (ptrLevelComponents->find(key) != ptrLevelComponents->end()) {
        ptrLevelComponents->erase(key.c_str());
    }else {
        throw new std::runtime_error("EXCEPTION: Attempted to remove an entity with a key which does not exist from level components map");
    }
}

void Level::removeEntityFromEnemiesMap(const std::string& key) {
    if (ptrLevelEnemies->find(key) != ptrLevelEnemies->end()) {
        ptrLevelComponents->erase(key);
    }else {
        throw new std::runtime_error("EXCEPTION: Attempted to remove an entity with a key which does not exist in level enemies map");
    }
}

LevelPart Level::getEntityFromComponentsMap(const std::string& key) {
    if (ptrLevelComponents->find(key) != ptrLevelComponents->end()) {
        auto entityToReturn = ptrLevelComponents->at(key);
        ptrLevelComponents->erase(key);
        return entityToReturn;
    }else {
        throw new std::runtime_error("EXCEPTION: Attempted to get an entity with a key which does not exist from level components map");
    }
}

Entity Level::getEntityFromEnemiesMap(const std::string& key) {
    if (ptrLevelEnemies->find(key) != ptrLevelEnemies->end()) {
        auto entityToReturn = ptrLevelEnemies->at(key);
        ptrLevelEnemies->erase(key);
        return entityToReturn;
    }else {
        throw new std::runtime_error("EXCEPTION: Attempted to get an entity with a key which does not exist from level enemies map");
    }
}