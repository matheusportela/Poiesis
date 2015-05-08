// @file   GameObjectContainer.h
// @author Matheus Vieira Portela
// @date   07/05/2015
//
// @brief Container for GameObject instances with access by key.

#include "GameObjectContainer.h"

void GameObjectContainer::Add(std::string key,
    std::shared_ptr<GameObject> object)
{
    if (HasKey(key))
        AddExistingKey(key, object);
    else
        AddNewKey(key, object);
}

void GameObjectContainer::AddExistingKey(std::string key,
    std::shared_ptr<GameObject> object)
{
    container[key].push_back(object);
}

void GameObjectContainer::AddNewKey(std::string key,
    std::shared_ptr<GameObject> object)
{
    std::vector<std::shared_ptr<GameObject>> objects = {object};
    container[key] = objects;
}

std::shared_ptr<GameObject> GameObjectContainer::GetObject(std::string key)
{
    if (HasKey(key))
    {
        return container[key][0];
    }
    else
    {
        LOG_E("[GameObjectContainer] No GameObject with key \"" << key
            << "\"");
        exit(1);
    }
}

std::vector<std::shared_ptr<GameObject>> GameObjectContainer::GetObjects(
    std::string key)
{
    if (HasKey(key))
    {
        return container[key];
    }
    else
    {
        LOG_E("[GameObjectContainer] No GameObject with key \"" << key
            << "\"");
        exit(1);
    }
}

std::vector<std::shared_ptr<GameObject>> GameObjectContainer::GetAllObjects()
{
    std::vector<std::shared_ptr<GameObject>> objects;
    std::shared_ptr<GameObject> object;

    for (auto keyAndObject : GetKeysAndObjects())
    {
        object = keyAndObject.second;
        objects.push_back(object);
    }

    return objects;
}

std::vector<std::pair<std::string, std::shared_ptr<GameObject>>>
    GameObjectContainer::GetKeysAndObjects()
{
    std::vector<std::pair<std::string, std::shared_ptr<GameObject>>> pairs;
    std::string key;

    for (std::pair<std::string, std::vector<std::shared_ptr<GameObject>>> pair
        : container)
    {
        key = pair.first;

        for (std::shared_ptr<GameObject> object : pair.second)
        {
            pairs.push_back(std::make_pair(key, object));
        }
    }

    return pairs;
}

void GameObjectContainer::DeleteObject(std::string key,
    std::shared_ptr<GameObject> object)
{
    if (HasKey(key))
    {
        std::vector<std::shared_ptr<GameObject>> objects = GetObjects(key);
        for (unsigned int i = 0; i < objects.size(); ++i)
        {
            if (objects[i] == object)
            {
                objects.erase(objects.begin() + i);
                --i; // Decrease index since objects is one size smaller
            }
        }

        if (objects.size() > 0)
            container[key] = objects;
        else
            container.erase(key);
    }
    else
    {
        LOG_E("[GameObjectContainer] No GameObject with key \"" << key
            << "\"");
        exit(1);
    }
}

void GameObjectContainer::DeleteObjects(std::string key)
{
    if (HasKey(key))
    {
        container.erase(key);
    }
    else
    {
        LOG_E("[GameObjectContainer] No GameObject with key \"" << key
            << "\"");
        exit(1);
    }
}

bool GameObjectContainer::HasKey(std::string key)
{
    return (container.find(key) != container.end());
}