// @file   GameObjectManager.h
// @author Matheus Vieira Portela
// @date   05/05/2015
//
// @brief Manager for objects life cycle

#include "GameObjectManager.h"

GameObjectManager& GameObjectManager::GetInstance()
{
    static GameObjectManager instance;
    return instance;
};

std::vector<std::shared_ptr<GameObject>> GameObjectManager::GetObjects()
{
    return container.GetAllObjects();
}

std::shared_ptr<GameObject> GameObjectManager::GetObject(std::string key)
{
    return container.GetObject(key);
}

void GameObjectManager::Add(std::shared_ptr<GameObject> object, std::string key)
{
    LOG_D("[GameObjectManager] Creating object with key \"" << key << "\"");
    container.Add(key, object);
}

void GameObjectManager::DeleteDeadObjects()
{
    std::string key;
    std::shared_ptr<GameObject> object;

    // It is important to execute the death behavior before deleting the object
    // since it might reference other object that is also marked to be deleted.
    for (auto object : container.GetAllObjects())
    {
        if (object->IsDead())
            object->OnDeath();
    }

    for (auto keyAndObject : container.GetKeysAndObjects())
    {
        key = keyAndObject.first;
        object = keyAndObject.second;

        if (object->IsDead())
        {
            LOG_D("[GameObjectManager] Deleting object with key \"" << key
                << "\"");
            container.DeleteObject(key, object);
        }
    }
}

void GameObjectManager::UpdateObjects(float dt)
{
    for (auto object : container.GetAllObjects())
        object->Update(dt);
}

void GameObjectManager::Update(float dt)
{
    DeleteDeadObjects();
    UpdateObjects(dt);
}

void GameObjectManager::Render()
{
    for (auto object : container.GetAllObjects())
        object->Render();
}