#include "bandit/core/entity/EntityManager.h"

std::shared_ptr<Entity> EntityManager::CreateEntity()
{
    std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    entities.push_back(entity);
    return entity;
}

void EntityManager::DeleteEntity(std::shared_ptr<Entity> entity)
{
    DeleteEntityComponents(entity);
    DeleteEntityFromContainer(entity);
}

void EntityManager::DeleteEntityComponents(std::shared_ptr<Entity> entity)
{
    componentsByEntity[entity->GetId()].clear();
    componentsByEntity.erase(entity->GetId());
}

void EntityManager::DeleteEntityFromContainer(std::shared_ptr<Entity> entity)
{
    for (unsigned int i = 0; i < entities.size(); ++i)
    {
        if (entity->GetId() == entities[i]->GetId())
        {
            entities.erase(entities.begin() + i);
            --i; // Decrease index since entities is one size smaller
        }
    }
}

void EntityManager::AddComponent(std::shared_ptr<Component> component,
    std::shared_ptr<Entity> entity)
{
    if (HasEntity(entity))
    {
        componentsByEntity[entity->GetId()].push_back(component);
    }
    else
    {
         std::vector<std::shared_ptr<Component>> componentsArray = { component };
        componentsByEntity[entity->GetId()] = componentsArray;
    }
}

bool EntityManager::HasEntity(std::shared_ptr<Entity> entity)
{
    return (componentsByEntity.find(entity->GetId()) != componentsByEntity.end());
}

std::vector<std::shared_ptr<Component>> EntityManager::GetComponentsOfClass(
    std::shared_ptr<Entity> entity, std::string componentClass)
{
    std::vector<std::shared_ptr<Component>> componentsArray;

    for (auto component : componentsByEntity[entity->GetId()])
    {
        if (component->GetComponentClass() == componentClass)
            componentsArray.push_back(component);
    }

    return componentsArray;
}

std::vector<std::shared_ptr<Entity>> EntityManager::GetAllEntitiesWithComponentOfClass(
    std::string componentClass)
{
    std::vector<std::shared_ptr<Entity>> entitiesArray;

    for (auto entity : entities)
    {
        for (auto component : componentsByEntity[entity->GetId()])
        {
            if (component->GetComponentClass() == componentClass)
            {
                entitiesArray.push_back(entity);
                break;
            }
        }
    }

    return entitiesArray;
}