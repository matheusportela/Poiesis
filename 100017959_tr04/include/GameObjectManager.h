// @file   GameObjectManager.h
// @author Matheus Vieira Portela
// @date   05/05/2015
//
// @brief Manager for objects life cycle
//
// Game object manager proves methods for managing objects update and rendering.

#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "GameObject.h"
#include "GameObjectContainer.h"

class GameObjectManager
{
  public:
    static std::string DEFAULT_TAG;

    // Gets game object manager as in the singleton pattern.
    static GameObjectManager& GetInstance();

    // Gets all GameObject references in vector form.
    std::vector<std::shared_ptr<GameObject>> GetObjects();

    // Get a GameObject reference with it's key.
    std::shared_ptr<GameObject> GetObject(std::string key);

    // Adds a new game object to be managed.
    void Add(std::shared_ptr<GameObject> object, std::string key);

    // Updates game objects.
    void Update(float dt);

    // Renders game objects.
    void Render();

  private:
    // Singleton pattern using the approach suggested at
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    GameObjectManager() {};
    GameObjectManager(const GameObjectManager&) = delete;
    void operator=(const GameObjectManager&) = delete;

    // Updates all registered game objects.
    void UpdateObjects(float dt);

    // Delete objects that are marked as dead.
    void DeleteDeadObjects();

    // Container for objects.
    GameObjectContainer container;
};

#endif // GAME_OBJECT_MANAGER_H_