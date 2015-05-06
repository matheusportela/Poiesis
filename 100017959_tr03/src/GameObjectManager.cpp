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

GameObjectManager::~GameObjectManager()
{
    objects.clear();
}

int GameObjectManager::GetSize()
{
    return objects.size();
}

std::shared_ptr<GameObject> GameObjectManager::GetObject(int i)
{
    return objects[i];
}

void GameObjectManager::Add(std::shared_ptr<GameObject> object)
{
    objects.push_back(std::move(object));
}

void GameObjectManager::DeleteDeadObjects()
{
    for (unsigned int i = 0; i < objects.size(); ++i)
    {
        if (objects[i]->IsDead())
        {
            objects.erase(objects.begin() + i);

            // Decrease index since objects is one size smaller
            --i;
        }
    }
}

void GameObjectManager::UpdateObjects(float dt)
{
    for (unsigned int i = 0; i < objects.size(); ++i)
        objects[i]->Update(dt);
}

void GameObjectManager::Update(float dt)
{
    DeleteDeadObjects();
    UpdateObjects(dt);
}

void GameObjectManager::Render()
{
    for (unsigned int i = 0; i < objects.size(); ++i)
        objects[i]->Render();
}