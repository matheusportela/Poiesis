// @file   GameObjectContainer.h
// @author Matheus Vieira Portela
// @date   07/05/2015
//
// @brief Container for GameObject instances with access by key.
//
// Game object container stores GameObject instances and allow access to them
// by key value.

#ifndef GAME_OBJECT_CONTAINER_H_
#define GAME_OBJECT_CONTAINER_H_

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

#include "GameObject.h"

class GameObjectContainer
{
  public:
    // Adds GameObject instance with an associated key. It can store
    // multiple objects with the same key.
    void Add(std::string key, std::shared_ptr<GameObject> object);

    // Gets the first GameObject instance with the associated key.
    std::shared_ptr<GameObject> GetObject(std::string key);

    // Gets vector with all GameObject instances associated with the given key.
    std::vector<std::shared_ptr<GameObject>> GetObjects(std::string key);

    // Gets vector with all GameObject instances.
    std::vector<std::shared_ptr<GameObject>> GetAllObjects();

    // Gets vector with all GameObject instances contained in the instance.
    std::vector<std::pair<std::string, std::shared_ptr<GameObject>>>
        GetKeysAndObjects();

    // Deletes one object given it's key and pointer.
    void DeleteObject(std::string key, std::shared_ptr<GameObject> object);

    // Deletes all GameObject instances with the associated key.
    void DeleteObjects(std::string key);

  private:
    // Checks whether the given key is already stored in container.
    bool HasKey(std::string key);

    // Adds an object with a not-previously seen key. 
    void AddExistingKey(std::string key, std::shared_ptr<GameObject> object);

    // Adds an object with a key that already exists.
    void AddNewKey(std::string key, std::shared_ptr<GameObject> object);

    // Container for GameObject instances.
    std::unordered_map<std::string,
        std::vector<std::shared_ptr<GameObject>>> container;
};

#endif // GAME_OBJECT_CONTAINER_H_